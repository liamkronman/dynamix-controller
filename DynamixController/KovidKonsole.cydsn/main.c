/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <math.h>
#include <stdlib.h>
#include "GUI.h"
#include "tft.h"
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "main.h"
#include <FS.h>
#include <string.h>
#include <Global.h>

typedef enum {
	FILTER_LOW_PASS,
	FILTER_HIGH_PASS
} FilterType;

typedef enum {
	TRACK_1,
	TRACK_2
} TrackType;

// Global variables
#define SAMPLE_OFFSET 32768
#define SAMPLE_RATE 11025
volatile uint32_t audioSampleIndex = 0;

#define AUDIO_BUFFER_SIZE 6140
signed short int audioBuffer1[AUDIO_BUFFER_SIZE];
signed short int audioBuffer2[AUDIO_BUFFER_SIZE];
signed short int audioBuffer3[AUDIO_BUFFER_SIZE];
signed short int audioBuffer4[AUDIO_BUFFER_SIZE];
signed short int* currentBuffer1 = audioBuffer1;  // Pointer to the current buffer being played
signed short int* loadingBuffer1 = audioBuffer2;  // Pointer to the buffer being loaded
signed short int* currentBuffer2 = audioBuffer3;  // Pointer to the current buffer being played
signed short int* loadingBuffer2 = audioBuffer4;  // Pointer to the buffer being loaded

#define SECONDS_PER_BAR 4

char file1[16] = "clarity.wav";
char file2[14] = "dieyoung.wav";
volatile uint32 overall_size = 0;
FS_FILE* audioFile1 = NULL;  // Global file pointer for audio data
FS_FILE* audioFile2 = NULL;  // Global file pointer for audio data
volatile size_t currentBufferFill = 0;  // How much valid data is in the current buffer
volatile size_t loadingBufferFill = 0;  // How much valid data is in the loading buffer
volatile int switchBuffers = 0x0;    // Flag to switch buffers
volatile int fileEnd1 = 0x0;
volatile int fileEnd2 = 0x0;

volatile float volumeControlCoef1 = 1;
volatile float volumeControlCoef2 = 0;
char volumeControlString1[128];
char volumeControlString2[128];

#define LSBperGee 16384.0       //from the register map, for the +/- 2 G setting, there are 16384 LSB's per gee

uint8_t topByte;        //we'll use these to hold and process the data from the MPU
uint8_t bottomByte;
uint16_t combinedData;
float geeForce;
char mpuString1[24];

// Audio processing variables
static int previousOutput = 0;
static int previousInput = 0;

#define DISPLAY_WIDTH 320  // Assume display width is 320 pixels
#define DISPLAY_HEIGHT 240 // Assume display height is 240 pixels

volatile int rectangleIndexTrackOne = 0;  // Index to track which rectangle (or second) is being displayed
volatile int rectangleIndexTrackTwo = 0;

volatile int secondsCount = 1;
char timeString[12];

void DisplayAmplitudeBar(signed short int* buffer, size_t bufferSize, TrackType trackType) {
    int samplesPerSecond = SAMPLE_RATE;
    long sumAmplitude = 0;
    int waveformHeight = DISPLAY_HEIGHT * 0.4;
    int waveformWidth = DISPLAY_WIDTH * 0.6;
    
    // Calculate the average amplitude for the current buffer
    size_t i;
    for (i = 0; i < bufferSize; ++i) {
        sumAmplitude += abs(buffer[i]);
    }

    int avgAmplitude = sumAmplitude / bufferSize;

    // Scale the average amplitude to fit the display height
    int barHeight = (avgAmplitude * waveformHeight) / SAMPLE_OFFSET;

    GUI_SetColor(GUI_BLUE);
    // Calculate the width of each bar based on the expected number of buffers to display
    uint16_t numSecs = (overall_size-44) / SAMPLE_RATE / sizeof(uint16);
    int barWidth = SECONDS_PER_BAR * waveformWidth / numSecs;

    // Draw a rectangle for the current buffer
    int widthOffset = (DISPLAY_WIDTH - waveformWidth) * (0.75);
    int xMidpoint;
    int rectangleIndex;
    if (trackType == TRACK_1) {
        GUI_SetColor(GUI_BLUE);
        xMidpoint = 60;
        rectangleIndex = rectangleIndexTrackOne;
        rectangleIndexTrackOne++;
    } else {
        // trackType = TRACK_2
        GUI_SetColor(GUI_GREEN);
        xMidpoint = 180;
        rectangleIndex = rectangleIndexTrackTwo;
        rectangleIndexTrackTwo++;
    }
    GUI_FillRect(xMidpoint-(barHeight/2), rectangleIndex * barWidth + widthOffset, xMidpoint+(barHeight/2), (rectangleIndex+1) * barWidth + widthOffset);
    //char *barHeightBuffer;
    //sprintf(barHeightBuffer, "Bar Height: %u", (uint16)barHeight);
    //GUI_DispStringAt(barHeightBuffer, 10, 220);
    
    // Increment the rectangle index for the next buffer
    rectangleIndex++;
    if (rectangleIndex * barWidth >= DISPLAY_WIDTH) {
        // rectangleIndex = 0;  // Reset if we reach the end of the display
        // GUI_Clear();  // Clear the screen to start over
    }
}


void adjustVolume(uint16_t *sample, float volumeScale) {
	int adjustedSample = (int)(*sample) - SAMPLE_OFFSET;
	adjustedSample = (int)(adjustedSample * volumeScale);

	// Clip to prevent overflow and underflow
	if (adjustedSample > 32767) adjustedSample = 32767;
	if (adjustedSample < -32768) adjustedSample = -32768;

	*sample = (uint16_t)(adjustedSample + SAMPLE_OFFSET);
}

void applyFilter(uint16_t *sample, float rc, float dt, FilterType filterType) {
	float alpha = dt / (rc + dt);
	float currentInput = (float)(*sample) - SAMPLE_OFFSET;
	float currentOutput;

	if (filterType == FILTER_LOW_PASS) {
    	currentOutput = alpha * currentInput + (1 - alpha) * previousOutput;
	} else { // FILTER_HIGH_PASS
    	currentOutput = (1 - alpha) * (previousOutput + currentInput - previousInput);
	}

	previousInput = currentInput;
	previousOutput = currentOutput;

	currentOutput += SAMPLE_OFFSET;
	*sample = (uint16_t)(currentOutput > 65535 ? 65535 : currentOutput < 0 ? 0 : currentOutput);
}

void GUI_Initialize()
{
	SPIM_TFT_Start();
	GUI_Init();                         	// initialize graphics library
	GUI_Clear();
	GUI_SetFont(&GUI_Font8x16);
}

void readWavHeader(FS_FILE* filePtr) {
    unsigned char buffer4[4];
    unsigned char buffer2[2];
    char debugString[128];

    // Read RIFF header
    FS_Read(filePtr, buffer4, 4);  // Read the 'RIFF' descriptor
    sprintf(debugString, "Descriptor: %c%c%c%c", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    GUI_DispStringAt(debugString, 10, 30);

    // Read size of file
    FS_Read(filePtr, buffer4, 4);
    overall_size = buffer4[0] | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24);
    sprintf(debugString, "Overall size: %lu bytes", overall_size);
    GUI_DispStringAt(debugString, 10, 50);

    // Read WAVE string
    FS_Read(filePtr, buffer4, 4);
    sprintf(debugString, "Format: %c%c%c%c", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    GUI_DispStringAt(debugString, 10, 70);

    // Read format chunk marker
    FS_Read(filePtr, buffer4, 4);
    sprintf(debugString, "Fmt marker: %c%c%c%c", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);
    GUI_DispStringAt(debugString, 10, 90);

    // Read length of format data
    FS_Read(filePtr, buffer4, 4);
    uint32 length_of_fmt = buffer4[0] | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24);
    sprintf(debugString, "Length of fmt: %lu", length_of_fmt);
    GUI_DispStringAt(debugString, 10, 110);

    // Read format type
    FS_Read(filePtr, buffer2, 2);
    uint16 format_type = buffer2[0] | (buffer2[1] << 8);
    sprintf(debugString, "Format type: %u", format_type);
    GUI_DispStringAt(debugString, 10, 130);

    // Read channels
    FS_Read(filePtr, buffer2, 2);
    uint16 channels = buffer2[0] | (buffer2[1] << 8);
    sprintf(debugString, "Channels: %u", channels);
    GUI_DispStringAt(debugString, 10, 150);

    // Read sample rate
    FS_Read(filePtr, buffer4, 4);
    uint32 sample_rate = buffer4[0] | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24);
    sprintf(debugString, "Sample rate: %lu", sample_rate);
    GUI_DispStringAt(debugString, 10, 170);

    // Read byte rate
    FS_Read(filePtr, buffer4, 4);
    uint32 byte_rate = buffer4[0] | (buffer4[1] << 8) | (buffer4[2] << 16) | (buffer4[3] << 24);
    sprintf(debugString, "Byte rate: %lu", byte_rate);
    GUI_DispStringAt(debugString, 10, 190);

    // Read block align
    FS_Read(filePtr, buffer2, 2);
    uint16 block_align = buffer2[0] | (buffer2[1] << 8);
    sprintf(debugString, "Block align: %u", block_align);
    GUI_DispStringAt(debugString, 10, 210);

    // Read bits per sample
    FS_Read(filePtr, buffer2, 2);
    uint16 bits_per_sample = buffer2[0] | (buffer2[1] << 8);
    sprintf(debugString, "Bits per sample: %u", bits_per_sample);
    GUI_DispStringAt(debugString, 10, 230);
}

void InitializeAudioFile() {
    char sdVolName[10];
    FS_Init();
    CyDelay(2000u);  // Delay to ensure stability after initialization

    if(FS_GetVolumeName(0u, &sdVolName[0], sizeof(sdVolName) - 1) == 0) {
        sdVolName[sizeof(sdVolName) - 1] = '\0';  // Ensure null termination
        GUI_DispStringAt("SD card name:", 10, 10);
        GUI_DispStringAt(sdVolName, 10, 30);
    } else {
        GUI_DispStringAt("Failed to get SD card name", 10, 10);
    }
    
    if(FS_Mount("0:") == 0) {
        GUI_DispStringAt("Failed to mount SD", 10, 50);
        return;
    } else {
        GUI_DispStringAt("SD Card mounted", 10, 50);
    }

    // New block: List all files
    FS_FIND_DATA fd;
    char filename[256];  // Adjust size as needed
    if(FS_FindFirstFile(&fd, "0:\\6115FP", file1, 16)) {
        do {
            char* fileString;
            strcpy(fileString, "Filename: ");
            strcat(fileString, filename);
            strcat(fileString, ",");
            GUI_DispStringAt("HERE", 10, 70);  // Display file name
            CyDelay(500);  // Delay for visibility
        } while(0);  // Corrected to remove extra arguments
        FS_FindClose(&fd);
    } else {
        GUI_DispStringAt("No files found", 10, 70);
    }

    // Continue with your existing file operations
    audioFile1 = FS_FOpen(file1, "r");
    if (audioFile1) {
        GUI_DispStringAt("File opened successfully", 10, 130);
        readWavHeader(audioFile1);
        //FS_FSeek(audioFile, 44, FS_SEEK_SET); // skip the WAV header
        currentBufferFill = FS_Read(audioFile1, currentBuffer1, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
        loadingBufferFill = FS_Read(audioFile1, loadingBuffer1, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
        char textBuffer[128];
        sprintf(textBuffer, "Buffer fill: %u", currentBufferFill);
        
        GUI_DispStringAt(textBuffer, 10, 280);
        if (currentBufferFill > 0) {
            GUI_DispStringAt("Data loaded into buffer", 10, 150);
        } else {
            GUI_DispStringAt("Failed to load data", 10, 170);
        }
    } else {
        GUI_DispStringAt("Failed to open file", 10, 130);
    }
    
    CyDelay(1000);
    FS_FIND_DATA fd2;
    if(FS_FindFirstFile(&fd, "0:\\6115FP", file2, 16)) {
        do {
            char* fileString;
            strcpy(fileString, "Filename: ");
            strcat(fileString, filename);
            strcat(fileString, ",");
            GUI_DispStringAt("HERE", 10, 70);  // Display file name
            CyDelay(500);  // Delay for visibility
        } while(0);  // Corrected to remove extra arguments
        FS_FindClose(&fd);
    } else {
        GUI_DispStringAt("No files found", 10, 70);
    }
    // Continue with your existing file operations
    audioFile2 = FS_FOpen(file2, "r");
    if (audioFile2) {
        GUI_DispStringAt("File opened successfully", 10, 130);
        readWavHeader(audioFile2);
        //FS_FSeek(audioFile, 44, FS_SEEK_SET); // skip the WAV header
        currentBufferFill = FS_Read(audioFile2, currentBuffer2, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
        loadingBufferFill = FS_Read(audioFile2, loadingBuffer2, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
        char textBuffer[128];
        sprintf(textBuffer, "Buffer fill: %u", currentBufferFill);
        
        GUI_DispStringAt(textBuffer, 10, 280);
        if (currentBufferFill > 0) {
            GUI_DispStringAt("Data loaded into buffer", 10, 150);
        } else {
            GUI_DispStringAt("Failed to load data", 10, 170);
        }
    } else {
        GUI_DispStringAt("Failed to open file", 10, 130);
    }
}

void playAudio() {
    signed short int signedSample1 = currentBuffer1[audioSampleIndex];
    signed short int signedSample2 = currentBuffer2[audioSampleIndex];
    
    // TODO: calculate scaling factor normalized based on the sum of the two audio tracks
    float totalVolumeControl = volumeControlCoef1 + volumeControlCoef2;
    float scalingFactor1 = volumeControlCoef1 / totalVolumeControl;
    float scalingFactor2 = volumeControlCoef2 / totalVolumeControl;
    signedSample1 = (signed short int)(signedSample1 * scalingFactor1);
    signedSample2 = (signed short int)(signedSample2 * scalingFactor2);
    
    int mixedSample = 0.85 * (signedSample1 + signedSample2);
    
    if (mixedSample > 32767) mixedSample = 32767;
    if (mixedSample < -32768) mixedSample = -32768;
    //signedSample *= volumeControlCoef;
    uint16 adjustedSample = mixedSample + SAMPLE_OFFSET;
    //adjustVolume(&adjustedSample, 0.3); // Adjust volume
    
    audioSampleIndex++;
    SPIM_Audio_WriteTxData(adjustedSample);
}

CY_ISR(audioTimerISRHandler) {
    if (!fileEnd1) {
    	if (audioSampleIndex >= AUDIO_BUFFER_SIZE) {
            audioSampleIndex = 0;
            switchBuffers = 0x1;
            // Switch the pointers of the buffers
            signed short int* temp = currentBuffer1;
            currentBuffer1 = loadingBuffer1;
            loadingBuffer1 = temp;
            temp = currentBuffer2;
            currentBuffer2 = loadingBuffer2;
            loadingBuffer2 = temp;
    	}
        playAudio();
    }
    // UpdateVolumeControlAndDisplay();
	AudioTimer_ReadStatusRegister(); // Clear the timer interrupt
}

CY_ISR(updateSecondsTimer) {
    GUI_SetColor(GUI_WHITE);
    uint16 currMin = secondsCount / 60;
    uint16 currSec = secondsCount % 60;
    sprintf(timeString, "Time: %02u:%02u", currMin, currSec);
    GUI_DispStringAt(timeString, 80, 30);
    secondsCount++;
    if (!fileEnd1 || !fileEnd2) TimeStamp_Timer_ReadStatusRegister();
}

CY_ISR(getADCs) {
    ADC_FlexSensor_L_StartConvert();
    while (!ADC_FlexSensor_L_IsEndConversion(ADC_FlexSensor_L_RETURN_STATUS));
    uint16_t adcValue1 = ADC_FlexSensor_L_GetResult16();
    volumeControlCoef1 = (adcValue1 / 4096.0);  // Normalize and invert ADC value to 0-1 range
    ADC_FlexSensor_R_StartConvert();
    while (!ADC_FlexSensor_R_IsEndConversion(ADC_FlexSensor_R_RETURN_STATUS));
    uint16_t adcValue2 = ADC_FlexSensor_R_GetResult16();
    volumeControlCoef2 = (adcValue2 * 2 / 65536.0);  // Normalize and invert ADC value to 0-1 range
	// high adcValue = unflexed, low = flexed
    GUI_SetColor(GUI_WHITE);
    sprintf(volumeControlString1, "Volume: %02u%% ", (uint16)(100*volumeControlCoef1));
    GUI_DispStringAt(volumeControlString1, 20, 50);
    
    sprintf(volumeControlString2, "Volume: %02u%% ", (uint16)(100*volumeControlCoef2));
    GUI_DispStringAt(volumeControlString2, 120, 50);
    
    //I2C_MASTER_L_MasterSendStart(0x68, 0);      //start the transaction
    //I2C_MASTER_L_MasterWriteByte(0x3B);         //The register address for the X-acceleration is 0x3B
    //I2C_MASTER_L_MasterSendRestart(0x68, 1);    //MasterSendRestart sends another start condition without needing to send a stop condition first
    
    //topByte = I2C_MASTER_L_MasterReadByte(I2C_MASTER_L_ACK_DATA);       //receive the first byte and acknowledge to signal we are not done reading
    //bottomByte = I2C_MASTER_L_MasterReadByte(I2C_MASTER_L_NAK_DATA);    //receive the second byte and non-acknowledge to signal we are done reading
    
    //I2C_MASTER_L_MasterSendStop();      //end the transaction
    
    //combinedData = ((uint16_t)topByte << 8) | (uint16_t)bottomByte;     //combine the two bytes into one 16-bit unsigned integer

    //geeForce = (int16_t)combinedData / LSBperGee;
    //sprintf(mpuString1, "Filter: %u", (uint16)(geeForce*10000));
    //GUI_DispStringAt(mpuString1, 80, 70);
    Get_ADCs_Timer_ReadStatusRegister();
}

void MPU_ByteWriteL(uint8_t reg, uint8_t byte){
    /* Writes a single Byte to the I2C device at address 0x68.
    parameters:
        uint8_t reg: the register on the device to write to
        uint8_t byte: the byte to be written
    
    returns:
        void
    */
    
    I2C_MASTER_L_MasterSendStart(0x68, 0);      //start a write to the MPU to begin the transaction
    I2C_MASTER_L_MasterWriteByte(reg);          //send the address of the register we want to write to
    I2C_MASTER_L_MasterWriteByte(byte);         //send the byte
    I2C_MASTER_L_MasterSendStop();              //send the stop signal to end the transaction
}

int main()
{
	CyGlobalIntEnable; /* Enable global interrupts. */
    
	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPIM_Audio_Start();
	GUI_Initialize();
    InitializeAudioFile();
    AudioTimer_Start();
	audiotimer_isr_StartEx(audioTimerISRHandler); // start the ISR
    
    GUI_Clear();
    GUI_DispStringAt("Dynamix", 100, 10);
    GUI_DispStringAt("Time: 00:00", 80, 30);
    sprintf(volumeControlString1, "Volume: %02u%% ", (uint16)(100*volumeControlCoef1));
    GUI_DispStringAt(volumeControlString1, 20, 50);
    sprintf(volumeControlString2, "Volume: %02u%% ", (uint16)(100*volumeControlCoef2));
    GUI_DispStringAt(volumeControlString2, 120, 50);
    
    DisplayAmplitudeBar(currentBuffer1, AUDIO_BUFFER_SIZE, TRACK_1);
    DisplayAmplitudeBar(currentBuffer2, AUDIO_BUFFER_SIZE, TRACK_2);
    uint16_t numSecs = (overall_size-44) / SAMPLE_RATE / sizeof(uint16);
    
    Get_ADCs_Timer_Start();
    ADC_FlexSensor_L_Start();
    TimeStamp_Timer_Start();
    ADC_FlexSensor_R_Start();
    timestamp_timer_isr_StartEx(updateSecondsTimer);
    I2C_MASTER_L_Start();
    I2C_MASTER_L_MasterSendStart(0x68, 0);      //starts an I2C write. The address of the MPU is 0x68
    I2C_MASTER_L_MasterWriteByte(0x1A);         //writes the address of the target register. 1A is the CONFIG register
    I2C_MASTER_L_MasterWriteByte(0x00);         //writes sets the frame sync to disabled and the DLPF to a bandwidth of 260 Hz
    I2C_MASTER_L_MasterSendStop();              //stops an I2C transaction.
    
    MPU_ByteWriteL(0x6B, 0x00);  //takes the MPU out of sleep mode
    MPU_ByteWriteL(0x1C, 0x00);  //sets the accelerometer to +/- 2 gees range
    MPU_ByteWriteL(0x23, 0x00);  //disables FIFO buffer and DLPF
    
    get_adcs_isr_StartEx(getADCs);
    
    int bufferCount = 1;
	for(;;)
	{
    	/* Place your application code here. */
        if (switchBuffers && (!fileEnd1 || !fileEnd2)) {
            // Load new data into the buffer that is not currently in use
            size_t bytesRead1 = 0;
            size_t bytesRead2 = 0;
            if (!fileEnd1) bytesRead1 = FS_Read(audioFile1, loadingBuffer1, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
            if (!fileEnd2) bytesRead2 = FS_Read(audioFile2, loadingBuffer2, AUDIO_BUFFER_SIZE * sizeof(uint16_t)) / sizeof(uint16_t);
            if (bytesRead1 == 0 && !fileEnd1) {
                // Buffer underflow, handle error or wait
                fileEnd1 = 0x1;
            }
            if (bytesRead2 == 0 && !fileEnd2) {
                // Buffer underflow, handle error or wait
                fileEnd2 = 0x1;
            }
            if (fileEnd1 && fileEnd2) {
                GUI_SetColor(GUI_LIGHTBLUE);
                GUI_DispStringAt("Playback complete!", 50, 300);
            	FS_FClose(audioFile1);
            	FS_Unmount("0:");
            }
            switchBuffers = 0x0;
            if (bufferCount >= SAMPLE_RATE * SECONDS_PER_BAR / AUDIO_BUFFER_SIZE) { // draw a bar every 4 seconds (smaller is bad for the number of pixels)
            	DisplayAmplitudeBar(currentBuffer1, AUDIO_BUFFER_SIZE, TRACK_1);
            	DisplayAmplitudeBar(currentBuffer2, AUDIO_BUFFER_SIZE, TRACK_2);
                bufferCount = 0;
            } else bufferCount++;
        }
        //GUI_Clear();
        //char textBuffer[128];
        //sprintf(textBuffer, "ADC Value: %u", adcValue);
        //GUI_DispStringAt(textBuffer, 50, 250);
    	// UpdateVolumeControlAndDisplay();
	}
}

/* [] END OF FILE */

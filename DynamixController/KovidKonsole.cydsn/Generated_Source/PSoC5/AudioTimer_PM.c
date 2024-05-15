/*******************************************************************************
* File Name: AudioTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "AudioTimer.h"

static AudioTimer_backupStruct AudioTimer_backup;


/*******************************************************************************
* Function Name: AudioTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AudioTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void AudioTimer_SaveConfig(void) 
{
    #if (!AudioTimer_UsingFixedFunction)
        AudioTimer_backup.TimerUdb = AudioTimer_ReadCounter();
        AudioTimer_backup.InterruptMaskValue = AudioTimer_STATUS_MASK;
        #if (AudioTimer_UsingHWCaptureCounter)
            AudioTimer_backup.TimerCaptureCounter = AudioTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!AudioTimer_UDB_CONTROL_REG_REMOVED)
            AudioTimer_backup.TimerControlRegister = AudioTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: AudioTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AudioTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void AudioTimer_RestoreConfig(void) 
{   
    #if (!AudioTimer_UsingFixedFunction)

        AudioTimer_WriteCounter(AudioTimer_backup.TimerUdb);
        AudioTimer_STATUS_MASK =AudioTimer_backup.InterruptMaskValue;
        #if (AudioTimer_UsingHWCaptureCounter)
            AudioTimer_SetCaptureCount(AudioTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!AudioTimer_UDB_CONTROL_REG_REMOVED)
            AudioTimer_WriteControlRegister(AudioTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: AudioTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AudioTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void AudioTimer_Sleep(void) 
{
    #if(!AudioTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(AudioTimer_CTRL_ENABLE == (AudioTimer_CONTROL & AudioTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            AudioTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            AudioTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    AudioTimer_Stop();
    AudioTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: AudioTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  AudioTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void AudioTimer_Wakeup(void) 
{
    AudioTimer_RestoreConfig();
    #if(!AudioTimer_UDB_CONTROL_REG_REMOVED)
        if(AudioTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                AudioTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

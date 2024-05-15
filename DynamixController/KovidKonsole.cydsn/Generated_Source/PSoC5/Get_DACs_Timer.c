/*******************************************************************************
* File Name: Get_DACs_Timer.c
* Version 2.70
*
* Description:
*  The Timer component consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Get_DACs_Timer.h"

uint8 Get_DACs_Timer_initVar = 0u;


/*******************************************************************************
* Function Name: Get_DACs_Timer_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_Init(void) 
{
    #if(!Get_DACs_Timer_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 Get_DACs_Timer_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (Get_DACs_Timer_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        Get_DACs_Timer_CONTROL &= Get_DACs_Timer_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            Get_DACs_Timer_CONTROL2 &= ((uint8)(~Get_DACs_Timer_CTRL_MODE_MASK));
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            Get_DACs_Timer_CONTROL3 &= ((uint8)(~Get_DACs_Timer_CTRL_MODE_MASK));
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (Get_DACs_Timer_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            Get_DACs_Timer_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (Get_DACs_Timer_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                Get_DACs_Timer_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                Get_DACs_Timer_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (Get_DACs_Timer_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                Get_DACs_Timer_CONTROL2 |= Get_DACs_Timer_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                Get_DACs_Timer_CONTROL3 &= ((uint8)(~Get_DACs_Timer_CTRL_RCOD_MASK));
                Get_DACs_Timer_CONTROL3 |= Get_DACs_Timer_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                Get_DACs_Timer_CONTROL3 &= ((uint8)(~Get_DACs_Timer_CTRL_ENBL_MASK));
                Get_DACs_Timer_CONTROL3 |= Get_DACs_Timer_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                Get_DACs_Timer_CONTROL3 |= Get_DACs_Timer_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Get_DACs_Timer_RT1 &= ((uint8)(~Get_DACs_Timer_RT1_MASK));
        Get_DACs_Timer_RT1 |= Get_DACs_Timer_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        Get_DACs_Timer_RT1 &= ((uint8)(~Get_DACs_Timer_SYNCDSI_MASK));
        Get_DACs_Timer_RT1 |= Get_DACs_Timer_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        Get_DACs_Timer_CONTROL2 |= Get_DACs_Timer_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    Get_DACs_Timer_WritePeriod(Get_DACs_Timer_INIT_PERIOD);
    Get_DACs_Timer_WriteCounter(Get_DACs_Timer_INIT_PERIOD);

    #if (Get_DACs_Timer_UsingHWCaptureCounter)/* Capture counter is enabled */
        Get_DACs_Timer_CAPTURE_COUNT_CTRL |= Get_DACs_Timer_CNTR_ENABLE;
        Get_DACs_Timer_SetCaptureCount(Get_DACs_Timer_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!Get_DACs_Timer_UsingFixedFunction)
        #if (Get_DACs_Timer_SoftwareCaptureMode)
            Get_DACs_Timer_SetCaptureMode(Get_DACs_Timer_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (Get_DACs_Timer_SoftwareTriggerMode)
            #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
                if (0u == (Get_DACs_Timer_CONTROL & Get_DACs_Timer__B_TIMER__TM_SOFTWARE))
                {
                    Get_DACs_Timer_SetTriggerMode(Get_DACs_Timer_INIT_TRIGGER_MODE);
                }
            #endif /* (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) */
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        Get_DACs_Timer_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        Get_DACs_Timer_STATUS_AUX_CTRL |= Get_DACs_Timer_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(Get_DACs_Timer_interruptState);

        #if (Get_DACs_Timer_EnableTriggerMode)
            Get_DACs_Timer_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/
		
		
        #if (Get_DACs_Timer_InterruptOnCaptureCount && !Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
            Get_DACs_Timer_SetInterruptCount(Get_DACs_Timer_INIT_INT_CAPTURE_COUNT);
        #endif /* Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        Get_DACs_Timer_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    Get_DACs_Timer_SetInterruptMode(Get_DACs_Timer_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Get_DACs_Timer_UsingFixedFunction)
        Get_DACs_Timer_GLOBAL_ENABLE |= Get_DACs_Timer_BLOCK_EN_MASK;
        Get_DACs_Timer_GLOBAL_STBY_ENABLE |= Get_DACs_Timer_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED || Get_DACs_Timer_UsingFixedFunction)
        Get_DACs_Timer_CONTROL |= Get_DACs_Timer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Get_DACs_Timer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Get_DACs_Timer_Start(void) 
{
    if(Get_DACs_Timer_initVar == 0u)
    {
        Get_DACs_Timer_Init();

        Get_DACs_Timer_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    Get_DACs_Timer_Enable();
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
*
*******************************************************************************/
void Get_DACs_Timer_Stop(void) 
{
    /* Disable Timer */
    #if(!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED || Get_DACs_Timer_UsingFixedFunction)
        Get_DACs_Timer_CONTROL &= ((uint8)(~Get_DACs_Timer_CTRL_ENABLE));
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (Get_DACs_Timer_UsingFixedFunction)
        Get_DACs_Timer_GLOBAL_ENABLE &= ((uint8)(~Get_DACs_Timer_BLOCK_EN_MASK));
        Get_DACs_Timer_GLOBAL_STBY_ENABLE &= ((uint8)(~Get_DACs_Timer_BLOCK_STBY_EN_MASK));
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_SetInterruptMode(uint8 interruptMode) 
{
    Get_DACs_Timer_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void Get_DACs_Timer_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    #if(Get_DACs_Timer_UsingFixedFunction)
        (void)CY_GET_REG16(Get_DACs_Timer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(Get_DACs_Timer_COUNTER_LSB_PTR_8BIT);
    #endif/* (Get_DACs_Timer_UsingFixedFunction) */
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
*******************************************************************************/
uint8   Get_DACs_Timer_ReadStatusRegister(void) 
{
    return (Get_DACs_Timer_STATUS);
}


#if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
*******************************************************************************/
uint8 Get_DACs_Timer_ReadControlRegister(void) 
{
    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) 
        return ((uint8)Get_DACs_Timer_CONTROL);
    #else
        return (0);
    #endif /* (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
*******************************************************************************/
void Get_DACs_Timer_WriteControlRegister(uint8 control) 
{
    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) 
        Get_DACs_Timer_CONTROL = control;
    #else
        control = 0u;
    #endif /* (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) */
}

#endif /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
*******************************************************************************/
uint32 Get_DACs_Timer_ReadPeriod(void) 
{
   #if(Get_DACs_Timer_UsingFixedFunction)
       return ((uint32)CY_GET_REG16(Get_DACs_Timer_PERIOD_LSB_PTR));
   #else
       return (CY_GET_REG32(Get_DACs_Timer_PERIOD_LSB_PTR));
   #endif /* (Get_DACs_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_WritePeriod(uint32 period) 
{
    #if(Get_DACs_Timer_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(Get_DACs_Timer_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG32(Get_DACs_Timer_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
*******************************************************************************/
uint32 Get_DACs_Timer_ReadCapture(void) 
{
   #if(Get_DACs_Timer_UsingFixedFunction)
       return ((uint32)CY_GET_REG16(Get_DACs_Timer_CAPTURE_LSB_PTR));
   #else
       return (CY_GET_REG32(Get_DACs_Timer_CAPTURE_LSB_PTR));
   #endif /* (Get_DACs_Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_WriteCounter(uint32 counter) 
{
   #if(Get_DACs_Timer_UsingFixedFunction)
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        CY_SET_REG16(Get_DACs_Timer_COUNTER_LSB_PTR, (uint16)counter);
        
    #else
        CY_SET_REG32(Get_DACs_Timer_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
*******************************************************************************/
uint32 Get_DACs_Timer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Get_DACs_Timer_UsingFixedFunction)
        (void)CY_GET_REG16(Get_DACs_Timer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(Get_DACs_Timer_COUNTER_LSB_PTR_8BIT);
    #endif/* (Get_DACs_Timer_UsingFixedFunction) */

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Get_DACs_Timer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Get_DACs_Timer_CAPTURE_LSB_PTR));
    #else
        return (CY_GET_REG32(Get_DACs_Timer_CAPTURE_LSB_PTR));
    #endif /* (Get_DACs_Timer_UsingFixedFunction) */
}


#if(!Get_DACs_Timer_UsingFixedFunction) /* UDB Specific Functions */

    
/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (Get_DACs_Timer_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: Get_DACs_Timer_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define Get_DACs_Timer__B_TIMER__CM_NONE 0
#define Get_DACs_Timer__B_TIMER__CM_RISINGEDGE 1
#define Get_DACs_Timer__B_TIMER__CM_FALLINGEDGE 2
#define Get_DACs_Timer__B_TIMER__CM_EITHEREDGE 3
#define Get_DACs_Timer__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  Get_DACs_Timer__B_TIMER__CM_NONE        - Set Capture mode to None
*  Get_DACs_Timer__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  Get_DACs_Timer__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  Get_DACs_Timer__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = ((uint8)((uint8)captureMode << Get_DACs_Timer_CTRL_CAP_MODE_SHIFT));
    captureMode &= (Get_DACs_Timer_CTRL_CAP_MODE_MASK);

    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        Get_DACs_Timer_CONTROL &= ((uint8)(~Get_DACs_Timer_CTRL_CAP_MODE_MASK));

        /* Write The New Setting */
        Get_DACs_Timer_CONTROL |= captureMode;
    #endif /* (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (Get_DACs_Timer_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: Get_DACs_Timer_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define Get_DACs_Timer__B_TIMER__TM_NONE 0x00u
    #define Get_DACs_Timer__B_TIMER__TM_RISINGEDGE 0x04u
    #define Get_DACs_Timer__B_TIMER__TM_FALLINGEDGE 0x08u
    #define Get_DACs_Timer__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define Get_DACs_Timer__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= Get_DACs_Timer_CTRL_TRIG_MODE_MASK;

    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
    
        /* Clear the Current Setting */
        Get_DACs_Timer_CONTROL &= ((uint8)(~Get_DACs_Timer_CTRL_TRIG_MODE_MASK));

        /* Write The New Setting */
        Get_DACs_Timer_CONTROL |= (triggerMode | Get_DACs_Timer__B_TIMER__TM_SOFTWARE);
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (Get_DACs_Timer_EnableTriggerMode)


/*******************************************************************************
* Function Name: Get_DACs_Timer_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_EnableTrigger(void) 
{
    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
        Get_DACs_Timer_CONTROL |= Get_DACs_Timer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_DisableTrigger(void) 
{
    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED )   /* Remove assignment if control register is removed */
        Get_DACs_Timer_CONTROL &= ((uint8)(~Get_DACs_Timer_CTRL_TRIG_EN));
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */

#if(Get_DACs_Timer_InterruptOnCaptureCount)


/*******************************************************************************
* Function Name: Get_DACs_Timer_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= Get_DACs_Timer_CTRL_INTCNT_MASK;

    #if (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        Get_DACs_Timer_CONTROL &= ((uint8)(~Get_DACs_Timer_CTRL_INTCNT_MASK));
        /* Write The New Setting */
        Get_DACs_Timer_CONTROL |= interruptCount;
    #endif /* (!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Get_DACs_Timer_InterruptOnCaptureCount */


#if (Get_DACs_Timer_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: Get_DACs_Timer_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_SetCaptureCount(uint8 captureCount) 
{
    Get_DACs_Timer_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 Get_DACs_Timer_ReadCaptureCount(void) 
{
    return ((uint8)Get_DACs_Timer_CAP_COUNT);
}
#endif /* Get_DACs_Timer_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: Get_DACs_Timer_ClearFIFO
********************************************************************************
*
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Get_DACs_Timer_ClearFIFO(void) 
{
    while(0u != (Get_DACs_Timer_ReadStatusRegister() & Get_DACs_Timer_STATUS_FIFONEMP))
    {
        (void)Get_DACs_Timer_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */

/*******************************************************************************
* File Name: FlexSensor_LD_Timer_PM.c
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

#include "FlexSensor_LD_Timer.h"

static FlexSensor_LD_Timer_backupStruct FlexSensor_LD_Timer_backup;


/*******************************************************************************
* Function Name: FlexSensor_LD_Timer_SaveConfig
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
*  FlexSensor_LD_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FlexSensor_LD_Timer_SaveConfig(void) 
{
    #if (!FlexSensor_LD_Timer_UsingFixedFunction)
        FlexSensor_LD_Timer_backup.TimerUdb = FlexSensor_LD_Timer_ReadCounter();
        FlexSensor_LD_Timer_backup.InterruptMaskValue = FlexSensor_LD_Timer_STATUS_MASK;
        #if (FlexSensor_LD_Timer_UsingHWCaptureCounter)
            FlexSensor_LD_Timer_backup.TimerCaptureCounter = FlexSensor_LD_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!FlexSensor_LD_Timer_UDB_CONTROL_REG_REMOVED)
            FlexSensor_LD_Timer_backup.TimerControlRegister = FlexSensor_LD_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: FlexSensor_LD_Timer_RestoreConfig
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
*  FlexSensor_LD_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FlexSensor_LD_Timer_RestoreConfig(void) 
{   
    #if (!FlexSensor_LD_Timer_UsingFixedFunction)

        FlexSensor_LD_Timer_WriteCounter(FlexSensor_LD_Timer_backup.TimerUdb);
        FlexSensor_LD_Timer_STATUS_MASK =FlexSensor_LD_Timer_backup.InterruptMaskValue;
        #if (FlexSensor_LD_Timer_UsingHWCaptureCounter)
            FlexSensor_LD_Timer_SetCaptureCount(FlexSensor_LD_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!FlexSensor_LD_Timer_UDB_CONTROL_REG_REMOVED)
            FlexSensor_LD_Timer_WriteControlRegister(FlexSensor_LD_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: FlexSensor_LD_Timer_Sleep
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
*  FlexSensor_LD_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void FlexSensor_LD_Timer_Sleep(void) 
{
    #if(!FlexSensor_LD_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(FlexSensor_LD_Timer_CTRL_ENABLE == (FlexSensor_LD_Timer_CONTROL & FlexSensor_LD_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            FlexSensor_LD_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            FlexSensor_LD_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    FlexSensor_LD_Timer_Stop();
    FlexSensor_LD_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: FlexSensor_LD_Timer_Wakeup
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
*  FlexSensor_LD_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FlexSensor_LD_Timer_Wakeup(void) 
{
    FlexSensor_LD_Timer_RestoreConfig();
    #if(!FlexSensor_LD_Timer_UDB_CONTROL_REG_REMOVED)
        if(FlexSensor_LD_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                FlexSensor_LD_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

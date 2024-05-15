/*******************************************************************************
* File Name: TimeStamp_Timer_PM.c
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

#include "TimeStamp_Timer.h"

static TimeStamp_Timer_backupStruct TimeStamp_Timer_backup;


/*******************************************************************************
* Function Name: TimeStamp_Timer_SaveConfig
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
*  TimeStamp_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimeStamp_Timer_SaveConfig(void) 
{
    #if (!TimeStamp_Timer_UsingFixedFunction)
        TimeStamp_Timer_backup.TimerUdb = TimeStamp_Timer_ReadCounter();
        TimeStamp_Timer_backup.InterruptMaskValue = TimeStamp_Timer_STATUS_MASK;
        #if (TimeStamp_Timer_UsingHWCaptureCounter)
            TimeStamp_Timer_backup.TimerCaptureCounter = TimeStamp_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimeStamp_Timer_UDB_CONTROL_REG_REMOVED)
            TimeStamp_Timer_backup.TimerControlRegister = TimeStamp_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimeStamp_Timer_RestoreConfig
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
*  TimeStamp_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimeStamp_Timer_RestoreConfig(void) 
{   
    #if (!TimeStamp_Timer_UsingFixedFunction)

        TimeStamp_Timer_WriteCounter(TimeStamp_Timer_backup.TimerUdb);
        TimeStamp_Timer_STATUS_MASK =TimeStamp_Timer_backup.InterruptMaskValue;
        #if (TimeStamp_Timer_UsingHWCaptureCounter)
            TimeStamp_Timer_SetCaptureCount(TimeStamp_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimeStamp_Timer_UDB_CONTROL_REG_REMOVED)
            TimeStamp_Timer_WriteControlRegister(TimeStamp_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimeStamp_Timer_Sleep
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
*  TimeStamp_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimeStamp_Timer_Sleep(void) 
{
    #if(!TimeStamp_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimeStamp_Timer_CTRL_ENABLE == (TimeStamp_Timer_CONTROL & TimeStamp_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimeStamp_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimeStamp_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimeStamp_Timer_Stop();
    TimeStamp_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: TimeStamp_Timer_Wakeup
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
*  TimeStamp_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimeStamp_Timer_Wakeup(void) 
{
    TimeStamp_Timer_RestoreConfig();
    #if(!TimeStamp_Timer_UDB_CONTROL_REG_REMOVED)
        if(TimeStamp_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimeStamp_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

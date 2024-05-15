/*******************************************************************************
* File Name: Get_DACs_Timer_PM.c
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

#include "Get_DACs_Timer.h"

static Get_DACs_Timer_backupStruct Get_DACs_Timer_backup;


/*******************************************************************************
* Function Name: Get_DACs_Timer_SaveConfig
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
*  Get_DACs_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Get_DACs_Timer_SaveConfig(void) 
{
    #if (!Get_DACs_Timer_UsingFixedFunction)
        Get_DACs_Timer_backup.TimerUdb = Get_DACs_Timer_ReadCounter();
        Get_DACs_Timer_backup.InterruptMaskValue = Get_DACs_Timer_STATUS_MASK;
        #if (Get_DACs_Timer_UsingHWCaptureCounter)
            Get_DACs_Timer_backup.TimerCaptureCounter = Get_DACs_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
            Get_DACs_Timer_backup.TimerControlRegister = Get_DACs_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_RestoreConfig
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
*  Get_DACs_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Get_DACs_Timer_RestoreConfig(void) 
{   
    #if (!Get_DACs_Timer_UsingFixedFunction)

        Get_DACs_Timer_WriteCounter(Get_DACs_Timer_backup.TimerUdb);
        Get_DACs_Timer_STATUS_MASK =Get_DACs_Timer_backup.InterruptMaskValue;
        #if (Get_DACs_Timer_UsingHWCaptureCounter)
            Get_DACs_Timer_SetCaptureCount(Get_DACs_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
            Get_DACs_Timer_WriteControlRegister(Get_DACs_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_Sleep
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
*  Get_DACs_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Get_DACs_Timer_Sleep(void) 
{
    #if(!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Get_DACs_Timer_CTRL_ENABLE == (Get_DACs_Timer_CONTROL & Get_DACs_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Get_DACs_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Get_DACs_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Get_DACs_Timer_Stop();
    Get_DACs_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Get_DACs_Timer_Wakeup
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
*  Get_DACs_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Get_DACs_Timer_Wakeup(void) 
{
    Get_DACs_Timer_RestoreConfig();
    #if(!Get_DACs_Timer_UDB_CONTROL_REG_REMOVED)
        if(Get_DACs_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Get_DACs_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

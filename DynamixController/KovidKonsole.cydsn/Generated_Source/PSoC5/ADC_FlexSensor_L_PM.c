/*******************************************************************************
* File Name: ADC_FlexSensor_L_PM.c
* Version 3.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_FlexSensor_L.h"


/***************************************
* Local data allocation
***************************************/

static ADC_FlexSensor_L_BACKUP_STRUCT  ADC_FlexSensor_L_backup =
{
    ADC_FlexSensor_L_DISABLED
};


/*******************************************************************************
* Function Name: ADC_FlexSensor_L_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_FlexSensor_L_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_FlexSensor_L_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_FlexSensor_L_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_FlexSensor_L_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_FlexSensor_L_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_FlexSensor_L_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_FlexSensor_L_Sleep(void)
{
    if((ADC_FlexSensor_L_PWRMGR_SAR_REG  & ADC_FlexSensor_L_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_FlexSensor_L_SAR_CSR0_REG & ADC_FlexSensor_L_SAR_SOF_START_CONV) != 0u)
        {
            ADC_FlexSensor_L_backup.enableState = ADC_FlexSensor_L_ENABLED | ADC_FlexSensor_L_STARTED;
        }
        else
        {
            ADC_FlexSensor_L_backup.enableState = ADC_FlexSensor_L_ENABLED;
        }
        ADC_FlexSensor_L_Stop();
    }
    else
    {
        ADC_FlexSensor_L_backup.enableState = ADC_FlexSensor_L_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_FlexSensor_L_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_FlexSensor_L_Sleep() was called. If the component was enabled before the
*  ADC_FlexSensor_L_Sleep() function was called, the
*  ADC_FlexSensor_L_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_FlexSensor_L_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_FlexSensor_L_Wakeup(void)
{
    if(ADC_FlexSensor_L_backup.enableState != ADC_FlexSensor_L_DISABLED)
    {
        ADC_FlexSensor_L_Enable();
        #if(ADC_FlexSensor_L_DEFAULT_CONV_MODE != ADC_FlexSensor_L__HARDWARE_TRIGGER)
            if((ADC_FlexSensor_L_backup.enableState & ADC_FlexSensor_L_STARTED) != 0u)
            {
                ADC_FlexSensor_L_StartConvert();
            }
        #endif /* End ADC_FlexSensor_L_DEFAULT_CONV_MODE != ADC_FlexSensor_L__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */

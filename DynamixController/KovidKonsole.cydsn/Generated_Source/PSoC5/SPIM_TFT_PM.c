/*******************************************************************************
* File Name: SPIM_TFT_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_TFT_PVT.h"

static SPIM_TFT_BACKUP_STRUCT SPIM_TFT_backup =
{
    SPIM_TFT_DISABLED,
    SPIM_TFT_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_TFT_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_TFT_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_TFT_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_TFT_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_TFT_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_TFT_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_TFT_Sleep(void) 
{
    /* Save components enable state */
    SPIM_TFT_backup.enableState = ((uint8) SPIM_TFT_IS_ENABLED);

    SPIM_TFT_Stop();
}


/*******************************************************************************
* Function Name: SPIM_TFT_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_TFT_backup - used when non-retention registers are restored.
*  SPIM_TFT_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_TFT_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_TFT_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_TFT_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_TFT_Wakeup(void) 
{
    #if(SPIM_TFT_RX_SOFTWARE_BUF_ENABLED)
        SPIM_TFT_rxBufferFull  = 0u;
        SPIM_TFT_rxBufferRead  = 0u;
        SPIM_TFT_rxBufferWrite = 0u;
    #endif /* (SPIM_TFT_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_TFT_TX_SOFTWARE_BUF_ENABLED)
        SPIM_TFT_txBufferFull  = 0u;
        SPIM_TFT_txBufferRead  = 0u;
        SPIM_TFT_txBufferWrite = 0u;
    #endif /* (SPIM_TFT_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_TFT_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_TFT_backup.enableState)
    {
        SPIM_TFT_Enable();
    }
}


/* [] END OF FILE */

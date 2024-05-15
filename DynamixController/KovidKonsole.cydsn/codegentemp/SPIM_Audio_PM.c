/*******************************************************************************
* File Name: SPIM_Audio_PM.c
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

#include "SPIM_Audio_PVT.h"

static SPIM_Audio_BACKUP_STRUCT SPIM_Audio_backup =
{
    SPIM_Audio_DISABLED,
    SPIM_Audio_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_Audio_SaveConfig
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
void SPIM_Audio_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_Audio_RestoreConfig
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
void SPIM_Audio_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_Audio_Sleep
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
*  SPIM_Audio_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_Audio_Sleep(void) 
{
    /* Save components enable state */
    SPIM_Audio_backup.enableState = ((uint8) SPIM_Audio_IS_ENABLED);

    SPIM_Audio_Stop();
}


/*******************************************************************************
* Function Name: SPIM_Audio_Wakeup
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
*  SPIM_Audio_backup - used when non-retention registers are restored.
*  SPIM_Audio_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_Audio_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_Audio_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_Audio_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_Audio_Wakeup(void) 
{
    #if(SPIM_Audio_RX_SOFTWARE_BUF_ENABLED)
        SPIM_Audio_rxBufferFull  = 0u;
        SPIM_Audio_rxBufferRead  = 0u;
        SPIM_Audio_rxBufferWrite = 0u;
    #endif /* (SPIM_Audio_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_Audio_TX_SOFTWARE_BUF_ENABLED)
        SPIM_Audio_txBufferFull  = 0u;
        SPIM_Audio_txBufferRead  = 0u;
        SPIM_Audio_txBufferWrite = 0u;
    #endif /* (SPIM_Audio_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_Audio_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_Audio_backup.enableState)
    {
        SPIM_Audio_Enable();
    }
}


/* [] END OF FILE */

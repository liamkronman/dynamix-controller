/*******************************************************************************
* File Name: SPIM_TFT_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_TFT_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START SPIM_TFT_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPIM_TFT_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIM_TFT_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPIM_TFT_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPIM_TFT_txBuffer[SPIM_TFT_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_TFT_TX_ISR)
{
    #if(SPIM_TFT_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPIM_TFT_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_TFT_TX_ISR_ENTRY_CALLBACK
        SPIM_TFT_TX_ISR_EntryCallback();
    #endif /* SPIM_TFT_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_TFT_TX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_TFT_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(SPIM_TFT_txBufferRead != SPIM_TFT_txBufferWrite)
        {
            tmpStatus = SPIM_TFT_GET_STATUS_TX(SPIM_TFT_swStatusTx);
            SPIM_TFT_swStatusTx = tmpStatus;

            if(0u != (SPIM_TFT_swStatusTx & SPIM_TFT_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == SPIM_TFT_txBufferFull)
                {
                   SPIM_TFT_txBufferRead++;

                    if(SPIM_TFT_txBufferRead >= SPIM_TFT_TX_BUFFER_SIZE)
                    {
                        SPIM_TFT_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPIM_TFT_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(SPIM_TFT_TXDATA_PTR, 
                                             SPIM_TFT_txBuffer[SPIM_TFT_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(SPIM_TFT_txBufferRead == SPIM_TFT_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            SPIM_TFT_TX_STATUS_MASK_REG &= ((uint8) ~SPIM_TFT_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (SPIM_TFT_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_TFT_TX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_TFT_TX_ISR_EXIT_CALLBACK
        SPIM_TFT_TX_ISR_ExitCallback();
    #endif /* SPIM_TFT_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: SPIM_TFT_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIM_TFT_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPIM_TFT_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPIM_TFT_rxBuffer[SPIM_TFT_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_TFT_RX_ISR)
{
    #if(SPIM_TFT_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (SPIM_TFT_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_TFT_RX_ISR_ENTRY_CALLBACK
        SPIM_TFT_RX_ISR_EntryCallback();
    #endif /* SPIM_TFT_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_TFT_RX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_TFT_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = SPIM_TFT_GET_STATUS_RX(SPIM_TFT_swStatusRx);
        SPIM_TFT_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (SPIM_TFT_swStatusRx & SPIM_TFT_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(SPIM_TFT_RXDATA_PTR);

            /* Set next pointer. */
            SPIM_TFT_rxBufferWrite++;
            if(SPIM_TFT_rxBufferWrite >= SPIM_TFT_RX_BUFFER_SIZE)
            {
                SPIM_TFT_rxBufferWrite = 0u;
            }

            if(SPIM_TFT_rxBufferWrite == SPIM_TFT_rxBufferRead)
            {
                SPIM_TFT_rxBufferRead++;
                if(SPIM_TFT_rxBufferRead >= SPIM_TFT_RX_BUFFER_SIZE)
                {
                    SPIM_TFT_rxBufferRead = 0u;
                }

                SPIM_TFT_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPIM_TFT_rxBuffer[SPIM_TFT_rxBufferWrite] = rxData;

            tmpStatus = SPIM_TFT_GET_STATUS_RX(SPIM_TFT_swStatusRx);
            SPIM_TFT_swStatusRx = tmpStatus;
        }

    #endif /* (SPIM_TFT_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_TFT_RX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_TFT_RX_ISR_EXIT_CALLBACK
        SPIM_TFT_RX_ISR_ExitCallback();
    #endif /* SPIM_TFT_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */

/*******************************************************************************
* File Name: SPIM_Audio_INT.c
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

#include "SPIM_Audio_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START SPIM_Audio_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPIM_Audio_TX_ISR
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
*  SPIM_Audio_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPIM_Audio_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPIM_Audio_txBuffer[SPIM_Audio_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_Audio_TX_ISR)
{
    #if(SPIM_Audio_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPIM_Audio_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_Audio_TX_ISR_ENTRY_CALLBACK
        SPIM_Audio_TX_ISR_EntryCallback();
    #endif /* SPIM_Audio_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_Audio_TX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_Audio_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(SPIM_Audio_txBufferRead != SPIM_Audio_txBufferWrite)
        {
            tmpStatus = SPIM_Audio_GET_STATUS_TX(SPIM_Audio_swStatusTx);
            SPIM_Audio_swStatusTx = tmpStatus;

            if(0u != (SPIM_Audio_swStatusTx & SPIM_Audio_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == SPIM_Audio_txBufferFull)
                {
                   SPIM_Audio_txBufferRead++;

                    if(SPIM_Audio_txBufferRead >= SPIM_Audio_TX_BUFFER_SIZE)
                    {
                        SPIM_Audio_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPIM_Audio_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG16(SPIM_Audio_TXDATA_PTR, 
                                             SPIM_Audio_txBuffer[SPIM_Audio_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(SPIM_Audio_txBufferRead == SPIM_Audio_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            SPIM_Audio_TX_STATUS_MASK_REG &= ((uint8) ~SPIM_Audio_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (SPIM_Audio_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_Audio_TX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_Audio_TX_ISR_EXIT_CALLBACK
        SPIM_Audio_TX_ISR_ExitCallback();
    #endif /* SPIM_Audio_TX_ISR_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: SPIM_Audio_RX_ISR
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
*  SPIM_Audio_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPIM_Audio_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPIM_Audio_rxBuffer[SPIM_Audio_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIM_Audio_RX_ISR)
{
    #if(SPIM_Audio_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint16 rxData;
    #endif /* (SPIM_Audio_RX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPIM_Audio_RX_ISR_ENTRY_CALLBACK
        SPIM_Audio_RX_ISR_EntryCallback();
    #endif /* SPIM_Audio_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPIM_Audio_RX_ISR_START` */

    /* `#END` */
    
    #if(SPIM_Audio_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = SPIM_Audio_GET_STATUS_RX(SPIM_Audio_swStatusRx);
        SPIM_Audio_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (SPIM_Audio_swStatusRx & SPIM_Audio_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG16(SPIM_Audio_RXDATA_PTR);

            /* Set next pointer. */
            SPIM_Audio_rxBufferWrite++;
            if(SPIM_Audio_rxBufferWrite >= SPIM_Audio_RX_BUFFER_SIZE)
            {
                SPIM_Audio_rxBufferWrite = 0u;
            }

            if(SPIM_Audio_rxBufferWrite == SPIM_Audio_rxBufferRead)
            {
                SPIM_Audio_rxBufferRead++;
                if(SPIM_Audio_rxBufferRead >= SPIM_Audio_RX_BUFFER_SIZE)
                {
                    SPIM_Audio_rxBufferRead = 0u;
                }

                SPIM_Audio_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPIM_Audio_rxBuffer[SPIM_Audio_rxBufferWrite] = rxData;

            tmpStatus = SPIM_Audio_GET_STATUS_RX(SPIM_Audio_swStatusRx);
            SPIM_Audio_swStatusRx = tmpStatus;
        }

    #endif /* (SPIM_Audio_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIM_Audio_RX_ISR_END` */

    /* `#END` */
    
    #ifdef SPIM_Audio_RX_ISR_EXIT_CALLBACK
        SPIM_Audio_RX_ISR_ExitCallback();
    #endif /* SPIM_Audio_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */

/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_SPIM_Audio_H)
#define CY_SPIM_PVT_SPIM_Audio_H

#include "SPIM_Audio.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 SPIM_Audio_swStatusTx;
extern volatile uint8 SPIM_Audio_swStatusRx;

#if(SPIM_Audio_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 SPIM_Audio_txBuffer[SPIM_Audio_TX_BUFFER_SIZE];
    extern volatile uint8 SPIM_Audio_txBufferRead;
    extern volatile uint8 SPIM_Audio_txBufferWrite;
    extern volatile uint8 SPIM_Audio_txBufferFull;
#endif /* (SPIM_Audio_TX_SOFTWARE_BUF_ENABLED) */

#if(SPIM_Audio_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 SPIM_Audio_rxBuffer[SPIM_Audio_RX_BUFFER_SIZE];
    extern volatile uint8 SPIM_Audio_rxBufferRead;
    extern volatile uint8 SPIM_Audio_rxBufferWrite;
    extern volatile uint8 SPIM_Audio_rxBufferFull;
#endif /* (SPIM_Audio_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_SPIM_Audio_H */


/* [] END OF FILE */

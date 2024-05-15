/*******************************************************************************
* File Name: audiotimer_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_audiotimer_isr_H)
#define CY_ISR_audiotimer_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void audiotimer_isr_Start(void);
void audiotimer_isr_StartEx(cyisraddress address);
void audiotimer_isr_Stop(void);

CY_ISR_PROTO(audiotimer_isr_Interrupt);

void audiotimer_isr_SetVector(cyisraddress address);
cyisraddress audiotimer_isr_GetVector(void);

void audiotimer_isr_SetPriority(uint8 priority);
uint8 audiotimer_isr_GetPriority(void);

void audiotimer_isr_Enable(void);
uint8 audiotimer_isr_GetState(void);
void audiotimer_isr_Disable(void);

void audiotimer_isr_SetPending(void);
void audiotimer_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the audiotimer_isr ISR. */
#define audiotimer_isr_INTC_VECTOR            ((reg32 *) audiotimer_isr__INTC_VECT)

/* Address of the audiotimer_isr ISR priority. */
#define audiotimer_isr_INTC_PRIOR             ((reg8 *) audiotimer_isr__INTC_PRIOR_REG)

/* Priority of the audiotimer_isr interrupt. */
#define audiotimer_isr_INTC_PRIOR_NUMBER      audiotimer_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable audiotimer_isr interrupt. */
#define audiotimer_isr_INTC_SET_EN            ((reg32 *) audiotimer_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the audiotimer_isr interrupt. */
#define audiotimer_isr_INTC_CLR_EN            ((reg32 *) audiotimer_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the audiotimer_isr interrupt state to pending. */
#define audiotimer_isr_INTC_SET_PD            ((reg32 *) audiotimer_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the audiotimer_isr interrupt. */
#define audiotimer_isr_INTC_CLR_PD            ((reg32 *) audiotimer_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_audiotimer_isr_H */


/* [] END OF FILE */

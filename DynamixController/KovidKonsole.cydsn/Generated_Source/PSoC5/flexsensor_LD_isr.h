/*******************************************************************************
* File Name: flexsensor_LD_isr.h
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
#if !defined(CY_ISR_flexsensor_LD_isr_H)
#define CY_ISR_flexsensor_LD_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void flexsensor_LD_isr_Start(void);
void flexsensor_LD_isr_StartEx(cyisraddress address);
void flexsensor_LD_isr_Stop(void);

CY_ISR_PROTO(flexsensor_LD_isr_Interrupt);

void flexsensor_LD_isr_SetVector(cyisraddress address);
cyisraddress flexsensor_LD_isr_GetVector(void);

void flexsensor_LD_isr_SetPriority(uint8 priority);
uint8 flexsensor_LD_isr_GetPriority(void);

void flexsensor_LD_isr_Enable(void);
uint8 flexsensor_LD_isr_GetState(void);
void flexsensor_LD_isr_Disable(void);

void flexsensor_LD_isr_SetPending(void);
void flexsensor_LD_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the flexsensor_LD_isr ISR. */
#define flexsensor_LD_isr_INTC_VECTOR            ((reg32 *) flexsensor_LD_isr__INTC_VECT)

/* Address of the flexsensor_LD_isr ISR priority. */
#define flexsensor_LD_isr_INTC_PRIOR             ((reg8 *) flexsensor_LD_isr__INTC_PRIOR_REG)

/* Priority of the flexsensor_LD_isr interrupt. */
#define flexsensor_LD_isr_INTC_PRIOR_NUMBER      flexsensor_LD_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable flexsensor_LD_isr interrupt. */
#define flexsensor_LD_isr_INTC_SET_EN            ((reg32 *) flexsensor_LD_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the flexsensor_LD_isr interrupt. */
#define flexsensor_LD_isr_INTC_CLR_EN            ((reg32 *) flexsensor_LD_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the flexsensor_LD_isr interrupt state to pending. */
#define flexsensor_LD_isr_INTC_SET_PD            ((reg32 *) flexsensor_LD_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the flexsensor_LD_isr interrupt. */
#define flexsensor_LD_isr_INTC_CLR_PD            ((reg32 *) flexsensor_LD_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_flexsensor_LD_isr_H */


/* [] END OF FILE */

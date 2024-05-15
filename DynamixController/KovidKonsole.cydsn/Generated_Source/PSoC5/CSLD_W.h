/*******************************************************************************
* File Name: CSLD_W.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CSLD_W_H) /* Pins CSLD_W_H */
#define CY_PINS_CSLD_W_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CSLD_W_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CSLD_W__PORT == 15 && ((CSLD_W__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CSLD_W_Write(uint8 value);
void    CSLD_W_SetDriveMode(uint8 mode);
uint8   CSLD_W_ReadDataReg(void);
uint8   CSLD_W_Read(void);
void    CSLD_W_SetInterruptMode(uint16 position, uint16 mode);
uint8   CSLD_W_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CSLD_W_SetDriveMode() function.
     *  @{
     */
        #define CSLD_W_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CSLD_W_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CSLD_W_DM_RES_UP          PIN_DM_RES_UP
        #define CSLD_W_DM_RES_DWN         PIN_DM_RES_DWN
        #define CSLD_W_DM_OD_LO           PIN_DM_OD_LO
        #define CSLD_W_DM_OD_HI           PIN_DM_OD_HI
        #define CSLD_W_DM_STRONG          PIN_DM_STRONG
        #define CSLD_W_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CSLD_W_MASK               CSLD_W__MASK
#define CSLD_W_SHIFT              CSLD_W__SHIFT
#define CSLD_W_WIDTH              1u

/* Interrupt constants */
#if defined(CSLD_W__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CSLD_W_SetInterruptMode() function.
     *  @{
     */
        #define CSLD_W_INTR_NONE      (uint16)(0x0000u)
        #define CSLD_W_INTR_RISING    (uint16)(0x0001u)
        #define CSLD_W_INTR_FALLING   (uint16)(0x0002u)
        #define CSLD_W_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CSLD_W_INTR_MASK      (0x01u) 
#endif /* (CSLD_W__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CSLD_W_PS                     (* (reg8 *) CSLD_W__PS)
/* Data Register */
#define CSLD_W_DR                     (* (reg8 *) CSLD_W__DR)
/* Port Number */
#define CSLD_W_PRT_NUM                (* (reg8 *) CSLD_W__PRT) 
/* Connect to Analog Globals */                                                  
#define CSLD_W_AG                     (* (reg8 *) CSLD_W__AG)                       
/* Analog MUX bux enable */
#define CSLD_W_AMUX                   (* (reg8 *) CSLD_W__AMUX) 
/* Bidirectional Enable */                                                        
#define CSLD_W_BIE                    (* (reg8 *) CSLD_W__BIE)
/* Bit-mask for Aliased Register Access */
#define CSLD_W_BIT_MASK               (* (reg8 *) CSLD_W__BIT_MASK)
/* Bypass Enable */
#define CSLD_W_BYP                    (* (reg8 *) CSLD_W__BYP)
/* Port wide control signals */                                                   
#define CSLD_W_CTL                    (* (reg8 *) CSLD_W__CTL)
/* Drive Modes */
#define CSLD_W_DM0                    (* (reg8 *) CSLD_W__DM0) 
#define CSLD_W_DM1                    (* (reg8 *) CSLD_W__DM1)
#define CSLD_W_DM2                    (* (reg8 *) CSLD_W__DM2) 
/* Input Buffer Disable Override */
#define CSLD_W_INP_DIS                (* (reg8 *) CSLD_W__INP_DIS)
/* LCD Common or Segment Drive */
#define CSLD_W_LCD_COM_SEG            (* (reg8 *) CSLD_W__LCD_COM_SEG)
/* Enable Segment LCD */
#define CSLD_W_LCD_EN                 (* (reg8 *) CSLD_W__LCD_EN)
/* Slew Rate Control */
#define CSLD_W_SLW                    (* (reg8 *) CSLD_W__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CSLD_W_PRTDSI__CAPS_SEL       (* (reg8 *) CSLD_W__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CSLD_W_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CSLD_W__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CSLD_W_PRTDSI__OE_SEL0        (* (reg8 *) CSLD_W__PRTDSI__OE_SEL0) 
#define CSLD_W_PRTDSI__OE_SEL1        (* (reg8 *) CSLD_W__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CSLD_W_PRTDSI__OUT_SEL0       (* (reg8 *) CSLD_W__PRTDSI__OUT_SEL0) 
#define CSLD_W_PRTDSI__OUT_SEL1       (* (reg8 *) CSLD_W__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CSLD_W_PRTDSI__SYNC_OUT       (* (reg8 *) CSLD_W__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CSLD_W__SIO_CFG)
    #define CSLD_W_SIO_HYST_EN        (* (reg8 *) CSLD_W__SIO_HYST_EN)
    #define CSLD_W_SIO_REG_HIFREQ     (* (reg8 *) CSLD_W__SIO_REG_HIFREQ)
    #define CSLD_W_SIO_CFG            (* (reg8 *) CSLD_W__SIO_CFG)
    #define CSLD_W_SIO_DIFF           (* (reg8 *) CSLD_W__SIO_DIFF)
#endif /* (CSLD_W__SIO_CFG) */

/* Interrupt Registers */
#if defined(CSLD_W__INTSTAT)
    #define CSLD_W_INTSTAT            (* (reg8 *) CSLD_W__INTSTAT)
    #define CSLD_W_SNAP               (* (reg8 *) CSLD_W__SNAP)
    
	#define CSLD_W_0_INTTYPE_REG 		(* (reg8 *) CSLD_W__0__INTTYPE)
#endif /* (CSLD_W__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CSLD_W_H */


/* [] END OF FILE */

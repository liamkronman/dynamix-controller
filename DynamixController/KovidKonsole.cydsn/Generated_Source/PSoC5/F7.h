/*******************************************************************************
* File Name: F7.h  
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

#if !defined(CY_PINS_F7_H) /* Pins F7_H */
#define CY_PINS_F7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F7_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F7__PORT == 15 && ((F7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F7_Write(uint8 value);
void    F7_SetDriveMode(uint8 mode);
uint8   F7_ReadDataReg(void);
uint8   F7_Read(void);
void    F7_SetInterruptMode(uint16 position, uint16 mode);
uint8   F7_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F7_SetDriveMode() function.
     *  @{
     */
        #define F7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F7_DM_RES_UP          PIN_DM_RES_UP
        #define F7_DM_RES_DWN         PIN_DM_RES_DWN
        #define F7_DM_OD_LO           PIN_DM_OD_LO
        #define F7_DM_OD_HI           PIN_DM_OD_HI
        #define F7_DM_STRONG          PIN_DM_STRONG
        #define F7_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F7_MASK               F7__MASK
#define F7_SHIFT              F7__SHIFT
#define F7_WIDTH              1u

/* Interrupt constants */
#if defined(F7__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F7_SetInterruptMode() function.
     *  @{
     */
        #define F7_INTR_NONE      (uint16)(0x0000u)
        #define F7_INTR_RISING    (uint16)(0x0001u)
        #define F7_INTR_FALLING   (uint16)(0x0002u)
        #define F7_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F7_INTR_MASK      (0x01u) 
#endif /* (F7__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F7_PS                     (* (reg8 *) F7__PS)
/* Data Register */
#define F7_DR                     (* (reg8 *) F7__DR)
/* Port Number */
#define F7_PRT_NUM                (* (reg8 *) F7__PRT) 
/* Connect to Analog Globals */                                                  
#define F7_AG                     (* (reg8 *) F7__AG)                       
/* Analog MUX bux enable */
#define F7_AMUX                   (* (reg8 *) F7__AMUX) 
/* Bidirectional Enable */                                                        
#define F7_BIE                    (* (reg8 *) F7__BIE)
/* Bit-mask for Aliased Register Access */
#define F7_BIT_MASK               (* (reg8 *) F7__BIT_MASK)
/* Bypass Enable */
#define F7_BYP                    (* (reg8 *) F7__BYP)
/* Port wide control signals */                                                   
#define F7_CTL                    (* (reg8 *) F7__CTL)
/* Drive Modes */
#define F7_DM0                    (* (reg8 *) F7__DM0) 
#define F7_DM1                    (* (reg8 *) F7__DM1)
#define F7_DM2                    (* (reg8 *) F7__DM2) 
/* Input Buffer Disable Override */
#define F7_INP_DIS                (* (reg8 *) F7__INP_DIS)
/* LCD Common or Segment Drive */
#define F7_LCD_COM_SEG            (* (reg8 *) F7__LCD_COM_SEG)
/* Enable Segment LCD */
#define F7_LCD_EN                 (* (reg8 *) F7__LCD_EN)
/* Slew Rate Control */
#define F7_SLW                    (* (reg8 *) F7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F7_PRTDSI__CAPS_SEL       (* (reg8 *) F7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F7_PRTDSI__OE_SEL0        (* (reg8 *) F7__PRTDSI__OE_SEL0) 
#define F7_PRTDSI__OE_SEL1        (* (reg8 *) F7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F7_PRTDSI__OUT_SEL0       (* (reg8 *) F7__PRTDSI__OUT_SEL0) 
#define F7_PRTDSI__OUT_SEL1       (* (reg8 *) F7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F7_PRTDSI__SYNC_OUT       (* (reg8 *) F7__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F7__SIO_CFG)
    #define F7_SIO_HYST_EN        (* (reg8 *) F7__SIO_HYST_EN)
    #define F7_SIO_REG_HIFREQ     (* (reg8 *) F7__SIO_REG_HIFREQ)
    #define F7_SIO_CFG            (* (reg8 *) F7__SIO_CFG)
    #define F7_SIO_DIFF           (* (reg8 *) F7__SIO_DIFF)
#endif /* (F7__SIO_CFG) */

/* Interrupt Registers */
#if defined(F7__INTSTAT)
    #define F7_INTSTAT            (* (reg8 *) F7__INTSTAT)
    #define F7_SNAP               (* (reg8 *) F7__SNAP)
    
	#define F7_0_INTTYPE_REG 		(* (reg8 *) F7__0__INTTYPE)
#endif /* (F7__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F7_H */


/* [] END OF FILE */

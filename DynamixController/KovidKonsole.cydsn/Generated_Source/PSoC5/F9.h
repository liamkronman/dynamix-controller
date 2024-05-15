/*******************************************************************************
* File Name: F9.h  
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

#if !defined(CY_PINS_F9_H) /* Pins F9_H */
#define CY_PINS_F9_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F9_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F9__PORT == 15 && ((F9__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F9_Write(uint8 value);
void    F9_SetDriveMode(uint8 mode);
uint8   F9_ReadDataReg(void);
uint8   F9_Read(void);
void    F9_SetInterruptMode(uint16 position, uint16 mode);
uint8   F9_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F9_SetDriveMode() function.
     *  @{
     */
        #define F9_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F9_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F9_DM_RES_UP          PIN_DM_RES_UP
        #define F9_DM_RES_DWN         PIN_DM_RES_DWN
        #define F9_DM_OD_LO           PIN_DM_OD_LO
        #define F9_DM_OD_HI           PIN_DM_OD_HI
        #define F9_DM_STRONG          PIN_DM_STRONG
        #define F9_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F9_MASK               F9__MASK
#define F9_SHIFT              F9__SHIFT
#define F9_WIDTH              1u

/* Interrupt constants */
#if defined(F9__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F9_SetInterruptMode() function.
     *  @{
     */
        #define F9_INTR_NONE      (uint16)(0x0000u)
        #define F9_INTR_RISING    (uint16)(0x0001u)
        #define F9_INTR_FALLING   (uint16)(0x0002u)
        #define F9_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F9_INTR_MASK      (0x01u) 
#endif /* (F9__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F9_PS                     (* (reg8 *) F9__PS)
/* Data Register */
#define F9_DR                     (* (reg8 *) F9__DR)
/* Port Number */
#define F9_PRT_NUM                (* (reg8 *) F9__PRT) 
/* Connect to Analog Globals */                                                  
#define F9_AG                     (* (reg8 *) F9__AG)                       
/* Analog MUX bux enable */
#define F9_AMUX                   (* (reg8 *) F9__AMUX) 
/* Bidirectional Enable */                                                        
#define F9_BIE                    (* (reg8 *) F9__BIE)
/* Bit-mask for Aliased Register Access */
#define F9_BIT_MASK               (* (reg8 *) F9__BIT_MASK)
/* Bypass Enable */
#define F9_BYP                    (* (reg8 *) F9__BYP)
/* Port wide control signals */                                                   
#define F9_CTL                    (* (reg8 *) F9__CTL)
/* Drive Modes */
#define F9_DM0                    (* (reg8 *) F9__DM0) 
#define F9_DM1                    (* (reg8 *) F9__DM1)
#define F9_DM2                    (* (reg8 *) F9__DM2) 
/* Input Buffer Disable Override */
#define F9_INP_DIS                (* (reg8 *) F9__INP_DIS)
/* LCD Common or Segment Drive */
#define F9_LCD_COM_SEG            (* (reg8 *) F9__LCD_COM_SEG)
/* Enable Segment LCD */
#define F9_LCD_EN                 (* (reg8 *) F9__LCD_EN)
/* Slew Rate Control */
#define F9_SLW                    (* (reg8 *) F9__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F9_PRTDSI__CAPS_SEL       (* (reg8 *) F9__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F9_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F9__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F9_PRTDSI__OE_SEL0        (* (reg8 *) F9__PRTDSI__OE_SEL0) 
#define F9_PRTDSI__OE_SEL1        (* (reg8 *) F9__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F9_PRTDSI__OUT_SEL0       (* (reg8 *) F9__PRTDSI__OUT_SEL0) 
#define F9_PRTDSI__OUT_SEL1       (* (reg8 *) F9__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F9_PRTDSI__SYNC_OUT       (* (reg8 *) F9__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F9__SIO_CFG)
    #define F9_SIO_HYST_EN        (* (reg8 *) F9__SIO_HYST_EN)
    #define F9_SIO_REG_HIFREQ     (* (reg8 *) F9__SIO_REG_HIFREQ)
    #define F9_SIO_CFG            (* (reg8 *) F9__SIO_CFG)
    #define F9_SIO_DIFF           (* (reg8 *) F9__SIO_DIFF)
#endif /* (F9__SIO_CFG) */

/* Interrupt Registers */
#if defined(F9__INTSTAT)
    #define F9_INTSTAT            (* (reg8 *) F9__INTSTAT)
    #define F9_SNAP               (* (reg8 *) F9__SNAP)
    
	#define F9_0_INTTYPE_REG 		(* (reg8 *) F9__0__INTTYPE)
#endif /* (F9__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F9_H */


/* [] END OF FILE */

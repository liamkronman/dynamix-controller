/*******************************************************************************
* File Name: F0.h  
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

#if !defined(CY_PINS_F0_H) /* Pins F0_H */
#define CY_PINS_F0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F0__PORT == 15 && ((F0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F0_Write(uint8 value);
void    F0_SetDriveMode(uint8 mode);
uint8   F0_ReadDataReg(void);
uint8   F0_Read(void);
void    F0_SetInterruptMode(uint16 position, uint16 mode);
uint8   F0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F0_SetDriveMode() function.
     *  @{
     */
        #define F0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F0_DM_RES_UP          PIN_DM_RES_UP
        #define F0_DM_RES_DWN         PIN_DM_RES_DWN
        #define F0_DM_OD_LO           PIN_DM_OD_LO
        #define F0_DM_OD_HI           PIN_DM_OD_HI
        #define F0_DM_STRONG          PIN_DM_STRONG
        #define F0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F0_MASK               F0__MASK
#define F0_SHIFT              F0__SHIFT
#define F0_WIDTH              1u

/* Interrupt constants */
#if defined(F0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F0_SetInterruptMode() function.
     *  @{
     */
        #define F0_INTR_NONE      (uint16)(0x0000u)
        #define F0_INTR_RISING    (uint16)(0x0001u)
        #define F0_INTR_FALLING   (uint16)(0x0002u)
        #define F0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F0_INTR_MASK      (0x01u) 
#endif /* (F0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F0_PS                     (* (reg8 *) F0__PS)
/* Data Register */
#define F0_DR                     (* (reg8 *) F0__DR)
/* Port Number */
#define F0_PRT_NUM                (* (reg8 *) F0__PRT) 
/* Connect to Analog Globals */                                                  
#define F0_AG                     (* (reg8 *) F0__AG)                       
/* Analog MUX bux enable */
#define F0_AMUX                   (* (reg8 *) F0__AMUX) 
/* Bidirectional Enable */                                                        
#define F0_BIE                    (* (reg8 *) F0__BIE)
/* Bit-mask for Aliased Register Access */
#define F0_BIT_MASK               (* (reg8 *) F0__BIT_MASK)
/* Bypass Enable */
#define F0_BYP                    (* (reg8 *) F0__BYP)
/* Port wide control signals */                                                   
#define F0_CTL                    (* (reg8 *) F0__CTL)
/* Drive Modes */
#define F0_DM0                    (* (reg8 *) F0__DM0) 
#define F0_DM1                    (* (reg8 *) F0__DM1)
#define F0_DM2                    (* (reg8 *) F0__DM2) 
/* Input Buffer Disable Override */
#define F0_INP_DIS                (* (reg8 *) F0__INP_DIS)
/* LCD Common or Segment Drive */
#define F0_LCD_COM_SEG            (* (reg8 *) F0__LCD_COM_SEG)
/* Enable Segment LCD */
#define F0_LCD_EN                 (* (reg8 *) F0__LCD_EN)
/* Slew Rate Control */
#define F0_SLW                    (* (reg8 *) F0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F0_PRTDSI__CAPS_SEL       (* (reg8 *) F0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F0_PRTDSI__OE_SEL0        (* (reg8 *) F0__PRTDSI__OE_SEL0) 
#define F0_PRTDSI__OE_SEL1        (* (reg8 *) F0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F0_PRTDSI__OUT_SEL0       (* (reg8 *) F0__PRTDSI__OUT_SEL0) 
#define F0_PRTDSI__OUT_SEL1       (* (reg8 *) F0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F0_PRTDSI__SYNC_OUT       (* (reg8 *) F0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F0__SIO_CFG)
    #define F0_SIO_HYST_EN        (* (reg8 *) F0__SIO_HYST_EN)
    #define F0_SIO_REG_HIFREQ     (* (reg8 *) F0__SIO_REG_HIFREQ)
    #define F0_SIO_CFG            (* (reg8 *) F0__SIO_CFG)
    #define F0_SIO_DIFF           (* (reg8 *) F0__SIO_DIFF)
#endif /* (F0__SIO_CFG) */

/* Interrupt Registers */
#if defined(F0__INTSTAT)
    #define F0_INTSTAT            (* (reg8 *) F0__INTSTAT)
    #define F0_SNAP               (* (reg8 *) F0__SNAP)
    
	#define F0_0_INTTYPE_REG 		(* (reg8 *) F0__0__INTTYPE)
#endif /* (F0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F0_H */


/* [] END OF FILE */

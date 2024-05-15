/*******************************************************************************
* File Name: F8.h  
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

#if !defined(CY_PINS_F8_H) /* Pins F8_H */
#define CY_PINS_F8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F8_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F8__PORT == 15 && ((F8__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F8_Write(uint8 value);
void    F8_SetDriveMode(uint8 mode);
uint8   F8_ReadDataReg(void);
uint8   F8_Read(void);
void    F8_SetInterruptMode(uint16 position, uint16 mode);
uint8   F8_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F8_SetDriveMode() function.
     *  @{
     */
        #define F8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F8_DM_RES_UP          PIN_DM_RES_UP
        #define F8_DM_RES_DWN         PIN_DM_RES_DWN
        #define F8_DM_OD_LO           PIN_DM_OD_LO
        #define F8_DM_OD_HI           PIN_DM_OD_HI
        #define F8_DM_STRONG          PIN_DM_STRONG
        #define F8_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F8_MASK               F8__MASK
#define F8_SHIFT              F8__SHIFT
#define F8_WIDTH              1u

/* Interrupt constants */
#if defined(F8__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F8_SetInterruptMode() function.
     *  @{
     */
        #define F8_INTR_NONE      (uint16)(0x0000u)
        #define F8_INTR_RISING    (uint16)(0x0001u)
        #define F8_INTR_FALLING   (uint16)(0x0002u)
        #define F8_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F8_INTR_MASK      (0x01u) 
#endif /* (F8__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F8_PS                     (* (reg8 *) F8__PS)
/* Data Register */
#define F8_DR                     (* (reg8 *) F8__DR)
/* Port Number */
#define F8_PRT_NUM                (* (reg8 *) F8__PRT) 
/* Connect to Analog Globals */                                                  
#define F8_AG                     (* (reg8 *) F8__AG)                       
/* Analog MUX bux enable */
#define F8_AMUX                   (* (reg8 *) F8__AMUX) 
/* Bidirectional Enable */                                                        
#define F8_BIE                    (* (reg8 *) F8__BIE)
/* Bit-mask for Aliased Register Access */
#define F8_BIT_MASK               (* (reg8 *) F8__BIT_MASK)
/* Bypass Enable */
#define F8_BYP                    (* (reg8 *) F8__BYP)
/* Port wide control signals */                                                   
#define F8_CTL                    (* (reg8 *) F8__CTL)
/* Drive Modes */
#define F8_DM0                    (* (reg8 *) F8__DM0) 
#define F8_DM1                    (* (reg8 *) F8__DM1)
#define F8_DM2                    (* (reg8 *) F8__DM2) 
/* Input Buffer Disable Override */
#define F8_INP_DIS                (* (reg8 *) F8__INP_DIS)
/* LCD Common or Segment Drive */
#define F8_LCD_COM_SEG            (* (reg8 *) F8__LCD_COM_SEG)
/* Enable Segment LCD */
#define F8_LCD_EN                 (* (reg8 *) F8__LCD_EN)
/* Slew Rate Control */
#define F8_SLW                    (* (reg8 *) F8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F8_PRTDSI__CAPS_SEL       (* (reg8 *) F8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F8_PRTDSI__OE_SEL0        (* (reg8 *) F8__PRTDSI__OE_SEL0) 
#define F8_PRTDSI__OE_SEL1        (* (reg8 *) F8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F8_PRTDSI__OUT_SEL0       (* (reg8 *) F8__PRTDSI__OUT_SEL0) 
#define F8_PRTDSI__OUT_SEL1       (* (reg8 *) F8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F8_PRTDSI__SYNC_OUT       (* (reg8 *) F8__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F8__SIO_CFG)
    #define F8_SIO_HYST_EN        (* (reg8 *) F8__SIO_HYST_EN)
    #define F8_SIO_REG_HIFREQ     (* (reg8 *) F8__SIO_REG_HIFREQ)
    #define F8_SIO_CFG            (* (reg8 *) F8__SIO_CFG)
    #define F8_SIO_DIFF           (* (reg8 *) F8__SIO_DIFF)
#endif /* (F8__SIO_CFG) */

/* Interrupt Registers */
#if defined(F8__INTSTAT)
    #define F8_INTSTAT            (* (reg8 *) F8__INTSTAT)
    #define F8_SNAP               (* (reg8 *) F8__SNAP)
    
	#define F8_0_INTTYPE_REG 		(* (reg8 *) F8__0__INTTYPE)
#endif /* (F8__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F8_H */


/* [] END OF FILE */

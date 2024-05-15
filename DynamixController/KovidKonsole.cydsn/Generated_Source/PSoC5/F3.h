/*******************************************************************************
* File Name: F3.h  
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

#if !defined(CY_PINS_F3_H) /* Pins F3_H */
#define CY_PINS_F3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F3__PORT == 15 && ((F3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F3_Write(uint8 value);
void    F3_SetDriveMode(uint8 mode);
uint8   F3_ReadDataReg(void);
uint8   F3_Read(void);
void    F3_SetInterruptMode(uint16 position, uint16 mode);
uint8   F3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F3_SetDriveMode() function.
     *  @{
     */
        #define F3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F3_DM_RES_UP          PIN_DM_RES_UP
        #define F3_DM_RES_DWN         PIN_DM_RES_DWN
        #define F3_DM_OD_LO           PIN_DM_OD_LO
        #define F3_DM_OD_HI           PIN_DM_OD_HI
        #define F3_DM_STRONG          PIN_DM_STRONG
        #define F3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F3_MASK               F3__MASK
#define F3_SHIFT              F3__SHIFT
#define F3_WIDTH              1u

/* Interrupt constants */
#if defined(F3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F3_SetInterruptMode() function.
     *  @{
     */
        #define F3_INTR_NONE      (uint16)(0x0000u)
        #define F3_INTR_RISING    (uint16)(0x0001u)
        #define F3_INTR_FALLING   (uint16)(0x0002u)
        #define F3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F3_INTR_MASK      (0x01u) 
#endif /* (F3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F3_PS                     (* (reg8 *) F3__PS)
/* Data Register */
#define F3_DR                     (* (reg8 *) F3__DR)
/* Port Number */
#define F3_PRT_NUM                (* (reg8 *) F3__PRT) 
/* Connect to Analog Globals */                                                  
#define F3_AG                     (* (reg8 *) F3__AG)                       
/* Analog MUX bux enable */
#define F3_AMUX                   (* (reg8 *) F3__AMUX) 
/* Bidirectional Enable */                                                        
#define F3_BIE                    (* (reg8 *) F3__BIE)
/* Bit-mask for Aliased Register Access */
#define F3_BIT_MASK               (* (reg8 *) F3__BIT_MASK)
/* Bypass Enable */
#define F3_BYP                    (* (reg8 *) F3__BYP)
/* Port wide control signals */                                                   
#define F3_CTL                    (* (reg8 *) F3__CTL)
/* Drive Modes */
#define F3_DM0                    (* (reg8 *) F3__DM0) 
#define F3_DM1                    (* (reg8 *) F3__DM1)
#define F3_DM2                    (* (reg8 *) F3__DM2) 
/* Input Buffer Disable Override */
#define F3_INP_DIS                (* (reg8 *) F3__INP_DIS)
/* LCD Common or Segment Drive */
#define F3_LCD_COM_SEG            (* (reg8 *) F3__LCD_COM_SEG)
/* Enable Segment LCD */
#define F3_LCD_EN                 (* (reg8 *) F3__LCD_EN)
/* Slew Rate Control */
#define F3_SLW                    (* (reg8 *) F3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F3_PRTDSI__CAPS_SEL       (* (reg8 *) F3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F3_PRTDSI__OE_SEL0        (* (reg8 *) F3__PRTDSI__OE_SEL0) 
#define F3_PRTDSI__OE_SEL1        (* (reg8 *) F3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F3_PRTDSI__OUT_SEL0       (* (reg8 *) F3__PRTDSI__OUT_SEL0) 
#define F3_PRTDSI__OUT_SEL1       (* (reg8 *) F3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F3_PRTDSI__SYNC_OUT       (* (reg8 *) F3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F3__SIO_CFG)
    #define F3_SIO_HYST_EN        (* (reg8 *) F3__SIO_HYST_EN)
    #define F3_SIO_REG_HIFREQ     (* (reg8 *) F3__SIO_REG_HIFREQ)
    #define F3_SIO_CFG            (* (reg8 *) F3__SIO_CFG)
    #define F3_SIO_DIFF           (* (reg8 *) F3__SIO_DIFF)
#endif /* (F3__SIO_CFG) */

/* Interrupt Registers */
#if defined(F3__INTSTAT)
    #define F3_INTSTAT            (* (reg8 *) F3__INTSTAT)
    #define F3_SNAP               (* (reg8 *) F3__SNAP)
    
	#define F3_0_INTTYPE_REG 		(* (reg8 *) F3__0__INTTYPE)
#endif /* (F3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F3_H */


/* [] END OF FILE */

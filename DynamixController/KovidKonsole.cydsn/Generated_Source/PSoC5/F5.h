/*******************************************************************************
* File Name: F5.h  
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

#if !defined(CY_PINS_F5_H) /* Pins F5_H */
#define CY_PINS_F5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F5__PORT == 15 && ((F5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F5_Write(uint8 value);
void    F5_SetDriveMode(uint8 mode);
uint8   F5_ReadDataReg(void);
uint8   F5_Read(void);
void    F5_SetInterruptMode(uint16 position, uint16 mode);
uint8   F5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F5_SetDriveMode() function.
     *  @{
     */
        #define F5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F5_DM_RES_UP          PIN_DM_RES_UP
        #define F5_DM_RES_DWN         PIN_DM_RES_DWN
        #define F5_DM_OD_LO           PIN_DM_OD_LO
        #define F5_DM_OD_HI           PIN_DM_OD_HI
        #define F5_DM_STRONG          PIN_DM_STRONG
        #define F5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F5_MASK               F5__MASK
#define F5_SHIFT              F5__SHIFT
#define F5_WIDTH              1u

/* Interrupt constants */
#if defined(F5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F5_SetInterruptMode() function.
     *  @{
     */
        #define F5_INTR_NONE      (uint16)(0x0000u)
        #define F5_INTR_RISING    (uint16)(0x0001u)
        #define F5_INTR_FALLING   (uint16)(0x0002u)
        #define F5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F5_INTR_MASK      (0x01u) 
#endif /* (F5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F5_PS                     (* (reg8 *) F5__PS)
/* Data Register */
#define F5_DR                     (* (reg8 *) F5__DR)
/* Port Number */
#define F5_PRT_NUM                (* (reg8 *) F5__PRT) 
/* Connect to Analog Globals */                                                  
#define F5_AG                     (* (reg8 *) F5__AG)                       
/* Analog MUX bux enable */
#define F5_AMUX                   (* (reg8 *) F5__AMUX) 
/* Bidirectional Enable */                                                        
#define F5_BIE                    (* (reg8 *) F5__BIE)
/* Bit-mask for Aliased Register Access */
#define F5_BIT_MASK               (* (reg8 *) F5__BIT_MASK)
/* Bypass Enable */
#define F5_BYP                    (* (reg8 *) F5__BYP)
/* Port wide control signals */                                                   
#define F5_CTL                    (* (reg8 *) F5__CTL)
/* Drive Modes */
#define F5_DM0                    (* (reg8 *) F5__DM0) 
#define F5_DM1                    (* (reg8 *) F5__DM1)
#define F5_DM2                    (* (reg8 *) F5__DM2) 
/* Input Buffer Disable Override */
#define F5_INP_DIS                (* (reg8 *) F5__INP_DIS)
/* LCD Common or Segment Drive */
#define F5_LCD_COM_SEG            (* (reg8 *) F5__LCD_COM_SEG)
/* Enable Segment LCD */
#define F5_LCD_EN                 (* (reg8 *) F5__LCD_EN)
/* Slew Rate Control */
#define F5_SLW                    (* (reg8 *) F5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F5_PRTDSI__CAPS_SEL       (* (reg8 *) F5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F5_PRTDSI__OE_SEL0        (* (reg8 *) F5__PRTDSI__OE_SEL0) 
#define F5_PRTDSI__OE_SEL1        (* (reg8 *) F5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F5_PRTDSI__OUT_SEL0       (* (reg8 *) F5__PRTDSI__OUT_SEL0) 
#define F5_PRTDSI__OUT_SEL1       (* (reg8 *) F5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F5_PRTDSI__SYNC_OUT       (* (reg8 *) F5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F5__SIO_CFG)
    #define F5_SIO_HYST_EN        (* (reg8 *) F5__SIO_HYST_EN)
    #define F5_SIO_REG_HIFREQ     (* (reg8 *) F5__SIO_REG_HIFREQ)
    #define F5_SIO_CFG            (* (reg8 *) F5__SIO_CFG)
    #define F5_SIO_DIFF           (* (reg8 *) F5__SIO_DIFF)
#endif /* (F5__SIO_CFG) */

/* Interrupt Registers */
#if defined(F5__INTSTAT)
    #define F5_INTSTAT            (* (reg8 *) F5__INTSTAT)
    #define F5_SNAP               (* (reg8 *) F5__SNAP)
    
	#define F5_0_INTTYPE_REG 		(* (reg8 *) F5__0__INTTYPE)
#endif /* (F5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F5_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: F4.h  
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

#if !defined(CY_PINS_F4_H) /* Pins F4_H */
#define CY_PINS_F4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F4__PORT == 15 && ((F4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F4_Write(uint8 value);
void    F4_SetDriveMode(uint8 mode);
uint8   F4_ReadDataReg(void);
uint8   F4_Read(void);
void    F4_SetInterruptMode(uint16 position, uint16 mode);
uint8   F4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F4_SetDriveMode() function.
     *  @{
     */
        #define F4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F4_DM_RES_UP          PIN_DM_RES_UP
        #define F4_DM_RES_DWN         PIN_DM_RES_DWN
        #define F4_DM_OD_LO           PIN_DM_OD_LO
        #define F4_DM_OD_HI           PIN_DM_OD_HI
        #define F4_DM_STRONG          PIN_DM_STRONG
        #define F4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F4_MASK               F4__MASK
#define F4_SHIFT              F4__SHIFT
#define F4_WIDTH              1u

/* Interrupt constants */
#if defined(F4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F4_SetInterruptMode() function.
     *  @{
     */
        #define F4_INTR_NONE      (uint16)(0x0000u)
        #define F4_INTR_RISING    (uint16)(0x0001u)
        #define F4_INTR_FALLING   (uint16)(0x0002u)
        #define F4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F4_INTR_MASK      (0x01u) 
#endif /* (F4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F4_PS                     (* (reg8 *) F4__PS)
/* Data Register */
#define F4_DR                     (* (reg8 *) F4__DR)
/* Port Number */
#define F4_PRT_NUM                (* (reg8 *) F4__PRT) 
/* Connect to Analog Globals */                                                  
#define F4_AG                     (* (reg8 *) F4__AG)                       
/* Analog MUX bux enable */
#define F4_AMUX                   (* (reg8 *) F4__AMUX) 
/* Bidirectional Enable */                                                        
#define F4_BIE                    (* (reg8 *) F4__BIE)
/* Bit-mask for Aliased Register Access */
#define F4_BIT_MASK               (* (reg8 *) F4__BIT_MASK)
/* Bypass Enable */
#define F4_BYP                    (* (reg8 *) F4__BYP)
/* Port wide control signals */                                                   
#define F4_CTL                    (* (reg8 *) F4__CTL)
/* Drive Modes */
#define F4_DM0                    (* (reg8 *) F4__DM0) 
#define F4_DM1                    (* (reg8 *) F4__DM1)
#define F4_DM2                    (* (reg8 *) F4__DM2) 
/* Input Buffer Disable Override */
#define F4_INP_DIS                (* (reg8 *) F4__INP_DIS)
/* LCD Common or Segment Drive */
#define F4_LCD_COM_SEG            (* (reg8 *) F4__LCD_COM_SEG)
/* Enable Segment LCD */
#define F4_LCD_EN                 (* (reg8 *) F4__LCD_EN)
/* Slew Rate Control */
#define F4_SLW                    (* (reg8 *) F4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F4_PRTDSI__CAPS_SEL       (* (reg8 *) F4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F4_PRTDSI__OE_SEL0        (* (reg8 *) F4__PRTDSI__OE_SEL0) 
#define F4_PRTDSI__OE_SEL1        (* (reg8 *) F4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F4_PRTDSI__OUT_SEL0       (* (reg8 *) F4__PRTDSI__OUT_SEL0) 
#define F4_PRTDSI__OUT_SEL1       (* (reg8 *) F4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F4_PRTDSI__SYNC_OUT       (* (reg8 *) F4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F4__SIO_CFG)
    #define F4_SIO_HYST_EN        (* (reg8 *) F4__SIO_HYST_EN)
    #define F4_SIO_REG_HIFREQ     (* (reg8 *) F4__SIO_REG_HIFREQ)
    #define F4_SIO_CFG            (* (reg8 *) F4__SIO_CFG)
    #define F4_SIO_DIFF           (* (reg8 *) F4__SIO_DIFF)
#endif /* (F4__SIO_CFG) */

/* Interrupt Registers */
#if defined(F4__INTSTAT)
    #define F4_INTSTAT            (* (reg8 *) F4__INTSTAT)
    #define F4_SNAP               (* (reg8 *) F4__SNAP)
    
	#define F4_0_INTTYPE_REG 		(* (reg8 *) F4__0__INTTYPE)
#endif /* (F4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F4_H */


/* [] END OF FILE */

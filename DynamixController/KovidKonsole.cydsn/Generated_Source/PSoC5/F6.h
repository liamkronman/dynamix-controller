/*******************************************************************************
* File Name: F6.h  
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

#if !defined(CY_PINS_F6_H) /* Pins F6_H */
#define CY_PINS_F6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F6__PORT == 15 && ((F6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F6_Write(uint8 value);
void    F6_SetDriveMode(uint8 mode);
uint8   F6_ReadDataReg(void);
uint8   F6_Read(void);
void    F6_SetInterruptMode(uint16 position, uint16 mode);
uint8   F6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F6_SetDriveMode() function.
     *  @{
     */
        #define F6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F6_DM_RES_UP          PIN_DM_RES_UP
        #define F6_DM_RES_DWN         PIN_DM_RES_DWN
        #define F6_DM_OD_LO           PIN_DM_OD_LO
        #define F6_DM_OD_HI           PIN_DM_OD_HI
        #define F6_DM_STRONG          PIN_DM_STRONG
        #define F6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F6_MASK               F6__MASK
#define F6_SHIFT              F6__SHIFT
#define F6_WIDTH              1u

/* Interrupt constants */
#if defined(F6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F6_SetInterruptMode() function.
     *  @{
     */
        #define F6_INTR_NONE      (uint16)(0x0000u)
        #define F6_INTR_RISING    (uint16)(0x0001u)
        #define F6_INTR_FALLING   (uint16)(0x0002u)
        #define F6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F6_INTR_MASK      (0x01u) 
#endif /* (F6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F6_PS                     (* (reg8 *) F6__PS)
/* Data Register */
#define F6_DR                     (* (reg8 *) F6__DR)
/* Port Number */
#define F6_PRT_NUM                (* (reg8 *) F6__PRT) 
/* Connect to Analog Globals */                                                  
#define F6_AG                     (* (reg8 *) F6__AG)                       
/* Analog MUX bux enable */
#define F6_AMUX                   (* (reg8 *) F6__AMUX) 
/* Bidirectional Enable */                                                        
#define F6_BIE                    (* (reg8 *) F6__BIE)
/* Bit-mask for Aliased Register Access */
#define F6_BIT_MASK               (* (reg8 *) F6__BIT_MASK)
/* Bypass Enable */
#define F6_BYP                    (* (reg8 *) F6__BYP)
/* Port wide control signals */                                                   
#define F6_CTL                    (* (reg8 *) F6__CTL)
/* Drive Modes */
#define F6_DM0                    (* (reg8 *) F6__DM0) 
#define F6_DM1                    (* (reg8 *) F6__DM1)
#define F6_DM2                    (* (reg8 *) F6__DM2) 
/* Input Buffer Disable Override */
#define F6_INP_DIS                (* (reg8 *) F6__INP_DIS)
/* LCD Common or Segment Drive */
#define F6_LCD_COM_SEG            (* (reg8 *) F6__LCD_COM_SEG)
/* Enable Segment LCD */
#define F6_LCD_EN                 (* (reg8 *) F6__LCD_EN)
/* Slew Rate Control */
#define F6_SLW                    (* (reg8 *) F6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F6_PRTDSI__CAPS_SEL       (* (reg8 *) F6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F6_PRTDSI__OE_SEL0        (* (reg8 *) F6__PRTDSI__OE_SEL0) 
#define F6_PRTDSI__OE_SEL1        (* (reg8 *) F6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F6_PRTDSI__OUT_SEL0       (* (reg8 *) F6__PRTDSI__OUT_SEL0) 
#define F6_PRTDSI__OUT_SEL1       (* (reg8 *) F6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F6_PRTDSI__SYNC_OUT       (* (reg8 *) F6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F6__SIO_CFG)
    #define F6_SIO_HYST_EN        (* (reg8 *) F6__SIO_HYST_EN)
    #define F6_SIO_REG_HIFREQ     (* (reg8 *) F6__SIO_REG_HIFREQ)
    #define F6_SIO_CFG            (* (reg8 *) F6__SIO_CFG)
    #define F6_SIO_DIFF           (* (reg8 *) F6__SIO_DIFF)
#endif /* (F6__SIO_CFG) */

/* Interrupt Registers */
#if defined(F6__INTSTAT)
    #define F6_INTSTAT            (* (reg8 *) F6__INTSTAT)
    #define F6_SNAP               (* (reg8 *) F6__SNAP)
    
	#define F6_0_INTTYPE_REG 		(* (reg8 *) F6__0__INTTYPE)
#endif /* (F6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F6_H */


/* [] END OF FILE */

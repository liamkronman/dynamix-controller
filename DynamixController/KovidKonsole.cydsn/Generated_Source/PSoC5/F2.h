/*******************************************************************************
* File Name: F2.h  
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

#if !defined(CY_PINS_F2_H) /* Pins F2_H */
#define CY_PINS_F2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F2__PORT == 15 && ((F2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F2_Write(uint8 value);
void    F2_SetDriveMode(uint8 mode);
uint8   F2_ReadDataReg(void);
uint8   F2_Read(void);
void    F2_SetInterruptMode(uint16 position, uint16 mode);
uint8   F2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F2_SetDriveMode() function.
     *  @{
     */
        #define F2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F2_DM_RES_UP          PIN_DM_RES_UP
        #define F2_DM_RES_DWN         PIN_DM_RES_DWN
        #define F2_DM_OD_LO           PIN_DM_OD_LO
        #define F2_DM_OD_HI           PIN_DM_OD_HI
        #define F2_DM_STRONG          PIN_DM_STRONG
        #define F2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F2_MASK               F2__MASK
#define F2_SHIFT              F2__SHIFT
#define F2_WIDTH              1u

/* Interrupt constants */
#if defined(F2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F2_SetInterruptMode() function.
     *  @{
     */
        #define F2_INTR_NONE      (uint16)(0x0000u)
        #define F2_INTR_RISING    (uint16)(0x0001u)
        #define F2_INTR_FALLING   (uint16)(0x0002u)
        #define F2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F2_INTR_MASK      (0x01u) 
#endif /* (F2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F2_PS                     (* (reg8 *) F2__PS)
/* Data Register */
#define F2_DR                     (* (reg8 *) F2__DR)
/* Port Number */
#define F2_PRT_NUM                (* (reg8 *) F2__PRT) 
/* Connect to Analog Globals */                                                  
#define F2_AG                     (* (reg8 *) F2__AG)                       
/* Analog MUX bux enable */
#define F2_AMUX                   (* (reg8 *) F2__AMUX) 
/* Bidirectional Enable */                                                        
#define F2_BIE                    (* (reg8 *) F2__BIE)
/* Bit-mask for Aliased Register Access */
#define F2_BIT_MASK               (* (reg8 *) F2__BIT_MASK)
/* Bypass Enable */
#define F2_BYP                    (* (reg8 *) F2__BYP)
/* Port wide control signals */                                                   
#define F2_CTL                    (* (reg8 *) F2__CTL)
/* Drive Modes */
#define F2_DM0                    (* (reg8 *) F2__DM0) 
#define F2_DM1                    (* (reg8 *) F2__DM1)
#define F2_DM2                    (* (reg8 *) F2__DM2) 
/* Input Buffer Disable Override */
#define F2_INP_DIS                (* (reg8 *) F2__INP_DIS)
/* LCD Common or Segment Drive */
#define F2_LCD_COM_SEG            (* (reg8 *) F2__LCD_COM_SEG)
/* Enable Segment LCD */
#define F2_LCD_EN                 (* (reg8 *) F2__LCD_EN)
/* Slew Rate Control */
#define F2_SLW                    (* (reg8 *) F2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F2_PRTDSI__CAPS_SEL       (* (reg8 *) F2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F2_PRTDSI__OE_SEL0        (* (reg8 *) F2__PRTDSI__OE_SEL0) 
#define F2_PRTDSI__OE_SEL1        (* (reg8 *) F2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F2_PRTDSI__OUT_SEL0       (* (reg8 *) F2__PRTDSI__OUT_SEL0) 
#define F2_PRTDSI__OUT_SEL1       (* (reg8 *) F2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F2_PRTDSI__SYNC_OUT       (* (reg8 *) F2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F2__SIO_CFG)
    #define F2_SIO_HYST_EN        (* (reg8 *) F2__SIO_HYST_EN)
    #define F2_SIO_REG_HIFREQ     (* (reg8 *) F2__SIO_REG_HIFREQ)
    #define F2_SIO_CFG            (* (reg8 *) F2__SIO_CFG)
    #define F2_SIO_DIFF           (* (reg8 *) F2__SIO_DIFF)
#endif /* (F2__SIO_CFG) */

/* Interrupt Registers */
#if defined(F2__INTSTAT)
    #define F2_INTSTAT            (* (reg8 *) F2__INTSTAT)
    #define F2_SNAP               (* (reg8 *) F2__SNAP)
    
	#define F2_0_INTTYPE_REG 		(* (reg8 *) F2__0__INTTYPE)
#endif /* (F2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F2_H */


/* [] END OF FILE */

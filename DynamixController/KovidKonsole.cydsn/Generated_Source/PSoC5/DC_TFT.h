/*******************************************************************************
* File Name: DC_TFT.h  
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

#if !defined(CY_PINS_DC_TFT_H) /* Pins DC_TFT_H */
#define CY_PINS_DC_TFT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DC_TFT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DC_TFT__PORT == 15 && ((DC_TFT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DC_TFT_Write(uint8 value);
void    DC_TFT_SetDriveMode(uint8 mode);
uint8   DC_TFT_ReadDataReg(void);
uint8   DC_TFT_Read(void);
void    DC_TFT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DC_TFT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DC_TFT_SetDriveMode() function.
     *  @{
     */
        #define DC_TFT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DC_TFT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DC_TFT_DM_RES_UP          PIN_DM_RES_UP
        #define DC_TFT_DM_RES_DWN         PIN_DM_RES_DWN
        #define DC_TFT_DM_OD_LO           PIN_DM_OD_LO
        #define DC_TFT_DM_OD_HI           PIN_DM_OD_HI
        #define DC_TFT_DM_STRONG          PIN_DM_STRONG
        #define DC_TFT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DC_TFT_MASK               DC_TFT__MASK
#define DC_TFT_SHIFT              DC_TFT__SHIFT
#define DC_TFT_WIDTH              1u

/* Interrupt constants */
#if defined(DC_TFT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DC_TFT_SetInterruptMode() function.
     *  @{
     */
        #define DC_TFT_INTR_NONE      (uint16)(0x0000u)
        #define DC_TFT_INTR_RISING    (uint16)(0x0001u)
        #define DC_TFT_INTR_FALLING   (uint16)(0x0002u)
        #define DC_TFT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DC_TFT_INTR_MASK      (0x01u) 
#endif /* (DC_TFT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DC_TFT_PS                     (* (reg8 *) DC_TFT__PS)
/* Data Register */
#define DC_TFT_DR                     (* (reg8 *) DC_TFT__DR)
/* Port Number */
#define DC_TFT_PRT_NUM                (* (reg8 *) DC_TFT__PRT) 
/* Connect to Analog Globals */                                                  
#define DC_TFT_AG                     (* (reg8 *) DC_TFT__AG)                       
/* Analog MUX bux enable */
#define DC_TFT_AMUX                   (* (reg8 *) DC_TFT__AMUX) 
/* Bidirectional Enable */                                                        
#define DC_TFT_BIE                    (* (reg8 *) DC_TFT__BIE)
/* Bit-mask for Aliased Register Access */
#define DC_TFT_BIT_MASK               (* (reg8 *) DC_TFT__BIT_MASK)
/* Bypass Enable */
#define DC_TFT_BYP                    (* (reg8 *) DC_TFT__BYP)
/* Port wide control signals */                                                   
#define DC_TFT_CTL                    (* (reg8 *) DC_TFT__CTL)
/* Drive Modes */
#define DC_TFT_DM0                    (* (reg8 *) DC_TFT__DM0) 
#define DC_TFT_DM1                    (* (reg8 *) DC_TFT__DM1)
#define DC_TFT_DM2                    (* (reg8 *) DC_TFT__DM2) 
/* Input Buffer Disable Override */
#define DC_TFT_INP_DIS                (* (reg8 *) DC_TFT__INP_DIS)
/* LCD Common or Segment Drive */
#define DC_TFT_LCD_COM_SEG            (* (reg8 *) DC_TFT__LCD_COM_SEG)
/* Enable Segment LCD */
#define DC_TFT_LCD_EN                 (* (reg8 *) DC_TFT__LCD_EN)
/* Slew Rate Control */
#define DC_TFT_SLW                    (* (reg8 *) DC_TFT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DC_TFT_PRTDSI__CAPS_SEL       (* (reg8 *) DC_TFT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DC_TFT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DC_TFT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DC_TFT_PRTDSI__OE_SEL0        (* (reg8 *) DC_TFT__PRTDSI__OE_SEL0) 
#define DC_TFT_PRTDSI__OE_SEL1        (* (reg8 *) DC_TFT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DC_TFT_PRTDSI__OUT_SEL0       (* (reg8 *) DC_TFT__PRTDSI__OUT_SEL0) 
#define DC_TFT_PRTDSI__OUT_SEL1       (* (reg8 *) DC_TFT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DC_TFT_PRTDSI__SYNC_OUT       (* (reg8 *) DC_TFT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DC_TFT__SIO_CFG)
    #define DC_TFT_SIO_HYST_EN        (* (reg8 *) DC_TFT__SIO_HYST_EN)
    #define DC_TFT_SIO_REG_HIFREQ     (* (reg8 *) DC_TFT__SIO_REG_HIFREQ)
    #define DC_TFT_SIO_CFG            (* (reg8 *) DC_TFT__SIO_CFG)
    #define DC_TFT_SIO_DIFF           (* (reg8 *) DC_TFT__SIO_DIFF)
#endif /* (DC_TFT__SIO_CFG) */

/* Interrupt Registers */
#if defined(DC_TFT__INTSTAT)
    #define DC_TFT_INTSTAT            (* (reg8 *) DC_TFT__INTSTAT)
    #define DC_TFT_SNAP               (* (reg8 *) DC_TFT__SNAP)
    
	#define DC_TFT_0_INTTYPE_REG 		(* (reg8 *) DC_TFT__0__INTTYPE)
#endif /* (DC_TFT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DC_TFT_H */


/* [] END OF FILE */

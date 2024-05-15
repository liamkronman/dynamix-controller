/*******************************************************************************
* File Name: CSLD.h  
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

#if !defined(CY_PINS_CSLD_H) /* Pins CSLD_H */
#define CY_PINS_CSLD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CSLD_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CSLD__PORT == 15 && ((CSLD__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CSLD_Write(uint8 value);
void    CSLD_SetDriveMode(uint8 mode);
uint8   CSLD_ReadDataReg(void);
uint8   CSLD_Read(void);
void    CSLD_SetInterruptMode(uint16 position, uint16 mode);
uint8   CSLD_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CSLD_SetDriveMode() function.
     *  @{
     */
        #define CSLD_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CSLD_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CSLD_DM_RES_UP          PIN_DM_RES_UP
        #define CSLD_DM_RES_DWN         PIN_DM_RES_DWN
        #define CSLD_DM_OD_LO           PIN_DM_OD_LO
        #define CSLD_DM_OD_HI           PIN_DM_OD_HI
        #define CSLD_DM_STRONG          PIN_DM_STRONG
        #define CSLD_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CSLD_MASK               CSLD__MASK
#define CSLD_SHIFT              CSLD__SHIFT
#define CSLD_WIDTH              1u

/* Interrupt constants */
#if defined(CSLD__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CSLD_SetInterruptMode() function.
     *  @{
     */
        #define CSLD_INTR_NONE      (uint16)(0x0000u)
        #define CSLD_INTR_RISING    (uint16)(0x0001u)
        #define CSLD_INTR_FALLING   (uint16)(0x0002u)
        #define CSLD_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CSLD_INTR_MASK      (0x01u) 
#endif /* (CSLD__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CSLD_PS                     (* (reg8 *) CSLD__PS)
/* Data Register */
#define CSLD_DR                     (* (reg8 *) CSLD__DR)
/* Port Number */
#define CSLD_PRT_NUM                (* (reg8 *) CSLD__PRT) 
/* Connect to Analog Globals */                                                  
#define CSLD_AG                     (* (reg8 *) CSLD__AG)                       
/* Analog MUX bux enable */
#define CSLD_AMUX                   (* (reg8 *) CSLD__AMUX) 
/* Bidirectional Enable */                                                        
#define CSLD_BIE                    (* (reg8 *) CSLD__BIE)
/* Bit-mask for Aliased Register Access */
#define CSLD_BIT_MASK               (* (reg8 *) CSLD__BIT_MASK)
/* Bypass Enable */
#define CSLD_BYP                    (* (reg8 *) CSLD__BYP)
/* Port wide control signals */                                                   
#define CSLD_CTL                    (* (reg8 *) CSLD__CTL)
/* Drive Modes */
#define CSLD_DM0                    (* (reg8 *) CSLD__DM0) 
#define CSLD_DM1                    (* (reg8 *) CSLD__DM1)
#define CSLD_DM2                    (* (reg8 *) CSLD__DM2) 
/* Input Buffer Disable Override */
#define CSLD_INP_DIS                (* (reg8 *) CSLD__INP_DIS)
/* LCD Common or Segment Drive */
#define CSLD_LCD_COM_SEG            (* (reg8 *) CSLD__LCD_COM_SEG)
/* Enable Segment LCD */
#define CSLD_LCD_EN                 (* (reg8 *) CSLD__LCD_EN)
/* Slew Rate Control */
#define CSLD_SLW                    (* (reg8 *) CSLD__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CSLD_PRTDSI__CAPS_SEL       (* (reg8 *) CSLD__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CSLD_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CSLD__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CSLD_PRTDSI__OE_SEL0        (* (reg8 *) CSLD__PRTDSI__OE_SEL0) 
#define CSLD_PRTDSI__OE_SEL1        (* (reg8 *) CSLD__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CSLD_PRTDSI__OUT_SEL0       (* (reg8 *) CSLD__PRTDSI__OUT_SEL0) 
#define CSLD_PRTDSI__OUT_SEL1       (* (reg8 *) CSLD__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CSLD_PRTDSI__SYNC_OUT       (* (reg8 *) CSLD__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CSLD__SIO_CFG)
    #define CSLD_SIO_HYST_EN        (* (reg8 *) CSLD__SIO_HYST_EN)
    #define CSLD_SIO_REG_HIFREQ     (* (reg8 *) CSLD__SIO_REG_HIFREQ)
    #define CSLD_SIO_CFG            (* (reg8 *) CSLD__SIO_CFG)
    #define CSLD_SIO_DIFF           (* (reg8 *) CSLD__SIO_DIFF)
#endif /* (CSLD__SIO_CFG) */

/* Interrupt Registers */
#if defined(CSLD__INTSTAT)
    #define CSLD_INTSTAT            (* (reg8 *) CSLD__INTSTAT)
    #define CSLD_SNAP               (* (reg8 *) CSLD__SNAP)
    
	#define CSLD_0_INTTYPE_REG 		(* (reg8 *) CSLD__0__INTTYPE)
#endif /* (CSLD__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CSLD_H */


/* [] END OF FILE */

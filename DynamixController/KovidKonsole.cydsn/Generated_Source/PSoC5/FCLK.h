/*******************************************************************************
* File Name: FCLK.h  
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

#if !defined(CY_PINS_FCLK_H) /* Pins FCLK_H */
#define CY_PINS_FCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FCLK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FCLK__PORT == 15 && ((FCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FCLK_Write(uint8 value);
void    FCLK_SetDriveMode(uint8 mode);
uint8   FCLK_ReadDataReg(void);
uint8   FCLK_Read(void);
void    FCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   FCLK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FCLK_SetDriveMode() function.
     *  @{
     */
        #define FCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FCLK_DM_RES_UP          PIN_DM_RES_UP
        #define FCLK_DM_RES_DWN         PIN_DM_RES_DWN
        #define FCLK_DM_OD_LO           PIN_DM_OD_LO
        #define FCLK_DM_OD_HI           PIN_DM_OD_HI
        #define FCLK_DM_STRONG          PIN_DM_STRONG
        #define FCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FCLK_MASK               FCLK__MASK
#define FCLK_SHIFT              FCLK__SHIFT
#define FCLK_WIDTH              1u

/* Interrupt constants */
#if defined(FCLK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FCLK_SetInterruptMode() function.
     *  @{
     */
        #define FCLK_INTR_NONE      (uint16)(0x0000u)
        #define FCLK_INTR_RISING    (uint16)(0x0001u)
        #define FCLK_INTR_FALLING   (uint16)(0x0002u)
        #define FCLK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FCLK_INTR_MASK      (0x01u) 
#endif /* (FCLK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FCLK_PS                     (* (reg8 *) FCLK__PS)
/* Data Register */
#define FCLK_DR                     (* (reg8 *) FCLK__DR)
/* Port Number */
#define FCLK_PRT_NUM                (* (reg8 *) FCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define FCLK_AG                     (* (reg8 *) FCLK__AG)                       
/* Analog MUX bux enable */
#define FCLK_AMUX                   (* (reg8 *) FCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define FCLK_BIE                    (* (reg8 *) FCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define FCLK_BIT_MASK               (* (reg8 *) FCLK__BIT_MASK)
/* Bypass Enable */
#define FCLK_BYP                    (* (reg8 *) FCLK__BYP)
/* Port wide control signals */                                                   
#define FCLK_CTL                    (* (reg8 *) FCLK__CTL)
/* Drive Modes */
#define FCLK_DM0                    (* (reg8 *) FCLK__DM0) 
#define FCLK_DM1                    (* (reg8 *) FCLK__DM1)
#define FCLK_DM2                    (* (reg8 *) FCLK__DM2) 
/* Input Buffer Disable Override */
#define FCLK_INP_DIS                (* (reg8 *) FCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define FCLK_LCD_COM_SEG            (* (reg8 *) FCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define FCLK_LCD_EN                 (* (reg8 *) FCLK__LCD_EN)
/* Slew Rate Control */
#define FCLK_SLW                    (* (reg8 *) FCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FCLK_PRTDSI__CAPS_SEL       (* (reg8 *) FCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FCLK_PRTDSI__OE_SEL0        (* (reg8 *) FCLK__PRTDSI__OE_SEL0) 
#define FCLK_PRTDSI__OE_SEL1        (* (reg8 *) FCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FCLK_PRTDSI__OUT_SEL0       (* (reg8 *) FCLK__PRTDSI__OUT_SEL0) 
#define FCLK_PRTDSI__OUT_SEL1       (* (reg8 *) FCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FCLK_PRTDSI__SYNC_OUT       (* (reg8 *) FCLK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FCLK__SIO_CFG)
    #define FCLK_SIO_HYST_EN        (* (reg8 *) FCLK__SIO_HYST_EN)
    #define FCLK_SIO_REG_HIFREQ     (* (reg8 *) FCLK__SIO_REG_HIFREQ)
    #define FCLK_SIO_CFG            (* (reg8 *) FCLK__SIO_CFG)
    #define FCLK_SIO_DIFF           (* (reg8 *) FCLK__SIO_DIFF)
#endif /* (FCLK__SIO_CFG) */

/* Interrupt Registers */
#if defined(FCLK__INTSTAT)
    #define FCLK_INTSTAT            (* (reg8 *) FCLK__INTSTAT)
    #define FCLK_SNAP               (* (reg8 *) FCLK__SNAP)
    
	#define FCLK_0_INTTYPE_REG 		(* (reg8 *) FCLK__0__INTTYPE)
#endif /* (FCLK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FCLK_H */


/* [] END OF FILE */

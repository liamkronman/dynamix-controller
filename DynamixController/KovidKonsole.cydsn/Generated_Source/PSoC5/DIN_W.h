/*******************************************************************************
* File Name: DIN_W.h  
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

#if !defined(CY_PINS_DIN_W_H) /* Pins DIN_W_H */
#define CY_PINS_DIN_W_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIN_W_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIN_W__PORT == 15 && ((DIN_W__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIN_W_Write(uint8 value);
void    DIN_W_SetDriveMode(uint8 mode);
uint8   DIN_W_ReadDataReg(void);
uint8   DIN_W_Read(void);
void    DIN_W_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIN_W_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIN_W_SetDriveMode() function.
     *  @{
     */
        #define DIN_W_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIN_W_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIN_W_DM_RES_UP          PIN_DM_RES_UP
        #define DIN_W_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIN_W_DM_OD_LO           PIN_DM_OD_LO
        #define DIN_W_DM_OD_HI           PIN_DM_OD_HI
        #define DIN_W_DM_STRONG          PIN_DM_STRONG
        #define DIN_W_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIN_W_MASK               DIN_W__MASK
#define DIN_W_SHIFT              DIN_W__SHIFT
#define DIN_W_WIDTH              1u

/* Interrupt constants */
#if defined(DIN_W__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIN_W_SetInterruptMode() function.
     *  @{
     */
        #define DIN_W_INTR_NONE      (uint16)(0x0000u)
        #define DIN_W_INTR_RISING    (uint16)(0x0001u)
        #define DIN_W_INTR_FALLING   (uint16)(0x0002u)
        #define DIN_W_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIN_W_INTR_MASK      (0x01u) 
#endif /* (DIN_W__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIN_W_PS                     (* (reg8 *) DIN_W__PS)
/* Data Register */
#define DIN_W_DR                     (* (reg8 *) DIN_W__DR)
/* Port Number */
#define DIN_W_PRT_NUM                (* (reg8 *) DIN_W__PRT) 
/* Connect to Analog Globals */                                                  
#define DIN_W_AG                     (* (reg8 *) DIN_W__AG)                       
/* Analog MUX bux enable */
#define DIN_W_AMUX                   (* (reg8 *) DIN_W__AMUX) 
/* Bidirectional Enable */                                                        
#define DIN_W_BIE                    (* (reg8 *) DIN_W__BIE)
/* Bit-mask for Aliased Register Access */
#define DIN_W_BIT_MASK               (* (reg8 *) DIN_W__BIT_MASK)
/* Bypass Enable */
#define DIN_W_BYP                    (* (reg8 *) DIN_W__BYP)
/* Port wide control signals */                                                   
#define DIN_W_CTL                    (* (reg8 *) DIN_W__CTL)
/* Drive Modes */
#define DIN_W_DM0                    (* (reg8 *) DIN_W__DM0) 
#define DIN_W_DM1                    (* (reg8 *) DIN_W__DM1)
#define DIN_W_DM2                    (* (reg8 *) DIN_W__DM2) 
/* Input Buffer Disable Override */
#define DIN_W_INP_DIS                (* (reg8 *) DIN_W__INP_DIS)
/* LCD Common or Segment Drive */
#define DIN_W_LCD_COM_SEG            (* (reg8 *) DIN_W__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIN_W_LCD_EN                 (* (reg8 *) DIN_W__LCD_EN)
/* Slew Rate Control */
#define DIN_W_SLW                    (* (reg8 *) DIN_W__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIN_W_PRTDSI__CAPS_SEL       (* (reg8 *) DIN_W__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIN_W_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIN_W__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIN_W_PRTDSI__OE_SEL0        (* (reg8 *) DIN_W__PRTDSI__OE_SEL0) 
#define DIN_W_PRTDSI__OE_SEL1        (* (reg8 *) DIN_W__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIN_W_PRTDSI__OUT_SEL0       (* (reg8 *) DIN_W__PRTDSI__OUT_SEL0) 
#define DIN_W_PRTDSI__OUT_SEL1       (* (reg8 *) DIN_W__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIN_W_PRTDSI__SYNC_OUT       (* (reg8 *) DIN_W__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIN_W__SIO_CFG)
    #define DIN_W_SIO_HYST_EN        (* (reg8 *) DIN_W__SIO_HYST_EN)
    #define DIN_W_SIO_REG_HIFREQ     (* (reg8 *) DIN_W__SIO_REG_HIFREQ)
    #define DIN_W_SIO_CFG            (* (reg8 *) DIN_W__SIO_CFG)
    #define DIN_W_SIO_DIFF           (* (reg8 *) DIN_W__SIO_DIFF)
#endif /* (DIN_W__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIN_W__INTSTAT)
    #define DIN_W_INTSTAT            (* (reg8 *) DIN_W__INTSTAT)
    #define DIN_W_SNAP               (* (reg8 *) DIN_W__SNAP)
    
	#define DIN_W_0_INTTYPE_REG 		(* (reg8 *) DIN_W__0__INTTYPE)
#endif /* (DIN_W__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIN_W_H */


/* [] END OF FILE */

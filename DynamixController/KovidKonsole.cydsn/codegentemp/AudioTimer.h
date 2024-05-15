/*******************************************************************************
* File Name: AudioTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_AudioTimer_H)
#define CY_Timer_v2_60_AudioTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 AudioTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define AudioTimer_Resolution                 16u
#define AudioTimer_UsingFixedFunction         1u
#define AudioTimer_UsingHWCaptureCounter      0u
#define AudioTimer_SoftwareCaptureMode        0u
#define AudioTimer_SoftwareTriggerMode        0u
#define AudioTimer_UsingHWEnable              0u
#define AudioTimer_EnableTriggerMode          0u
#define AudioTimer_InterruptOnCaptureCount    0u
#define AudioTimer_RunModeUsed                0u
#define AudioTimer_ControlRegRemoved          0u

#if defined(AudioTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define AudioTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (AudioTimer_UsingFixedFunction)
    #define AudioTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define AudioTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End AudioTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!AudioTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (AudioTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!AudioTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}AudioTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    AudioTimer_Start(void) ;
void    AudioTimer_Stop(void) ;

void    AudioTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   AudioTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define AudioTimer_GetInterruptSource() AudioTimer_ReadStatusRegister()

#if(!AudioTimer_UDB_CONTROL_REG_REMOVED)
    uint8   AudioTimer_ReadControlRegister(void) ;
    void    AudioTimer_WriteControlRegister(uint8 control) ;
#endif /* (!AudioTimer_UDB_CONTROL_REG_REMOVED) */

uint16  AudioTimer_ReadPeriod(void) ;
void    AudioTimer_WritePeriod(uint16 period) ;
uint16  AudioTimer_ReadCounter(void) ;
void    AudioTimer_WriteCounter(uint16 counter) ;
uint16  AudioTimer_ReadCapture(void) ;
void    AudioTimer_SoftwareCapture(void) ;

#if(!AudioTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (AudioTimer_SoftwareCaptureMode)
        void    AudioTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!AudioTimer_UsingFixedFunction) */

    #if (AudioTimer_SoftwareTriggerMode)
        void    AudioTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (AudioTimer_SoftwareTriggerMode) */

    #if (AudioTimer_EnableTriggerMode)
        void    AudioTimer_EnableTrigger(void) ;
        void    AudioTimer_DisableTrigger(void) ;
    #endif /* (AudioTimer_EnableTriggerMode) */


    #if(AudioTimer_InterruptOnCaptureCount)
        void    AudioTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (AudioTimer_InterruptOnCaptureCount) */

    #if (AudioTimer_UsingHWCaptureCounter)
        void    AudioTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   AudioTimer_ReadCaptureCount(void) ;
    #endif /* (AudioTimer_UsingHWCaptureCounter) */

    void AudioTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void AudioTimer_Init(void)          ;
void AudioTimer_Enable(void)        ;
void AudioTimer_SaveConfig(void)    ;
void AudioTimer_RestoreConfig(void) ;
void AudioTimer_Sleep(void)         ;
void AudioTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define AudioTimer__B_TIMER__CM_NONE 0
#define AudioTimer__B_TIMER__CM_RISINGEDGE 1
#define AudioTimer__B_TIMER__CM_FALLINGEDGE 2
#define AudioTimer__B_TIMER__CM_EITHEREDGE 3
#define AudioTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define AudioTimer__B_TIMER__TM_NONE 0x00u
#define AudioTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define AudioTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define AudioTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define AudioTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define AudioTimer_INIT_PERIOD             2176u
#define AudioTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << AudioTimer_CTRL_CAP_MODE_SHIFT))
#define AudioTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << AudioTimer_CTRL_TRIG_MODE_SHIFT))
#if (AudioTimer_UsingFixedFunction)
    #define AudioTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << AudioTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << AudioTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define AudioTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << AudioTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AudioTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AudioTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (AudioTimer_UsingFixedFunction) */
#define AudioTimer_INIT_CAPTURE_COUNT      (2u)
#define AudioTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << AudioTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (AudioTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define AudioTimer_STATUS         (*(reg8 *) AudioTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define AudioTimer_STATUS_MASK    (*(reg8 *) AudioTimer_TimerHW__SR0 )
    #define AudioTimer_CONTROL        (*(reg8 *) AudioTimer_TimerHW__CFG0)
    #define AudioTimer_CONTROL2       (*(reg8 *) AudioTimer_TimerHW__CFG1)
    #define AudioTimer_CONTROL2_PTR   ( (reg8 *) AudioTimer_TimerHW__CFG1)
    #define AudioTimer_RT1            (*(reg8 *) AudioTimer_TimerHW__RT1)
    #define AudioTimer_RT1_PTR        ( (reg8 *) AudioTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define AudioTimer_CONTROL3       (*(reg8 *) AudioTimer_TimerHW__CFG2)
        #define AudioTimer_CONTROL3_PTR   ( (reg8 *) AudioTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define AudioTimer_GLOBAL_ENABLE  (*(reg8 *) AudioTimer_TimerHW__PM_ACT_CFG)
    #define AudioTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) AudioTimer_TimerHW__PM_STBY_CFG)

    #define AudioTimer_CAPTURE_LSB         (* (reg16 *) AudioTimer_TimerHW__CAP0 )
    #define AudioTimer_CAPTURE_LSB_PTR       ((reg16 *) AudioTimer_TimerHW__CAP0 )
    #define AudioTimer_PERIOD_LSB          (* (reg16 *) AudioTimer_TimerHW__PER0 )
    #define AudioTimer_PERIOD_LSB_PTR        ((reg16 *) AudioTimer_TimerHW__PER0 )
    #define AudioTimer_COUNTER_LSB         (* (reg16 *) AudioTimer_TimerHW__CNT_CMP0 )
    #define AudioTimer_COUNTER_LSB_PTR       ((reg16 *) AudioTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define AudioTimer_BLOCK_EN_MASK                     AudioTimer_TimerHW__PM_ACT_MSK
    #define AudioTimer_BLOCK_STBY_EN_MASK                AudioTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define AudioTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define AudioTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define AudioTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define AudioTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define AudioTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define AudioTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << AudioTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define AudioTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define AudioTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << AudioTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define AudioTimer_CTRL_MODE_SHIFT                 0x01u
        #define AudioTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << AudioTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define AudioTimer_CTRL_RCOD_SHIFT        0x02u
        #define AudioTimer_CTRL_ENBL_SHIFT        0x00u
        #define AudioTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define AudioTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << AudioTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define AudioTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << AudioTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define AudioTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << AudioTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define AudioTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << AudioTimer_CTRL_RCOD_SHIFT))
        #define AudioTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << AudioTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define AudioTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define AudioTimer_RT1_MASK                        ((uint8)((uint8)0x03u << AudioTimer_RT1_SHIFT))
    #define AudioTimer_SYNC                            ((uint8)((uint8)0x03u << AudioTimer_RT1_SHIFT))
    #define AudioTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define AudioTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << AudioTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define AudioTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << AudioTimer_SYNCDSI_SHIFT))

    #define AudioTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << AudioTimer_CTRL_MODE_SHIFT))
    #define AudioTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << AudioTimer_CTRL_MODE_SHIFT))
    #define AudioTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << AudioTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AudioTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AudioTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AudioTimer_STATUS_TC_INT_MASK_SHIFT        (AudioTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AudioTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (AudioTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define AudioTimer_STATUS_TC                       ((uint8)((uint8)0x01u << AudioTimer_STATUS_TC_SHIFT))
    #define AudioTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << AudioTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define AudioTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << AudioTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define AudioTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << AudioTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define AudioTimer_STATUS              (* (reg8 *) AudioTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define AudioTimer_STATUS_MASK         (* (reg8 *) AudioTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define AudioTimer_STATUS_AUX_CTRL     (* (reg8 *) AudioTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define AudioTimer_CONTROL             (* (reg8 *) AudioTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(AudioTimer_Resolution <= 8u) /* 8-bit Timer */
        #define AudioTimer_CAPTURE_LSB         (* (reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define AudioTimer_CAPTURE_LSB_PTR       ((reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define AudioTimer_PERIOD_LSB          (* (reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define AudioTimer_PERIOD_LSB_PTR        ((reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define AudioTimer_COUNTER_LSB         (* (reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define AudioTimer_COUNTER_LSB_PTR       ((reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(AudioTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define AudioTimer_CAPTURE_LSB         (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define AudioTimer_CAPTURE_LSB_PTR       ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define AudioTimer_PERIOD_LSB          (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define AudioTimer_PERIOD_LSB_PTR        ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define AudioTimer_COUNTER_LSB         (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define AudioTimer_COUNTER_LSB_PTR       ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define AudioTimer_CAPTURE_LSB         (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define AudioTimer_CAPTURE_LSB_PTR       ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define AudioTimer_PERIOD_LSB          (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define AudioTimer_PERIOD_LSB_PTR        ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define AudioTimer_COUNTER_LSB         (* (reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define AudioTimer_COUNTER_LSB_PTR       ((reg16 *) AudioTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(AudioTimer_Resolution <= 24u)/* 24-bit Timer */
        #define AudioTimer_CAPTURE_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define AudioTimer_CAPTURE_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define AudioTimer_PERIOD_LSB          (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define AudioTimer_PERIOD_LSB_PTR        ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define AudioTimer_COUNTER_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define AudioTimer_COUNTER_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define AudioTimer_CAPTURE_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define AudioTimer_CAPTURE_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define AudioTimer_PERIOD_LSB          (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define AudioTimer_PERIOD_LSB_PTR        ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define AudioTimer_COUNTER_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define AudioTimer_COUNTER_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define AudioTimer_CAPTURE_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define AudioTimer_CAPTURE_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define AudioTimer_PERIOD_LSB          (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define AudioTimer_PERIOD_LSB_PTR        ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define AudioTimer_COUNTER_LSB         (* (reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define AudioTimer_COUNTER_LSB_PTR       ((reg32 *) AudioTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define AudioTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) AudioTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (AudioTimer_UsingHWCaptureCounter)
        #define AudioTimer_CAP_COUNT              (*(reg8 *) AudioTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AudioTimer_CAP_COUNT_PTR          ( (reg8 *) AudioTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AudioTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) AudioTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define AudioTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) AudioTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (AudioTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define AudioTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define AudioTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define AudioTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define AudioTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define AudioTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define AudioTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << AudioTimer_CTRL_INTCNT_SHIFT))
    #define AudioTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << AudioTimer_CTRL_TRIG_MODE_SHIFT))
    #define AudioTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << AudioTimer_CTRL_TRIG_EN_SHIFT))
    #define AudioTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << AudioTimer_CTRL_CAP_MODE_SHIFT))
    #define AudioTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << AudioTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define AudioTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define AudioTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define AudioTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define AudioTimer_STATUS_TC_INT_MASK_SHIFT       AudioTimer_STATUS_TC_SHIFT
    #define AudioTimer_STATUS_CAPTURE_INT_MASK_SHIFT  AudioTimer_STATUS_CAPTURE_SHIFT
    #define AudioTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define AudioTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define AudioTimer_STATUS_FIFOFULL_INT_MASK_SHIFT AudioTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define AudioTimer_STATUS_TC                      ((uint8)((uint8)0x01u << AudioTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define AudioTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << AudioTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AudioTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << AudioTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AudioTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << AudioTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define AudioTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << AudioTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define AudioTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << AudioTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AudioTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << AudioTimer_STATUS_FIFOFULL_SHIFT))

    #define AudioTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define AudioTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define AudioTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define AudioTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define AudioTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define AudioTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_AudioTimer_H */


/* [] END OF FILE */

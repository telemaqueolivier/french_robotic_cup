/*******************************************************************************
* File Name: timer_asserv.h  
* Version 2.0
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_0_timer_asserv_H)
#define CY_Timer_v2_0_timer_asserv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

/***************************************
*   Conditional Compilation Parameters
***************************************/

/* PSoC3 ES2 or early */
#define timer_asserv_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES1 or early */
#define timer_asserv_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define timer_asserv_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES2 or later */
#define timer_asserv_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


/**************************************
*           Parameter Defaults        
**************************************/

#define timer_asserv_Resolution                 24u
#define timer_asserv_UsingFixedFunction         0u
#define timer_asserv_UsingHWCaptureCounter      0u
#define timer_asserv_SoftwareCaptureMode        0u
#define timer_asserv_SoftwareTriggerMode        0u
#define timer_asserv_UsingHWEnable              0u
#define timer_asserv_EnableTriggerMode          0u
#define timer_asserv_InterruptOnCaptureCount    0u
#define timer_asserv_RunModeUsed                0u
#define timer_asserv_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/
/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct timer_asserv_backupStruct
{
    uint8 TimerEnableState; 
    #if(!timer_asserv_UsingFixedFunction) 
        #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
            uint32 TimerUdb;                 /* Timer internal counter value      */
            uint32 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (timer_asserv_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;  /* Timer Capture Counter Value */           
            #endif
        #endif
        
        #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
            uint32 TimerUdb;  
            uint8 InterruptMaskValue;
            #if (timer_asserv_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;
            #endif
        #endif
        
        #if (!timer_asserv_ControlRegRemoved)
        uint8 TimerControlRegister;
        #endif
    #endif
}timer_asserv_backupStruct;


/*************************************** 
*       Function Prototypes 
***************************************/

void    timer_asserv_Start(void);
void    timer_asserv_Stop(void) ;

void    timer_asserv_SetInterruptMode(uint8 interruptMode) ;
uint8   timer_asserv_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define timer_asserv_GetInterruptSource() timer_asserv_ReadStatusRegister() 

#if(!timer_asserv_ControlRegRemoved)
    uint8   timer_asserv_ReadControlRegister(void) ;
    void    timer_asserv_WriteControlRegister(uint8 control) \
        ;
#endif

uint32  timer_asserv_ReadPeriod(void) ;
void    timer_asserv_WritePeriod(uint32 period) \
    ;
uint32  timer_asserv_ReadCounter(void) ;
void    timer_asserv_WriteCounter(uint32 counter) \
    ;
uint32  timer_asserv_ReadCapture(void) ;
void    timer_asserv_SoftwareCapture(void) ;


#if(!timer_asserv_UsingFixedFunction) /* UDB Prototypes */
    #if (timer_asserv_SoftwareCaptureMode)
        void    timer_asserv_SetCaptureMode(uint8 captureMode) ;
    #endif

    #if (timer_asserv_SoftwareTriggerMode)
        void    timer_asserv_SetTriggerMode(uint8 triggerMode) ;
    #endif
    #if (timer_asserv_EnableTriggerMode)
        void    timer_asserv_EnableTrigger(void) ;
        void    timer_asserv_DisableTrigger(void) ;
    #endif

    #if(timer_asserv_InterruptOnCaptureCount)
        #if(!timer_asserv_ControlRegRemoved)
            void    timer_asserv_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif
    #endif

    #if (timer_asserv_UsingHWCaptureCounter)
        void    timer_asserv_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   timer_asserv_ReadCaptureCount(void) ;
    #endif

    void timer_asserv_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void timer_asserv_Init(void)          ;
void timer_asserv_Enable(void)        ;
void timer_asserv_SaveConfig(void);
void timer_asserv_RestoreConfig(void) ;
void timer_asserv_Sleep(void);
void timer_asserv_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define timer_asserv__B_TIMER__CM_NONE 0
#define timer_asserv__B_TIMER__CM_RISINGEDGE 1
#define timer_asserv__B_TIMER__CM_FALLINGEDGE 2
#define timer_asserv__B_TIMER__CM_EITHEREDGE 3
#define timer_asserv__B_TIMER__CM_SOFTWARE 4


  
/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define timer_asserv__B_TIMER__TM_NONE 0x00u
#define timer_asserv__B_TIMER__TM_RISINGEDGE 0x04u
#define timer_asserv__B_TIMER__TM_FALLINGEDGE 0x08u
#define timer_asserv__B_TIMER__TM_EITHEREDGE 0x0Cu
#define timer_asserv__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define timer_asserv_INIT_PERIOD             119999u
#define timer_asserv_INIT_CAPTURE_MODE       (0u << timer_asserv_CTRL_CAP_MODE_SHIFT)
#define timer_asserv_INIT_TRIGGER_MODE       (0u << timer_asserv_CTRL_TRIG_MODE_SHIFT)
#if (timer_asserv_UsingFixedFunction)
    #define timer_asserv_INIT_INTERRUPT_MODE ((1u << timer_asserv_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (0 << timer_asserv_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define timer_asserv_INIT_INTERRUPT_MODE ((1u << timer_asserv_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (0 << timer_asserv_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                  (0 << timer_asserv_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif
#define timer_asserv_INIT_CAPTURE_COUNT      (2u)
#define timer_asserv_INIT_INT_CAPTURE_COUNT  ((1u - 1) << timer_asserv_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (timer_asserv_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */

    
    /***************************************
    *    Fixed Function Registers 
    ***************************************/
    
    #define timer_asserv_STATUS         (*(reg8 *) timer_asserv_TimerHW__SR0 )
    #define timer_asserv_STATUS_MASK    (*(reg8 *) timer_asserv_TimerHW__SR0 ) /* In Fixed Function Block Status and Mask are the same register */
    #define timer_asserv_CONTROL        (*(reg8 *) timer_asserv_TimerHW__CFG0)
    #define timer_asserv_CONTROL2       (*(reg8 *) timer_asserv_TimerHW__CFG1)
    #define timer_asserv_CONTROL2_PTR   ( (reg8 *) timer_asserv_TimerHW__CFG1)    
    #define timer_asserv_RT1            (*(reg8 *) timer_asserv_TimerHW__RT1)
    #define timer_asserv_RT1_PTR        ( (reg8 *) timer_asserv_TimerHW__RT1)

    #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
        #define timer_asserv_CONTROL3       (*(reg8 *) timer_asserv_TimerHW__CFG2)
        #define timer_asserv_CONTROL3_PTR   ( (reg8 *) timer_asserv_TimerHW__CFG2)
    #endif
    #define timer_asserv_GLOBAL_ENABLE  (*(reg8 *) timer_asserv_TimerHW__PM_ACT_CFG)
    #define timer_asserv_GLOBAL_STBY_ENABLE  (*(reg8 *) timer_asserv_TimerHW__PM_STBY_CFG)
    
    #define timer_asserv_CAPTURE_LSB         (* (reg16 *) timer_asserv_TimerHW__CAP0 )
    #define timer_asserv_CAPTURE_LSB_PTR       ((reg16 *) timer_asserv_TimerHW__CAP0 )
    #define timer_asserv_PERIOD_LSB          (* (reg16 *) timer_asserv_TimerHW__PER0 )
    #define timer_asserv_PERIOD_LSB_PTR        ((reg16 *) timer_asserv_TimerHW__PER0 )
    #define timer_asserv_COUNTER_LSB         (* (reg16 *) timer_asserv_TimerHW__CNT_CMP0 )
    #define timer_asserv_COUNTER_LSB_PTR       ((reg16 *) timer_asserv_TimerHW__CNT_CMP0 )
    
    /***************************************
    *    Register Constants
    ***************************************/
    
    /* Fixed Function Block Chosen */
    #define timer_asserv_BLOCK_EN_MASK                     timer_asserv_TimerHW__PM_ACT_MSK
    #define timer_asserv_BLOCK_STBY_EN_MASK                timer_asserv_TimerHW__PM_STBY_MSK    
    
    /* Control Register Bit Locations */
    #define timer_asserv_CTRL_INTCNT_SHIFT                  0x00u       /* Interrupt Count - Not valid for Fixed Function Block */
    #define timer_asserv_CTRL_TRIG_MODE_SHIFT               0x00u       /* Trigger Polarity - Not valid for Fixed Function Block */
    #define timer_asserv_CTRL_TRIG_EN_SHIFT                 0x00u       /* Trigger Enable - Not valid for Fixed Function Block */
    #define timer_asserv_CTRL_CAP_MODE_SHIFT                0x00u       /* Capture Polarity - Not valid for Fixed Function Block */ 
    #define timer_asserv_CTRL_ENABLE_SHIFT                  0x00u       /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */

    /* Control Register Bit Masks */
    #define timer_asserv_CTRL_ENABLE                        (0x01u << timer_asserv_CTRL_ENABLE_SHIFT)
    
    /* Control2 Register Bit Masks */
    #define timer_asserv_CTRL2_IRQ_SEL_SHIFT                 0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define timer_asserv_CTRL2_IRQ_SEL                      (0x01u << timer_asserv_CTRL2_IRQ_SEL_SHIFT) 
    
    #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
        /* Use CFG1 Mode bits to set run mode */
        #define timer_asserv_CTRL_MODE_SHIFT                     0x01u       /* As defined by Verilog Implementation */ 
        #define timer_asserv_CTRL_MODE_MASK                     (0x07u << timer_asserv_CTRL_MODE_SHIFT) 
    #endif
    #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
        /* Control3 Register Bit Locations */
        #define timer_asserv_CTRL_RCOD_SHIFT        0x02u
        #define timer_asserv_CTRL_ENBL_SHIFT        0x00u
        #define timer_asserv_CTRL_MODE_SHIFT        0x00u 
        
        /* Control3 Register Bit Masks */
        #define timer_asserv_CTRL_RCOD_MASK  (0x03u << timer_asserv_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define timer_asserv_CTRL_ENBL_MASK  (0x80u << timer_asserv_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define timer_asserv_CTRL_MODE_MASK  (0x03u << timer_asserv_CTRL_MODE_SHIFT) /* Run mode bit mask */
        
        #define timer_asserv_CTRL_RCOD       (0x03u << timer_asserv_CTRL_RCOD_SHIFT)
        #define timer_asserv_CTRL_ENBL       (0x80u << timer_asserv_CTRL_ENBL_SHIFT) 
    #endif
    
    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define timer_asserv_RT1_SHIFT                                              0x04u
    #define timer_asserv_RT1_MASK                                               (0x03u << timer_asserv_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define timer_asserv_SYNC                                                   (0x03u << timer_asserv_RT1_SHIFT)
    #define timer_asserv_SYNCDSI_SHIFT                                          0x00u
    #define timer_asserv_SYNCDSI_MASK                                           (0x0Fu << timer_asserv_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define timer_asserv_SYNCDSI_EN                                             (0x0Fu << timer_asserv_SYNCDSI_SHIFT) /* Sync all DSI inputs */

    #define timer_asserv_CTRL_MODE_PULSEWIDTH               (0x01u << timer_asserv_CTRL_MODE_SHIFT) 
    #define timer_asserv_CTRL_MODE_PERIOD                   (0x02u << timer_asserv_CTRL_MODE_SHIFT) 
    #define timer_asserv_CTRL_MODE_CONTINUOUS               (0x00u << timer_asserv_CTRL_MODE_SHIFT) 
    
    /* Status Register Bit Locations */
    #define timer_asserv_STATUS_TC_SHIFT                    0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define timer_asserv_STATUS_CAPTURE_SHIFT               0x06u  /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define timer_asserv_STATUS_TC_INT_MASK_SHIFT           (timer_asserv_STATUS_TC_SHIFT - 4)      /* As defined in Register Map, part of TMRX_SR0 register */ 
    #define timer_asserv_STATUS_CAPTURE_INT_MASK_SHIFT      (timer_asserv_STATUS_CAPTURE_SHIFT - 4) /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */ 
    
    /* Status Register Bit Masks */
    #define timer_asserv_STATUS_TC                          (0x01u << timer_asserv_STATUS_TC_SHIFT)
    #define timer_asserv_STATUS_CAPTURE                     (0x01u << timer_asserv_STATUS_CAPTURE_SHIFT)
    #define timer_asserv_STATUS_TC_INT_MASK                 (0x01u << timer_asserv_STATUS_TC_INT_MASK_SHIFT)      /* Interrupt Enable Bit-Mask */ 
    #define timer_asserv_STATUS_CAPTURE_INT_MASK            (0x01u << timer_asserv_STATUS_CAPTURE_INT_MASK_SHIFT) /* Interrupt Enable Bit-Mask */ 
    
#else   /* UDB Registers and Register Constants */

    
    /***************************************
    *           UDB Registers 
    ***************************************/
    
    #define timer_asserv_STATUS              (* (reg8 *) timer_asserv_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define timer_asserv_STATUS_MASK         (* (reg8 *) timer_asserv_TimerUDB_rstSts_stsreg__MASK_REG)
    #define timer_asserv_STATUS_AUX_CTRL     (* (reg8 *) timer_asserv_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define timer_asserv_CONTROL             (* (reg8 *) timer_asserv_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #define timer_asserv_CAPTURE_LSB         (* (reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__F0_REG )
    #define timer_asserv_CAPTURE_LSB_PTR       ((reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__F0_REG )
    #define timer_asserv_PERIOD_LSB          (* (reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__D0_REG )
    #define timer_asserv_PERIOD_LSB_PTR        ((reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__D0_REG )
    #define timer_asserv_COUNTER_LSB         (* (reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__A0_REG )
    #define timer_asserv_COUNTER_LSB_PTR       ((reg32 *) timer_asserv_TimerUDB_sT24_timerdp_u0__A0_REG )

    #if (timer_asserv_UsingHWCaptureCounter)
        #define timer_asserv_CAP_COUNT              (*(reg8 *) timer_asserv_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define timer_asserv_CAP_COUNT_PTR          ( (reg8 *) timer_asserv_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define timer_asserv_CAPTURE_COUNT_CTRL     (*(reg8 *) timer_asserv_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define timer_asserv_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) timer_asserv_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif


    /***************************************
    *       Register Constants
    ***************************************/
    
    /* Control Register Bit Locations */
    #define timer_asserv_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define timer_asserv_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define timer_asserv_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define timer_asserv_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define timer_asserv_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */
    
    /* Control Register Bit Masks */
    #define timer_asserv_CTRL_INTCNT_MASK               (0x03u << timer_asserv_CTRL_INTCNT_SHIFT)
    #define timer_asserv_CTRL_TRIG_MODE_MASK            (0x03u << timer_asserv_CTRL_TRIG_MODE_SHIFT)  
    #define timer_asserv_CTRL_TRIG_EN                   (0x01u << timer_asserv_CTRL_TRIG_EN_SHIFT)
    #define timer_asserv_CTRL_CAP_MODE_MASK             (0x03u << timer_asserv_CTRL_CAP_MODE_SHIFT)   
    #define timer_asserv_CTRL_ENABLE                    (0x01u << timer_asserv_CTRL_ENABLE_SHIFT)
    
    /* Bit Counter (7-bit) Control Register Bit Definitions */
    #define timer_asserv_CNTR_ENABLE                    0x20u   /* As defined by the Register map for the AUX Control Register */
    
    /* Status Register Bit Locations */
    #define timer_asserv_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define timer_asserv_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define timer_asserv_STATUS_TC_INT_MASK_SHIFT       timer_asserv_STATUS_TC_SHIFT                
    #define timer_asserv_STATUS_CAPTURE_INT_MASK_SHIFT  timer_asserv_STATUS_CAPTURE_SHIFT
    #define timer_asserv_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define timer_asserv_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define timer_asserv_STATUS_FIFOFULL_INT_MASK_SHIFT timer_asserv_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    #define timer_asserv_STATUS_TC                      (0x01u << timer_asserv_STATUS_TC_SHIFT)             /* Sticky TC Event Bit-Mask */ 
    #define timer_asserv_STATUS_CAPTURE                 (0x01u << timer_asserv_STATUS_CAPTURE_SHIFT)        /* Sticky Capture Event Bit-Mask */ 
    #define timer_asserv_STATUS_TC_INT_MASK             (0x01u << timer_asserv_STATUS_TC_SHIFT)             /* Interrupt Enable Bit-Mask */            
    #define timer_asserv_STATUS_CAPTURE_INT_MASK        (0x01u << timer_asserv_STATUS_CAPTURE_SHIFT)        /* Interrupt Enable Bit-Mask */ 
    #define timer_asserv_STATUS_FIFOFULL                (0x01u << timer_asserv_STATUS_FIFOFULL_SHIFT)       /* NOT-Sticky FIFO Full Bit-Mask */ 
    #define timer_asserv_STATUS_FIFONEMP                (0x01u << timer_asserv_STATUS_FIFONEMP_SHIFT)       /* NOT-Sticky FIFO Not Empty Bit-Mask */ 
    #define timer_asserv_STATUS_FIFOFULL_INT_MASK       (0x01u << timer_asserv_STATUS_FIFOFULL_SHIFT)       /* Interrupt Enable Bit-Mask */ 
    
    #define timer_asserv_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define timer_asserv_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define timer_asserv_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define timer_asserv_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define timer_asserv_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define timer_asserv_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */
    
#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_0_timer_asserv_H */


/* [] END OF FILE */

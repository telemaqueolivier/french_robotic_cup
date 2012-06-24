/*******************************************************************************
* File Name: pwm_right.h  
* Version 2.0
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

#if !defined(CY_PWM_pwm_right_H)
#define CY_PWM_pwm_right_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define pwm_right_Resolution 16
#define pwm_right_UsingFixedFunction 1
#define pwm_right_DeadBandMode 0
#define pwm_right_KillModeMinTime 0
#define pwm_right_KillMode 1
#define pwm_right_PWMMode 0
#define pwm_right_PWMModeIsCenterAligned 0
#define pwm_right_DeadBandUsed 0
#define pwm_right_DeadBand2_4 0
#if !defined(pwm_right_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define pwm_right_UseStatus 0
#else
    #define pwm_right_UseStatus 0
#endif
#if !defined(pwm_right_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define pwm_right_UseControl 1
#else
    #define pwm_right_UseControl 0
#endif
#define pwm_right_UseOneCompareMode 1
#define pwm_right_MinimumKillTime 1
#define pwm_right_EnableMode 0

#define pwm_right_CompareMode1SW 0
#define pwm_right_CompareMode2SW 0

/* PSoC3 ES2 or early */
#define pwm_right_PSOC3_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))

/* PSoC5 ES1 or early */
#define pwm_right_PSOC5_ES1   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))

/* PSoC3 ES3 or later */
#define pwm_right_PSOC3_ES3   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                     (CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3))

/* PSoC5 ES2 or later */
#define pwm_right_PSOC5_ES2   ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)   && \
                                     (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))

/* Use Kill Mode Enumerated Types */
#define pwm_right__B_PWM__DISABLED 0
#define pwm_right__B_PWM__ASYNCHRONOUS 1
#define pwm_right__B_PWM__SINGLECYCLE 2
#define pwm_right__B_PWM__LATCHED 3
#define pwm_right__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define pwm_right__B_PWM__DBMDISABLED 0
#define pwm_right__B_PWM__DBM_2_4_CLOCKS 1
#define pwm_right__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define pwm_right__B_PWM__ONE_OUTPUT 0
#define pwm_right__B_PWM__TWO_OUTPUTS 1
#define pwm_right__B_PWM__DUAL_EDGE 2
#define pwm_right__B_PWM__CENTER_ALIGN 3
#define pwm_right__B_PWM__DITHER 5
#define pwm_right__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define pwm_right__B_PWM__LESS_THAN 1
#define pwm_right__B_PWM__LESS_THAN_OR_EQUAL 2
#define pwm_right__B_PWM__GREATER_THAN 3
#define pwm_right__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define pwm_right__B_PWM__EQUAL 0
#define pwm_right__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/

/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct pwm_right_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!pwm_right_UsingFixedFunction)
        #if (pwm_right_PSOC3_ES2 || pwm_right_PSOC5_ES1)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (pwm_right_UseStatus)
				uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
			#endif
            #if(pwm_right_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif
            
            /* Backup for Deadband parameters */
            #if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS || pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(pwm_right_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
            
        #endif
        
        #if (pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if (pwm_right_UseStatus)
				uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
			#endif
            
            /* Backup for Deadband parameters */
            #if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS || pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif
            
            /* Backup Kill Mode Counter*/
            #if(pwm_right_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif
        #endif
        
        
        /* Backup control register */
        #if(pwm_right_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif
        
    #endif 
   
}pwm_right_backupStruct;

/***************************************
*        Function Prototypes
 **************************************/
 
void    pwm_right_Start(void);
void    pwm_right_Stop(void) ;
#if (pwm_right_UseStatus || pwm_right_UsingFixedFunction)
    #define pwm_right_SetInterruptMode(interruptMode) CY_SET_REG8(pwm_right_STATUS_MASK_PTR, interruptMode)
    #define pwm_right_ReadStatusRegister() CY_GET_REG8(pwm_right_STATUS_PTR)
#endif
#define pwm_right_GetInterruptSource() pwm_right_ReadStatusRegister()
#if (pwm_right_UseControl)
    #define pwm_right_ReadControlRegister() CY_GET_REG8(pwm_right_CONTROL_PTR) 
    #define pwm_right_WriteControlRegister(control) CY_SET_REG8(pwm_right_CONTROL_PTR, control)
#endif
#if (pwm_right_UseOneCompareMode)
   #if (pwm_right_CompareMode1SW)
       void    pwm_right_SetCompareMode(uint8 comparemode) ;
   #endif
#else
    #if (pwm_right_CompareMode1SW)
        void    pwm_right_SetCompareMode1(uint8 comparemode) ;
    #endif
    #if (pwm_right_CompareMode2SW)
        void    pwm_right_SetCompareMode2(uint8 comparemode) ;
    #endif
#endif

#if (!pwm_right_UsingFixedFunction)
    uint16   pwm_right_ReadCounter(void) ;
    #define pwm_right_ReadCapture() CY_GET_REG16(pwm_right_CAPTURE_LSB_PTR)
    #if (pwm_right_UseStatus)
        void pwm_right_ClearFIFO(void) ;
    #endif
#endif

void    pwm_right_WriteCounter(uint16 counter) ;
void    pwm_right_WritePeriod(uint16 period) ;
#define pwm_right_ReadPeriod() CY_GET_REG16(pwm_right_PERIOD_LSB_PTR) 
#if (pwm_right_UseOneCompareMode)
    void    pwm_right_WriteCompare(uint16 compare) ;
    #define pwm_right_ReadCompare() CY_GET_REG16(pwm_right_COMPARE1_LSB_PTR) 
#else
    void    pwm_right_WriteCompare1(uint16 compare) ;
    #define pwm_right_ReadCompare1() CY_GET_REG16(pwm_right_COMPARE1_LSB_PTR) 
    void    pwm_right_WriteCompare2(uint16 compare) ;
    #define pwm_right_ReadCompare2() CY_GET_REG16(pwm_right_COMPARE2_LSB_PTR) 
#endif


#if (pwm_right_DeadBandUsed)
    void    pwm_right_WriteDeadTime(uint8 deadtime) ;
    uint8   pwm_right_ReadDeadTime(void) ;
#endif

#if ( pwm_right_KillModeMinTime)
    #define pwm_right_WriteKillTime(killtime) CY_SET_REG8(pwm_right_KILLMODEMINTIME_PTR, killtime) 
    #define pwm_right_ReadKillTime() CY_GET_REG8(pwm_right_KILLMODEMINTIME_PTR) 
#endif

void pwm_right_Init(void) ;
void pwm_right_Enable(void) ;
void pwm_right_Sleep(void);
void pwm_right_Wakeup(void) ;
void pwm_right_SaveConfig(void);
void pwm_right_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define pwm_right_INIT_PERIOD_VALUE        1024
#define pwm_right_INIT_COMPARE_VALUE1      0
#define pwm_right_INIT_COMPARE_VALUE2      63
#define pwm_right_INIT_INTERRUPTS_MODE     ((0 << pwm_right_STATUS_TC_INT_EN_MASK_SHIFT) | (0 << pwm_right_STATUS_CMP2_INT_EN_MASK_SHIFT) | (0 << pwm_right_STATUS_CMP1_INT_EN_MASK_SHIFT ) | (0 << pwm_right_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define pwm_right_DEFAULT_COMPARE2_MODE    (1 << pwm_right_CTRL_CMPMODE2_SHIFT)
#define pwm_right_DEFAULT_COMPARE1_MODE    (1 << pwm_right_CTRL_CMPMODE1_SHIFT)
#define pwm_right_INIT_DEAD_TIME           1


/********************************
*         Registers
******************************** */

#if (pwm_right_UsingFixedFunction)
   #define pwm_right_PERIOD_LSB          (*(reg16 *) pwm_right_PWMHW__PER0)
   #define pwm_right_PERIOD_LSB_PTR      ( (reg16 *) pwm_right_PWMHW__PER0)
   #define pwm_right_COMPARE1_LSB        (*(reg16 *) pwm_right_PWMHW__CNT_CMP0)
   #define pwm_right_COMPARE1_LSB_PTR    ( (reg16 *) pwm_right_PWMHW__CNT_CMP0)
   #define pwm_right_COMPARE2_LSB        0x00u
   #define pwm_right_COMPARE2_LSB_PTR    0x00u
   #define pwm_right_COUNTER_LSB         (*(reg16 *) pwm_right_PWMHW__CNT_CMP0)
   #define pwm_right_COUNTER_LSB_PTR     ( (reg16 *) pwm_right_PWMHW__CNT_CMP0)
   #define pwm_right_CAPTURE_LSB         (*(reg16 *) pwm_right_PWMHW__CAP0)
   #define pwm_right_CAPTURE_LSB_PTR     ( (reg16 *) pwm_right_PWMHW__CAP0)
   #define pwm_right_RT1                 (*(reg8 *)  pwm_right_PWMHW__RT1)
   #define pwm_right_RT1_PTR             ( (reg8 *)  pwm_right_PWMHW__RT1)
      
#else
   #if(pwm_right_PWMModeIsCenterAligned)
       #define pwm_right_PERIOD_LSB      (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define pwm_right_PERIOD_LSB_PTR   ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #else
       #define pwm_right_PERIOD_LSB      (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #define pwm_right_PERIOD_LSB_PTR   ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__F0_REG)
   #endif
   #define pwm_right_COMPARE1_LSB    (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define pwm_right_COMPARE1_LSB_PTR ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define pwm_right_COMPARE2_LSB    (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define pwm_right_COMPARE2_LSB_PTR ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define pwm_right_COUNTERCAP_LSB   *(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define pwm_right_COUNTERCAP_LSB_PTR ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define pwm_right_COUNTER_LSB     (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define pwm_right_COUNTER_LSB_PTR  ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define pwm_right_CAPTURE_LSB     (*(reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define pwm_right_CAPTURE_LSB_PTR  ((reg16 *) pwm_right_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define pwm_right_AUX_CONTROLDP0      (*(reg8 *) pwm_right_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define pwm_right_AUX_CONTROLDP0_PTR  ((reg8 *) pwm_right_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #if (pwm_right_Resolution == 16)
       #define pwm_right_AUX_CONTROLDP1    (*(reg8 *) pwm_right_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define pwm_right_AUX_CONTROLDP1_PTR  ((reg8 *) pwm_right_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
   #endif
#endif
   
#if(pwm_right_KillModeMinTime )
    #define pwm_right_KILLMODEMINTIME      (*(reg8 *) pwm_right_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define pwm_right_KILLMODEMINTIME_PTR   ((reg8 *) pwm_right_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif

#if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS)
    #define pwm_right_DEADBAND_COUNT        (*(reg8 *) pwm_right_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define pwm_right_DEADBAND_COUNT_PTR     ((reg8 *) pwm_right_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define pwm_right_DEADBAND_LSB_PTR       ((reg8 *) pwm_right_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define pwm_right_DEADBAND_LSB          (*(reg8 *) pwm_right_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (pwm_right_UsingFixedFunction)
        #define pwm_right_DEADBAND_COUNT        (*(reg8 *) pwm_right_PWMHW__CFG0) 
        #define pwm_right_DEADBAND_COUNT_PTR     ((reg8 *) pwm_right_PWMHW__CFG0)
        #define pwm_right_DEADBAND_COUNT_MASK    (0x03u << pwm_right_DEADBAND_COUNT_SHIFT) 
        #define pwm_right_DEADBAND_COUNT_SHIFT   0x06u /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */ 
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define pwm_right_DEADBAND_COUNT        (*(reg8 *) pwm_right_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define pwm_right_DEADBAND_COUNT_PTR     ((reg8 *) pwm_right_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define pwm_right_DEADBAND_COUNT_MASK    (0x03u << pwm_right_DEADBAND_COUNT_SHIFT) 
        #define pwm_right_DEADBAND_COUNT_SHIFT   0x00u /* As defined by the verilog implementation of the Control Register */
    #endif
#endif



#if (pwm_right_UsingFixedFunction)
    #define pwm_right_STATUS                (*(reg8 *) pwm_right_PWMHW__SR0)
    #define pwm_right_STATUS_PTR            ((reg8 *) pwm_right_PWMHW__SR0)
    #define pwm_right_STATUS_MASK           (*(reg8 *) pwm_right_PWMHW__SR0)
    #define pwm_right_STATUS_MASK_PTR       ((reg8 *) pwm_right_PWMHW__SR0)
    #define pwm_right_CONTROL               (*(reg8 *) pwm_right_PWMHW__CFG0)
    #define pwm_right_CONTROL_PTR           ((reg8 *) pwm_right_PWMHW__CFG0)    
    #define pwm_right_CONTROL2              (*(reg8 *) pwm_right_PWMHW__CFG1)    
    #if(pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
        #define pwm_right_CONTROL3              (*(reg8 *) pwm_right_PWMHW__CFG2)
    #endif
    #define pwm_right_GLOBAL_ENABLE         (*(reg8 *) pwm_right_PWMHW__PM_ACT_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/
    /* Fixed Function Block Chosen */
    #define pwm_right_BLOCK_EN_MASK          pwm_right_PWMHW__PM_ACT_MSK
    /* Control Register definitions */
    #define pwm_right_CTRL_ENABLE_SHIFT      0x00u
    
    #if(pwm_right_PSOC3_ES2 || pwm_right_PSOC5_ES1)
        #define pwm_right_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif
    #if(pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
        #define pwm_right_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif
    
    #define pwm_right_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define pwm_right_CFG0_MODE              0x02u   /*  Set to compare mode */
    //#define pwm_right_CFG0_ENABLE            0x01u   /* Enable the block to run */
    #define pwm_right_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define pwm_right_CTRL_ENABLE            (0x01u << pwm_right_CTRL_ENABLE_SHIFT)
    #define pwm_right_CTRL_RESET             (0x01u << pwm_right_CTRL_RESET_SHIFT)
    #define pwm_right_CTRL_CMPMODE2_MASK     (0x07u << pwm_right_CTRL_CMPMODE2_SHIFT)
    #if(pwm_right_PSOC3_ES2 || pwm_right_PSOC5_ES1)
        #define pwm_right_CTRL_CMPMODE1_MASK     (0x07u << pwm_right_CTRL_CMPMODE1_SHIFT)
    #endif
    #if(pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
        #define pwm_right_CTRL_CMPMODE1_MASK     (0x07u << pwm_right_CTRL_CMPMODE1_SHIFT)
    #endif
    
    /* Control2 Register Bit Masks */
    #define pwm_right_CTRL2_IRQ_SEL_SHIFT    0x00u       /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define pwm_right_CTRL2_IRQ_SEL          (0x01u << pwm_right_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define pwm_right_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define pwm_right_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define pwm_right_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define pwm_right_STATUS_TC_INT_EN_MASK_SHIFT            (pwm_right_STATUS_TC_SHIFT - 4)
    #define pwm_right_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define pwm_right_STATUS_CMP1_INT_EN_MASK_SHIFT          (pwm_right_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define pwm_right_STATUS_TC              (0x01u << pwm_right_STATUS_TC_SHIFT)
    #define pwm_right_STATUS_CMP1            (0x01u << pwm_right_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define pwm_right_STATUS_TC_INT_EN_MASK              (pwm_right_STATUS_TC >> 4)
    #define pwm_right_STATUS_CMP1_INT_EN_MASK            (pwm_right_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 ES2/PSoC3 ES3 PSoC5 ES2*/
    #define pwm_right_RT1_SHIFT              0x04u
    #define pwm_right_RT1_MASK               (0x03u << pwm_right_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define pwm_right_SYNC                   (0x03u << pwm_right_RT1_SHIFT)
    #define pwm_right_SYNCDSI_SHIFT          0x00u
    #define pwm_right_SYNCDSI_MASK           (0x0Fu << pwm_right_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define pwm_right_SYNCDSI_EN             (0x0Fu << pwm_right_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define pwm_right_STATUS                (*(reg8 *) pwm_right_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define pwm_right_STATUS_PTR            ((reg8 *) pwm_right_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define pwm_right_STATUS_MASK           (*(reg8 *) pwm_right_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define pwm_right_STATUS_MASK_PTR       ((reg8 *) pwm_right_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define pwm_right_STATUS_AUX_CTRL       (*(reg8 *) pwm_right_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define pwm_right_CONTROL               (*(reg8 *) pwm_right_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define pwm_right_CONTROL_PTR           ((reg8 *) pwm_right_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/
    /* Control Register definitions */
    #define pwm_right_CTRL_ENABLE_SHIFT      0x07u
    #define pwm_right_CTRL_RESET_SHIFT       0x06u
    #define pwm_right_CTRL_CMPMODE2_SHIFT    0x03u
    #define pwm_right_CTRL_CMPMODE1_SHIFT    0x00u
    #define pwm_right_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define pwm_right_CTRL_ENABLE            (0x01u << pwm_right_CTRL_ENABLE_SHIFT)
    #define pwm_right_CTRL_RESET             (0x01u << pwm_right_CTRL_RESET_SHIFT)
    #define pwm_right_CTRL_CMPMODE2_MASK     (0x07u << pwm_right_CTRL_CMPMODE2_SHIFT)
    #define pwm_right_CTRL_CMPMODE1_MASK     (0x07u << pwm_right_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define pwm_right_STATUS_KILL_SHIFT          0x05u
    #define pwm_right_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define pwm_right_STATUS_FIFOFULL_SHIFT      0x03u  
    #define pwm_right_STATUS_TC_SHIFT            0x02u
    #define pwm_right_STATUS_CMP2_SHIFT          0x01u
    #define pwm_right_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define pwm_right_STATUS_KILL_INT_EN_MASK_SHIFT          pwm_right_STATUS_KILL_SHIFT          
    #define pwm_right_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    pwm_right_STATUS_FIFONEMPTY_SHIFT    
    #define pwm_right_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      pwm_right_STATUS_FIFOFULL_SHIFT        
    #define pwm_right_STATUS_TC_INT_EN_MASK_SHIFT            pwm_right_STATUS_TC_SHIFT            
    #define pwm_right_STATUS_CMP2_INT_EN_MASK_SHIFT          pwm_right_STATUS_CMP2_SHIFT          
    #define pwm_right_STATUS_CMP1_INT_EN_MASK_SHIFT          pwm_right_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define pwm_right_STATUS_KILL            (0x00u << pwm_right_STATUS_KILL_SHIFT )
    #define pwm_right_STATUS_FIFOFULL        (0x01u << pwm_right_STATUS_FIFOFULL_SHIFT)
    #define pwm_right_STATUS_FIFONEMPTY      (0x01u << pwm_right_STATUS_FIFONEMPTY_SHIFT)
    #define pwm_right_STATUS_TC              (0x01u << pwm_right_STATUS_TC_SHIFT)
    #define pwm_right_STATUS_CMP2            (0x01u << pwm_right_STATUS_CMP2_SHIFT) 
    #define pwm_right_STATUS_CMP1            (0x01u << pwm_right_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define pwm_right_STATUS_KILL_INT_EN_MASK            pwm_right_STATUS_KILL
    #define pwm_right_STATUS_FIFOFULL_INT_EN_MASK        pwm_right_STATUS_FIFOFULL
    #define pwm_right_STATUS_FIFONEMPTY_INT_EN_MASK      pwm_right_STATUS_FIFONEMPTY
    #define pwm_right_STATUS_TC_INT_EN_MASK              pwm_right_STATUS_TC
    #define pwm_right_STATUS_CMP2_INT_EN_MASK            pwm_right_STATUS_CMP2
    #define pwm_right_STATUS_CMP1_INT_EN_MASK            pwm_right_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define pwm_right_AUX_CTRL_FIFO0_CLR     0x01u
    #define pwm_right_AUX_CTRL_FIFO1_CLR     0x02u
    #define pwm_right_AUX_CTRL_FIFO0_LVL     0x04u
    #define pwm_right_AUX_CTRL_FIFO1_LVL     0x08u
    #define pwm_right_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* pwm_right_UsingFixedFunction */

#endif  /* CY_PWM_pwm_right_H */

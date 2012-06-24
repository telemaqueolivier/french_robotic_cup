/*******************************************************************************
* File Name: quaddec_left_Cnt16.h  
* Version 1.50
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
    
#if !defined(CY_COUNTER_quaddec_left_Cnt16_H)
#define CY_COUNTER_quaddec_left_Cnt16_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* PSoC3 ES2 or early */
#define quaddec_left_Cnt16_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES1 or early */
#define quaddec_left_Cnt16_PSOC5_ES1  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_5A_ES1))
/* PSoC3 ES3 or later */
#define quaddec_left_Cnt16_PSOC3_ES3  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2))
/* PSoC5 ES2 or later */
#define quaddec_left_Cnt16_PSOC5_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)    && \
                                    (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_5A_ES1))


/**************************************
*           Parameter Defaults        
**************************************/

#define quaddec_left_Cnt16_Resolution            16u
#define quaddec_left_Cnt16_UsingFixedFunction    0u
#define quaddec_left_Cnt16_ControlRegRemoved     0u
#define quaddec_left_Cnt16_COMPARE_MODE_SOFTWARE 0u
#define quaddec_left_Cnt16_CAPTURE_MODE_SOFTWARE 0u
#define quaddec_left_Cnt16_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct quaddec_left_Cnt16_backupStruct
{
    #if (!quaddec_left_Cnt16_ControlRegRemoved)
        #if (!quaddec_left_Cnt16_UsingFixedFunction)
            uint8 control;
        #endif
        
        uint8 enableState;
    #endif   
    
    #if (!quaddec_left_Cnt16_UsingFixedFunction)
        uint16 counterUdb;
        uint16 captureValue;
    #endif
}quaddec_left_Cnt16_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    quaddec_left_Cnt16_Start(void);
void    quaddec_left_Cnt16_Stop(void) ;
void    quaddec_left_Cnt16_SetInterruptMode(uint8 interruptsMask) ;
uint8   quaddec_left_Cnt16_GetInterruptSource(void) ;
uint8   quaddec_left_Cnt16_ReadStatusRegister(void) ;
#if(!quaddec_left_Cnt16_ControlRegRemoved)
    uint8   quaddec_left_Cnt16_ReadControlRegister(void) ;
    void    quaddec_left_Cnt16_WriteControlRegister(uint8 control) \
        ;
#endif
void    quaddec_left_Cnt16_WriteCounter(uint16 counter) \
    ; 
uint16  quaddec_left_Cnt16_ReadCounter(void) ;
uint16  quaddec_left_Cnt16_ReadCapture(void) ;
void    quaddec_left_Cnt16_WritePeriod(uint16 period) \
    ;
uint16  quaddec_left_Cnt16_ReadPeriod( void ) ;
#if (!quaddec_left_Cnt16_UsingFixedFunction)
    void    quaddec_left_Cnt16_WriteCompare(uint16 compare) \
        ;
    uint16  quaddec_left_Cnt16_ReadCompare( void ) \
        ;
#endif

#if (quaddec_left_Cnt16_COMPARE_MODE_SOFTWARE)
    void    quaddec_left_Cnt16_SetCompareMode(uint8 comparemode) ;
#endif
#if (quaddec_left_Cnt16_CAPTURE_MODE_SOFTWARE)
    void    quaddec_left_Cnt16_SetCaptureMode(uint8 capturemode) ;
#endif
void quaddec_left_Cnt16_ClearFIFO(void)     ;
void quaddec_left_Cnt16_Init(void)          ;
void quaddec_left_Cnt16_Enable(void)        ;
void quaddec_left_Cnt16_SaveConfig(void)    ;
void quaddec_left_Cnt16_RestoreConfig(void) ;
void quaddec_left_Cnt16_Sleep(void)         ;
void quaddec_left_Cnt16_Wakeup(void)        ;

/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode */
#define quaddec_left_Cnt16__B_COUNTER__LESS_THAN 1
#define quaddec_left_Cnt16__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define quaddec_left_Cnt16__B_COUNTER__EQUAL 0
#define quaddec_left_Cnt16__B_COUNTER__GREATER_THAN 3
#define quaddec_left_Cnt16__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define quaddec_left_Cnt16__B_COUNTER__SOFTWARE 5


/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode */
#define quaddec_left_Cnt16__B_COUNTER__NONE 0
#define quaddec_left_Cnt16__B_COUNTER__RISING_EDGE 1
#define quaddec_left_Cnt16__B_COUNTER__FALLING_EDGE 2
#define quaddec_left_Cnt16__B_COUNTER__EITHER_EDGE 3
#define quaddec_left_Cnt16__B_COUNTER__SOFTWARE_CONTROL 4


/***************************************
 *  Initialization Values
 **************************************/
#define quaddec_left_Cnt16_INIT_PERIOD_VALUE       32768u
#define quaddec_left_Cnt16_INIT_COUNTER_VALUE      32768u
#if (quaddec_left_Cnt16_UsingFixedFunction)
#define quaddec_left_Cnt16_INIT_INTERRUPTS_MASK    ((0u << quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define quaddec_left_Cnt16_INIT_COMPARE_VALUE      32768u
#define quaddec_left_Cnt16_INIT_INTERRUPTS_MASK ((0u << quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        (0u << quaddec_left_Cnt16_STATUS_CAPTURE_INT_EN_MASK_SHIFT) | \
        (0u << quaddec_left_Cnt16_STATUS_CMP_INT_EN_MASK_SHIFT) | \
        (0u << quaddec_left_Cnt16_STATUS_OVERFLOW_INT_EN_MASK_SHIFT) | \
        (0u << quaddec_left_Cnt16_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT))
#define quaddec_left_Cnt16_DEFAULT_COMPARE_MODE    (0u << quaddec_left_Cnt16_CTRL_CMPMODE0_SHIFT)
#define quaddec_left_Cnt16_DEFAULT_CAPTURE_MODE    (0u << quaddec_left_Cnt16_CTRL_CAPMODE0_SHIFT)
#endif /* (quaddec_left_Cnt16_UsingFixedFunction) */

/**************************************
 *  Registers
 *************************************/
#if (quaddec_left_Cnt16_UsingFixedFunction)
    #define quaddec_left_Cnt16_STATICCOUNT_LSB     (*(reg16 *) quaddec_left_Cnt16_CounterHW__CAP0 )
    #define quaddec_left_Cnt16_STATICCOUNT_LSB_PTR ( (reg16 *) quaddec_left_Cnt16_CounterHW__CAP0 )
    #define quaddec_left_Cnt16_PERIOD_LSB          (*(reg16 *) quaddec_left_Cnt16_CounterHW__PER0 )
    #define quaddec_left_Cnt16_PERIOD_LSB_PTR      ( (reg16 *) quaddec_left_Cnt16_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define quaddec_left_Cnt16_COMPARE_LSB         (*(reg16 *) quaddec_left_Cnt16_CounterHW__CNT_CMP0 )
    #define quaddec_left_Cnt16_COMPARE_LSB_PTR     ( (reg16 *) quaddec_left_Cnt16_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define quaddec_left_Cnt16_COUNTER_LSB         (*(reg16 *) quaddec_left_Cnt16_CounterHW__CNT_CMP0 )
    #define quaddec_left_Cnt16_COUNTER_LSB_PTR     ( (reg16 *) quaddec_left_Cnt16_CounterHW__CNT_CMP0 )
#else
    #define quaddec_left_Cnt16_STATICCOUNT_LSB     (*(reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__F0_REG )
    #define quaddec_left_Cnt16_STATICCOUNT_LSB_PTR ( (reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__F0_REG )
    #define quaddec_left_Cnt16_PERIOD_LSB          (*(reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__D0_REG )
    #define quaddec_left_Cnt16_PERIOD_LSB_PTR      ( (reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__D0_REG )
    #define quaddec_left_Cnt16_COMPARE_LSB         (*(reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__D1_REG )
    #define quaddec_left_Cnt16_COMPARE_LSB_PTR     ( (reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__D1_REG )
    #define quaddec_left_Cnt16_COUNTER_LSB         (*(reg16 *) \
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__A0_REG )
    #define quaddec_left_Cnt16_COUNTER_LSB_PTR     ( (reg16 *)\
        quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__A0_REG )

	#define quaddec_left_Cnt16_AUX_CONTROLDP0 \
        (*(reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    #define quaddec_left_Cnt16_AUX_CONTROLDP0_PTR \
        ( (reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    #if (quaddec_left_Cnt16_Resolution == 16 || quaddec_left_Cnt16_Resolution == 24 || quaddec_left_Cnt16_Resolution == 32)
       #define quaddec_left_Cnt16_AUX_CONTROLDP1 \
           (*(reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define quaddec_left_Cnt16_AUX_CONTROLDP1_PTR \
           ( (reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif
    #if (quaddec_left_Cnt16_Resolution == 24 || quaddec_left_Cnt16_Resolution == 32)
       #define quaddec_left_Cnt16_AUX_CONTROLDP2 \
           (*(reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define quaddec_left_Cnt16_AUX_CONTROLDP2_PTR \
           ( (reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif
    #if (quaddec_left_Cnt16_Resolution == 32)
       #define quaddec_left_Cnt16_AUX_CONTROLDP3 \
           (*(reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define quaddec_left_Cnt16_AUX_CONTROLDP3_PTR \
           ( (reg8 *) quaddec_left_Cnt16_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif
#endif  /* (quaddec_left_Cnt16_UsingFixedFunction) */

#if (quaddec_left_Cnt16_UsingFixedFunction)
    #define quaddec_left_Cnt16_STATUS         (*(reg8 *) quaddec_left_Cnt16_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define quaddec_left_Cnt16_STATUS_MASK             (*(reg8 *) quaddec_left_Cnt16_CounterHW__SR0 )
    #define quaddec_left_Cnt16_STATUS_MASK_PTR         ( (reg8 *) quaddec_left_Cnt16_CounterHW__SR0 )
    #define quaddec_left_Cnt16_CONTROL                 (*(reg8 *) quaddec_left_Cnt16_CounterHW__CFG0)
    #define quaddec_left_Cnt16_CONTROL_PTR             ( (reg8 *) quaddec_left_Cnt16_CounterHW__CFG0)
    #define quaddec_left_Cnt16_CONTROL2                (*(reg8 *) quaddec_left_Cnt16_CounterHW__CFG1)
    #define quaddec_left_Cnt16_CONTROL2_PTR            ( (reg8 *) quaddec_left_Cnt16_CounterHW__CFG1)
    #if (quaddec_left_Cnt16_PSOC3_ES3 || quaddec_left_Cnt16_PSOC5_ES2)
        #define quaddec_left_Cnt16_CONTROL3       (*(reg8 *) quaddec_left_Cnt16_CounterHW__CFG2)
        #define quaddec_left_Cnt16_CONTROL3_PTR   ( (reg8 *) quaddec_left_Cnt16_CounterHW__CFG2)
    #endif
    #define quaddec_left_Cnt16_GLOBAL_ENABLE           (*(reg8 *) quaddec_left_Cnt16_CounterHW__PM_ACT_CFG)
    #define quaddec_left_Cnt16_GLOBAL_ENABLE_PTR       ( (reg8 *) quaddec_left_Cnt16_CounterHW__PM_ACT_CFG)
    #define quaddec_left_Cnt16_GLOBAL_STBY_ENABLE      (*(reg8 *) quaddec_left_Cnt16_CounterHW__PM_STBY_CFG)
    #define quaddec_left_Cnt16_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) quaddec_left_Cnt16_CounterHW__PM_STBY_CFG)
    
    /********************************
    *    Constants
    ********************************/
    /* Fixed Function Block Chosen */
    #define quaddec_left_Cnt16_BLOCK_EN_MASK          quaddec_left_Cnt16_CounterHW__PM_ACT_MSK
    #define quaddec_left_Cnt16_BLOCK_STBY_EN_MASK     quaddec_left_Cnt16_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define quaddec_left_Cnt16_CTRL_ENABLE_SHIFT      0x00u
    /* Control Register Bit Masks */
    #define quaddec_left_Cnt16_CTRL_ENABLE            (0x01u << quaddec_left_Cnt16_CTRL_ENABLE_SHIFT)         

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (quaddec_left_Cnt16_PSOC3_ES2 || quaddec_left_Cnt16_PSOC5_ES1)
        /* Use CFG1 Mode bits to set run mode */
        #define quaddec_left_Cnt16_CTRL_MODE_SHIFT        0x01u    
        #define quaddec_left_Cnt16_CTRL_MODE_MASK         (0x07u << quaddec_left_Cnt16_CTRL_MODE_SHIFT)
    #endif
    #if (quaddec_left_Cnt16_PSOC3_ES3 || quaddec_left_Cnt16_PSOC5_ES2)
        /* Use CFG2 Mode bits to set run mode */
        #define quaddec_left_Cnt16_CTRL_MODE_SHIFT        0x00u    
        #define quaddec_left_Cnt16_CTRL_MODE_MASK         (0x03u << quaddec_left_Cnt16_CTRL_MODE_SHIFT)
    #endif
    /* Set the mask for interrupt (raw/status register) */
    #define quaddec_left_Cnt16_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define quaddec_left_Cnt16_CTRL2_IRQ_SEL          (0x01u << quaddec_left_Cnt16_CTRL2_IRQ_SEL_SHIFT)     
    
    /* Status Register Bit Locations */
    #define quaddec_left_Cnt16_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK_SHIFT      (quaddec_left_Cnt16_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define quaddec_left_Cnt16_STATUS_ZERO            (0x01u << quaddec_left_Cnt16_STATUS_ZERO_SHIFT)

    /* Status Register Interrupt Bit Masks*/
    #define quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK       (quaddec_left_Cnt16_STATUS_ZERO >> 0x04u)

#else /* !quaddec_left_Cnt16_UsingFixedFunction */
    #define quaddec_left_Cnt16_STATUS               (* (reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define quaddec_left_Cnt16_STATUS_PTR           (  (reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define quaddec_left_Cnt16_STATUS_MASK          (* (reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define quaddec_left_Cnt16_STATUS_MASK_PTR      (  (reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define quaddec_left_Cnt16_STATUS_AUX_CTRL      (*(reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define quaddec_left_Cnt16_STATUS_AUX_CTRL_PTR  ( (reg8 *) quaddec_left_Cnt16_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define quaddec_left_Cnt16_CONTROL              (* (reg8 *) quaddec_left_Cnt16_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define quaddec_left_Cnt16_CONTROL_PTR          (  (reg8 *) quaddec_left_Cnt16_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )

    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define quaddec_left_Cnt16_CTRL_CMPMODE0_SHIFT    0x00u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define quaddec_left_Cnt16_CTRL_CMPMODE_MASK      (0x07u << quaddec_left_Cnt16_CTRL_CMPMODE0_SHIFT)  
    #define quaddec_left_Cnt16_CTRL_CAPMODE_MASK      (0x03u << quaddec_left_Cnt16_CTRL_CAPMODE0_SHIFT)  
    #define quaddec_left_Cnt16_CTRL_RESET             (0x01u << quaddec_left_Cnt16_CTRL_RESET_SHIFT)  
    #define quaddec_left_Cnt16_CTRL_ENABLE            (0x01u << quaddec_left_Cnt16_CTRL_ENABLE_SHIFT) 

    /* Status Register Bit Locations */
    #define quaddec_left_Cnt16_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define quaddec_left_Cnt16_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define quaddec_left_Cnt16_STATUS_CMP_INT_EN_MASK_SHIFT       quaddec_left_Cnt16_STATUS_CMP_SHIFT       
    #define quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK_SHIFT      quaddec_left_Cnt16_STATUS_ZERO_SHIFT      
    #define quaddec_left_Cnt16_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  quaddec_left_Cnt16_STATUS_OVERFLOW_SHIFT  
    #define quaddec_left_Cnt16_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT quaddec_left_Cnt16_STATUS_UNDERFLOW_SHIFT 
    #define quaddec_left_Cnt16_STATUS_CAPTURE_INT_EN_MASK_SHIFT   quaddec_left_Cnt16_STATUS_CAPTURE_SHIFT   
    #define quaddec_left_Cnt16_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  quaddec_left_Cnt16_STATUS_FIFOFULL_SHIFT  
    #define quaddec_left_Cnt16_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  quaddec_left_Cnt16_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define quaddec_left_Cnt16_STATUS_CMP             (0x01u << quaddec_left_Cnt16_STATUS_CMP_SHIFT)  
    #define quaddec_left_Cnt16_STATUS_ZERO            (0x01u << quaddec_left_Cnt16_STATUS_ZERO_SHIFT) 
    #define quaddec_left_Cnt16_STATUS_OVERFLOW        (0x01u << quaddec_left_Cnt16_STATUS_OVERFLOW_SHIFT) 
    #define quaddec_left_Cnt16_STATUS_UNDERFLOW       (0x01u << quaddec_left_Cnt16_STATUS_UNDERFLOW_SHIFT) 
    #define quaddec_left_Cnt16_STATUS_CAPTURE         (0x01u << quaddec_left_Cnt16_STATUS_CAPTURE_SHIFT) 
    #define quaddec_left_Cnt16_STATUS_FIFOFULL        (0x01u << quaddec_left_Cnt16_STATUS_FIFOFULL_SHIFT)
    #define quaddec_left_Cnt16_STATUS_FIFONEMP        (0x01u << quaddec_left_Cnt16_STATUS_FIFONEMP_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define quaddec_left_Cnt16_STATUS_CMP_INT_EN_MASK            quaddec_left_Cnt16_STATUS_CMP                    
    #define quaddec_left_Cnt16_STATUS_ZERO_INT_EN_MASK           quaddec_left_Cnt16_STATUS_ZERO            
    #define quaddec_left_Cnt16_STATUS_OVERFLOW_INT_EN_MASK       quaddec_left_Cnt16_STATUS_OVERFLOW        
    #define quaddec_left_Cnt16_STATUS_UNDERFLOW_INT_EN_MASK      quaddec_left_Cnt16_STATUS_UNDERFLOW       
    #define quaddec_left_Cnt16_STATUS_CAPTURE_INT_EN_MASK        quaddec_left_Cnt16_STATUS_CAPTURE         
    #define quaddec_left_Cnt16_STATUS_FIFOFULL_INT_EN_MASK       quaddec_left_Cnt16_STATUS_FIFOFULL        
    #define quaddec_left_Cnt16_STATUS_FIFONEMP_INT_EN_MASK       quaddec_left_Cnt16_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define quaddec_left_Cnt16_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define quaddec_left_Cnt16_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define quaddec_left_Cnt16_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define quaddec_left_Cnt16_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define quaddec_left_Cnt16_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define quaddec_left_Cnt16_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* quaddec_left_Cnt16_UsingFixedFunction */

#endif  /* CY_COUNTER_quaddec_left_Cnt16_H */


/* [] END OF FILE */


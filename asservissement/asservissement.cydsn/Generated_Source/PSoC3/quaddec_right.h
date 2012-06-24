/*******************************************************************************
* File Name: quaddec_right.h  
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_quaddec_right_H)
#define CY_QUADRATURE_DECODER_quaddec_right_H

#include "cyfitter.h"

#define quaddec_right_COUNTER_SIZE               (32u)

#if (quaddec_right_COUNTER_SIZE == 8u)
    #include "quaddec_right_Cnt8.h"
#else
    #include "quaddec_right_Cnt16.h"
#endif /* quaddec_right_COUNTER_SIZE == 8u */

#if(quaddec_right_COUNTER_SIZE == 32u)

    /* PSoC3 ES2 or early */
    #define quaddec_right_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
                                        (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
                                        
    #if(quaddec_right_PSOC3_ES2 && (quaddec_right_isr__ES2_PATCH))
    
        #include <intrins.h>
        #define quaddec_right_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
        
    #endif /* End PSOC3_ES2 */

#endif /* quaddec_right_COUNTER_SIZE == 32u */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define quaddec_right_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _quaddec_right_backupStruct
{
    uint8 enableState;
} quaddec_right_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void    quaddec_right_Init(void) ;
void    quaddec_right_Start(void);
void    quaddec_right_Stop(void) ;
void    quaddec_right_Enable(void) ;
uint8   quaddec_right_GetEvents(void) ;
void    quaddec_right_SetInterruptMask(uint8 mask) ;
uint8   quaddec_right_GetInterruptMask(void) ;
int32    quaddec_right_GetCounter(void) ;
void    quaddec_right_SetCounter(int32 value);
void    quaddec_right_Sleep(void);
void    quaddec_right_Wakeup(void) ;
void    quaddec_right_SaveConfig(void) ;
void    quaddec_right_RestoreConfig(void) ;

CY_ISR_PROTO(quaddec_right_ISR);


/***************************************
*           API Constants
***************************************/

#define quaddec_right_ISR_NUMBER                 (quaddec_right_isr__INTC_NUMBER)
#define quaddec_right_ISR_PRIORITY               (quaddec_right_isr__INTC_PRIOR_NUM)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define quaddec_right_GLITCH_FILTERING           (1u)
#define quaddec_right_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (quaddec_right_COUNTER_SIZE == 8u)    
    #define quaddec_right_COUNTER_INIT_VALUE    (0x80u)
#else /* (quaddec_right_COUNTER_SIZE == 16u) || (quaddec_right_COUNTER_SIZE == 32u) */
    #define quaddec_right_COUNTER_INIT_VALUE    (0x8000u)
#endif /* quaddec_right_COUNTER_SIZE == 8u */   


/***************************************
*             Registers
***************************************/

#define quaddec_right_STATUS_REG                 (* (reg8 *) quaddec_right_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_right_STATUS_PTR                 (  (reg8 *) quaddec_right_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_right_STATUS_MASK                (* (reg8 *) quaddec_right_bQuadDec_Stsreg__MASK_REG)
#define quaddec_right_STATUS_MASK_PTR            (  (reg8 *) quaddec_right_bQuadDec_Stsreg__MASK_REG)
#define quaddec_right_SR_AUX_CONTROL             (* (reg8 *) quaddec_right_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define quaddec_right_SR_AUX_CONTROL_PTR         (  (reg8 *) quaddec_right_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define quaddec_right_Count32SoftPart            quaddec_right_count32SoftPart
#define quaddec_right_SwStatus                   quaddec_right_swStatus
#define quaddec_right_STATUS                     quaddec_right_STATUS_REG


/***************************************
*        Register Constants
***************************************/

#define quaddec_right_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define quaddec_right_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define quaddec_right_COUNTER_RESET_SHIFT        (0x02u)
#define quaddec_right_INVALID_IN_SHIFT           (0x03u)
#define quaddec_right_COUNTER_OVERFLOW           (0x01u << quaddec_right_COUNTER_OVERFLOW_SHIFT)
#define quaddec_right_COUNTER_UNDERFLOW          (0x01u << quaddec_right_COUNTER_UNDERFLOW_SHIFT)
#define quaddec_right_COUNTER_RESET              (0x01u << quaddec_right_COUNTER_RESET_SHIFT)
#define quaddec_right_INVALID_IN                 (0x01u << quaddec_right_INVALID_IN_SHIFT)

#define quaddec_right_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define quaddec_right_INTERRUPTS_ENABLE          (0x01u << quaddec_right_INTERRUPTS_ENABLE_SHIFT)
#define quaddec_right_INIT_INT_MASK              (0x0Fu)
#define quaddec_right_DISABLE                    (0x00u)     

#endif /* CY_QUADRATURE_DECODER_quaddec_right_H */


/* [] END OF FILE */

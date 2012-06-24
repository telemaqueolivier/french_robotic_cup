/*******************************************************************************
* File Name: quaddec_left.h  
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

#if !defined(CY_QUADRATURE_DECODER_quaddec_left_H)
#define CY_QUADRATURE_DECODER_quaddec_left_H

#include "cyfitter.h"

#define quaddec_left_COUNTER_SIZE               (32u)

#if (quaddec_left_COUNTER_SIZE == 8u)
    #include "quaddec_left_Cnt8.h"
#else
    #include "quaddec_left_Cnt16.h"
#endif /* quaddec_left_COUNTER_SIZE == 8u */

#if(quaddec_left_COUNTER_SIZE == 32u)

    /* PSoC3 ES2 or early */
    #define quaddec_left_PSOC3_ES2  ((CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A) && \
                                        (CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2))
                                        
    #if(quaddec_left_PSOC3_ES2 && (quaddec_left_isr__ES2_PATCH))
    
        #include <intrins.h>
        #define quaddec_left_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
        
    #endif /* End PSOC3_ES2 */

#endif /* quaddec_left_COUNTER_SIZE == 32u */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define quaddec_left_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct _quaddec_left_backupStruct
{
    uint8 enableState;
} quaddec_left_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void    quaddec_left_Init(void) ;
void    quaddec_left_Start(void);
void    quaddec_left_Stop(void) ;
void    quaddec_left_Enable(void) ;
uint8   quaddec_left_GetEvents(void) ;
void    quaddec_left_SetInterruptMask(uint8 mask) ;
uint8   quaddec_left_GetInterruptMask(void) ;
int32    quaddec_left_GetCounter(void) ;
void    quaddec_left_SetCounter(int32 value);
void    quaddec_left_Sleep(void);
void    quaddec_left_Wakeup(void) ;
void    quaddec_left_SaveConfig(void) ;
void    quaddec_left_RestoreConfig(void) ;

CY_ISR_PROTO(quaddec_left_ISR);


/***************************************
*           API Constants
***************************************/

#define quaddec_left_ISR_NUMBER                 (quaddec_left_isr__INTC_NUMBER)
#define quaddec_left_ISR_PRIORITY               (quaddec_left_isr__INTC_PRIOR_NUM)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define quaddec_left_GLITCH_FILTERING           (1u)
#define quaddec_left_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (quaddec_left_COUNTER_SIZE == 8u)    
    #define quaddec_left_COUNTER_INIT_VALUE    (0x80u)
#else /* (quaddec_left_COUNTER_SIZE == 16u) || (quaddec_left_COUNTER_SIZE == 32u) */
    #define quaddec_left_COUNTER_INIT_VALUE    (0x8000u)
#endif /* quaddec_left_COUNTER_SIZE == 8u */   


/***************************************
*             Registers
***************************************/

#define quaddec_left_STATUS_REG                 (* (reg8 *) quaddec_left_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_left_STATUS_PTR                 (  (reg8 *) quaddec_left_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_left_STATUS_MASK                (* (reg8 *) quaddec_left_bQuadDec_Stsreg__MASK_REG)
#define quaddec_left_STATUS_MASK_PTR            (  (reg8 *) quaddec_left_bQuadDec_Stsreg__MASK_REG)
#define quaddec_left_SR_AUX_CONTROL             (* (reg8 *) quaddec_left_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define quaddec_left_SR_AUX_CONTROL_PTR         (  (reg8 *) quaddec_left_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define quaddec_left_Count32SoftPart            quaddec_left_count32SoftPart
#define quaddec_left_SwStatus                   quaddec_left_swStatus
#define quaddec_left_STATUS                     quaddec_left_STATUS_REG


/***************************************
*        Register Constants
***************************************/

#define quaddec_left_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define quaddec_left_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define quaddec_left_COUNTER_RESET_SHIFT        (0x02u)
#define quaddec_left_INVALID_IN_SHIFT           (0x03u)
#define quaddec_left_COUNTER_OVERFLOW           (0x01u << quaddec_left_COUNTER_OVERFLOW_SHIFT)
#define quaddec_left_COUNTER_UNDERFLOW          (0x01u << quaddec_left_COUNTER_UNDERFLOW_SHIFT)
#define quaddec_left_COUNTER_RESET              (0x01u << quaddec_left_COUNTER_RESET_SHIFT)
#define quaddec_left_INVALID_IN                 (0x01u << quaddec_left_INVALID_IN_SHIFT)

#define quaddec_left_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define quaddec_left_INTERRUPTS_ENABLE          (0x01u << quaddec_left_INTERRUPTS_ENABLE_SHIFT)
#define quaddec_left_INIT_INT_MASK              (0x0Fu)
#define quaddec_left_DISABLE                    (0x00u)     

#endif /* CY_QUADRATURE_DECODER_quaddec_left_H */


/* [] END OF FILE */

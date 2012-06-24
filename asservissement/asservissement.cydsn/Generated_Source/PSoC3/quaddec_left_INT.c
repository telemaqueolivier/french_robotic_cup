/*******************************************************************************
* File Name: quaddec_left_INT.c  
* Version 1.50
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
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

#include "quaddec_left.h"

volatile int32 quaddec_left_count32SoftPart = 0u;
static uint8 quaddec_left_swStatus;


/*******************************************************************************
* FUNCTION NAME: void quaddec_left_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  quaddec_left_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  quaddec_left_swStatus - modified with the updated values of STATUS 
*  register.
*
*******************************************************************************/
CY_ISR( quaddec_left_ISR )
{
   quaddec_left_swStatus = quaddec_left_STATUS_REG;
   
    /* User code required at start of ISR */
    /* `#START quaddec_left_ISR_START` */

    /* `#END` */
    
    if(quaddec_left_swStatus & quaddec_left_COUNTER_OVERFLOW)
    {
        quaddec_left_count32SoftPart += 0x7FFFu;
    }
    else if(quaddec_left_swStatus & quaddec_left_COUNTER_UNDERFLOW)
    {
        quaddec_left_count32SoftPart -= 0x8000u;
    }
    
    if(quaddec_left_swStatus & quaddec_left_COUNTER_RESET)
    {
        quaddec_left_count32SoftPart = 0u;
    }
    
    /* User code required at end of ISR */
    /* `#START quaddec_left_ISR_END` */

    /* `#END` */
    
    /* PSoC3 ES1, ES2 quaddec_left ISR PATCH  */     
    #if(quaddec_left_PSOC3_ES2 && (quaddec_left_isr__ES2_PATCH))
        quaddec_left_ISR_PATCH();
    #endif /* End quaddec_left_PSOC3_ES2*/   
}


/* [] END OF FILE */

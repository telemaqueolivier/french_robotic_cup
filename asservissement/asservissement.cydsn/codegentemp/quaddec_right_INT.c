/*******************************************************************************
* File Name: quaddec_right_INT.c  
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

#include "quaddec_right.h"

volatile int32 quaddec_right_count32SoftPart = 0u;
static uint8 quaddec_right_swStatus;


/*******************************************************************************
* FUNCTION NAME: void quaddec_right_ISR
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
*  quaddec_right_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  quaddec_right_swStatus - modified with the updated values of STATUS 
*  register.
*
*******************************************************************************/
CY_ISR( quaddec_right_ISR )
{
   quaddec_right_swStatus = quaddec_right_STATUS_REG;
   
    /* User code required at start of ISR */
    /* `#START quaddec_right_ISR_START` */

    /* `#END` */
    
    if(quaddec_right_swStatus & quaddec_right_COUNTER_OVERFLOW)
    {
        quaddec_right_count32SoftPart += 0x7FFFu;
    }
    else if(quaddec_right_swStatus & quaddec_right_COUNTER_UNDERFLOW)
    {
        quaddec_right_count32SoftPart -= 0x8000u;
    }
    
    if(quaddec_right_swStatus & quaddec_right_COUNTER_RESET)
    {
        quaddec_right_count32SoftPart = 0u;
    }
    
    /* User code required at end of ISR */
    /* `#START quaddec_right_ISR_END` */

    /* `#END` */
    
    /* PSoC3 ES1, ES2 quaddec_right ISR PATCH  */     
    #if(quaddec_right_PSOC3_ES2 && (quaddec_right_isr__ES2_PATCH))
        quaddec_right_ISR_PATCH();
    #endif /* End quaddec_right_PSOC3_ES2*/   
}


/* [] END OF FILE */

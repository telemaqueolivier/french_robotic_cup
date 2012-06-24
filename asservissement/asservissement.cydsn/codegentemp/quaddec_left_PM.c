/*******************************************************************************
* File Name: quaddec_left_PM.c
* Version 1.50
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

static quaddec_left_BACKUP_STRUCT quaddec_left_backup = {0u};


/*******************************************************************************
* Function Name: quaddec_left_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_left_SaveConfig(void) 
{
    #if (quaddec_left_COUNTER_SIZE == 8u)
        quaddec_left_Cnt8_SaveConfig();
    #else /* (quaddec_left_COUNTER_SIZE == 16u) || (quaddec_left_COUNTER_SIZE == 32u) */
        quaddec_left_Cnt16_SaveConfig();                                          
    #endif /* (quaddec_left_COUNTER_SIZE == 8u) */
}


/*******************************************************************************
* Function Name: quaddec_left_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_left_RestoreConfig(void) 
{
    #if (quaddec_left_COUNTER_SIZE == 8u)
        quaddec_left_Cnt8_RestoreConfig();
    #else /* (quaddec_left_COUNTER_SIZE == 16u) || (quaddec_left_COUNTER_SIZE == 32u) */
        quaddec_left_Cnt16_RestoreConfig();                                          
    #endif /* (quaddec_left_COUNTER_SIZE == 8u) */
}


/*******************************************************************************
* Function Name: quaddec_left_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:  
*  None.  
*
* Return: 
*  None.
*
* Global Variables:
*  quaddec_left_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_left_Sleep(void)
{   
    if((quaddec_left_SR_AUX_CONTROL & quaddec_left_INTERRUPTS_ENABLE) == quaddec_left_INTERRUPTS_ENABLE)
    {
        quaddec_left_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        quaddec_left_backup.enableState = 0u;
    }
    
    quaddec_left_Stop();
    
    quaddec_left_SaveConfig();
}


/*******************************************************************************
* Function Name: quaddec_left_Wakeup
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  quaddec_left_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void quaddec_left_Wakeup(void) 
{             
    quaddec_left_RestoreConfig();
    
    if(quaddec_left_backup.enableState != 0u)
    {       
        #if (quaddec_left_COUNTER_SIZE == 8u)
            quaddec_left_Cnt8_Enable();
        #else /* (quaddec_left_COUNTER_SIZE == 16u) || (quaddec_left_COUNTER_SIZE == 32u) */
            quaddec_left_Cnt16_Enable();                                          
        #endif /* (quaddec_left_COUNTER_SIZE == 8u) */
        
        /* Enable component's operation */
        quaddec_left_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */


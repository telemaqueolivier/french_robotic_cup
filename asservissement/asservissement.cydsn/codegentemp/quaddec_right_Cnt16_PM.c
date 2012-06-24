/*******************************************************************************
* File Name: quaddec_right_Cnt16_PM.c  
* Version 1.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "quaddec_right_Cnt16.h"

static quaddec_right_Cnt16_backupStruct quaddec_right_Cnt16_backup;


/*******************************************************************************
* Function Name: quaddec_right_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_right_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*    No
*
*******************************************************************************/
void quaddec_right_Cnt16_SaveConfig(void)
{
    #if (! quaddec_right_Cnt16_UsingFixedFunction)    
        #if(!quaddec_right_Cnt16_ControlRegRemoved)
            quaddec_right_Cnt16_backup.control = quaddec_right_Cnt16_ReadControlRegister();
        #endif
        
        quaddec_right_Cnt16_backup.counterUdb = quaddec_right_Cnt16_ReadCounter();
        quaddec_right_Cnt16_backup.captureValue = quaddec_right_Cnt16_ReadCapture();
    #endif
}


/*******************************************************************************
* Function Name: quaddec_right_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_right_Cnt16_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void quaddec_right_Cnt16_RestoreConfig(void) 
{      
    #if (! quaddec_right_Cnt16_UsingFixedFunction)     
        #if(!quaddec_right_Cnt16_ControlRegRemoved)
            quaddec_right_Cnt16_WriteControlRegister(quaddec_right_Cnt16_backup.control);
        #endif
        
        quaddec_right_Cnt16_WriteCounter(quaddec_right_Cnt16_backup.counterUdb);        
        CY_SET_REG16 (quaddec_right_Cnt16_STATICCOUNT_LSB_PTR, quaddec_right_Cnt16_backup.captureValue);
    #endif
}


/*******************************************************************************
* Function Name: quaddec_right_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_right_Cnt16_backup.enableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void quaddec_right_Cnt16_Sleep(void)
{
    #if(!quaddec_right_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(quaddec_right_Cnt16_CTRL_ENABLE == (quaddec_right_Cnt16_CONTROL & quaddec_right_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            quaddec_right_Cnt16_backup.enableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            quaddec_right_Cnt16_backup.enableState = 0u;
        }
    #endif
    
    quaddec_right_Cnt16_Stop();
    quaddec_right_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: quaddec_right_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_right_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void quaddec_right_Cnt16_Wakeup(void) 
{
    quaddec_right_Cnt16_RestoreConfig();
    
    #if(!quaddec_right_Cnt16_ControlRegRemoved)
        if(quaddec_right_Cnt16_backup.enableState == 1u)
        {
            /* Enable Counter's operation */
            quaddec_right_Cnt16_Enable();
    
        } /* Do nothing if Counter was disabled before */    
    #endif
}


/* [] END OF FILE */

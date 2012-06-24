/*******************************************************************************
* File Name: timer_asserv_PM.c  
* Version 2.0
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.  
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

#include "timer_asserv.h"
static timer_asserv_backupStruct timer_asserv_backup;

/*******************************************************************************
* Function Name: timer_asserv_SaveConfig
********************************************************************************
*
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
*  timer_asserv_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*    No
*
*******************************************************************************/
void timer_asserv_SaveConfig(void)
{   
    #if (!timer_asserv_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
            timer_asserv_backup.TimerUdb = timer_asserv_ReadCounter();
            timer_asserv_backup.TimerPeriod = timer_asserv_ReadPeriod();
            timer_asserv_backup.InterruptMaskValue = timer_asserv_STATUS_MASK;
            #if (timer_asserv_UsingHWCaptureCounter)
                timer_asserv_backup.TimerCaptureCounter = timer_asserv_ReadCaptureCount();        
            #endif
        #endif
        
        #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
            timer_asserv_backup.TimerUdb = timer_asserv_ReadCounter();
            timer_asserv_backup.InterruptMaskValue = timer_asserv_STATUS_MASK;
            #if (timer_asserv_UsingHWCaptureCounter)
                timer_asserv_backup.TimerCaptureCounter = timer_asserv_ReadCaptureCount();        
            #endif
        #endif
        
        #if(!timer_asserv_ControlRegRemoved)
            timer_asserv_backup.TimerControlRegister = timer_asserv_ReadControlRegister();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: timer_asserv_RestoreConfig
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
*  timer_asserv_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void timer_asserv_RestoreConfig(void) 
{
    #if (!timer_asserv_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
            timer_asserv_WriteCounter(timer_asserv_backup.TimerUdb);
            timer_asserv_WritePeriod(timer_asserv_backup.TimerPeriod);
            timer_asserv_STATUS_MASK =timer_asserv_backup.InterruptMaskValue;
            #if (timer_asserv_UsingHWCaptureCounter)
                timer_asserv_SetCaptureCount(timer_asserv_backup.TimerCaptureCounter);        
            #endif
        #endif
        
        #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
            timer_asserv_WriteCounter(timer_asserv_backup.TimerUdb);
            timer_asserv_STATUS_MASK =timer_asserv_backup.InterruptMaskValue;
            #if (timer_asserv_UsingHWCaptureCounter)
                timer_asserv_SetCaptureCount(timer_asserv_backup.TimerCaptureCounter);           
            #endif
        #endif
        
        #if(!timer_asserv_ControlRegRemoved)
            timer_asserv_WriteControlRegister(timer_asserv_backup.TimerControlRegister);
        #endif
    #endif
}


/*******************************************************************************
* Function Name: timer_asserv_Sleep
********************************************************************************
*
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
*  timer_asserv_backup.TimerEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*    No
*
*******************************************************************************/
void timer_asserv_Sleep(void)
{
    #if(!timer_asserv_ControlRegRemoved)
        /* Save Counter's enable state */
        if(timer_asserv_CTRL_ENABLE == (timer_asserv_CONTROL & timer_asserv_CTRL_ENABLE))
        {
            /* Timer is enabled */
            timer_asserv_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            timer_asserv_backup.TimerEnableState = 0u;
        }
    #endif
    timer_asserv_Stop();
    timer_asserv_SaveConfig();
}


/*******************************************************************************
* Function Name: timer_asserv_Wakeup
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
*  timer_asserv_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void timer_asserv_Wakeup(void) 
{
    timer_asserv_RestoreConfig();
    #if(!timer_asserv_ControlRegRemoved)
        if(timer_asserv_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                timer_asserv_Enable();
        } /* Do nothing if Timer was disabled before */ 
    #endif
}


/* [] END OF FILE */

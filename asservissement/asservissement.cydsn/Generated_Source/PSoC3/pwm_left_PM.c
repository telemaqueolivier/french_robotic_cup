/*******************************************************************************
* File Name: pwm_left_PM.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "pwm_left.h"

static pwm_left_backupStruct pwm_left_backup;


/*******************************************************************************
* Function Name: pwm_left_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pwm_left_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pwm_left_SaveConfig(void)
{
    
    #if(!pwm_left_UsingFixedFunction)
        #if (pwm_left_PSOC3_ES2 || pwm_left_PSOC5_ES1)
            pwm_left_backup.PWMUdb = pwm_left_ReadCounter();
            pwm_left_backup.PWMPeriod = pwm_left_ReadPeriod();
            #if (pwm_left_UseStatus)
				pwm_left_backup.InterruptMaskValue = pwm_left_STATUS_MASK;
            #endif
			
            #if(pwm_left_UseOneCompareMode)
                pwm_left_backup.PWMCompareValue = pwm_left_ReadCompare();
            #else
                pwm_left_backup.PWMCompareValue1 = pwm_left_ReadCompare1();
                pwm_left_backup.PWMCompareValue2 = pwm_left_ReadCompare2();
            #endif
            
           #if(pwm_left_DeadBandUsed)
                pwm_left_backup.PWMdeadBandValue = pwm_left_ReadDeadTime();
            #endif
          
            #if ( pwm_left_KillModeMinTime)
                pwm_left_backup.PWMKillCounterPeriod = pwm_left_ReadKillTime();
            #endif
        #endif
        
        #if (pwm_left_PSOC3_ES3 || pwm_left_PSOC5_ES2)
            pwm_left_backup.PWMUdb = pwm_left_ReadCounter();
            #if (pwm_left_UseStatus)
				pwm_left_backup.InterruptMaskValue = pwm_left_STATUS_MASK;
			#endif
            
            #if(pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_256_CLOCKS || pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_2_4_CLOCKS)
                pwm_left_backup.PWMdeadBandValue = pwm_left_ReadDeadTime();
            #endif
            
            #if(pwm_left_KillModeMinTime)
                 pwm_left_backup.PWMKillCounterPeriod = pwm_left_ReadKillTime();
            #endif
        #endif
        
        #if(pwm_left_UseControl)
            pwm_left_backup.PWMControlRegister = pwm_left_ReadControlRegister();
        #endif
    #endif  
}


/*******************************************************************************
* Function Name: pwm_left_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pwm_left_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void pwm_left_RestoreConfig(void) 
{
        #if(!pwm_left_UsingFixedFunction)
            #if (pwm_left_PSOC3_ES2 || pwm_left_PSOC5_ES1)
                pwm_left_WriteCounter(pwm_left_backup.PWMUdb);
                pwm_left_WritePeriod(pwm_left_backup.PWMPeriod);
                #if (pwm_left_UseStatus)
					pwm_left_STATUS_MASK = pwm_left_backup.InterruptMaskValue;
                #endif
				
                #if(pwm_left_UseOneCompareMode)
                    pwm_left_WriteCompare(pwm_left_backup.PWMCompareValue);
                #else
                    pwm_left_WriteCompare1(pwm_left_backup.PWMCompareValue1);
                    pwm_left_WriteCompare2(pwm_left_backup.PWMCompareValue2);
                #endif
                
               #if(pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_256_CLOCKS || pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_2_4_CLOCKS)
                    pwm_left_WriteDeadTime(pwm_left_backup.PWMdeadBandValue);
                #endif
            
                #if ( pwm_left_KillModeMinTime)
                    pwm_left_WriteKillTime(pwm_left_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if (pwm_left_PSOC3_ES3 || pwm_left_PSOC5_ES2)
                pwm_left_WriteCounter(pwm_left_backup.PWMUdb);
                #if (pwm_left_UseStatus)
                    pwm_left_STATUS_MASK = pwm_left_backup.InterruptMaskValue;
                #endif
                
                #if(pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_256_CLOCKS || pwm_left_DeadBandMode == pwm_left__B_PWM__DBM_2_4_CLOCKS)
                    pwm_left_WriteDeadTime(pwm_left_backup.PWMdeadBandValue);
                #endif
                
                #if(pwm_left_KillModeMinTime)
                    pwm_left_WriteKillTime(pwm_left_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if(pwm_left_UseControl)
                pwm_left_WriteControlRegister(pwm_left_backup.PWMControlRegister); 
            #endif
        #endif  
    }


/*******************************************************************************
* Function Name: pwm_left_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pwm_left_backup.PWMEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pwm_left_Sleep(void)
{
    #if(pwm_left_UseControl)
        if(pwm_left_CTRL_ENABLE == (pwm_left_CONTROL & pwm_left_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwm_left_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwm_left_backup.PWMEnableState = 0u;
        }
    #endif
    /* Stop component */
    pwm_left_Stop();
    
    /* Save registers configuration */
    pwm_left_SaveConfig();
}


/*******************************************************************************
* Function Name: pwm_left_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  pwm_left_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_Wakeup(void) 
{
     /* Restore registers values */
    pwm_left_RestoreConfig();
    
    if(pwm_left_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwm_left_Enable();
    } /* Do nothing if component's block was disabled before */
    
}

/* [] END OF FILE */

/*******************************************************************************
* File Name: pwm_right_PM.c
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
#include "pwm_right.h"

static pwm_right_backupStruct pwm_right_backup;


/*******************************************************************************
* Function Name: pwm_right_SaveConfig
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
*  pwm_right_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pwm_right_SaveConfig(void)
{
    
    #if(!pwm_right_UsingFixedFunction)
        #if (pwm_right_PSOC3_ES2 || pwm_right_PSOC5_ES1)
            pwm_right_backup.PWMUdb = pwm_right_ReadCounter();
            pwm_right_backup.PWMPeriod = pwm_right_ReadPeriod();
            #if (pwm_right_UseStatus)
				pwm_right_backup.InterruptMaskValue = pwm_right_STATUS_MASK;
            #endif
			
            #if(pwm_right_UseOneCompareMode)
                pwm_right_backup.PWMCompareValue = pwm_right_ReadCompare();
            #else
                pwm_right_backup.PWMCompareValue1 = pwm_right_ReadCompare1();
                pwm_right_backup.PWMCompareValue2 = pwm_right_ReadCompare2();
            #endif
            
           #if(pwm_right_DeadBandUsed)
                pwm_right_backup.PWMdeadBandValue = pwm_right_ReadDeadTime();
            #endif
          
            #if ( pwm_right_KillModeMinTime)
                pwm_right_backup.PWMKillCounterPeriod = pwm_right_ReadKillTime();
            #endif
        #endif
        
        #if (pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
            pwm_right_backup.PWMUdb = pwm_right_ReadCounter();
            #if (pwm_right_UseStatus)
				pwm_right_backup.InterruptMaskValue = pwm_right_STATUS_MASK;
			#endif
            
            #if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS || pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
                pwm_right_backup.PWMdeadBandValue = pwm_right_ReadDeadTime();
            #endif
            
            #if(pwm_right_KillModeMinTime)
                 pwm_right_backup.PWMKillCounterPeriod = pwm_right_ReadKillTime();
            #endif
        #endif
        
        #if(pwm_right_UseControl)
            pwm_right_backup.PWMControlRegister = pwm_right_ReadControlRegister();
        #endif
    #endif  
}


/*******************************************************************************
* Function Name: pwm_right_RestoreConfig
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
*  pwm_right_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes.
*
*******************************************************************************/
void pwm_right_RestoreConfig(void) 
{
        #if(!pwm_right_UsingFixedFunction)
            #if (pwm_right_PSOC3_ES2 || pwm_right_PSOC5_ES1)
                pwm_right_WriteCounter(pwm_right_backup.PWMUdb);
                pwm_right_WritePeriod(pwm_right_backup.PWMPeriod);
                #if (pwm_right_UseStatus)
					pwm_right_STATUS_MASK = pwm_right_backup.InterruptMaskValue;
                #endif
				
                #if(pwm_right_UseOneCompareMode)
                    pwm_right_WriteCompare(pwm_right_backup.PWMCompareValue);
                #else
                    pwm_right_WriteCompare1(pwm_right_backup.PWMCompareValue1);
                    pwm_right_WriteCompare2(pwm_right_backup.PWMCompareValue2);
                #endif
                
               #if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS || pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
                    pwm_right_WriteDeadTime(pwm_right_backup.PWMdeadBandValue);
                #endif
            
                #if ( pwm_right_KillModeMinTime)
                    pwm_right_WriteKillTime(pwm_right_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if (pwm_right_PSOC3_ES3 || pwm_right_PSOC5_ES2)
                pwm_right_WriteCounter(pwm_right_backup.PWMUdb);
                #if (pwm_right_UseStatus)
                    pwm_right_STATUS_MASK = pwm_right_backup.InterruptMaskValue;
                #endif
                
                #if(pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_256_CLOCKS || pwm_right_DeadBandMode == pwm_right__B_PWM__DBM_2_4_CLOCKS)
                    pwm_right_WriteDeadTime(pwm_right_backup.PWMdeadBandValue);
                #endif
                
                #if(pwm_right_KillModeMinTime)
                    pwm_right_WriteKillTime(pwm_right_backup.PWMKillCounterPeriod);
                #endif
            #endif
            
            #if(pwm_right_UseControl)
                pwm_right_WriteControlRegister(pwm_right_backup.PWMControlRegister); 
            #endif
        #endif  
    }


/*******************************************************************************
* Function Name: pwm_right_Sleep
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
*  pwm_right_backup.PWMEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void pwm_right_Sleep(void)
{
    #if(pwm_right_UseControl)
        if(pwm_right_CTRL_ENABLE == (pwm_right_CONTROL & pwm_right_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwm_right_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwm_right_backup.PWMEnableState = 0u;
        }
    #endif
    /* Stop component */
    pwm_right_Stop();
    
    /* Save registers configuration */
    pwm_right_SaveConfig();
}


/*******************************************************************************
* Function Name: pwm_right_Wakeup
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
*  pwm_right_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_right_Wakeup(void) 
{
     /* Restore registers values */
    pwm_right_RestoreConfig();
    
    if(pwm_right_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwm_right_Enable();
    } /* Do nothing if component's block was disabled before */
    
}

/* [] END OF FILE */

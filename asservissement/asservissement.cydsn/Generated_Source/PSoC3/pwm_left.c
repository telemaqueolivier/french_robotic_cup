/*******************************************************************************
* File Name: pwm_left.c  
* Version 2.0
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks. 
*  The compare value output may be configured to be active when the present 
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "pwm_left.h"

uint8 pwm_left_initVar = 0u;

/*******************************************************************************
* Function Name: pwm_left_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  pwm_left_initVar: Is modified when this function is called for the first 
*   time. Is used to ensure that initialization happens only once.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(pwm_left_initVar == 0u)
    {
        pwm_left_Init();
        pwm_left_initVar = 1u;
    }
    pwm_left_Enable();

}


/*******************************************************************************
* Function Name: pwm_left_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  pwm_left_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_Init(void) 
{
    #if (pwm_left_UsingFixedFunction || pwm_left_UseControl)
        uint8 ctrl;
    #endif
    
    #if(!pwm_left_UsingFixedFunction) 
        #if(pwm_left_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 pwm_left_interruptState;
        #endif
    #endif
    
   #if (pwm_left_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        pwm_left_CONTROL |= pwm_left_CFG0_MODE;
        #if (pwm_left_DeadBand2_4)
            pwm_left_CONTROL |= pwm_left_CFG0_DB;
        #endif
                
        /* Set the default Compare Mode */
        #if(pwm_left_PSOC3_ES2 || pwm_left_PSOC5_ES1)
                ctrl = pwm_left_CONTROL2 & ~pwm_left_CTRL_CMPMODE1_MASK;
                pwm_left_CONTROL2 = ctrl | pwm_left_DEFAULT_COMPARE1_MODE;
        #endif
        #if(pwm_left_PSOC3_ES3 || pwm_left_PSOC5_ES2)
                ctrl = pwm_left_CONTROL3 & ~pwm_left_CTRL_CMPMODE1_MASK;
                pwm_left_CONTROL3 = ctrl | pwm_left_DEFAULT_COMPARE1_MODE;
        #endif
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        pwm_left_RT1 &= ~pwm_left_RT1_MASK;
        pwm_left_RT1 |= pwm_left_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        pwm_left_RT1 &= ~(pwm_left_SYNCDSI_MASK);
        pwm_left_RT1 |= pwm_left_SYNCDSI_EN;
       
    #elif (pwm_left_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = pwm_left_CONTROL & ~pwm_left_CTRL_CMPMODE2_MASK & ~pwm_left_CTRL_CMPMODE1_MASK;
        pwm_left_CONTROL = ctrl | pwm_left_DEFAULT_COMPARE2_MODE | pwm_left_DEFAULT_COMPARE1_MODE;
    #endif 
        
    #if (!pwm_left_UsingFixedFunction)
        #if (pwm_left_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            pwm_left_AUX_CONTROLDP0 |= (pwm_left_AUX_CTRL_FIFO0_CLR);
        #else /* (pwm_left_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            pwm_left_AUX_CONTROLDP0 |= (pwm_left_AUX_CTRL_FIFO0_CLR);
            pwm_left_AUX_CONTROLDP1 |= (pwm_left_AUX_CTRL_FIFO0_CLR);
        #endif
    #endif
        
    pwm_left_WritePeriod(pwm_left_INIT_PERIOD_VALUE);
    pwm_left_WriteCounter(pwm_left_INIT_PERIOD_VALUE);
        
        #if (pwm_left_UseOneCompareMode)
            pwm_left_WriteCompare(pwm_left_INIT_COMPARE_VALUE1);
        #else
            pwm_left_WriteCompare1(pwm_left_INIT_COMPARE_VALUE1);
            pwm_left_WriteCompare2(pwm_left_INIT_COMPARE_VALUE2);
        #endif
        
        #if (pwm_left_KillModeMinTime)
            pwm_left_WriteKillTime(pwm_left_MinimumKillTime);
        #endif
        
        #if (pwm_left_DeadBandUsed)
            pwm_left_WriteDeadTime(pwm_left_INIT_DEAD_TIME);
        #endif

    #if (pwm_left_UseStatus || pwm_left_UsingFixedFunction)
        pwm_left_SetInterruptMode(pwm_left_INIT_INTERRUPTS_MODE);
    #endif
        
    #if (pwm_left_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        pwm_left_GLOBAL_ENABLE |= pwm_left_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        pwm_left_CONTROL2 |= pwm_left_CTRL2_IRQ_SEL;
    #else
        #if(pwm_left_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            pwm_left_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            pwm_left_STATUS_AUX_CTRL |= pwm_left_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(pwm_left_interruptState);
            
            /* Clear the FIFO to enable the pwm_left_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            pwm_left_ClearFIFO();
        #endif
    #endif
}


/*******************************************************************************
* Function Name: pwm_left_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_Enable(void) 
{
    #if (pwm_left_UseControl || pwm_left_UsingFixedFunction)
        pwm_left_CONTROL |= pwm_left_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: pwm_left_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_Stop(void) 
{
    #if (pwm_left_UseControl || pwm_left_UsingFixedFunction)
        pwm_left_CONTROL &= ~pwm_left_CTRL_ENABLE;
    #endif
}


#if (pwm_left_UseOneCompareMode)
#if (pwm_left_CompareMode1SW)
/*******************************************************************************
* Function Name: pwm_left_SetCompareMode
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm output when in Dither mode,
*  Center Align Mode or One Output Mode.
*
* Parameters:
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return:
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_SetCompareMode(uint8 comparemode) 
{
    #if(pwm_left_UsingFixedFunction)
            #if(pwm_left_PSOC3_ES2 || pwm_left_PSOC5_ES1)
                        uint8 comparemodemasked = (comparemode << pwm_left_CTRL_CMPMODE1_SHIFT);
                        pwm_left_CONTROL2 &= ~pwm_left_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
                        pwm_left_CONTROL2 |= comparemodemasked;  
                #endif
                
            #if(pwm_left_PSOC3_ES3 || pwm_left_PSOC5_ES2)
                    uint8 comparemodemasked = (comparemode << pwm_left_CTRL_CMPMODE1_SHIFT);
            pwm_left_CONTROL3 &= ~pwm_left_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            pwm_left_CONTROL3 |= comparemodemasked;     
                #endif
                
    #elif (pwm_left_UseControl)
        uint8 comparemode1masked = (comparemode << pwm_left_CTRL_CMPMODE1_SHIFT) & pwm_left_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << pwm_left_CTRL_CMPMODE2_SHIFT) & pwm_left_CTRL_CMPMODE2_MASK;
        pwm_left_CONTROL &= ~(pwm_left_CTRL_CMPMODE1_MASK | pwm_left_CTRL_CMPMODE2_MASK); /*Clear existing mode */
        pwm_left_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif
}
#endif /* pwm_left_CompareMode1SW */

#else /* UseOneCompareMode */


#if (pwm_left_CompareMode1SW)
/*******************************************************************************
* Function Name: pwm_left_SetCompareMode1
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm1 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << pwm_left_CTRL_CMPMODE1_SHIFT) & pwm_left_CTRL_CMPMODE1_MASK;
    #if(pwm_left_UsingFixedFunction)
            #if(pwm_left_PSOC3_ES2 || pwm_left_PSOC5_ES1)
                        pwm_left_CONTROL2 &= pwm_left_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        pwm_left_CONTROL2 |= comparemodemasked; 
            #endif
                
                #if(pwm_left_PSOC3_ES3 || pwm_left_PSOC5_ES2)
                    pwm_left_CONTROL3 &= pwm_left_CTRL_CMPMODE1_MASK; /*Clear existing mode */
                        pwm_left_CONTROL3 |= comparemodemasked; 
            #endif
                
    #elif (pwm_left_UseControl)
        pwm_left_CONTROL &= pwm_left_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        pwm_left_CONTROL |= comparemodemasked;
    #endif    
}
#endif /* pwm_left_CompareMode1SW */


#if (pwm_left_CompareMode2SW)
/*******************************************************************************
* Function Name: pwm_left_SetCompareMode2
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm2 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_SetCompareMode2(uint8 comparemode) 
{
    #if(pwm_left_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block*/ 
    #elif (pwm_left_UseControl)
    uint8 comparemodemasked = (comparemode << pwm_left_CTRL_CMPMODE2_SHIFT) & pwm_left_CTRL_CMPMODE2_MASK;
    pwm_left_CONTROL &= pwm_left_CTRL_CMPMODE2_MASK; /*Clear existing mode */
    pwm_left_CONTROL |= comparemodemasked;
    #endif    
}
#endif /*pwm_left_CompareMode2SW */
#endif /* UseOneCompareMode */


/*******************************************************************************
* Function Name: pwm_left_WriteCounter
********************************************************************************
* 
* Summary:
*  This function is used to change the counter value.
*
* Parameters:  
*  counter:  This value may be between 1 and (2^Resolution)-1.   
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WriteCounter(uint16 counter) 
{
    #if(pwm_left_UsingFixedFunction)
        CY_SET_REG16(pwm_left_COUNTER_LSB_PTR, (uint16)counter);
    #else
        CY_SET_REG16(pwm_left_COUNTER_LSB_PTR, counter);
    #endif
}


#if (!pwm_left_UsingFixedFunction)
/*******************************************************************************
* Function Name: pwm_left_ReadCounter
********************************************************************************
* 
* Summary:
*  This function returns the current value of the counter.  It doesn't matter
*  if the counter is enabled or running.
*
* Parameters:  
*  void  
*
* Return: 
*  The current value of the counter.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint16 pwm_left_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(pwm_left_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG16(pwm_left_CAPTURE_LSB_PTR));
}


#if (pwm_left_UseStatus)
/*******************************************************************************
* Function Name: pwm_left_ClearFIFO
********************************************************************************
* 
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_ClearFIFO(void) 
{
    while(pwm_left_ReadStatusRegister() & pwm_left_STATUS_FIFONEMPTY)
        pwm_left_ReadCapture();
}
#endif /* pwm_left_UseStatus */
#endif /* !pwm_left_UsingFixedFunction */


/*******************************************************************************
* Function Name: pwm_left_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0 
*           will result in the counter remaining at zero.
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WritePeriod(uint16 period) 
{
    #if(pwm_left_UsingFixedFunction)
        CY_SET_REG16(pwm_left_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(pwm_left_PERIOD_LSB_PTR, period);
    #endif
}


#if (pwm_left_UseOneCompareMode)
/*******************************************************************************
* Function Name: pwm_left_WriteCompare
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value when the PWM is in Dither
*  mode. The compare output will reflect the new value on the next UDB clock. 
*  The compare output will be driven high when the present counter value is 
*  compared to the compare value based on the compare mode defined in 
*  Dither Mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Side Effects:
*  This function is only available if the PWM mode parameter is set to
*  Dither Mode, Center Aligned Mode or One Output Mode
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WriteCompare(uint16 compare) 
{
   CY_SET_REG16(pwm_left_COMPARE1_LSB_PTR, compare);
   #if (pwm_left_PWMMode == pwm_left__B_PWM__DITHER)
        CY_SET_REG16(pwm_left_COMPARE2_LSB_PTR, compare+1);
   #endif
}


#else


/*******************************************************************************
* Function Name: pwm_left_WriteCompare1
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value.  The compare output will 
*  reflect the new value on the next UDB clock.  The compare output will be 
*  driven high when the present counter value is less than or less than or 
*  equal to the compare register, depending on the mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WriteCompare1(uint16 compare) 
{
    #if(pwm_left_UsingFixedFunction)
        CY_SET_REG16(pwm_left_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(pwm_left_COMPARE1_LSB_PTR, compare);
    #endif
}


/*******************************************************************************
* Function Name: pwm_left_WriteCompare2
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare value, for compare1 output.  
*  The compare output will reflect the new value on the next UDB clock.  
*  The compare output will be driven high when the present counter value is 
*  less than or less than or equal to the compare register, depending on the 
*  mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WriteCompare2(uint16 compare) 
{
    #if(pwm_left_UsingFixedFunction)
        CY_SET_REG16(pwm_left_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG16(pwm_left_COMPARE2_LSB_PTR, compare);
    #endif
}
#endif /* UseOneCompareMode */


#if (pwm_left_DeadBandUsed)
/*******************************************************************************
* Function Name: pwm_left_WriteDeadTime
********************************************************************************
* 
* Summary:
*  This function writes the dead-band counts to the corresponding register
*
* Parameters:  
*  deadtime:  Number of counts for dead time 
*
* Return: 
*  void
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void pwm_left_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!pwm_left_DeadBand2_4)
        CY_SET_REG8(pwm_left_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        pwm_left_DEADBAND_COUNT &= ~pwm_left_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        pwm_left_DEADBAND_COUNT |= (deadtime << pwm_left_DEADBAND_COUNT_SHIFT) & pwm_left_DEADBAND_COUNT_MASK; 
    #endif
}


/*******************************************************************************
* Function Name: pwm_left_ReadDeadTime
********************************************************************************
* 
* Summary:
*  This function reads the dead-band counts from the corresponding register
*
* Parameters:  
*  void
*
* Return: 
*  Dead Band Counts
*
* Reentrant:
*  Yes
*
*******************************************************************************/
uint8 pwm_left_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!pwm_left_DeadBand2_4)
        return (CY_GET_REG8(pwm_left_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((pwm_left_DEADBAND_COUNT & pwm_left_DEADBAND_COUNT_MASK) >> pwm_left_DEADBAND_COUNT_SHIFT);
    #endif
}
#endif /* DeadBandUsed */


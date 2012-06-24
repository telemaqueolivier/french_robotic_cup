/*******************************************************************************
* File Name: timer_asserv.c  
* Version 2.0
*
* Description:
*  The Timer User Module consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "timer_asserv.h"

uint8 timer_asserv_initVar = 0u;


/*******************************************************************************
* Function Name: timer_asserv_Init
********************************************************************************
* 
* Summary:
*  Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void timer_asserv_Init(void) 
{
    #if(!timer_asserv_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 timer_asserv_interruptState;
    #endif

    #if (timer_asserv_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        timer_asserv_CONTROL &= timer_asserv_CTRL_ENABLE;
        
        /* Clear the mode bits for continuous run mode */
        #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
            timer_asserv_CONTROL2 &= ~timer_asserv_CTRL_MODE_MASK;
        #endif
        #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
            timer_asserv_CONTROL3 &= ~timer_asserv_CTRL_MODE_MASK;                
        #endif

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (timer_asserv_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            timer_asserv_CONTROL |= 0x04u;
        #endif
        
        #if (timer_asserv_RunModeUsed == 2)
            #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
                /* Set last 2 bits of control2 register if one shot(halt on 
                interrupt) is enabled*/
                timer_asserv_CONTROL2 |= 0x03u;
            #endif
            #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
                /* Set last 2 bits of control3 register if one shot(halt on 
                interrupt) is enabled*/
                timer_asserv_CONTROL3 |= 0x03u;                
            #endif
        #endif
        
        #if (timer_asserv_UsingHWEnable != 0)
            #if (timer_asserv_PSOC3_ES2 || timer_asserv_PSOC5_ES1)
                /* Set the default Run Mode of the Timer to Continuous */
                timer_asserv_CONTROL2 |= timer_asserv_CTRL_MODE_PULSEWIDTH;
            #endif
            #if (timer_asserv_PSOC3_ES3 || timer_asserv_PSOC5_ES2)
                /* Clear and Set ROD and COD bits of CFG2 register */
                timer_asserv_CONTROL3 &= ~timer_asserv_CTRL_RCOD_MASK;
                timer_asserv_CONTROL3 |= timer_asserv_CTRL_RCOD;  
                
                /* Clear and Enable the HW enable bit in CFG2 register */
                timer_asserv_CONTROL3 &= ~timer_asserv_CTRL_ENBL_MASK;
                timer_asserv_CONTROL3 |= timer_asserv_CTRL_ENBL;     
                
                /* Set the default Run Mode of the Timer to Continuous */
                timer_asserv_CONTROL3 |= timer_asserv_CTRL_MODE_CONTINUOUS;
            #endif
        #endif
        
        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        timer_asserv_RT1 &= ~timer_asserv_RT1_MASK;
        timer_asserv_RT1 |= timer_asserv_SYNC;     
                
        /*Enable DSI Sync all all inputs of the Timer*/
        timer_asserv_RT1 &= ~(timer_asserv_SYNCDSI_MASK);
        timer_asserv_RT1 |= timer_asserv_SYNCDSI_EN;
                
        /* Set the IRQ to use the status register interrupts */
        timer_asserv_CONTROL2 |= timer_asserv_CTRL2_IRQ_SEL;
    #endif 
        
    /* Set Initial values from Configuration */
    timer_asserv_WritePeriod(timer_asserv_INIT_PERIOD);
    timer_asserv_WriteCounter(timer_asserv_INIT_PERIOD);
    
    #if (timer_asserv_UsingHWCaptureCounter)/* Capture counter is enabled */
        timer_asserv_CAPTURE_COUNT_CTRL |= timer_asserv_CNTR_ENABLE;
        timer_asserv_SetCaptureCount(timer_asserv_INIT_CAPTURE_COUNT);
    #endif
        
    #if (!timer_asserv_UsingFixedFunction)
        #if (timer_asserv_SoftwareCaptureMode)
            timer_asserv_SetCaptureMode(timer_asserv_INIT_CAPTURE_MODE);
        #endif
        
        #if (timer_asserv_SoftwareTriggerMode)
            if (!(timer_asserv_CONTROL & timer_asserv__B_TIMER__TM_SOFTWARE))
            {
                timer_asserv_SetTriggerMode(timer_asserv_INIT_TRIGGER_MODE);
            }
        #endif
        
        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        timer_asserv_interruptState = CyEnterCriticalSection();
        
        /* Use the interrupt output of the status register for IRQ output */
        timer_asserv_STATUS_AUX_CTRL |= timer_asserv_STATUS_ACTL_INT_EN_MASK;
        
        /* Exit Critical Region*/
        CyExitCriticalSection(timer_asserv_interruptState);

        #if (timer_asserv_EnableTriggerMode)
            timer_asserv_EnableTrigger();
        #endif

        #if (timer_asserv_InterruptOnCaptureCount)
             #if (!timer_asserv_ControlRegRemoved)
                timer_asserv_SetInterruptCount(timer_asserv_INIT_INT_CAPTURE_COUNT);
            #endif
        #endif
        
        timer_asserv_ClearFIFO();  
    #endif

    timer_asserv_SetInterruptMode(timer_asserv_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: timer_asserv_Enable
********************************************************************************
* 
* Summary:
*  Enable the Timer
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void timer_asserv_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (timer_asserv_UsingFixedFunction)
        timer_asserv_GLOBAL_ENABLE |= timer_asserv_BLOCK_EN_MASK;
        timer_asserv_GLOBAL_STBY_ENABLE |= timer_asserv_BLOCK_STBY_EN_MASK;
    #endif   
    
    /* Remove assignment if control register is removed */
    #if (!timer_asserv_ControlRegRemoved || timer_asserv_UsingFixedFunction)     
        timer_asserv_CONTROL |= timer_asserv_CTRL_ENABLE;
    #endif
}


/*******************************************************************************
* Function Name: timer_asserv_Start
********************************************************************************
* 
* Summary:
*  The start function initializes the timer with the default values, the 
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  timer_asserv_initVar: Is modified when this function is called for the first 
*   time. Is used to ensure that initialization happens only once.
*
* Reentrant
*  No
*
*******************************************************************************/
void timer_asserv_Start(void) 
{
    if(timer_asserv_initVar == 0u)
    {
        timer_asserv_Init();
        
        timer_asserv_initVar = 1u;   /* Clear this bit for Initialization */
    }
    
    /* Enable the Timer */		
    timer_asserv_Enable();    
}


/*******************************************************************************
* Function Name: timer_asserv_Stop
********************************************************************************
* 
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_Stop(void) 
{
    /* Disable Timer */
    #if(!timer_asserv_ControlRegRemoved || timer_asserv_UsingFixedFunction)    /* Remove assignment if control register is removed */  
        timer_asserv_CONTROL &= ~timer_asserv_CTRL_ENABLE;
    #endif  
    
    /* Globally disable the Fixed Function Block chosen */
    #if (timer_asserv_UsingFixedFunction)
        timer_asserv_GLOBAL_ENABLE &= ~timer_asserv_BLOCK_EN_MASK;
        timer_asserv_GLOBAL_STBY_ENABLE &= ~timer_asserv_BLOCK_STBY_EN_MASK;
    #endif
}


/*******************************************************************************
* Function Name: timer_asserv_SetInterruptMode
********************************************************************************
* 
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.  
*  The twosources are caputure and terminal.  One, both or neither may 
*  be selected.
*
* Parameters:  
*  interruptMode:   This parameter is used to enable interrups on either/or 
*                   terminal count or capture.  
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SetInterruptMode(uint8 interruptMode) 
{
    timer_asserv_STATUS_MASK = interruptMode;
}

/*******************************************************************************
* Function Name: timer_asserv_SoftwareCapture
********************************************************************************
* 
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    CY_GET_REG8(timer_asserv_COUNTER_LSB_PTR);
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: timer_asserv_ReadStatusRegister
********************************************************************************
* 
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read. 
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8   timer_asserv_ReadStatusRegister(void) 
{
    return timer_asserv_STATUS;
}


#if (!timer_asserv_ControlRegRemoved)   /* Remove API if control register is removed */
/*******************************************************************************
* Function Name: timer_asserv_ReadControlRegister
********************************************************************************
* 
* Summary:
*  Reads the control register and returns it's value. 
*
* Parameters:  
*  void
*
* Return: 
*  The contents of the control register
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint8 timer_asserv_ReadControlRegister(void) 
{
    return timer_asserv_CONTROL;
}


/*******************************************************************************
* Function Name: timer_asserv_WriteControlRegister
********************************************************************************
* 
* Summary:
*  Sets the bit-field of the control register.  
*
* Parameters:  
*  control: The contents of the control register
*
* Return: 
*  
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_WriteControlRegister(uint8 control) 
{
    timer_asserv_CONTROL = control;
}
#endif /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: timer_asserv_ReadPeriod
********************************************************************************
* 
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:  
*  void
*
* Return: 
*  The present value of the counter.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint32 timer_asserv_ReadPeriod(void) 
{
   return ( CY_GET_REG24(timer_asserv_PERIOD_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: timer_asserv_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will result in
*          the counter remaining at zero.
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_WritePeriod(uint32 period) 
{
    #if(timer_asserv_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(timer_asserv_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG24(timer_asserv_PERIOD_LSB_PTR, period);
    #endif
}


/*******************************************************************************
* Function Name: timer_asserv_ReadCapture
********************************************************************************
* 
* Summary:
*  This function returns the last value captured.
*
* Parameters:  
*  void 
*
* Return: 
*  Present Capture value.
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint32 timer_asserv_ReadCapture(void) 
{
   return ( CY_GET_REG24(timer_asserv_CAPTURE_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: timer_asserv_WriteCounter
********************************************************************************
* 
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_WriteCounter(uint32 counter) 
{
    #if(timer_asserv_UsingFixedFunction)
        counter = counter;
        /* This functionality is removed until a FixedFunction HW update to 
         * allow this register to be written 
         */
        /* uint16 counter_temp = (uint16)counter;
         * CY_SET_REG16(timer_asserv_COUNTER_LSB_PTR, counter_temp);
         */
    #else
        CY_SET_REG24(timer_asserv_COUNTER_LSB_PTR, counter);
    #endif
}


/*******************************************************************************
* Function Name: timer_asserv_ReadCounter
********************************************************************************
* 
* Summary:
*  This function returns the current counter value.
*
* Parameters:  
*  void
*
* Return: 
*  Present compare value. 
*
* Reentrant
*  Yes
*
*******************************************************************************/
uint32 timer_asserv_ReadCounter(void) 
{
    
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(timer_asserv_COUNTER_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG24(timer_asserv_CAPTURE_LSB_PTR));
}


#if(!timer_asserv_UsingFixedFunction) /* UDB Specific Functions */

/*******************************************************************************
 * The functions below this point are only available using the UDB 
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (timer_asserv_SoftwareCaptureMode)
/*******************************************************************************
* Function Name: timer_asserv_SetCaptureMode
********************************************************************************
* 
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:  
*  captureMode:  This parameter sets the capture mode of the UDB capture feature.
*  The parameter values are defined using the #define timer_asserv__B_TIMER__CM_NONE 0
#define timer_asserv__B_TIMER__CM_RISINGEDGE 1
#define timer_asserv__B_TIMER__CM_FALLINGEDGE 2
#define timer_asserv__B_TIMER__CM_EITHEREDGE 3
#define timer_asserv__B_TIMER__CM_SOFTWARE 4
. 
*  The following are the possible values of the parameter
*  timer_asserv__B_TIMER__CM_NONE        - Set Capture mode to None
*  timer_asserv__B_TIMER__CM_RISINGEDGE  - Capture on rising edge of Capture input
*  timer_asserv__B_TIMER__CM_FALLINGEDGE - Capture on falling edge of Capture input
*  timer_asserv__B_TIMER__CM_EITHEREDGE  - Capture on falling edge of Capture input
* 
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = (captureMode << timer_asserv_CTRL_CAP_MODE_SHIFT);
    captureMode &= (timer_asserv_CTRL_CAP_MODE_MASK);
    
	/* Clear the Current Setting */
    timer_asserv_CONTROL &= ~timer_asserv_CTRL_CAP_MODE_MASK;
    
    /* Write The New Setting */   
    timer_asserv_CONTROL |= captureMode;
}
#endif

#if (timer_asserv_SoftwareTriggerMode)
/*******************************************************************************
* Function Name: timer_asserv_SetTriggerMode
********************************************************************************
* 
* Summary:
*  This function sets the trigger input mode
*
* Parameters:  
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define timer_asserv__B_TIMER__TM_NONE 0x00
    #define timer_asserv__B_TIMER__TM_RISINGEDGE 0x04
    #define timer_asserv__B_TIMER__TM_FALLINGEDGE 0x08
    #define timer_asserv__B_TIMER__TM_EITHEREDGE 0x0C
    #define timer_asserv__B_TIMER__TM_SOFTWARE 0x10
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= timer_asserv_CTRL_TRIG_MODE_MASK;
    
    /* Clear the Current Setting */
    timer_asserv_CONTROL &= ~timer_asserv_CTRL_TRIG_MODE_MASK;
    
    /* Write The New Setting */   
    timer_asserv_CONTROL |= (triggerMode | timer_asserv__B_TIMER__TM_SOFTWARE);     

}
#endif

#if (timer_asserv_EnableTriggerMode)
/*******************************************************************************
* Function Name: timer_asserv_EnableTrigger
********************************************************************************
* 
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_EnableTrigger(void) 
{
    #if (!timer_asserv_ControlRegRemoved)   /* Remove assignment if control register is removed */
        timer_asserv_CONTROL |= timer_asserv_CTRL_TRIG_EN;
    #endif
}

/*******************************************************************************
* Function Name: timer_asserv_DisableTrigger
********************************************************************************
* 
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_DisableTrigger(void) 
{
    #if (!timer_asserv_ControlRegRemoved)   /* Remove assignment if control register is removed */
        timer_asserv_CONTROL &= ~timer_asserv_CTRL_TRIG_EN;
    #endif
}
#endif


#if(timer_asserv_InterruptOnCaptureCount)
#if (!timer_asserv_ControlRegRemoved)   /* Remove API if control register is removed */
/*******************************************************************************
* Function Name: timer_asserv_SetInterruptCount
********************************************************************************
* 
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:  
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then 
*                   an interrupt will occur each time a capture occurs.  
*                   A value of 1 to 3 will cause the interrupt  
*                   to delay by the same number of captures.
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= timer_asserv_CTRL_INTCNT_MASK;
    
    /* Clear the Current Setting */
    timer_asserv_CONTROL &= ~timer_asserv_CTRL_INTCNT_MASK;
    /* Write The New Setting */   
    timer_asserv_CONTROL |= interruptCount;    
}
#endif /* Remove API if control register is removed */
#endif /* timer_asserv_InterruptOnCaptureCount */


#if (timer_asserv_UsingHWCaptureCounter)
/*******************************************************************************
* Function Name: timer_asserv_SetCaptureCount
********************************************************************************
* 
* Summary:
*  This function sets the capture count
*
* Parameters:  
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1 
*                to 127 will cause the interrupt to delay by the same number of 
*                captures.
*
* Return: 
*  void
*
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_SetCaptureCount(uint8 captureCount) 
{
    timer_asserv_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: timer_asserv_ReadCaptureCount
********************************************************************************
* 
* Summary:
*  This function reads the capture count setting
*
* Parameters:  
*  void
*
* Return: 
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 timer_asserv_ReadCaptureCount(void) 
{
    return timer_asserv_CAP_COUNT ;
}
#endif /* timer_asserv_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: timer_asserv_ClearFIFO
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
* Reentrant
*  Yes
*
*******************************************************************************/
void timer_asserv_ClearFIFO(void) 
{
    while(timer_asserv_ReadStatusRegister() & timer_asserv_STATUS_FIFONEMP)
    {
        timer_asserv_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */

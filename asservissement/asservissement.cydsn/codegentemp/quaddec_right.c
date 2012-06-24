/*******************************************************************************
* File Name: quaddec_right.c  
* Version 1.50
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "CyLib.h"
#include "quaddec_right.h"

#if(quaddec_right_COUNTER_SIZE == 32u)
    extern volatile int32 quaddec_right_count32SoftPart;    
#endif /*quaddec_right_COUNTER_SIZE == 32u*/

uint8 quaddec_right_initVar = 0u;


/*******************************************************************************
* Function Name: quaddec_right_Init
********************************************************************************
*
* Summary:   
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void quaddec_right_Init(void) 
{      
    #if (quaddec_right_COUNTER_SIZE == 32u)
      
        /* Disable Interrupt. */
        CyIntDisable(quaddec_right_ISR_NUMBER);
        
        /* Set the ISR to point to the quaddec_right_isr Interrupt. */
        CyIntSetVector(quaddec_right_ISR_NUMBER, quaddec_right_ISR);
        
        /* Set the priority. */
        CyIntSetPriority(quaddec_right_ISR_NUMBER, quaddec_right_ISR_PRIORITY);       
        
    #endif /* quaddec_right_COUNTER_SIZE == 32u */    
}


/*******************************************************************************
* Function Name: quaddec_right_Enable
********************************************************************************
*
* Summary:   
*  This function enable interrupts from Component and also enable Component's 
*  isr for 32-bit counter.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void quaddec_right_Enable(void) 
{
    uint8 enableInterrupts = 0u;
    
    quaddec_right_SetInterruptMask(quaddec_right_INIT_INT_MASK);
    
    enableInterrupts = CyEnterCriticalSection();
    
    /* Enable interrupts from Statusi register */
    quaddec_right_SR_AUX_CONTROL |= quaddec_right_INTERRUPTS_ENABLE;
    
    CyExitCriticalSection(enableInterrupts);
    
    #if (quaddec_right_COUNTER_SIZE == 32u)
        /* Enable Component interrupts */
        CyIntEnable(quaddec_right_ISR_NUMBER);
    #endif /* quaddec_right_COUNTER_SIZE == 32u */
}


/*******************************************************************************
* Function Name: quaddec_right_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware. 
*  Resets counter to 0, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global variables:
*  quaddec_right_initVar - used to check initial configuration, modified on 
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_right_Start(void)
{  
    #if (quaddec_right_COUNTER_SIZE == 8u)
    
        quaddec_right_Cnt8_Start();
        quaddec_right_Cnt8_WriteCounter(quaddec_right_COUNTER_INIT_VALUE);
        
    #else /* (quaddec_right_COUNTER_SIZE == 16u) || (quaddec_right_COUNTER_SIZE == 32u) */
    
        quaddec_right_Cnt16_Start();
        quaddec_right_Cnt16_WriteCounter(quaddec_right_COUNTER_INIT_VALUE);
        
    #endif /* quaddec_right_COUNTER_SIZE == 8u */        
    
    if(quaddec_right_initVar == 0u)
    {
        quaddec_right_Init();
        quaddec_right_initVar = 1u;
    }        

    quaddec_right_Enable();
}


/*******************************************************************************
* Function Name: quaddec_right_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:  
*  None.  
*
* Return: 
*  None.
*
*******************************************************************************/
void quaddec_right_Stop(void) 
{                        
    uint8 enableInterrupts = 0u;
    
    #if (quaddec_right_COUNTER_SIZE == 8u)
        quaddec_right_Cnt8_Stop();
    #else /* (quaddec_right_COUNTER_SIZE == 16u) || (quaddec_right_COUNTER_SIZE == 32u) */
        quaddec_right_Cnt16_Stop();                                          /* counter disable */
    #endif /* (quaddec_right_COUNTER_SIZE == 8u) */
    
    enableInterrupts = CyEnterCriticalSection();
    
    /* Disable interrupts interrupts from Statusi register */
    quaddec_right_SR_AUX_CONTROL &= ~quaddec_right_INTERRUPTS_ENABLE;
    
    CyExitCriticalSection(enableInterrupts);
    
    #if (quaddec_right_COUNTER_SIZE == 32u)
        CyIntDisable(quaddec_right_ISR_NUMBER);                              /* interrupt disable */
    #endif /* quaddec_right_COUNTER_SIZE == 32u */
}


/*******************************************************************************
* Function Name: quaddec_right_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:  
*  None.  
*
* Return: 
*  The counter value. Return type is signed and per 
*  the counter size setting. A positive value indicates 
*  clockwise movement (B before A).
*
* Global variables:
*  quaddec_right_count32SoftPart - used to get hi 16 bit for current value 
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 quaddec_right_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;   
    
    #if (quaddec_right_COUNTER_SIZE == 32u)  
    
        int16 hwCount;   
        
    #endif /* quaddec_right_COUNTER_SIZE == 32u */
    
    #if (quaddec_right_COUNTER_SIZE == 8u)
    
        tmpCnt = quaddec_right_Cnt8_ReadCounter();
        count = tmpCnt ^ 0x80u;
        
    #endif /* quaddec_right_COUNTER_SIZE == 8u */
    
    #if (quaddec_right_COUNTER_SIZE == 16u)
    
        tmpCnt = quaddec_right_Cnt16_ReadCounter();
        count = tmpCnt ^ 0x8000u;    
        
    #endif /* quaddec_right_COUNTER_SIZE == 16u */ 
    
    #if (quaddec_right_COUNTER_SIZE == 32u)
    
        CyIntDisable(quaddec_right_ISR_NUMBER);
        
        tmpCnt = quaddec_right_Cnt16_ReadCounter();
        hwCount = tmpCnt ^ 0x8000u;
        count = quaddec_right_count32SoftPart + hwCount;
        
        CyIntEnable(quaddec_right_ISR_NUMBER);
        
    #endif /* quaddec_right_COUNTER_SIZE == 32u */
        
    return(count);    
}


/*******************************************************************************
* Function Name: quaddec_right_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:  
*  value:  The new value. Parameter type is signed and per the counter size  
*  setting.  
*
* Return: 
*  None.
*
* Global variables:
*  quaddec_right_count32SoftPart - modified to set hi 16 bit for current value 
*  of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_right_SetCounter(int32 value)
{    
    #if ((quaddec_right_COUNTER_SIZE == 8u) || (quaddec_right_COUNTER_SIZE == 16u))        
        uint16 count;         
    #endif  /* (quaddec_right_COUNTER_SIZE == 8u) || (quaddec_right_COUNTER_SIZE == 16u) */   
    
    #if (quaddec_right_COUNTER_SIZE == 8u)     
    
        count = (value ^ 0x80u);
        quaddec_right_Cnt8_WriteCounter(count);
        
    #endif  /* quaddec_right_COUNTER_SIZE == 8u */
    
    #if (quaddec_right_COUNTER_SIZE == 16u) 
    
        count = (value ^ 0x8000u);
        quaddec_right_Cnt16_WriteCounter(count);
        
    #endif  /* quaddec_right_COUNTER_SIZE == 16u */
    
    #if (quaddec_right_COUNTER_SIZE == 32u)
    
        CyIntDisable(quaddec_right_ISR_NUMBER);
        
        quaddec_right_Cnt16_WriteCounter(0x8000u);
        quaddec_right_count32SoftPart = value;
        
        CyIntEnable(quaddec_right_ISR_NUMBER);
        
    #endif  /* quaddec_right_COUNTER_SIZE == 32u */
}


/*******************************************************************************
* Function Name: quaddec_right_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events.
*
* Parameters:  
*  None.  
*
* Return: 
*  The events, as bits in an unsigned 8-bit value:
*        Bit      Description
*
*        0        Counter overflow.
*        1        Counter underflow.
*        2        Counter reset due to index, if index input is used.
*        3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 quaddec_right_GetEvents(void) 
{   
    return(quaddec_right_STATUS_REG & quaddec_right_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: quaddec_right_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events. 
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot 
*  be disabled, these bits are ignored.
*
* Parameters:  
*  mask:  Enable / disable bits in an 8-bit value,where 1 enables the interrupt. 
*
* Return: 
*  None.
*
*******************************************************************************/
void quaddec_right_SetInterruptMask(uint8 mask) 
{
    #if (quaddec_right_COUNTER_SIZE == 32u)
    
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (quaddec_right_COUNTER_OVERFLOW | quaddec_right_COUNTER_UNDERFLOW |
                 quaddec_right_COUNTER_RESET);
                 
    #endif /* quaddec_right_COUNTER_SIZE == 32u */
    
    quaddec_right_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: quaddec_right_GetInterruptMask
********************************************************************************
* 
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:  
*  None.
*
* Return: 
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow and underflow enable bits are always 
*  set.
*
*******************************************************************************/
uint8 quaddec_right_GetInterruptMask(void) 
{
    return(quaddec_right_STATUS_MASK & quaddec_right_INIT_INT_MASK);
}


/* [] END OF FILE */

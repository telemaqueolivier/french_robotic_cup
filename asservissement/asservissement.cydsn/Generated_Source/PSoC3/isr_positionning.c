/*******************************************************************************
* File Name: isr_positionning.c  
* Version 1.50
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <isr_positionning.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_positionning_intc` */
#include "global_variable.h"
#include "trajectory.h"
/* `#END` */


/*******************************************************************************
* Function Name: isr_positionning_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_positionning_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_positionning_Disable();

    /* Set the ISR to point to the isr_positionning Interrupt. */
    isr_positionning_SetVector(isr_positionning_Interrupt);

    /* Set the priority. */
    isr_positionning_SetPriority(isr_positionning_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_positionning_Enable();
}

/*******************************************************************************
* Function Name: isr_positionning_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_positionning_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    isr_positionning_Disable();

    /* Set the ISR to point to the isr_positionning Interrupt. */
    isr_positionning_SetVector(address);

    /* Set the priority. */
    isr_positionning_SetPriority(isr_positionning_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_positionning_Enable();
}

/*******************************************************************************
* Function Name: isr_positionning_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_positionning_Stop(void) 
{
    /* Disable this interrupt. */
    isr_positionning_Disable();
}

/*******************************************************************************
* Function Name: isr_positionning_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for isr_positionning.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(isr_positionning_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_positionning_Interrupt` */
	rsT.t = TIME_ASSERV;
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (isr_positionning__ES2_PATCH ))      
            isr_positionning_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: isr_positionning_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling isr_positionning_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use isr_positionning_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_SetVector(cyisraddress address) 
{
    CY_SET_REG16(isr_positionning_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: isr_positionning_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress isr_positionning_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(isr_positionning_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: isr_positionning_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling isr_positionning_Start
*   or isr_positionning_StartEx will override any effect this method would have had. 
*	This method should only be called after isr_positionning_Start or 
*	isr_positionning_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_SetPriority(uint8 priority) 
{
    *isr_positionning_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: isr_positionning_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 isr_positionning_GetPriority(void) 
{
    uint8 priority;


    priority = *isr_positionning_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: isr_positionning_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_Enable(void) 
{
    /* Enable the general interrupt. */
    *isr_positionning_INTC_SET_EN = isr_positionning__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_positionning_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 isr_positionning_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*isr_positionning_INTC_SET_EN & isr_positionning__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: isr_positionning_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_Disable(void) 
{
    /* Disable the general interrupt. */
    *isr_positionning_INTC_CLR_EN = isr_positionning__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_positionning_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_SetPending(void) 
{
    *isr_positionning_INTC_SET_PD = isr_positionning__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_positionning_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_positionning_ClearPending(void) 
{
    *isr_positionning_INTC_CLR_PD = isr_positionning__INTC_MASK;
}

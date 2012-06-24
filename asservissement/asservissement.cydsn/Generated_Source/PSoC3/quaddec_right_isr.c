/*******************************************************************************
* File Name: quaddec_right_isr.c  
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
#include <quaddec_right_isr.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START quaddec_right_isr_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: quaddec_right_isr_Start
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
void quaddec_right_isr_Start(void)
{
    /* For all we know the interrupt is active. */
    quaddec_right_isr_Disable();

    /* Set the ISR to point to the quaddec_right_isr Interrupt. */
    quaddec_right_isr_SetVector(quaddec_right_isr_Interrupt);

    /* Set the priority. */
    quaddec_right_isr_SetPriority(quaddec_right_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    quaddec_right_isr_Enable();
}

/*******************************************************************************
* Function Name: quaddec_right_isr_StartEx
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
void quaddec_right_isr_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    quaddec_right_isr_Disable();

    /* Set the ISR to point to the quaddec_right_isr Interrupt. */
    quaddec_right_isr_SetVector(address);

    /* Set the priority. */
    quaddec_right_isr_SetPriority(quaddec_right_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    quaddec_right_isr_Enable();
}

/*******************************************************************************
* Function Name: quaddec_right_isr_Stop
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
void quaddec_right_isr_Stop(void) 
{
    /* Disable this interrupt. */
    quaddec_right_isr_Disable();
}

/*******************************************************************************
* Function Name: quaddec_right_isr_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for quaddec_right_isr.
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
CY_ISR(quaddec_right_isr_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START quaddec_right_isr_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (quaddec_right_isr__ES2_PATCH ))      
            quaddec_right_isr_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: quaddec_right_isr_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling quaddec_right_isr_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use quaddec_right_isr_StartEx instead.
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
void quaddec_right_isr_SetVector(cyisraddress address) 
{
    CY_SET_REG16(quaddec_right_isr_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: quaddec_right_isr_GetVector
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
cyisraddress quaddec_right_isr_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(quaddec_right_isr_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: quaddec_right_isr_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling quaddec_right_isr_Start
*   or quaddec_right_isr_StartEx will override any effect this method would have had. 
*	This method should only be called after quaddec_right_isr_Start or 
*	quaddec_right_isr_StartEx has been called. To set the initial
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
void quaddec_right_isr_SetPriority(uint8 priority) 
{
    *quaddec_right_isr_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_GetPriority
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
uint8 quaddec_right_isr_GetPriority(void) 
{
    uint8 priority;


    priority = *quaddec_right_isr_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_Enable
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
void quaddec_right_isr_Enable(void) 
{
    /* Enable the general interrupt. */
    *quaddec_right_isr_INTC_SET_EN = quaddec_right_isr__INTC_MASK;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_GetState
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
uint8 quaddec_right_isr_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*quaddec_right_isr_INTC_SET_EN & quaddec_right_isr__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_Disable
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
void quaddec_right_isr_Disable(void) 
{
    /* Disable the general interrupt. */
    *quaddec_right_isr_INTC_CLR_EN = quaddec_right_isr__INTC_MASK;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_SetPending
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
void quaddec_right_isr_SetPending(void) 
{
    *quaddec_right_isr_INTC_SET_PD = quaddec_right_isr__INTC_MASK;
}

/*******************************************************************************
* Function Name: quaddec_right_isr_ClearPending
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
void quaddec_right_isr_ClearPending(void) 
{
    *quaddec_right_isr_INTC_CLR_PD = quaddec_right_isr__INTC_MASK;
}

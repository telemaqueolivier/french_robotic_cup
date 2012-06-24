/*******************************************************************************
* File Name: mot_right_backward.c  
* Version 1.50
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "mot_right_backward.h"


/*******************************************************************************
* Function Name: mot_right_backward_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void mot_right_backward_Write(uint8 value) 
{
    uint8 staticBits = mot_right_backward_DR & ~mot_right_backward_MASK;
    mot_right_backward_DR = staticBits | ((value << mot_right_backward_SHIFT) & mot_right_backward_MASK);
}


/*******************************************************************************
* Function Name: mot_right_backward_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void mot_right_backward_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(mot_right_backward_0, mode);
}


/*******************************************************************************
* Function Name: mot_right_backward_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro mot_right_backward_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 mot_right_backward_Read(void) 
{
    return (mot_right_backward_PS & mot_right_backward_MASK) >> mot_right_backward_SHIFT;
}


/*******************************************************************************
* Function Name: mot_right_backward_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 mot_right_backward_ReadDataReg(void) 
{
    return (mot_right_backward_DR & mot_right_backward_MASK) >> mot_right_backward_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(mot_right_backward_INTSTAT) 

    /*******************************************************************************
    * Function Name: mot_right_backward_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 mot_right_backward_ClearInterrupt(void) 
    {
        return (mot_right_backward_INTSTAT & mot_right_backward_MASK) >> mot_right_backward_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 

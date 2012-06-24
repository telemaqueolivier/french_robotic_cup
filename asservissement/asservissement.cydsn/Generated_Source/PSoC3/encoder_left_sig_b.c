/*******************************************************************************
* File Name: encoder_left_sig_b.c  
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
#include "encoder_left_sig_b.h"


/*******************************************************************************
* Function Name: encoder_left_sig_b_Write
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
void encoder_left_sig_b_Write(uint8 value) 
{
    uint8 staticBits = encoder_left_sig_b_DR & ~encoder_left_sig_b_MASK;
    encoder_left_sig_b_DR = staticBits | ((value << encoder_left_sig_b_SHIFT) & encoder_left_sig_b_MASK);
}


/*******************************************************************************
* Function Name: encoder_left_sig_b_SetDriveMode
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
void encoder_left_sig_b_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(encoder_left_sig_b_0, mode);
}


/*******************************************************************************
* Function Name: encoder_left_sig_b_Read
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
*  Macro encoder_left_sig_b_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 encoder_left_sig_b_Read(void) 
{
    return (encoder_left_sig_b_PS & encoder_left_sig_b_MASK) >> encoder_left_sig_b_SHIFT;
}


/*******************************************************************************
* Function Name: encoder_left_sig_b_ReadDataReg
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
uint8 encoder_left_sig_b_ReadDataReg(void) 
{
    return (encoder_left_sig_b_DR & encoder_left_sig_b_MASK) >> encoder_left_sig_b_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(encoder_left_sig_b_INTSTAT) 

    /*******************************************************************************
    * Function Name: encoder_left_sig_b_ClearInterrupt
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
    uint8 encoder_left_sig_b_ClearInterrupt(void) 
    {
        return (encoder_left_sig_b_INTSTAT & encoder_left_sig_b_MASK) >> encoder_left_sig_b_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 

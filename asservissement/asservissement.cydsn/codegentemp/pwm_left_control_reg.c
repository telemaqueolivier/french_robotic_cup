/*******************************************************************************
* File Name: pwm_left_control_reg.c  
* Version 1.50
*
* Description:
*  This file contains API to enable firmware control of a control register.
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
#include "pwm_left_control_reg.h"

#if !defined(pwm_left_control_reg_ctrl_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: pwm_left_control_reg_Write
********************************************************************************
*
* Summary:
*  Write a byte to a control register.
*
* Parameters:  
*  control:  The value to be assigned to the control register. 
*
* Return: 
*  void 
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
void pwm_left_control_reg_Write(uint8 control) 
{
    pwm_left_control_reg_Control = control;
}


/*******************************************************************************
* Function Name: pwm_left_control_reg_Read
********************************************************************************
*
* Summary:
*  Read the current value assigned to a control register.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the control register
*
* Reentrant:
*  Yes
*  
*******************************************************************************/
uint8 pwm_left_control_reg_Read(void) 
{
    return pwm_left_control_reg_Control;
}

#endif /* End check for removal by optimization */

/*******************************************************************************
* File Name: pwm_left_control_reg.h  
* Version 1.50
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CONTROL_REG_pwm_left_control_reg_H) /* CY_CONTROL_REG_pwm_left_control_reg_H */
#define CY_CONTROL_REG_pwm_left_control_reg_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*         Function Prototypes 
***************************************/    

void    pwm_left_control_reg_Write(uint8 control) ;
uint8   pwm_left_control_reg_Read(void) ;

/***************************************
*            Registers        
***************************************/

/* Control Register */
#define pwm_left_control_reg_Control         (* (reg8 *) pwm_left_control_reg_ctrl_reg__CONTROL_REG )
#endif /* End CY_CONTROL_REG_pwm_left_control_reg_H */

/* [] END OF FILE */

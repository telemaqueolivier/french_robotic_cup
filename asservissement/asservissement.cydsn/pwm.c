/*  
 *  Copyright Projet & Tech' (2008-2009)
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 *	Fay??al GUENNAR <f.guennar@gmail.com>
 */
 
#include "pwm.h"
#include "pwm_right.h"
#include "pwm_left.h"
#include "pwm_right_control_reg.h"
#include "pwm_left_control_reg.h"
#include "options.h"

#define FORWARD_LEFT 0
#define BACKWARD_LEFT 1
#define FORWARD_RIGHT 1
#define BACKWARD_RIGHT 0

void pwm_init(void)
{
	pwm_right_Start();
	pwm_left_Start();
	pwm_right_control_reg_Write(FORWARD_RIGHT);
	pwm_left_control_reg_Write(FORWARD_LEFT);
}

void pwm_left(int16 value)
{
	//initialised at the first function call
	static uint8 pwmg_prev_direction = FORWARD_LEFT;

	if(value < 0)
	{
		//If we should go BACKWARD_LEFT
 		if(pwmg_prev_direction != BACKWARD_LEFT)
		{
			//If we were going FORWARD_LEFT
			pwm_left_Stop(); 
			//change output to P_0_2 
			pwm_left_control_reg_Write(BACKWARD_LEFT);
			
			pwmg_prev_direction = BACKWARD_LEFT;
		}
		//invert value
		value = -value;
	}
 	else
	{
		//If we should go FORWARD_LEFT
 		if(pwmg_prev_direction != FORWARD_LEFT)
		{
			//If we were going BACKWARD_LEFT
			pwm_left_Stop(); 
			//change output to P_0_3
			pwm_left_control_reg_Write(FORWARD_LEFT);
			
			pwmg_prev_direction = FORWARD_LEFT;
		}
	}
	//cut the value if it is over the maximum
	if(value > PWM_MAX) value = PWM_MAX;  

	#ifdef DEBUG_PWM
	{
		char buff[20];
		
		sprintf(buff, "debug PWM L value = %d\r\n>", value);
		uart_pc_PutString(buff);
	}
	#endif
	
 	pwm_left_WriteCompare(value);  
	pwm_left_Start(); 
}

void pwm_right(int16 value)
{
	//initialised at the first function call
	static uint8 pwmg_prev_direction = FORWARD_RIGHT;

	if(value < 0)
	{
		//If we should go BACKWARD_RIGHT
 		if(pwmg_prev_direction != BACKWARD_RIGHT)
		{
			//If we were going FORWARD_RIGHT
			pwm_right_Stop(); 
			//change output to P_0_0 
			pwm_right_control_reg_Write(BACKWARD_RIGHT);
			
			pwmg_prev_direction = BACKWARD_RIGHT;
		}
		//invert value
		value = -value;
	}
 	else
	{
		//If we should go FORWARD_RIGHT
 		if(pwmg_prev_direction != FORWARD_RIGHT)
		{
			//If we were going BACKWARD_RIGHT
			pwm_right_Stop(); 
			//change output to P_0_1
			pwm_right_control_reg_Write(FORWARD_RIGHT);
			
			pwmg_prev_direction = FORWARD_RIGHT;
		}
	}
	//cut the value if it is over the maximum
	if(value > PWM_MAX) value = PWM_MAX;  

	#ifdef DEBUG_PWM
	{
		char buff[20];
		
		sprintf(buff, "debug PWM R value = %d\r\n>", value);
		UART_1_PutString(buff);
	}
	#endif
	
 	pwm_right_WriteCompare(value);  
	pwm_right_Start(); 
}

void pwm_stop(void)
{
	pwm_right_Stop(); 
	pwm_left_Stop(); 
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pwm_right_control_reg.h>
#include <pwm_left_control_reg.h>
#include <uart_pc.h>
#include <quaddec_right.h>
#include <quaddec_left.h>
#include "uart_base.h"
#include "position.h"
#include "distance.h"
#include "robot_system.h"
#include "control_system_manager.h"
#include "pwm_right.h"
#include "pwm_left.h"
#include "options.h"
#include "global_variable.h"
#include "trajectory.h"

unsigned char xdata malloc_mempool [200];

void uart_init(	struct uart* uart,
				uint8_t number_commands,
				void (*start)(void),
				void (*stop)(void),
				uint8_t (*get_char)(void),
				void (*clear_rx_buffer)(void),
				void (*clear_tx_buffer)(void),
				void (*put_string)(uint8_t*),
				void (*put_string_const)(const uint8_t*))
{
	memset(uart->buffer, 1, sizeof(char) * SIZE_MAX_BUFFER);
	uart->buffer[SIZE_MAX_BUFFER - 1] = '\0';
	uart->number_commands = number_commands;
	uart->commands = malloc(sizeof(struct uart_command) * number_commands);
	uart->index = 0;
	uart->first_parameter_call = 1;
	uart->is_buffer_unlocked = 1;
	uart->start = start;
	uart->stop = stop;
	uart->get_char = get_char;
	uart->clear_rx_buffer = clear_rx_buffer;
	uart->clear_tx_buffer = clear_tx_buffer;
	uart->put_string = put_string;
	uart->put_string_const = put_string_const;
}

void uart_set_command(struct uart* uart, uint8_t index, const char* command, void (*function)(char*))
{
	uart->commands[index].command = command;
	uart->commands[index].function = function;
}

void uart_check (struct uart* uart)
{ 
	if(uart_command_check(uart))
	{
		char command[20];
		
		if(strcpy(command, uart_get_param(uart))) 
		{
			char param[20];
			uart_call(uart, command, strcpy(param, uart_get_param(uart)));
		}
		
		uart_command_reset(uart);
	}
}

BOOL uart_command_check(struct uart* uart)
{
	char caractere;
	BOOL end_of_command = 0;
	
	if(uart->is_buffer_unlocked)
	{
		caractere = uart->get_char();
		
		if(uart->index < SIZE_MAX_BUFFER /*&& caractere != '\r'*/ && caractere != '\0' && caractere != '\n' && caractere != 127 && caractere != 11 && caractere != 9 && caractere != 8)
		{
			if(caractere == /*'z'*/ '\r')
			{
				uart->buffer[uart->index] = '\0';
				uart->index = 0;
				end_of_command = 1;
				uart->is_buffer_unlocked = 0;
			}
			else
			{
				uart->buffer[uart->index] = caractere;
				++uart->index;
			}
		}
	}
	
	return end_of_command;
}

char* uart_get_param(struct uart* uart)
{
	char* param = NULL;
	
	if(uart->first_parameter_call)
	{
		uart->first_parameter_call = 0;
		param = strtok(uart->buffer, " ");
	}
	else
		param = strtok(NULL, " ");
		
	return param;
}

void uart_call(struct uart* uart, char* command, char* str)
{
	uint8 i = 0;
	char* p = NULL;
	
	while(i < uart->number_commands && strcmp(uart->commands[i].command, command) != 0)
		i++;
		
	if(i < NB_CMD)
		uart->commands[i].function(str);
	else	
		uart->put_string_const("NACK\r");
}

void uart_command_reset(struct uart* uart)
{
	uart->clear_rx_buffer();
	uart->clear_tx_buffer();
	uart->is_buffer_unlocked = 1;
}

void uart_stop(struct uart* uart)
{
	free(uart->commands);
	uart->stop();
}

void quad_dec_value(struct uart* uart, char* p)
{
	char buff[49];
	
	sprintf(buff, "QD left = %ld QD right = %ld\r", quaddec_left_GetCounter (), quaddec_right_GetCounter ());
	uart->put_string(buff);
}

void read_xy(struct uart* uart, char* p)
{
	char buff[100];
	
	sprintf(buff, "AngleC = %ld\n\rDistanceC = %f\n\r>", (int32_t)(rsT.robot.pext_prev.angle * 180 / (TRACK_TOP * _PI )), (double)rsT.robot.pext_prev.distance / TOPS_PER_MM);
	uart->put_string(buff);
	sprintf(buff, "x = %f\n\ry = %f\n\r>", (double)(rsT.robot_pos.xy.x / TOPS_PER_MM), (double)(rsT.robot_pos.xy.y / TOPS_PER_MM));
	uart->put_string(buff);
}

void time_exec_counter(struct uart* uart, char* p)
{
	int32_t begin, end;
	char buff[50];
	
	begin = (int32_t)(timer_asserv_ReadCounter());
		
	end = (int32_t)(timer_asserv_ReadCounter());
	
	uart->put_string(buff);
}

void reset(struct uart* uart, char* p)
{
	trajectory_init(&rsT);
	pid_set_gains(&rsT.csm_angle.correct_filter_params, PIDA_P, PIDA_I, PIDA_D);
	pid_set_out_shift(&rsT.csm_angle.correct_filter_params, PIDA_SH);
	pid_set_gains(&rsT.csm_distance.correct_filter_params, PIDD_P, PIDD_I, PIDD_D );
	pid_set_out_shift(&rsT.csm_distance.correct_filter_params, PIDD_SH);
	uart->put_string_const("reset\n\r>");
}

void set_consigne_asserv(struct uart* uart, char* p)
{
	char buff[20];
	char param[20]; 
	int32_t consigne; 
	
	switch(p[0])
	{
		case 'a' :
			consigne = atoi(strcpy(param, uart_get_param(uart))) * TRACK_TOP * _PI / 180;
			cs_set_consign(&rsT.csm_angle, &consigne, &rsT.robot);
		break;
		
		case 'd' :
			consigne = atoi(strcpy(param, uart_get_param(uart))) * TOPS_PER_MM;
			cs_set_consign(&rsT.csm_distance, &consigne, &rsT.robot);
		break;
	}
	
	sprintf(buff ,"%s %s\r\n", p, param);
	uart->put_string(buff);
	uart->put_string_const("consign updated\n\r>");
}

void set_PID(struct uart* uart, char* p)
{
	char buff[10], p1[10], p2[10], p3[10], param[20];
	int Pr = 0 , I = 0 , D = 0;
	
	strcpy ( param ,  p );
	Pr = atoi(strcpy(p1, uart_get_param(uart)));
	I = atoi(strcpy(p2, uart_get_param(uart)));
	D = atoi(strcpy(p3, uart_get_param(uart)));
	
	switch(param[0])
	{
		case 'a' :
			pid_set_gains(&rsT.csm_angle.correct_filter_params, Pr, I, D);
			sprintf(buff , "p = %ld i = %ld d = %ld\r\n", rsT.csm_angle.correct_filter_params.gain_P, rsT.csm_angle.correct_filter_params.gain_I, rsT.csm_angle.correct_filter_params.gain_D);
			uart->put_string(buff);
			uart->put_string_const("PID updated\n\r>");
		break;
		
		case 'd' :
			pid_set_gains(&rsT.csm_distance.correct_filter_params, Pr, I, D);
			sprintf(buff, "p = %ld i = %ld d = %ld\r\n", rsT.csm_distance.correct_filter_params.gain_P, rsT.csm_distance.correct_filter_params.gain_I, rsT.csm_distance.correct_filter_params.gain_D);
			uart->put_string(buff);
			uart->put_string_const("PID updated\n\r>");
		break;
	}
	
	
}

void pwmR (struct uart* uart, char* p)
{
	char buff[50];
	uint16_t compare = atoi(p);
	
	if(compare >= 0 && compare <= pwm_right_ReadPeriod())
		pwm_right_WriteCompare(compare);
		
	sprintf(buff, "compare value updated to %u\r\n>", compare);
	uart->put_string(buff);
}

void pwmL(struct uart* uart, char* p)
{
	char buff[50];
	uint16_t compare = atoi(p);
	
	if(compare >= 0 && compare <= pwm_left_ReadPeriod())
		pwm_left_WriteCompare(compare);
		
	sprintf(buff, "compare value updated to %u\r\n>", compare);
	uart->put_string(buff);
}

void demuxR(struct uart* uart, char* p)
{
	pwm_right_control_reg_Write(atoi(p));
}

void demuxL(struct uart* uart, char* p)
{
	pwm_left_control_reg_Write(atoi(p));
}

void stop(struct uart* uart, char* p) 
{
	uart->put_string_const("STOP !aaaa\r");
}

void gotoxy(struct uart* uart, char* p)
{
	char buff[50];
	struct cartesian posXY;
	
	posXY.x = atof(p) * TOPS_PER_MM;
	posXY.y = atof(uart_get_param(uart)) * TOPS_PER_MM;
	
	trajectory_goto_xy(&rsT, &posXY, NO_CARE);
	
	sprintf(buff ,"goto x = %f y = %f\r\n", posXY.x, posXY.y);
	uart->put_string(buff);
}

void gotoa(struct uart* uart, char* p)
{
	char buff[50];
	int32_t angle = (int32_t)(atof(p) * TRACK_TOP * _PI / 180);
	
	trajectory_goto_a_without_event(&rsT, angle);
	
	sprintf(buff, "goto angle %ld\r\n>", angle);
	uart->put_string(buff);
}

void gotod(struct uart* uart, char* p)
{
	char buff[50];
	int32_t dist = (int32_t)(atoi(p) * TOPS_PER_MM);
	
	trajectory_goto_d(&rsT, dist);
	
	sprintf(buff, "goto distance %ld\r\n>", dist);
	uart->put_string(buff);
}

void resetCoef(struct uart* uart, char* p)
{
	pid_set_gains(&rsT.csm_angle.correct_filter_params, 0, 0, 0);
	pid_set_gains(&rsT.csm_distance.correct_filter_params, 0, 0, 0);
}

void set_multiple_xy(struct uart* uart, char* p)
{
	targets[0].x = atof(p) * TOPS_PER_MM;
	targets[0].y = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[1].x = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[1].y = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[2].x = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[2].y = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[3].x = atof(uart_get_param(uart)) * TOPS_PER_MM;
	targets[3].y = atof(uart_get_param(uart)) * TOPS_PER_MM;
	
	uart->put_string_const("multiple xy setted");
}
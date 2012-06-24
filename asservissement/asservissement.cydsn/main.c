#include <device.h>
#include <isr_positionning.h>
#include <timer_asserv.h>
#include "uart_base.h"
#include "trajectory.h"
#include "global_variable.h"

void main(void)
{	
	struct uart uart_pc;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */	
    CYGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	color_sign = RED;
	timer_asserv_Start();
	isr_positionning_Start();
	
	uart_init(&uart_pc, 16, &uart_pc_Start, &uart_pc_Stop, &uart_pc_GetChar, &uart_pc_ClearRxBuffer, &uart_pc_ClearTxBuffer, &uart_pc_PutString, &uart_pc_PutStringConst);
	uart_set_command(&uart_pc, 0, "value", &quad_dec_value);
    uart_set_command(&uart_pc, 1, "readxy", &read_xy);
	uart_set_command(&uart_pc, 2, "exec", &time_exec_counter);
	uart_set_command(&uart_pc, 3, "reset", &reset);
	uart_set_command(&uart_pc, 4, "asserv", &set_consigne_asserv);
	uart_set_command(&uart_pc, 5, "setcoeff", &set_PID);
	uart_set_command(&uart_pc, 6, "pwmr", &pwmR);
	uart_set_command(&uart_pc, 7, "pwml", &pwmL);
	uart_set_command(&uart_pc, 8, "demuxr", &demuxR);
	uart_set_command(&uart_pc, 9, "demuxl", &demuxL);
	uart_set_command(&uart_pc, 10, "stop", &stop);
	uart_set_command(&uart_pc, 11, "gotoxy", &gotoxy);
	uart_set_command(&uart_pc, 12, "gotoa", &gotoa);
	uart_set_command(&uart_pc, 13, "gotod", &gotod);
	uart_set_command(&uart_pc, 14, "resetcoeff", &resetCoef);
	uart_set_command(&uart_pc, 15, "setxy", &set_multiple_xy); 
	
	uart_pc.put_string_const("Asserv\n\r>");

	trajectory_init(&rsT);
	pid_set_gains(&rsT.csm_angle.correct_filter_params, PIDA_P, PIDA_I, PIDA_D);
	pid_set_out_shift(&rsT.csm_angle.correct_filter_params, PIDA_SH);
	pid_set_gains(&rsT.csm_distance.correct_filter_params, PIDD_P, PIDD_I, PIDD_D);
	pid_set_out_shift(&rsT.csm_distance.correct_filter_params, PIDD_SH);
	
	while(1)
    {
       	uart_check(&uart_pc);
		
		if(rsT.t == TIME_ASSERV)
		{
			rsT.t = TIME_IDLE;
			++rsT.time;

			trajectory_update(&rsT);
		}
	}
}
/* [] END OF FILE */
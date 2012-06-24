/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2005), Projet & Tech' (2008-2009)
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
 *  Olivier MATZ <zer0@droids-corp.org> 
 *	Fay??al GUENNAR <f.guennar@gmail.com>
 *	Olivier TELEMAQUE <telemaque.olivier@gmail.com>
 */
 
#include "control_system_manager.h"
#include "options.h"
#include <string.h>

void cs_init(struct cs* cs, char process_out) 
{
	cs->process_out = process_out; //0 = ANGLE ou 1 = DISTANCE
	cs->prev_process_out_value = 0;
	cs->consign_value = 0;
	cs->filtered_consign_value = 0;
	cs->error_value = 0;
	cs->out_value = 0;
	cs->speed = 0;
	
	pid_init(&cs->correct_filter_params);
	
	if(process_out==PROCESS_ANGLE)
		speed_filter_init(&cs->consign_filter_params, A_SPEED_POS, A_SPEED_NEG, A_ACC_POS, A_ACC_NEG);
	else
		speed_filter_init(&cs->consign_filter_params, D_SPEED_POS, D_SPEED_NEG, D_ACC_POS, D_ACC_NEG);
}

void  cs_do_process(struct cs* cs, struct robot_system* rs) 
{
  	speed_filter_do_filter(&cs->consign_filter_params, &cs->filtered_consign_value);

    if (cs->process_out == PROCESS_DISTANCE)
	{
    	cs->prev_process_out_value = rs->pext_prev.distance;
	}
    else
	{ //PROCESS_ANGLE
      	cs->prev_process_out_value = rs->pext_prev.angle; 
    }
#ifndef NO_SPEED_FILTER
    cs->error_value = cs->filtered_consign_value - cs->prev_process_out_value + cs->first_value;
#else 
	cs->error_value = cs->consign_value - cs->prev_process_out_value;
#endif
    cs->out_value = pid_do_filter(&cs->correct_filter_params, cs->error_value);

	if(cs->process_out == PROCESS_DISTANCE)
 		rs_set_distance(rs, cs->out_value);
 	else
 		rs_set_angle(rs, cs->out_value);
}

void cs_set_consign(struct cs* cs, int32_t* consign, struct robot_system* rs)
{	
	cs->consign_value = *consign;
	//New Ramp
	if (cs->process_out == PROCESS_DISTANCE)
	{
		cs->first_value = *consign - rs->pext_prev.distance;
		
		speed_filter_set_consign(&cs->consign_filter_params, &cs->first_value);
		
		cs->first_value = rs->pext_prev.distance;
	}
	else
	{
		cs->first_value= *consign-rs->pext_prev.angle;
		
		speed_filter_set_consign(&cs->consign_filter_params, &cs->first_value);

		cs->first_value = rs->pext_prev.angle;
	}
}
void cs_stop(struct cs* cs, struct robot_system* rs)//? ?tudier
{
	speed_filter_stop(&cs->consign_filter_params);
	
	if(cs->process_out == PROCESS_DISTANCE)
	{
		#ifndef NEW_RAMP
			cs->consign_value = (cs->consign_filter_params.consign >> 10) + rs->pext_prev.distance;
			cs->first_value = rs->pext_prev.distance;
		#else
			cs->consign_value = /*cs->consign_filter_params.consign - cs->consign_filter_params.prev_out + rs->pext_prev.distance*/cs->consign_filter_params.consign +cs->first_value;
			//cs->first_value=rs->pext_prev.distance;
		#endif
	}
	else
	{
		#ifndef NEW_RAMP
			cs->consign_value = (cs->consign_filter_params.consign >> 10) + rs->pext_prev.angle;
			cs->first_value = rs->pext_prev.angle;
		#else
			cs->consign_value = cs->consign_filter_params.consign +cs->first_value;
		#endif
	}
}
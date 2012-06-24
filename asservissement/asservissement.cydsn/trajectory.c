#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <quaddec_right.h>
#include <quaddec_left.h>
#include <uart_pc.h>
#include "trajectory.h"
#include "types.h"
#include "global_variable.h"
#include "encoders.h"
#include "position.h"

long int copyconsig; //debug du chgt de traj->target_pol.distance, ne conserve pas sa valeur alors que pas d'appel à goto_xy 

void trajectory_init(struct trajectory* T)
{
	memset(T, 0, sizeof(struct trajectory));
	memset(&T->curr_obj, 0, sizeof(struct cartesian));
	rs_init(&T->robot);
	cs_init(&T->csm_angle, PROCESS_ANGLE);
	cs_init(&T->csm_distance, PROCESS_DISTANCE);
	position_init(&T->robot_pos);
    T->state = IS_READY;
	T->d_win = D_WIN;
	T->a_win = A_WIN;
	T->t = TIME_ASSERV;
	T->time = 0;
}



#ifndef STRAT_OPTIMIZED
void Trajectory_goto_d_a_real(struct Trajectory * traj, double d_mm, 
	double a_rad, uint8_t flags) 
{
	int32_t consigne;
	if (flags & UPDATE_A) 
	{
		if (flags & RESET_A) 
		{
			consigne = 0;
		}
		else 
		{
			consigne = (int32_t)(a_rad*TRACK_TOP);
		}
		consigne+= traj->robot.pext_prev.angle;
		cs_set_consign(&traj->csm_angle,&consigne,&traj->robot);
	}
	if (flags & UPDATE_D) 
	{
		if (flags & RESET_D) 
		{
			consigne = 0;
		}
		else
		{
			consigne = (int32_t)(d_mm * TOPS_PER_MM);
		}
		consigne += traj->robot.pext_prev.distance;
		cs_set_consign(&traj->csm_distance,&consigne,&traj->robot);
	}
}
#else
void trajectory_goto_d(struct trajectory* traj, int32_t d) 
{
	traj->target_pol.angle = traj->curr_pos.angle;
	traj->target_pol.distance = d + traj->robot.pext_prev.distance;
	//copyconsig = traj->target_pol.distance;
	cartesian_from_polar(&traj->target_pol, &traj->curr_obj.xy);
	traj->state = NEW_TRAJ;
}
	
void trajectory_goto_a(struct trajectory* traj, int32_t ang) 
{
//		int16_t a;
//		a=(traj->curr_pos.angle%TURN_TOP);//actual angle in [-2pi,2pi]
//		if(abs(a)>TURN_TOP/2)//we set it behind [-pi,pi]
//		{
//			if(a>0)
//				a-=TURN_TOP;
//			else
//				a+=TURN_TOP;
//		}
	if(abs(ang) > TURN_TOP / 2)
	{
		if(ang > 0)
			traj->target_pol.angle = ang - TURN_TOP;
		else
			traj->target_pol.angle = ang + TURN_TOP;
	}
	else
		traj->target_pol.angle = ang;
		
	traj->curr_pos.xy = traj->curr_pos.xy;//we don't change the xy position
	traj->target_pol.angle += traj->curr_pos.angle;
	//traj->target_pol.distance=0;
	traj->state = NEW_TRAJ;	
	
//		{
//			char buff[50];
//			
//			sprintf ( buff , "target_pol.angle = %ld\r\n" , traj->target_pol.angle );
//			UART_1_PutString ( buff );
//		}
}

void trajectory_goto_a_without_event(struct trajectory* traj, int32_t ang)
{
	trajectory_goto_a(traj, ang);
	cs_set_consign(&traj->csm_angle, &traj->target_pol.angle, &traj->robot);
	
	traj->state = IS_READY;
}
#endif //STRAT_OPTIMIZED

//mis à zéro du terme intégral supprimé le 17 04 à tester unitairement
void trajectory_update(struct trajectory* traj)
{
	static int32_t start_stab_time = 0;//stabilization begining time
	rs_update(&traj->robot);
	process_xy(traj);
	cs_do_process(&traj->csm_angle, &traj->robot);
	cs_do_process(&traj->csm_distance, &traj->robot);

	traj->curr_pos.angle = traj->robot.pext_prev.angle;
	
	if(traj->state & STOP_TRAJ)
	{
		traj->state &= ~STOP_TRAJ;
		
		trajectory_stop ( traj , traj->state );//cette fonction ne fonctionne qu'avec NEW_RAMP défini
	}
	
	switch(traj->state & ~NEAR_END)
	{
		case NEW_TRAJ:
		
//			UART_1_PutString ( "NEW TRAJ\r\n" );
			cs_set_consign(&traj->csm_angle, &traj->target_pol.angle, &traj->robot);
			
			traj->state = DOING_ANGLE;
		break;
		case DOING_ANGLE:
			if(abs(traj->curr_pos.angle - traj->target_pol.angle) < traj->a_win)
			{
				if(traj->state & NEAR_END /*&& time-start_stab_time>STAB_TIME*/)
				{
					if(traj->time - start_stab_time > STAB_TIME)
					{
						traj->state = DOING_DISTANCE;
						//traj->target_pol.distance = copyconsig + traj->robot.pext_prev.distance;//apparemment mal mis à jour
						
						cs_set_consign(&traj->csm_distance, &traj->target_pol.distance, &traj->robot);
					}
				}
				else
				{
					traj->state |= NEAR_END;
					traj->state &= ~STOP_TRAJ;//sans cette ligne on rentre constamment dans le cas STOP_TRAJ
					start_stab_time = traj->time;
				}
			}
			else
				traj->state &= ~NEAR_END;
		break;
		case DOING_DISTANCE:
			if(abs(traj->target_pol.distance - traj->robot.pext_prev.distance) < traj->d_win)
			{
				if((traj->state & NEAR_END) /*&& (time-start_stab_time>STAB_TIME)*/)
				{
					if(traj->time - start_stab_time > STAB_TIME)
					{
						traj->state = IS_READY/*CHECK_XY*/;
						traj->curr_pos.xy = traj->robot_pos.xy;
						uart_pc_PutString("Traj IS_READY\r\n");
					}
				}
				else
				{
					traj->state |= NEAR_END;
					traj->state &= ~STOP_TRAJ;
					start_stab_time = traj->time;
				}
			}
			else
				traj->state &= ~NEAR_END;
		break;
		
		case CHECK_XY :
//			UART_1_PutString ( "CHECK_XY\r\n" );
						
//			Trajectory_check_xy ( traj );
		break;
		
		default:
		break;
	}
}

void trajectory_goto_xy(struct trajectory* T, struct cartesian* pos, uint8_t how)
{
	struct cartesian s;
	int16_t a;
	
	s.x = pos->x - T->curr_pos.xy.x;
	s.y = pos->y - T->curr_pos.xy.y;
	polar_from_cartesian(&s, &T->target_pol);

	//if there's no distance an angle is meaningless
	if(T->target_pol.distance == 0)
        T->target_pol.angle = T->curr_pos.angle;

	a = T->curr_pos.angle % (uint16_t)floor(TURN_TOP);//actual angle in [-2pi,2pi]
	
	if(abs(a) > TURN_TOP / 2)//we set it behind [-pi,pi]
	{
		if(a > 0)
			a-=TURN_TOP;
		else
			a+=TURN_TOP;
	}

	if (how == NO_CARE)
	{
		//we move closer angles
		if(abs(T->target_pol.angle - a) > TURN_TOP / 2)
		{
			if(T->target_pol.angle > 0)
				T->target_pol.angle -= TURN_TOP;
			else
				T->target_pol.angle += TURN_TOP;
		}
		//is it more interesting to go backward or forward ?
		if(abs(T->target_pol.angle - a) > TURN_TOP / 4)
		{//we go backward
			if(T->target_pol.angle > 0)
				T->target_pol.angle -= TURN_TOP / 2;
			else
				T->target_pol.angle += TURN_TOP / 2;
			T->target_pol.distance = -T->target_pol.distance;
		}
	}
	else
	{
		if (how == BACKWARD)
		{
			if(T->target_pol.angle > 0)
				T->target_pol.angle -= TURN_TOP / 2;
			else
				T->target_pol.angle += TURN_TOP / 2;
			T->target_pol.distance = -T->target_pol.distance;
		}
		//we move closer angles
		if(abs(T->target_pol.angle - a) > TURN_TOP / 2)
		{
			if(T->target_pol.angle > 0)
				T->target_pol.angle -= TURN_TOP;
			else
				T->target_pol.angle += TURN_TOP;
		}
	}
	//absolute position
	T->target_pol.distance += T->robot.pext_prev.distance;
	//copyconsig = T->target_pol.distance;
	T->curr_obj.xy = *pos;
	T->target_pol.angle += T->curr_pos.angle - a;
	T->state = NEW_TRAJ;
}

void trajectory_stop(struct trajectory* traj, uint8_t flags)
{
	switch(flags & ~NEAR_END)
	{
		case NEW_TRAJ:
			//cancel traj
			traj->state = IS_READY;
//			UART_1_PutString ( "IS_READY\r\n" );
			break;
		case DOING_ANGLE:
			//finish angle but no distance
			traj->target_pol.distance = traj->robot.pext_prev.distance;
			traj->state = DOING_ANGLE;
//			UART_1_PutString ( "STOP ANGLE\r\n" );
			break;
		case DOING_DISTANCE:
			//Stop trajectory and actualize position.
			cs_stop(&traj->csm_distance, &traj->robot);
			traj->target_pol.distance = traj->csm_distance.consign_value;//ne fonctionne qu'avec NEW_RAMP defini
			traj->target_pol.angle = traj->csm_angle.consign_value;//à méditer
			cartesian_from_polar(&traj->target_pol, &traj->curr_obj.xy);
			traj->state = DOING_DISTANCE;
//			UART_1_PutString ( "STOP DISTANCE\r\n" );
		break;
	}
}

void trajectory_check_xy(struct trajectory* traj)
{
	if(euclidian_distance(&traj->curr_obj.xy, &traj->curr_pos.xy) <= D_XY_WIN)
	{	
//		UART_1_PutString ( "IS_READY\r\n" );
		//Trajectory_goto_a_without_event ( traj , traj->curr_obj.angle );
		traj->state = IS_READY;
	}
	else
		trajectory_goto_xy(traj, &traj->curr_obj.xy, NO_CARE);
}

void trajectory_goto_xy2(struct trajectory* traj, struct cartesian* pos, uint8_t how, int16_t  d_speed_pos, int16_t d_speed_neg, double d_acc_pos, double  d_acc_neg, int16_t a_speed_pos, int16_t a_speed_neg, double a_acc_pos, double a_acc_neg)
{
	speed_filter_set_cinematic_parameter(&traj->csm_distance.consign_filter_params, d_speed_pos, d_speed_neg, d_acc_pos, d_acc_neg);
	speed_filter_set_cinematic_parameter(&traj->csm_angle.consign_filter_params, a_speed_pos, a_speed_neg, a_acc_pos, a_acc_neg);
	trajectory_goto_xy(traj, pos, how);
}
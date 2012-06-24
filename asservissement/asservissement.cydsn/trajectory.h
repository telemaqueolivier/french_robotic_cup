#ifndef TRAJECTORY_DEFINED
#define TRAJECTORY_DEFINED

#include "distance.h"
#include "robot_system.h"
#include "control_system_manager.h"
#include "position.h"
#include "options.h"


//default distance/angle winwows
#define D_WIN 100
#define A_WIN 25
#define D_XY_WIN 20 // TOP
//time spent in windows needed to validate the position.
#define STAB_TIME 50

//gotoda flags
#define UPDATE_D 0x01
#define UPDATE_A 0x02
#define RESET_D  0x04
#define RESET_A  0x08

//How flag values
#define NO_CARE 0x00//Don't matter
#define FORWARD 0x01
#define BACKWARD 0x02


//State fag values
#define IS_READY 0x00
#define DOING_DISTANCE 0x01
#define DOING_ANGLE 0x02
#define NEW_TRAJ 0x04	
#define NEAR_END 0x88
#define STOP_TRAJ 0x80
#define CHECK_XY 0x10

#define CAL_ACTION			0x80
#define END_CALAGE			0x00
#define CANCEL_CSM_ANGLE 	0x01
#define GOING_BACKWARD  	0x02
#define GOING_FORWARD		0x04
#define CHECK_ENCODER    	0x08
#define GOING_ANGLE			0x10

#define HOW_X            1
#define HOW_Y            2

#define TIME_ASSERV 1
#define TIME_IDLE 0

struct trajectory 
{
    uint8_t state; /*trajectory state*/
	uint8_t t;
	uint32_t time;
	struct polar target_pol; /*objective*/
    uint16_t d_win;  /**<< distance window (for END_NEAR) */
    uint16_t a_win;  /**<< angle window (for END_NEAR) */
    struct robot_system robot;      /**<< *RS associé */
    struct cs csm_angle;    /**Angle consign managing*/
    struct cs csm_distance; /**Distance consign managing*/
	struct int_position curr_obj; //pointer because there's a limit in objects' size(2009-2010), in 2010-2011 PSOC3 seems not to be limited at this
	struct int_position curr_pos;
	struct robot_position robot_pos;
};

void trajectory_init(struct trajectory* T );

//Trajectory manager. Call in main loop.
void trajectory_update(struct trajectory* traj);

//Relative goto for polar distance.Use system distance.
void trajectory_goto_d(struct trajectory* traj, int32_t d);

//Relative goto for polar angle.Use system angle.
void trajectory_goto_a(struct trajectory * traj, int32_t ang);
void trajectory_goto_a_without_event(struct trajectory* traj, int32_t ang);

#ifndef STRAT_OPTIMIZED
	//Relative polar goto. it is not coupled with the trajectory  manager 
	//so do not use except for tests. d is in milimeters, a in radians
	void trajectory_goto_d_a_real(struct Trajectory * traj, double d_mm, double a_rad, uint8_t flags);
#endif //STRAT_OPTIMIZED

//absolute goto. Use system distance.
void trajectory_goto_xy(struct trajectory* T, struct cartesian* pos, uint8_t how);
void trajectory_goto_xy2(struct trajectory* traj, struct cartesian* pos, uint8_t how, int16_t  d_speed_pos, int16_t d_speed_neg, double d_acc_pos, double  d_acc_neg, int16_t a_speed_pos, int16_t a_speed_neg, double a_acc_pos, double a_acc_neg );
void trajectory_stop(struct trajectory* traj, uint8_t flags);
void trajectory_check_xy(struct trajectory* traj );
#endif //TRAJECTORY_DEFINED

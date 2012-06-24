#include "position.h"
#include "uart_pc.h"
#include <stdio.h>
#include <math.h>
#include "global_variable.h"
#include "robot_system.h"
#include "trajectory.h"

void position_init (struct robot_position* robot)
{
	robot->xy.y = 0;
	robot->xy.x = 0;
	robot->old_polar.distance = 0;
	robot->old_polar.angle = ANGLE_INIT;
}

void process_xy(struct trajectory* traj)
{
	struct polar delta_polar;
	struct cartesian delta_xy;
	
	delta_polar.distance = /*abs*/ (traj->robot.pext_prev.distance - traj->robot_pos.old_polar.distance);//test ? faire, abs est une faute empêche le bon fonctionnement en cas de marche arrière du robot
	delta_polar.angle = (traj->robot.pext_prev.angle + ANGLE_INIT + traj->robot_pos.old_polar.angle) >> 1;
	
	cartesian_from_polar(&delta_polar, &delta_xy);

	traj->robot_pos.xy.y += delta_xy.y;
	traj->robot_pos.xy.x += delta_xy.x;
	traj->robot_pos.old_polar = traj->robot.pext_prev;
}
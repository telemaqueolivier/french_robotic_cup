#ifndef POSITION_DEFINED
#define POSITION_DEFINED

#include "encoders.h"
#include "distance.h"
#include "types.h"

/** \file Position.h
 *  Ce module d??crit des structures repr??sentant la position du robot utile au module
 *  Trajectory.h.
 */

struct int_position
{
	int32_t angle;
	struct cartesian xy;
};

struct double_position
{
	double angle;
	double x;
	double y;
};

struct robot_position
{
	struct cartesian xy;
	struct polar old_polar;
};

void position_init(struct robot_position* robot);
void process_xy(struct trajectory* traj);
/** Fonction non d??finie.
 */
//void Position_Process();//ds trajectory.

#endif // POSITION_DEFINED

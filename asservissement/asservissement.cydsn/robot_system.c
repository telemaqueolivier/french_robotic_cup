/*  
 *  Copyright Droids Corporation, Microb Technology, Eirbot (2005), Projet & Tech' (2008-20011)
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
 *	Fay????al GUENNAR <f.guennar@gmail.com>
 */
 
#include "robot_system.h"
#include <string.h>
#include "encoders.h"
#include "pwm.h"
#include "options.h"

void rs_init(struct robot_system* rs)
{
  	memset(rs, 0, sizeof(struct robot_system));
	encoders_init(&rs->wext_prev);
	pwm_init();
}

void rs_update(struct robot_system* rs)
{
	encoders_read(&rs->wext_prev);
	polar_from_wheels(&rs->wext_prev, &rs->pext_prev);
}

void rs_set_angle(struct robot_system* rs, int32_t angle)
{
    struct polar p;
    struct wheels w;

    p.distance = rs->virtual_pwm.distance ;
    rs->virtual_pwm.angle = angle;
   
    p.angle = angle;
	wheels_from_polar(&p, &w);

	pwm_left(w.left);
  	pwm_right(w.right);

}

void rs_set_distance(struct robot_system* rs, int32_t distance)
{
    struct polar p2;
    struct wheels w2;

    p2.angle = rs->virtual_pwm.angle ;
    rs->virtual_pwm.distance = distance;
    p2.distance = distance;
    wheels_from_polar(&p2, &w2);

    pwm_left(w2.left);
  	pwm_right(w2.right);
}

void rs_set_angle_value(struct robot_system * rs, int32_t val)
{
	rs->pext_prev.angle = val;
}
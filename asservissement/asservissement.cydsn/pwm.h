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
 
 /** \file pwm.h
  *  Ce module g?re les signaux PWM commandant les moteurs.
  */
  

#ifndef _PWM_H_
#define _PWM_H_

#define PWM_MAX 1023

#include "types.h"
/** La fonction \a init_pwm initialise les blocs num??riques PWM.
 */
 
void pwm_init(void);

/** La fonction \a pwm_left g??n??re un signal PWM au moteur de propulsion gauche de largeur \a value. Le sens de
 *  de rotation du moteur d??pend du signe de la \a value.
 *  \param value : largeur du niveau haut du signal PWM.
 */
 
void pwm_left(int16_t value);

/** La fonction \a pwm_right g??n??re un signal PWM au moteur de propulsion droit de largeur \a value. Le sens de
 *  de rotation du moteur d??pend du signe de la \a value.
 *  \param value : largeur du niveau haut du signal PWM.
 */
 
void pwm_right(int16_t value);

/** La fonction \a pwm_stop arr??te les blocs num??rique g??n??rant les PWM.
 */
 
void pwm_stop(void);

#endif //_PWM_H_
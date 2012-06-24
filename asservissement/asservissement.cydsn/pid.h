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
 */
 
 /** \file pid.h
  *  Ce module repr??sente un correcteur PID. Il permet d'appliquer un PID, c'est ?? dire la somme pond??r??e de 
  *  l'int16_t??grale, de la d??riv??e et de l'entr??e elle-m??me.
  */
  
#ifndef _PID_H_
#define _PID_H_

#include "types.h"

//default PID Config 
#define PIDA_P 3000//1000
#define PIDA_I 3
#define PIDA_D 7000//5000
#define PIDA_SH 10

#define PIDD_P 1000//400
#define PIDD_I 3
#define PIDD_D 5000//3000
#define PIDD_SH 10

/** La macro \a S_MAX permet de limiter les valeurs maximale et minimale de la la variable \a to_saturate ?? 
 *  la valeur \a +-value_max
 *  \param to_saturate : variable ?? saturer
 *  \param value_max : valeur de saturation
 */
 
#define S_MAX(to_saturate, value_max)    \
do {                                     \
   if (to_saturate > value_max)          \
     to_saturate = value_max;            \
   else if (to_saturate < -value_max)    \
     to_saturate = -value_max;           \
 } while(0)


/** structure pid_filter */
struct pid_filter
{
//changement des types from int32_t ?? uint16_t 
    int32_t gain_P; /**< Gain Proportionnel */
    int32_t gain_I; /**< Gain Integral */
    int32_t gain_D; /**< Gain Derivee */

    char out_shift;

    //int32_t max_in; /**<  niveau de saturation en entree*/
    //int32_t max_I; /**<   niveau de saturation en integrale */
    //int32_t max_out; /**< niveau de saturation en sortie */

    int32_t integral; /**< integrale precedente */
    int32_t prev_in;  /**< pr??c??dente entr??e */
    int32_t prev_D;   /**< pr??c??dente d??riv??e */
    int32_t prev_out; /**< pr??c??dente commande de sortie*/
};

/** Prototyping */

void pid_init(struct pid_filter* p);

/* Fonctions de configuration du filtre pid */
void pid_set_gains(struct pid_filter* p, int32_t gp, int32_t gi, int32_t gd) ;
//void pid_set_maximums(struct pid_filter *p, int32_t max_in, int32_t max_I, int32_t max_out);
void pid_set_out_shift(struct pid_filter* p, char out_shift);
int32_t pid_do_filter(struct pid_filter* p, int32_t in);       
        
#endif

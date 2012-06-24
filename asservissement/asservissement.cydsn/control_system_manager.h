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
 
 /** \file control_system_manager.h
  * Module permettant de r??aliser l'asservissement.
  * Cet ensemble de fonction va appliquer l'ensemble des filtres ?? la consigne et ?? l'erreur afin d'??laborer la commande de sortie.
  */

#ifndef _CONTROL_SYSTEM_MANAGER_
#define _CONTROL_SYSTEM_MANAGER_

#include "types.h"
#include "robot_system.h"
#include "pid.h"
#include "speed_filter.h"
#include "options.h"

#define PROCESS_DISTANCE 1
#define PROCESS_ANGLE 2

/** Structure du csm */
struct cs {
		struct speed_filter consign_filter_params;
        struct pid_filter correct_filter_params;
        char process_out; //0 = ANGLE ou 1 = DISTANCE
		int32_t prev_process_out_value;
		int32_t first_value; //used to memorise the starting value.
        int32_t consign_value;
        int32_t filtered_consign_value;
        int32_t error_value;
		int32_t out_value;
		int16_t speed;
};

/** La fonction \a cs_init initialise la structure \a cs en mettant tout ses champs ?? 0 except?? le champ
 *  \a process_out qui est initialis?? ?? la valeur process_out
 *  \param cs : structure ?? initialiser
 *  \param process_out : le type de proc??d?? ( angle ou distance ) auquel doit ??tre initialis?? \a cs
 */
 
void cs_init(struct cs* cs, char process_out);

/** L'appel de la fonction \a cs_do_process r??alise un asservissement angulaire ou de distance du robot. 
 *  \image html Asserv_diagram.png
 *  Il effectue les op??rations suivantes :
 *
 * - Application du filtre de vitesse sur la consigne filtr??e \a cs->filtered_consign_value.
 * - Soustraction de la derni??re valeur de sortie \a rs->pext_prev du syst??me \a robot_system ( donc la valeur renvoy??e par
 *	 les codeurs ) ?? la consigne ( filtr??e ? ) puis stockage du r??sultat dans la variable cs->error_value.
 * - Application du correcteur PID \a cs->correct_filter_params sur \a cs->error_value puis stockage de la commande retourn??e par le correcteur PID dans la variable \a cs->out_value.
 * - Envoi des signaux PWM image de la commande \a cs->out_value aux moteurs.
 * 
 * \param cs : pointeur vers une structure cs contenant les valeurs de la boucle ferm??e d'asservissement
 * \param rs : pointeur vers une structure robot_system contenant les valeurs physique des codeurs
 */

void cs_do_process(struct cs* cs,  struct robot_system* rs);

/** La fonction \a cs_set_consign met ?? jour affecte la consigne \a cs->consign_value avec \a consign et met ?? jour 
 *	la consigne de vitesse  
 */
void cs_set_consign(struct cs* cs, int32_t* consign, struct robot_system* rs);
void cs_stop(struct cs* cs, struct robot_system* rs);
#endif
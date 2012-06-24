#ifndef ENCODER_DEFINED
#define ENCODER_DEFINED

/** \file Encoders.h
 *  Module d??crivant la structure du syst??me de codeur.
 *  Ce module fournit les param??tres physiques des roues folles codeuses, ainsi quqe les structures de donn??es
 *  associ??es, de plus un certain nombre de variables globales y sont d??finies afin de retenir l'??tat des codeurs
 *  durant le fonctionnement de l'asservissement.
 */
#include "types.h"

//Physical params
#define ENCODER_RESOLUTION 1024 /**< resolution des codeurs. */
#define ENCODER_RADIUS 28.145 /**< rayon des codeurs en mm. */
#define ENCODER_DIAMETER 56.29 /**<diametre des codeurs en mm. */
#define TRACK 300.5//300.5 //342  	/**< distance entre  les codeurs (diameter), nombre de mm par radian. */
					//=number of mm per radian.
					//(number of mm per turn=2*perimeter (2 encoder)
					//						=2*PI*diameter
					//=>diameter=number of mm per turn / (2*PI)
//#define RAd_ROUE_CODEUSE_MM 28
#define TOPS_PER_MM 5.790536924 /**< ENCODER_RESOLUTION/(2*M_PI*ENCODER_RADIUS). */ 
//#define DIST_IMP_PER_CM DIST_IMP_PER_MM*10
#define TRACK_TOP 1737.1610772  /**< TRACK_TOP=TRACK*TOPS_PER_MM=nombre de top par radian. */ 
									//number of top per radian
#define TURN_TOP 10914.904956467303338106084103315				/**< nombre de top par tour. */
			  // 12442.99165		//=TRACK_TOP*2*PI
									//TRACK*ENCODER_RESOLUTION/ENCODER_RADIUS
#define ANGLE_INIT 0
/** Cette structure repr??sente le nombre de top comptabilis?? par chaque roue folle codeuse
 */
 
struct wheels 
{
    int32_t left;
    int32_t right;
};

/** La fonction Encoders_init initialise chacune des varaibles globales d??finies dans le fichier Encoders.h
 *  de plus il lance les blocs numeriques associ??s aux roues folles codeuses
 */
 
void encoders_init(struct wheels* encoders);
void encoders_read(struct wheels* encoders);
void encoders_stop(void);

#endif //ENCODER_DEFINED
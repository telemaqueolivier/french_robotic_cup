#ifndef _ANGLE_DISTANCE_H_
#define _ANGLE_DISTANCE_H_

/** \file Distance.h
 *  Ce module r??alise les conversions des donn??es des roues codeuses vers une information d'angle-distance exploitable par
 *  par la boucle d'asservissement.
 */
 
#include "types.h"
#include "encoders.h"

#define _PI	3.1415926535897932
#define _PI2 1.5707963267948966
#define _2PI 6.2831853071795864
#define RAD_PER_DEG 0.0174532925199
#define LEFT_SIGN +
#define RIGHT_SIGN -
#define NEG_LEFT -
#define NEG_RIGHT +

/** Cette structure repr??sente un point en coordonn??e polaire donc une coordonn??e d'angle et de distance.
 */
 
struct polar 
{
    int32_t distance;
    int32_t angle;
};

/** Cette structure repr??sente un point en coordonn??e cart??sienne donc une abscisse et une ordonn??e.
 */
 
struct cartesian
{
   double x;
   double y; 
};

/** La fonction \a polar_from_wheels convertit les valeurs des roues codeuses ( gauche et droite ) en coordonn??es polaires.
 * \param in : valeurs des roues codeuses.
 * \param out : coordonn??es polaires. 
 */
 
void polar_from_wheels(struct wheels *_in, struct polar *_out);

/**  La fonction \a wheels_from_polar convertit les coordonn??es polaires en valeurs des roues codeuses ( gauche et droite ).
 * \param in : coordonn??es polaires.
 * \param out : valeurs des roues codeuses.
 */
 
void wheels_from_polar(struct polar * _in, struct wheels *_out);

/** La fonction \a Cartesian_from_polar convertit les coordonn??es polaires en coordonn??es cart??siennes.
 *  \param in : coordonn??es polaires.
 *  \param out : coordonn??es cart??siennes.
 */
 
void cartesian_from_polar(struct polar * _in, struct cartesian *_out);

/** La fonction \a polar_from_Cartesian convertit les coordonn??es cart??siennes en coordonn??es polaires.
 *  \param in : coordonn??es cart??siennes.
 *  \param out : coordonn??es polaires.
 */
 
void polar_from_cartesian(struct cartesian * _in, struct polar *_out);
float euclidian_distance (struct cartesian* pt1 , struct cartesian* pt2);

#endif //_ANGLE_DISTANCE_H_

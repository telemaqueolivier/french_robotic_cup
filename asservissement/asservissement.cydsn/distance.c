#include <math.h>
#include "distance.h"
#include "options.h"
#include "global_variable.h"

void polar_from_wheels(struct wheels *_in, struct polar *_out)
{
    _out->distance = (-_in->right + _in->left)>>1;//>>1 pour plus de perfs ?
    _out->angle    = color_sign * ( -_in->right - _in->left );
}

void wheels_from_polar(struct polar *_in, struct wheels *_out)
{
    _out->left  =  (_in->distance - (_in->angle >>1));//>>1 pour plus de perfs ?
    _out->right =  -(_in->distance + (_in->angle >> 1));//>>1 pour plus de perfs ?
}


void cartesian_from_polar(struct polar * _in, struct cartesian *_out)
{
	_out->x = _in->distance * cos((float)(_in->angle / TRACK_TOP));
	_out->y = _in->distance * sin((float)(_in->angle / TRACK_TOP));//-si "en haut"
}

void polar_from_cartesian( struct cartesian * _in, struct polar *_out)
{
	_out->distance = (int32_t)sqrt(_in->x*_in->x + _in->y*_in->y);
	
	if(_in->x < 0)
	{
		if(_in->y < 0)
			_out->angle = (int32_t)((atan(((double)_in->y) / _in->x) - _PI) * TRACK_TOP);
		else
			_out->angle = (int32_t)((atan(((double)_in->y) / _in->x) + _PI )* TRACK_TOP);
	}
	else if(_in->x != 0)
		_out->angle = (int32_t)(atan(((double)_in->y) / _in->x) * TRACK_TOP);
		else
		{
			if(_in->y < 0)
				_out->angle =(int32_t)(-_PI2 * TRACK_TOP);
			else
				_out->angle = (int32_t)(_PI2 * TRACK_TOP);	
		}
}

float euclidian_distance(struct cartesian* pt1, struct cartesian* pt2)
{
	return sqrt((pt1->x - pt2->x) * (pt1->x - pt2->x)  + (pt1->y - pt2->y) * (pt1->y - pt2->y));
} 
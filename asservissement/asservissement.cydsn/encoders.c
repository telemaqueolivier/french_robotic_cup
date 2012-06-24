#include <string.h>
#include <quaddec_right.h>
#include <quaddec_left.h>
#include "encoders.h"

void encoders_init(struct wheels* encoders)
{
	memset(encoders, 0, sizeof(struct wheels));
	quaddec_right_Start();
	quaddec_left_Start();
	quaddec_right_SetCounter(0);
	quaddec_left_SetCounter(0);
}

void encoders_read(struct wheels* encoders)
{
	encoders->left = quaddec_left_GetCounter();
	encoders->right = quaddec_right_GetCounter();
}

void encoders_stop(void)
{
	quaddec_right_Stop();
	quaddec_left_Stop(); 
}
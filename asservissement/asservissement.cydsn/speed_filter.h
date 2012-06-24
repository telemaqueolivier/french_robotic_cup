#ifndef SPEED_FILTER_H_INCLUDED
#define SPEED_FILTER_H_INCLUDED

#include "types.h"
#include "options.h"

#ifndef NEW_RAMP

#define A_SPEED_POS 2500
#define A_SPEED_NEG 2500

#define A_ACC_NEG 4
//#define A_DECC_NEG 8
#define A_ACC_POS 4
//#define A_DECC_POS 8

#define D_SPEED_POS 3000
#define D_SPEED_NEG 3000

#define D_ACC_NEG 2
//#define D_DECC_NEG 8
#define D_ACC_POS 2
//#define D_DECC_POS 8


struct speed_filter         //Simple trapeze speed ramp
{
    uint16_t speed_pos; //maximum positive speed
    uint16_t speed_neg; //maximum negative speed

    uint16_t acc_pos;   //maximum positive acceleration
    //unsigned int32_t decc_pos;  //maximum positive slowing
    uint16_t acc_neg;   //maximum negative acceleration
    //unsigned int32_t decc_neg;  //maximum negative slowing

    int32_t consign;    //the consign being computed
    int32_t prev_out;
    int16_t prev_speed;

   /* //  The times are those represented below.
    //   dx
    //   --
    //   dt
    //    ^
    //    |
    //  x1|.. ___________     x1=speed_pos | 2*consign/t2
    //    |  /:         :\
    //    | / :         : \
    //    |/  :         :  \
    //    O---------------------> t
    //        t0        t1 t2*/
    uint16_t x;         //double maximum
    uint16_t t;         //time, in number of calls of speed_filter_do_filter
    uint16_t t0;
    uint16_t t1;
    uint16_t t2;
	uint8_t  ta;		//speed adjustment flag
};

//initiate the speed filter parameters.
void speed_filter_init(struct speed_filter * sf,uint16_t speed_pos,uint16_t speed_neg,
                        uint16_t acc_pos/*,unsigned int32_t decc_pos*/,uint16_t acc_neg/*,
                        unsigned int32_t decc_neg*/);
//New consign. calculate it.
void speed_filter_set_consign(struct speed_filter * sf,int32_t *consign);

//set filtered consign to the filtered value.
//return true if the consign is virtually reached
char speed_filter_do_filter(struct speed_filter * sf,int32_t *filtered_consign);

//generate a "stop" ramp.
void speed_filter_stop(struct speed_filter * sf);

//change speed smoothly
char speed_change(struct speed_filter *sf, int32_t speed);

#else
/************************Modification de la rampe de vitesse 2011********************************************/
#define RAMP_SHIFT 10
#define A_SPEED_POS 25 //* ( 1 << RAMP_SHIFT )// 23 car on veut une vitesse de 0.8 m/s -> 4 mm/Te -> 23 Tops/Te avec Te = 5 ms
#define A_SPEED_NEG 25 //* ( 1 << RAMP_SHIFT )

#define A_ACC_NEG 0.5820523633 / 3 //* ( 1 << RAMP_SHIFT )//0.5820523633 car on veut une acc?l?ration de 4 m/s^2 -> 10^-1 mm/Te^2 -> 0.5820523633 Tops/Te^2
//#define A_DECC_NEG 8
#define A_ACC_POS 0.5820523633 / 3//* ( 1 << RAMP_SHIFT ) 
//#define A_DECC_POS 8

#define D_SPEED_POS 10 //* ( 1 << RAMP_SHIFT )
#define D_SPEED_NEG 10 //* ( 1 << RAMP_SHIFT )

#define D_ACC_NEG 0.5820523633  //* ( 1 << RAMP_SHIFT )
//#define D_DECC_NEG 8
#define D_ACC_POS 0.5820523633 //* ( 1 << RAMP_SHIFT )

//Le type des variables d'acc?l?rations sont devenues des double pour garder en pr?cision du fait de leurs faibles valeurs
struct speed_filter         //Simple trapeze speed ramp
{
    int16_t speed_pos; //maximum positive speed
    int16_t speed_neg; //maximum negative speed

    double acc_pos;   //maximum positive acceleration
    double acc_neg;   //maximum negative acceleration
	
    int32_t consign;    //the consign being computed
    int32_t prev_out;
    int32_t prev_speed;

    /*//  The times are those represented below.
    //   dx
    //   --
    //   dt
    //    ^
    //    |
    //  x1|.. ___________     x1=speed_pos | 2*consign/t2
    //    |  /:         :\
    //    | / :         : \
    //    |/A :    B    : C\
    //    O---------------------> t
    //        t0        t1 t2*/
    uint16_t x;         //real maximum
    uint32_t t;         //time, in number of calls of speed_filter_do_filter
    int16_t t0;
    int16_t t1;
    int16_t t2;
};

void speed_filter_init(struct speed_filter* sf, int16_t speed_pos, int16_t speed_neg, double acc_pos, double acc_neg);
void speed_filter_set_consign(struct speed_filter* sf, int32_t* consign);
char speed_filter_do_filter(struct speed_filter* sf, int32_t* filtered_consign);
void speed_filter_stop(struct speed_filter* sf);
void speed_filter_set_cinematic_parameter(struct speed_filter* sf, int16_t speed_pos, int16_t speed_neg, double acc_pos, double acc_neg);

#endif
#endif // SPEED_FILTER_H_INCLUDED

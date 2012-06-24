#include "speed_filter.h"
#include "Options.h"
#include <math.h>
#include <string.h>
#ifndef NEW_RAMP

void speed_filter_init(struct speed_filter * sf,uint16_t speed_pos,uint16_t speed_neg,
                        uint16_t acc_pos/*,uint16_t decc_pos*/,uint16_t acc_neg/*,
                        uint16_t decc_neg*/)
{	
	//memset ( sf , 0 , sizeof ( struct speed_filter ) );
    sf->speed_pos=speed_pos;
    sf->speed_neg=speed_neg;
    sf->acc_pos=acc_pos;
    //sf->decc_pos=decc_pos;
    sf->acc_neg=acc_neg;
    //sf->decc_neg=decc_neg;
    sf->consign=0;
    sf->prev_out=0;
    sf->prev_speed=0;
}

void speed_filter_set_consign(struct speed_filter * sf,int32_t *consign)
{
	int16_t pt1;
	
	if (*consign>=0)
    	sf->consign=*consign<<10;
	else
		sf->consign=-((-*consign)<<10);
	
    //Calcul of instants t0,t1 et t2.
    //Those results are provided by the solve of the equation :
    //              consign=integral(dx/dt);
    /* assuming that acc_pos*t0=-decc_pos*t1+decc_pos*t2=x.*/
    
    if (sf->consign>=0)
    {

        sf->t0=sf->speed_pos/sf->acc_pos;
        //pt1=sf->t0/2+(sf->consign)/sf->speed_pos-sf->speed_pos/(2*sf->decc_pos);
        pt1=sf->t0/2+(sf->consign)/sf->speed_pos-sf->speed_pos/(2*sf->acc_pos);
        if(pt1<(int16_t)sf->t0)
        {
            /*//Now, the problem is different
            //it could be solved assuming that the
            //[(0,0),(0,t2),(x,t2),(x,0)] rectangle
            //has an area equal to 2*C.
            //   dx
            //   --
            //   dt
            //    ^
            //    |
            //   x|.. .     x=2sf->consign/t2
            //    |  /:\
            //    | / : \
            //    |/  :  \
            //    O---------------------> t
            //      t0=t1 t2
            /*sf->t2=(uint16_t)sqrt((double)
                    (2*(sf->consign)*(sf->acc_pos+sf->decc_pos))/(sf->acc_pos*sf->decc_pos));//*/
            sf->t2=(uint16_t)sqrt((double)
                    (2*(sf->consign)*(sf->acc_pos+sf->acc_pos))/(sf->acc_pos*sf->acc_pos));

            sf->t0=2*(sf->consign)/(sf->acc_pos*sf->t2);
            pt1=sf->t0;
            sf->x=2*(sf->consign)/sf->t2;
        }
        else
        {
            //sf->t2=sf->speed_pos/sf->decc_pos + pt1;
            sf->t2=sf->speed_pos/sf->acc_pos + pt1;
            sf->x=sf->speed_pos;
        }
        sf->t1=pt1;
    }
    else//equivalent negative case
    {
        sf->t0=sf->speed_neg/sf->acc_neg;
        //pt1=sf->speed_neg/(sf->acc_neg*2)+(-sf->consign)/sf->speed_neg-sf->speed_neg/(2*sf->decc_neg);
        pt1=sf->speed_neg/(sf->acc_neg*2)+(-sf->consign)/sf->speed_neg-sf->speed_neg/(2*sf->acc_neg);
        if(pt1<( int16_t)sf->t0)
        {
            /*sf->t2=(uint16_t)sqrt((double)
                    (2*(-sf->consign)*(sf->acc_neg+sf->decc_neg))/(sf->acc_neg*sf->decc_neg));//*/
            sf->t2=(uint16_t)sqrt((double)
                    (2*(-sf->consign)*(sf->acc_neg+sf->acc_neg))/(sf->acc_neg*sf->acc_neg));
            sf->t0=2*(-sf->consign)/(sf->acc_neg*sf->t2);
            pt1=sf->t0;
            sf->x=2*(-sf->consign)/sf->t2;
        }
        else
        {
            //sf->t2=sf->speed_neg/sf->decc_neg + pt1;
            sf->t2=sf->speed_neg/sf->acc_neg + pt1;
            sf->x=sf->speed_neg;
        }
        sf->t1=pt1;
    }
    sf->prev_out=0;
    sf->prev_speed=0;
    sf->t=0;
    //sf->prev_speed=sf->consign>=0?1:-1;
}


char speed_filter_do_filter(struct speed_filter * sf,int32_t *filtered_consign)
{
    if(sf->consign>=0)
    {
        if(sf->t>sf->t1)
        {
            if(sf->t+1>=sf->t2)
            {
                *filtered_consign=sf->consign>>10;
                return 1;
            }
            //sf->prev_speed-=sf->decc_pos;
            sf->prev_speed-=sf->acc_pos;
        }
        else if (sf->t<sf->t0)
        {
            sf->prev_speed+=sf->acc_pos;
        }
        else
        {
			if(sf->ta)
			{
				if(sf->prev_speed>sf->x)
					sf->prev_speed-=sf->acc_pos;
				else
				{
					sf->prev_speed=sf->x;
					sf->ta=0;
				}
			}
			else
			{
            	sf->prev_speed=sf->x;
			}
        }
    }
    else
    {
        if(sf->t>sf->t1)
        {
            if(sf->t+1>=sf->t2)
            {
                *filtered_consign=sf->consign>>10;;
                return 1;
            }
            //sf->prev_speed+=sf->decc_neg;
            sf->prev_speed+=sf->acc_neg;
        }
        else if (sf->t<sf->t0)
        {
            sf->prev_speed-=sf->acc_neg;
        }
        else
        {
            if(sf->ta)
			{
				if(sf->prev_speed<sf->x)
					sf->prev_speed+=sf->acc_pos;
				else
				{
					sf->prev_speed=-sf->x;
					sf->ta=0;
				}
			}
			else
			{
            	sf->prev_speed=-sf->x;
			}
        }
    }
    sf->prev_out+=sf->prev_speed;
	if (sf->prev_out>=0)
    	*filtered_consign=sf->prev_out>>10;
	else
		*filtered_consign=-((-sf->prev_out)>>10);
		
	
	
	/*int16 uart_buff[2];
	uint16_t i;
	char ret[32];
	if(Debug_speed)
	{
		if (sf->prev_out>0)
		{
			uart_buff[0]=sf->prev_out>>16;
			i=sf->prev_out;
			sprintf(ret,"\r %d %u`|",uart_buff[0],i);
			UART_1_PutString(&ret);
		}
		else
		{
			uart_buff[0]=(-sf->prev_out)>>16;
			i=sf->prev_out;
			sprintf(ret,"\r -%d %u|",uart_buff[0],i);
			UART_1_PutString(&ret);
		}
		if (*filtered_consign>0)
		{
			uart_buff[1]=*filtered_consign>>16;
			i=*filtered_consign;
			sprintf(ret,",  %d %u",uart_buff[1],i);
			UART_1_PutString(&ret);
		}
		else
		{
			uart_buff[1]=(-*filtered_consign)>>16;
			i=*filtered_consign;
			sprintf(ret,", -%d %u",uart_buff[1],i);
			UART_1_PutString(&ret);
		}
	}*/
	
    ++sf->t;
    return 0;
}


void speed_filter_stop(struct speed_filter * sf)
{
	sf->prev_out=0;
	sf->t=0;sf->t0=0;sf->t1=0;
	if(sf->prev_speed>=0)
	{
		sf->t2=sf->prev_speed/sf->acc_pos;
		sf->consign=(sf->prev_speed*sf->prev_speed)/(2*sf->acc_pos);
	}
	else
	{
		sf->t2=(-sf->prev_speed)/sf->acc_pos;
		sf->consign=-(sf->prev_speed*sf->prev_speed)/(2*sf->acc_pos);
	}
}

char speed_change(struct speed_filter *sf, int32_t speed)
{
	int16_t pt1;
	if(sf->t>sf->t1)
	{
		sf->speed_neg=speed;
		return 1;
	}
		
	if(sf->consign>=0)
	{
		if(sf->t<sf->t0)
		{
			if(sf->prev_speed>speed)
			{
				sf->t0=sf->t;
				sf->t1=sf->t+(sf->prev_speed-speed)/sf->acc_pos +
					(sf->consign-sf->prev_out - (((sf->prev_speed-speed)*speed)+
					((sf->prev_speed-speed)*(sf->prev_speed-speed)+speed*speed)/2)
					/sf->acc_pos)/speed;
				sf->t2=sf->t1 + speed/sf->acc_pos;
				sf->ta=1;
				sf->x=speed;
				sf->speed_pos=speed;
			}
			else 
			{
				sf->speed_pos=speed;
				sf->t0=sf->speed_pos/sf->acc_pos;
				pt1=sf->t0/2+(sf->consign)/sf->speed_pos-sf->speed_pos
					/(2*sf->acc_pos);
				if(pt1<( int16_t)sf->t0)
				{
					sf->t2=(uint16_t)sqrt((double)
							(2*(sf->consign)*(sf->acc_pos+sf->acc_pos))
							/(sf->acc_pos*sf->acc_pos));
		
					sf->t0=2*(sf->consign)/(sf->acc_pos*sf->t2);
					pt1=sf->t0;
					sf->x=2*(sf->consign)/sf->t2;
				}
				else
				{
					//sf->t2=sf->speed_pos/sf->decc_pos + pt1;
					sf->t2=sf->speed_pos/sf->acc_pos + pt1;
					sf->x=sf->speed_pos;
				}
				sf->t1=pt1;
			}
		}
		else if (sf->t<sf->t1)
		{
		
			sf->t1=sf->t+(sf->prev_speed-speed)/sf->acc_pos +
				(sf->consign-sf->prev_out - (((sf->prev_speed-speed)*speed)+
				((sf->prev_speed-speed)*(sf->prev_speed-speed)+speed*speed)/2)
				/sf->acc_pos)/speed;
			sf->t2=sf->t1 + speed/sf->acc_pos;
			sf->ta=1;
			sf->x=speed;
			sf->speed_pos=speed;
		}
		else
			return 0;
	}
	else
	{
		if(sf->t<sf->t0)
		{
			if((-sf->prev_speed)>speed)
			{
				sf->t0=sf->t;
				sf->t1=sf->t+((-sf->prev_speed)-speed)/sf->acc_pos +
					((-sf->consign)-sf->prev_out - ((((-sf->prev_speed)-speed)*speed)+
					(((-sf->prev_speed)-speed)*((-sf->prev_speed)-speed)+speed*speed)/2)
					/sf->acc_neg)/speed;
				sf->t2=sf->t1 + speed/sf->acc_neg;
				sf->ta=1;
				sf->x=speed;
				sf->speed_neg=speed;
			}
			else 
			{
				sf->speed_pos=speed;
				sf->t0=sf->speed_neg/sf->acc_neg;
				pt1=sf->speed_neg/(sf->acc_neg*2)+(-sf->consign)/
					sf->speed_neg-sf->speed_neg/(2*sf->acc_neg);
				if(pt1<( int16_t)sf->t0)
				{
					sf->t2=(uint16_t)sqrt((double)
						(2*(-sf->consign)*(sf->acc_neg+sf->acc_neg))/
						(sf->acc_neg*sf->acc_neg));
					sf->t0=2*(-sf->consign)/(sf->acc_neg*sf->t2);
					pt1=sf->t0;
					sf->x=2*(-sf->consign)/sf->t2;
				}
				else
				{
					sf->t2=sf->speed_neg/sf->acc_neg + pt1;
					sf->x=sf->speed_neg;
				}
				sf->t1=pt1;
			}
		}
		else if (sf->t<sf->t1)
		{
			sf->t1=sf->t+((-sf->prev_speed)-speed)/sf->acc_pos +
				((-sf->consign)-sf->prev_out - ((((-sf->prev_speed)-speed)*speed)+
				(((-sf->prev_speed)-speed)*((-sf->prev_speed)-speed)+speed*speed)/2)
				/sf->acc_neg)/speed;
			sf->t2=sf->t1 + speed/sf->acc_neg;
			sf->ta=1;
			sf->x=speed;
			sf->speed_neg=speed;
		}
		else
			return 0;
	}
	return 1;
}




#else
/************************Modification par TELEMAQUE Olivier de la rampe de vitesse********************************************/

void speed_filter_init(struct speed_filter* sf, int16_t speed_pos, int16_t speed_neg, double acc_pos, double acc_neg)
{
    sf->speed_pos = speed_pos;
    sf->speed_neg = speed_neg;
    sf->acc_pos = acc_pos;
    sf->acc_neg = acc_neg;
    sf->consign = 0;
    sf->prev_out = 0;
    sf->prev_speed = 0;
	sf->t = 0;
	sf->t0 = 0;
	sf->t1 = 0;
	sf->t2 = 0;
}

void speed_filter_set_consign(struct speed_filter* sf, int32_t* consign)//penser ? g?rer consigne n?gative,quelques optimisations possibles
{
	int32_t aire_A, aire_B, aire_C, t2_t1, pt1, absolute_consign;
    double speed;
	 
	sf->consign = *consign;
    absolute_consign = *consign >= 0 ? *consign : -*consign;

	sf->t0 = (int16_t)(sf->speed_pos / sf->acc_pos);
	t2_t1 = (int32_t)(sf->speed_pos / sf->acc_neg);
	aire_A = sf->t0 * sf->speed_pos / 2;
	aire_C = t2_t1 * sf->speed_pos / 2;
	aire_B = absolute_consign - aire_A - aire_C;
	pt1 = (int32_t)(aire_B / sf->speed_pos + sf->t0);
	sf->t2 = (int16_t)(t2_t1 + pt1);

	if(pt1 < sf->t0)//cas ou le trapèze est dégénéré
	{ 
     	speed = sqrt((2 * absolute_consign * (sf->acc_neg * sf->acc_pos)) / (sf->acc_neg + sf->acc_pos));
		sf->speed_pos = (int16_t)speed;
		sf->t0 = (int16_t)(sf->t1 = speed / sf->acc_pos);
		sf->t2 = (int16_t)(sf->t1 + speed/sf->acc_neg);
	}
	else
		sf->t1 = (int16_t)(pt1);
	
	sf->t = 0;
	sf->prev_speed = 0;
	sf->prev_out = 0;
}


char speed_filter_do_filter(struct speed_filter* sf, int32_t* filtered_consign)
{
	double consign = sf->prev_out;
	uint16_t cte = sf->speed_pos*sf->t0 / 2.0 + (sf->t1 - sf->t0) * sf->speed_pos;

    if(sf->t < sf->t0)
    {
		sf->prev_speed = (sf->t + 1) * sf->acc_pos;
		consign = (sf->t + 1) * (sf->t + 1) * sf->acc_pos / 2.0;
    }
	else if(sf->t < sf->t1)
	{
	    sf->prev_speed = sf->speed_pos;
	    consign = sf->speed_pos * sf->t0 / 2.0 + ((sf->t + 1) - sf->t0) * sf->prev_speed;
	}
	else if(sf->t < sf->t2)
	{
		sf->prev_speed = sf->speed_pos - floor(((sf->t + 1) - sf->t1) * sf->acc_neg);
		consign = cte + ((sf->t2 - sf->t1) * sf->speed_pos / 2.0) - ((sf->t2 - (sf->t + 1)) * (sf->t2 - (sf->t + 1)) * sf->acc_neg / 2.0);
	}
	
	if (sf->t >= sf->t2)
	{	
		if(sf->prev_out < abs(sf->consign))
		{
			sf->t++;
			
			if(sf->prev_speed != 0)
				sf->prev_speed = 0;
	
			consign = sf->prev_out + 1;// + 1 n'a aucun sens, + acc_pos ou acc_neg * temps semble etre la solution
		}
	}
	else
		sf->t++;

    sf->prev_out = consign;	
    *filtered_consign = sf->consign >= 0 ? consign : -consign;

    return 0;
}

//void speed_filter_init(struct speed_filter * sf,int16_t speed_pos,int16_t speed_neg,
//                        int16_t acc_pos,int16_t acc_neg)
//{
//    sf->speed_pos=speed_pos;
//    sf->speed_neg=speed_neg;
//    sf->acc_pos=acc_pos;
//    sf->acc_neg=acc_neg;
//    sf->consign=0;
//    sf->prev_out=0;
//    sf->prev_speed=0;
//	sf->t = 0;
//	sf->t0 = 0;
//	sf->t1 = 0;
//	sf->t2 = 0;
//}
//
//void speed_filter_set_consign(struct speed_filter * sf,int32_t *consign)//penser ? g?rer consigne n?gative,quelques optimisations possibles
//{
//	int32_t aire_A , aire_B , aire_C , t2_t1 , pt1 , absolute_consign;
//    int32_t speed;
//	
//	sf->consign = *consign;
//    absolute_consign = ( *consign >= 0 ? *consign : -*consign ) << RAMP_SHIFT;
//
//	sf->t0 =  sf->speed_pos / sf->acc_pos;
//	t2_t1 = sf->speed_pos / sf->acc_neg;
//	aire_A = sf->t0 * sf->speed_pos / 2;
//	aire_C = t2_t1 * sf->speed_pos / 2;
//	aire_B = absolute_consign - aire_A - aire_C;
//	pt1 = aire_B / sf->speed_pos  + sf->t0;
//	sf->t2 = t2_t1 + pt1;
//
//	if ( pt1 < sf->t0 )//cas ou le trapèze est dégénéré
//	{ 
//     	speed = sqrt ( ( 2 * absolute_consign * ( sf->acc_neg * sf->acc_pos ) ) / ( sf->acc_neg + sf->acc_pos ) );
//		sf->speed_pos = speed;
//		sf->t0 = sf->t1 = speed/sf->acc_pos;
//		sf->t2 = sf->t1 + speed/sf->acc_neg;
//	}
//	else
//		sf->t1 = pt1;
//	
//	sf->t = 0;
//	sf->prev_out = 0;
//	sf->prev_speed = 0;
//
//	/*{
//		char buff[51];
//		
//		sprintf ( buff , "new ramp consign %ld t0 %ld t1 %ld t2 %ld\r\n" , sf->consign , sf->t0 , sf->t1 , sf->t2 );
//		UART_1_PutString ( buff );
//	}*/
//}
//
//char speed_filter_do_filter ( struct speed_filter * sf , int32_t* filtered_consign)
//{
//	int32_t absolute_cons , cte = sf->speed_pos*sf->t0/2.0 + ( sf->t1 - sf->t0 ) * sf->speed_pos;;
//	
//    if ( sf->t < sf->t0 )
//		sf->prev_speed += sf->acc_pos;
//	else if ( sf->t < sf->t1 )
//	    sf->prev_speed = sf->speed_pos;
//	else if ( sf->t < sf->t2 )
//		sf->prev_speed -= sf->acc_neg;
//	
//	if ( sf->t >= sf->t2 )
//	{	
//		if (  sf->prev_out < abs ( sf->consign ) )
//		{
//			sf->t++;
//			
//			if ( sf->prev_speed > 0 )
//				sf->prev_speed -= sf->acc_neg;
//				
//			if ( sf->prev_speed < 0 )
//				sf->prev_speed = 0;
//		}
//		else
//		{
//			sf->prev_speed = 0;
//			sf->prev_out = sf->consign;
//		}
//	}
//	else
//		sf->t++;
//
//    sf->prev_out += sf->prev_speed;
//	absolute_cons = sf->prev_out >> RAMP_SHIFT;
//	
//	if ( sf->prev_speed > 0 )
//    	*filtered_consign = ( sf->consign >= 0 ? absolute_cons : -absolute_cons );
//	else
//		*filtered_consign = sf->consign;
//	
//	{
//		char buff[51];
//		
//		sprintf ( buff , "new ramp consign_filtered %ld\r\n" , *filtered_consign );
//		UART_1_PutString ( buff );
//	}
//	
//    return 0;
//}

void speed_filter_stop(struct speed_filter* sf)
{
	int32_t time_decc = (int32_t)(sf->prev_speed / sf->acc_neg);
	
	if(sf->t < sf->t1)
	{
		if(sf->t < sf->t0)
		{
			sf->t0 = sf->t;
			sf->t1 = sf->t;
		}
		else
			sf->t1 = sf->t;
			
		sf->t2 = sf->t + time_decc;
		sf->consign = sf->consign > 0 ? sf->prev_out + (int32_t)(time_decc * sf->prev_speed / 2) : -(sf->prev_out + (int32_t)(time_decc * sf->prev_speed / 2));
	}
}

void speed_filter_set_cinematic_parameter(struct speed_filter* sf, int16_t speed_pos, int16_t speed_neg, double acc_pos, double acc_neg)
{
	sf->speed_pos = speed_pos;
	sf->speed_neg = speed_neg;
	sf->acc_pos = acc_pos;
	sf->acc_neg = acc_neg;
}

/**
* TODO 2013 Integrate Microb Quadramp
*
**/
#endif
//le speed change n'est pas nécessaire

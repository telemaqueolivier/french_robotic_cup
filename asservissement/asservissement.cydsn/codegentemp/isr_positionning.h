/*******************************************************************************
* File Name: isr_positionning.h
* Version 1.50
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__isr_positionning_INTC_H__)
#define __isr_positionning_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define isr_positionning_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void isr_positionning_Start(void);
void isr_positionning_StartEx(cyisraddress address);
void isr_positionning_Stop(void) ;

CY_ISR_PROTO(isr_positionning_Interrupt);

void isr_positionning_SetVector(cyisraddress address) ;
cyisraddress isr_positionning_GetVector(void) ;

void isr_positionning_SetPriority(uint8 priority) ;
uint8 isr_positionning_GetPriority(void) ;

void isr_positionning_Enable(void) ;
uint8 isr_positionning_GetState(void) ;
void isr_positionning_Disable(void) ;

void isr_positionning_SetPending(void) ;
void isr_positionning_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_positionning ISR. */
#define isr_positionning_INTC_VECTOR            ((reg16 *) isr_positionning__INTC_VECT)

/* Address of the isr_positionning ISR priority. */
#define isr_positionning_INTC_PRIOR             ((reg8 *) isr_positionning__INTC_PRIOR_REG)

/* Priority of the isr_positionning interrupt. */
#define isr_positionning_INTC_PRIOR_NUMBER      isr_positionning__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_positionning interrupt. */
#define isr_positionning_INTC_SET_EN            ((reg8 *) isr_positionning__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_positionning interrupt. */
#define isr_positionning_INTC_CLR_EN            ((reg8 *) isr_positionning__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_positionning interrupt state to pending. */
#define isr_positionning_INTC_SET_PD            ((reg8 *) isr_positionning__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_positionning interrupt. */
#define isr_positionning_INTC_CLR_PD            ((reg8 *) isr_positionning__INTC_CLR_PD_REG)



/* __isr_positionning_INTC_H__ */
#endif

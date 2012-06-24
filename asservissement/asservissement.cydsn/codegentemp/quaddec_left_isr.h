/*******************************************************************************
* File Name: quaddec_left_isr.h
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
#if !defined(__quaddec_left_isr_INTC_H__)
#define __quaddec_left_isr_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define quaddec_left_isr_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void quaddec_left_isr_Start(void);
void quaddec_left_isr_StartEx(cyisraddress address);
void quaddec_left_isr_Stop(void) ;

CY_ISR_PROTO(quaddec_left_isr_Interrupt);

void quaddec_left_isr_SetVector(cyisraddress address) ;
cyisraddress quaddec_left_isr_GetVector(void) ;

void quaddec_left_isr_SetPriority(uint8 priority) ;
uint8 quaddec_left_isr_GetPriority(void) ;

void quaddec_left_isr_Enable(void) ;
uint8 quaddec_left_isr_GetState(void) ;
void quaddec_left_isr_Disable(void) ;

void quaddec_left_isr_SetPending(void) ;
void quaddec_left_isr_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the quaddec_left_isr ISR. */
#define quaddec_left_isr_INTC_VECTOR            ((reg16 *) quaddec_left_isr__INTC_VECT)

/* Address of the quaddec_left_isr ISR priority. */
#define quaddec_left_isr_INTC_PRIOR             ((reg8 *) quaddec_left_isr__INTC_PRIOR_REG)

/* Priority of the quaddec_left_isr interrupt. */
#define quaddec_left_isr_INTC_PRIOR_NUMBER      quaddec_left_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable quaddec_left_isr interrupt. */
#define quaddec_left_isr_INTC_SET_EN            ((reg8 *) quaddec_left_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the quaddec_left_isr interrupt. */
#define quaddec_left_isr_INTC_CLR_EN            ((reg8 *) quaddec_left_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the quaddec_left_isr interrupt state to pending. */
#define quaddec_left_isr_INTC_SET_PD            ((reg8 *) quaddec_left_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the quaddec_left_isr interrupt. */
#define quaddec_left_isr_INTC_CLR_PD            ((reg8 *) quaddec_left_isr__INTC_CLR_PD_REG)



/* __quaddec_left_isr_INTC_H__ */
#endif

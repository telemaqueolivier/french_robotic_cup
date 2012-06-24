/*******************************************************************************
* File Name: mot_right_backward.h  
* Version 1.50
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_mot_right_backward_H) /* Pins mot_right_backward_H */
#define CY_PINS_mot_right_backward_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "mot_right_backward_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    mot_right_backward_Write(uint8 value) ;
void    mot_right_backward_SetDriveMode(uint8 mode) ;
uint8   mot_right_backward_ReadDataReg(void) ;
uint8   mot_right_backward_Read(void) ;
uint8   mot_right_backward_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define mot_right_backward_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define mot_right_backward_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define mot_right_backward_DM_RES_UP          PIN_DM_RES_UP
#define mot_right_backward_DM_RES_DWN         PIN_DM_RES_DWN
#define mot_right_backward_DM_OD_LO           PIN_DM_OD_LO
#define mot_right_backward_DM_OD_HI           PIN_DM_OD_HI
#define mot_right_backward_DM_STRONG          PIN_DM_STRONG
#define mot_right_backward_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define mot_right_backward_MASK               mot_right_backward__MASK
#define mot_right_backward_SHIFT              mot_right_backward__SHIFT
#define mot_right_backward_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define mot_right_backward_PS                     (* (reg8 *) mot_right_backward__PS)
/* Data Register */
#define mot_right_backward_DR                     (* (reg8 *) mot_right_backward__DR)
/* Port Number */
#define mot_right_backward_PRT_NUM                (* (reg8 *) mot_right_backward__PRT) 
/* Connect to Analog Globals */                                                  
#define mot_right_backward_AG                     (* (reg8 *) mot_right_backward__AG)                       
/* Analog MUX bux enable */
#define mot_right_backward_AMUX                   (* (reg8 *) mot_right_backward__AMUX) 
/* Bidirectional Enable */                                                        
#define mot_right_backward_BIE                    (* (reg8 *) mot_right_backward__BIE)
/* Bit-mask for Aliased Register Access */
#define mot_right_backward_BIT_MASK               (* (reg8 *) mot_right_backward__BIT_MASK)
/* Bypass Enable */
#define mot_right_backward_BYP                    (* (reg8 *) mot_right_backward__BYP)
/* Port wide control signals */                                                   
#define mot_right_backward_CTL                    (* (reg8 *) mot_right_backward__CTL)
/* Drive Modes */
#define mot_right_backward_DM0                    (* (reg8 *) mot_right_backward__DM0) 
#define mot_right_backward_DM1                    (* (reg8 *) mot_right_backward__DM1)
#define mot_right_backward_DM2                    (* (reg8 *) mot_right_backward__DM2) 
/* Input Buffer Disable Override */
#define mot_right_backward_INP_DIS                (* (reg8 *) mot_right_backward__INP_DIS)
/* LCD Common or Segment Drive */
#define mot_right_backward_LCD_COM_SEG            (* (reg8 *) mot_right_backward__LCD_COM_SEG)
/* Enable Segment LCD */
#define mot_right_backward_LCD_EN                 (* (reg8 *) mot_right_backward__LCD_EN)
/* Slew Rate Control */
#define mot_right_backward_SLW                    (* (reg8 *) mot_right_backward__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define mot_right_backward_PRTDSI__CAPS_SEL       (* (reg8 *) mot_right_backward__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define mot_right_backward_PRTDSI__DBL_SYNC_IN    (* (reg8 *) mot_right_backward__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define mot_right_backward_PRTDSI__OE_SEL0        (* (reg8 *) mot_right_backward__PRTDSI__OE_SEL0) 
#define mot_right_backward_PRTDSI__OE_SEL1        (* (reg8 *) mot_right_backward__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define mot_right_backward_PRTDSI__OUT_SEL0       (* (reg8 *) mot_right_backward__PRTDSI__OUT_SEL0) 
#define mot_right_backward_PRTDSI__OUT_SEL1       (* (reg8 *) mot_right_backward__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define mot_right_backward_PRTDSI__SYNC_OUT       (* (reg8 *) mot_right_backward__PRTDSI__SYNC_OUT) 


#if defined(mot_right_backward__INTSTAT)  /* Interrupt Registers */

    #define mot_right_backward_INTSTAT                (* (reg8 *) mot_right_backward__INTSTAT)
    #define mot_right_backward_SNAP                   (* (reg8 *) mot_right_backward__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins mot_right_backward_H */


/* [] END OF FILE */

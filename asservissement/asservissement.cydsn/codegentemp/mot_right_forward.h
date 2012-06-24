/*******************************************************************************
* File Name: mot_right_forward.h  
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

#if !defined(CY_PINS_mot_right_forward_H) /* Pins mot_right_forward_H */
#define CY_PINS_mot_right_forward_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "mot_right_forward_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    mot_right_forward_Write(uint8 value) ;
void    mot_right_forward_SetDriveMode(uint8 mode) ;
uint8   mot_right_forward_ReadDataReg(void) ;
uint8   mot_right_forward_Read(void) ;
uint8   mot_right_forward_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define mot_right_forward_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define mot_right_forward_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define mot_right_forward_DM_RES_UP          PIN_DM_RES_UP
#define mot_right_forward_DM_RES_DWN         PIN_DM_RES_DWN
#define mot_right_forward_DM_OD_LO           PIN_DM_OD_LO
#define mot_right_forward_DM_OD_HI           PIN_DM_OD_HI
#define mot_right_forward_DM_STRONG          PIN_DM_STRONG
#define mot_right_forward_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define mot_right_forward_MASK               mot_right_forward__MASK
#define mot_right_forward_SHIFT              mot_right_forward__SHIFT
#define mot_right_forward_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define mot_right_forward_PS                     (* (reg8 *) mot_right_forward__PS)
/* Data Register */
#define mot_right_forward_DR                     (* (reg8 *) mot_right_forward__DR)
/* Port Number */
#define mot_right_forward_PRT_NUM                (* (reg8 *) mot_right_forward__PRT) 
/* Connect to Analog Globals */                                                  
#define mot_right_forward_AG                     (* (reg8 *) mot_right_forward__AG)                       
/* Analog MUX bux enable */
#define mot_right_forward_AMUX                   (* (reg8 *) mot_right_forward__AMUX) 
/* Bidirectional Enable */                                                        
#define mot_right_forward_BIE                    (* (reg8 *) mot_right_forward__BIE)
/* Bit-mask for Aliased Register Access */
#define mot_right_forward_BIT_MASK               (* (reg8 *) mot_right_forward__BIT_MASK)
/* Bypass Enable */
#define mot_right_forward_BYP                    (* (reg8 *) mot_right_forward__BYP)
/* Port wide control signals */                                                   
#define mot_right_forward_CTL                    (* (reg8 *) mot_right_forward__CTL)
/* Drive Modes */
#define mot_right_forward_DM0                    (* (reg8 *) mot_right_forward__DM0) 
#define mot_right_forward_DM1                    (* (reg8 *) mot_right_forward__DM1)
#define mot_right_forward_DM2                    (* (reg8 *) mot_right_forward__DM2) 
/* Input Buffer Disable Override */
#define mot_right_forward_INP_DIS                (* (reg8 *) mot_right_forward__INP_DIS)
/* LCD Common or Segment Drive */
#define mot_right_forward_LCD_COM_SEG            (* (reg8 *) mot_right_forward__LCD_COM_SEG)
/* Enable Segment LCD */
#define mot_right_forward_LCD_EN                 (* (reg8 *) mot_right_forward__LCD_EN)
/* Slew Rate Control */
#define mot_right_forward_SLW                    (* (reg8 *) mot_right_forward__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define mot_right_forward_PRTDSI__CAPS_SEL       (* (reg8 *) mot_right_forward__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define mot_right_forward_PRTDSI__DBL_SYNC_IN    (* (reg8 *) mot_right_forward__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define mot_right_forward_PRTDSI__OE_SEL0        (* (reg8 *) mot_right_forward__PRTDSI__OE_SEL0) 
#define mot_right_forward_PRTDSI__OE_SEL1        (* (reg8 *) mot_right_forward__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define mot_right_forward_PRTDSI__OUT_SEL0       (* (reg8 *) mot_right_forward__PRTDSI__OUT_SEL0) 
#define mot_right_forward_PRTDSI__OUT_SEL1       (* (reg8 *) mot_right_forward__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define mot_right_forward_PRTDSI__SYNC_OUT       (* (reg8 *) mot_right_forward__PRTDSI__SYNC_OUT) 


#if defined(mot_right_forward__INTSTAT)  /* Interrupt Registers */

    #define mot_right_forward_INTSTAT                (* (reg8 *) mot_right_forward__INTSTAT)
    #define mot_right_forward_SNAP                   (* (reg8 *) mot_right_forward__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins mot_right_forward_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: encoder_left_sig_a.h  
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

#if !defined(CY_PINS_encoder_left_sig_a_H) /* Pins encoder_left_sig_a_H */
#define CY_PINS_encoder_left_sig_a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "encoder_left_sig_a_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    encoder_left_sig_a_Write(uint8 value) ;
void    encoder_left_sig_a_SetDriveMode(uint8 mode) ;
uint8   encoder_left_sig_a_ReadDataReg(void) ;
uint8   encoder_left_sig_a_Read(void) ;
uint8   encoder_left_sig_a_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define encoder_left_sig_a_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define encoder_left_sig_a_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define encoder_left_sig_a_DM_RES_UP          PIN_DM_RES_UP
#define encoder_left_sig_a_DM_RES_DWN         PIN_DM_RES_DWN
#define encoder_left_sig_a_DM_OD_LO           PIN_DM_OD_LO
#define encoder_left_sig_a_DM_OD_HI           PIN_DM_OD_HI
#define encoder_left_sig_a_DM_STRONG          PIN_DM_STRONG
#define encoder_left_sig_a_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define encoder_left_sig_a_MASK               encoder_left_sig_a__MASK
#define encoder_left_sig_a_SHIFT              encoder_left_sig_a__SHIFT
#define encoder_left_sig_a_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define encoder_left_sig_a_PS                     (* (reg8 *) encoder_left_sig_a__PS)
/* Data Register */
#define encoder_left_sig_a_DR                     (* (reg8 *) encoder_left_sig_a__DR)
/* Port Number */
#define encoder_left_sig_a_PRT_NUM                (* (reg8 *) encoder_left_sig_a__PRT) 
/* Connect to Analog Globals */                                                  
#define encoder_left_sig_a_AG                     (* (reg8 *) encoder_left_sig_a__AG)                       
/* Analog MUX bux enable */
#define encoder_left_sig_a_AMUX                   (* (reg8 *) encoder_left_sig_a__AMUX) 
/* Bidirectional Enable */                                                        
#define encoder_left_sig_a_BIE                    (* (reg8 *) encoder_left_sig_a__BIE)
/* Bit-mask for Aliased Register Access */
#define encoder_left_sig_a_BIT_MASK               (* (reg8 *) encoder_left_sig_a__BIT_MASK)
/* Bypass Enable */
#define encoder_left_sig_a_BYP                    (* (reg8 *) encoder_left_sig_a__BYP)
/* Port wide control signals */                                                   
#define encoder_left_sig_a_CTL                    (* (reg8 *) encoder_left_sig_a__CTL)
/* Drive Modes */
#define encoder_left_sig_a_DM0                    (* (reg8 *) encoder_left_sig_a__DM0) 
#define encoder_left_sig_a_DM1                    (* (reg8 *) encoder_left_sig_a__DM1)
#define encoder_left_sig_a_DM2                    (* (reg8 *) encoder_left_sig_a__DM2) 
/* Input Buffer Disable Override */
#define encoder_left_sig_a_INP_DIS                (* (reg8 *) encoder_left_sig_a__INP_DIS)
/* LCD Common or Segment Drive */
#define encoder_left_sig_a_LCD_COM_SEG            (* (reg8 *) encoder_left_sig_a__LCD_COM_SEG)
/* Enable Segment LCD */
#define encoder_left_sig_a_LCD_EN                 (* (reg8 *) encoder_left_sig_a__LCD_EN)
/* Slew Rate Control */
#define encoder_left_sig_a_SLW                    (* (reg8 *) encoder_left_sig_a__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define encoder_left_sig_a_PRTDSI__CAPS_SEL       (* (reg8 *) encoder_left_sig_a__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define encoder_left_sig_a_PRTDSI__DBL_SYNC_IN    (* (reg8 *) encoder_left_sig_a__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define encoder_left_sig_a_PRTDSI__OE_SEL0        (* (reg8 *) encoder_left_sig_a__PRTDSI__OE_SEL0) 
#define encoder_left_sig_a_PRTDSI__OE_SEL1        (* (reg8 *) encoder_left_sig_a__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define encoder_left_sig_a_PRTDSI__OUT_SEL0       (* (reg8 *) encoder_left_sig_a__PRTDSI__OUT_SEL0) 
#define encoder_left_sig_a_PRTDSI__OUT_SEL1       (* (reg8 *) encoder_left_sig_a__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define encoder_left_sig_a_PRTDSI__SYNC_OUT       (* (reg8 *) encoder_left_sig_a__PRTDSI__SYNC_OUT) 


#if defined(encoder_left_sig_a__INTSTAT)  /* Interrupt Registers */

    #define encoder_left_sig_a_INTSTAT                (* (reg8 *) encoder_left_sig_a__INTSTAT)
    #define encoder_left_sig_a_SNAP                   (* (reg8 *) encoder_left_sig_a__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins encoder_left_sig_a_H */


/* [] END OF FILE */

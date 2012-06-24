/*******************************************************************************
* File Name: encoder_right_sig_b.h  
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

#if !defined(CY_PINS_encoder_right_sig_b_H) /* Pins encoder_right_sig_b_H */
#define CY_PINS_encoder_right_sig_b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "encoder_right_sig_b_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    encoder_right_sig_b_Write(uint8 value) ;
void    encoder_right_sig_b_SetDriveMode(uint8 mode) ;
uint8   encoder_right_sig_b_ReadDataReg(void) ;
uint8   encoder_right_sig_b_Read(void) ;
uint8   encoder_right_sig_b_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define encoder_right_sig_b_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define encoder_right_sig_b_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define encoder_right_sig_b_DM_RES_UP          PIN_DM_RES_UP
#define encoder_right_sig_b_DM_RES_DWN         PIN_DM_RES_DWN
#define encoder_right_sig_b_DM_OD_LO           PIN_DM_OD_LO
#define encoder_right_sig_b_DM_OD_HI           PIN_DM_OD_HI
#define encoder_right_sig_b_DM_STRONG          PIN_DM_STRONG
#define encoder_right_sig_b_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define encoder_right_sig_b_MASK               encoder_right_sig_b__MASK
#define encoder_right_sig_b_SHIFT              encoder_right_sig_b__SHIFT
#define encoder_right_sig_b_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define encoder_right_sig_b_PS                     (* (reg8 *) encoder_right_sig_b__PS)
/* Data Register */
#define encoder_right_sig_b_DR                     (* (reg8 *) encoder_right_sig_b__DR)
/* Port Number */
#define encoder_right_sig_b_PRT_NUM                (* (reg8 *) encoder_right_sig_b__PRT) 
/* Connect to Analog Globals */                                                  
#define encoder_right_sig_b_AG                     (* (reg8 *) encoder_right_sig_b__AG)                       
/* Analog MUX bux enable */
#define encoder_right_sig_b_AMUX                   (* (reg8 *) encoder_right_sig_b__AMUX) 
/* Bidirectional Enable */                                                        
#define encoder_right_sig_b_BIE                    (* (reg8 *) encoder_right_sig_b__BIE)
/* Bit-mask for Aliased Register Access */
#define encoder_right_sig_b_BIT_MASK               (* (reg8 *) encoder_right_sig_b__BIT_MASK)
/* Bypass Enable */
#define encoder_right_sig_b_BYP                    (* (reg8 *) encoder_right_sig_b__BYP)
/* Port wide control signals */                                                   
#define encoder_right_sig_b_CTL                    (* (reg8 *) encoder_right_sig_b__CTL)
/* Drive Modes */
#define encoder_right_sig_b_DM0                    (* (reg8 *) encoder_right_sig_b__DM0) 
#define encoder_right_sig_b_DM1                    (* (reg8 *) encoder_right_sig_b__DM1)
#define encoder_right_sig_b_DM2                    (* (reg8 *) encoder_right_sig_b__DM2) 
/* Input Buffer Disable Override */
#define encoder_right_sig_b_INP_DIS                (* (reg8 *) encoder_right_sig_b__INP_DIS)
/* LCD Common or Segment Drive */
#define encoder_right_sig_b_LCD_COM_SEG            (* (reg8 *) encoder_right_sig_b__LCD_COM_SEG)
/* Enable Segment LCD */
#define encoder_right_sig_b_LCD_EN                 (* (reg8 *) encoder_right_sig_b__LCD_EN)
/* Slew Rate Control */
#define encoder_right_sig_b_SLW                    (* (reg8 *) encoder_right_sig_b__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define encoder_right_sig_b_PRTDSI__CAPS_SEL       (* (reg8 *) encoder_right_sig_b__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define encoder_right_sig_b_PRTDSI__DBL_SYNC_IN    (* (reg8 *) encoder_right_sig_b__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define encoder_right_sig_b_PRTDSI__OE_SEL0        (* (reg8 *) encoder_right_sig_b__PRTDSI__OE_SEL0) 
#define encoder_right_sig_b_PRTDSI__OE_SEL1        (* (reg8 *) encoder_right_sig_b__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define encoder_right_sig_b_PRTDSI__OUT_SEL0       (* (reg8 *) encoder_right_sig_b__PRTDSI__OUT_SEL0) 
#define encoder_right_sig_b_PRTDSI__OUT_SEL1       (* (reg8 *) encoder_right_sig_b__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define encoder_right_sig_b_PRTDSI__SYNC_OUT       (* (reg8 *) encoder_right_sig_b__PRTDSI__SYNC_OUT) 


#if defined(encoder_right_sig_b__INTSTAT)  /* Interrupt Registers */

    #define encoder_right_sig_b_INTSTAT                (* (reg8 *) encoder_right_sig_b__INTSTAT)
    #define encoder_right_sig_b_SNAP                   (* (reg8 *) encoder_right_sig_b__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins encoder_right_sig_b_H */


/* [] END OF FILE */

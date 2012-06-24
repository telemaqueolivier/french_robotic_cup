/*******************************************************************************
* File Name: uart_pc.c
* Version 2.0
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "uart_pc.h"


/***************************************
* Local data allocation
***************************************/

static uart_pc_BACKUP_STRUCT  uart_pc_backup =
{
    /* enableState - disabled */
    0u,
};        



/*******************************************************************************
* Function Name: uart_pc_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_SaveConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (uart_pc_PSOC3_ES2 || uart_pc_PSOC5_ES1)

        #if(uart_pc_CONTROL_REG_REMOVED == 0u)
            uart_pc_backup.cr = uart_pc_CONTROL_REG;
        #endif /* End uart_pc_CONTROL_REG_REMOVED */

        #if( (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) )
            uart_pc_backup.rx_period = uart_pc_RXBITCTR_PERIOD_REG;
            uart_pc_backup.rx_mask = uart_pc_RXSTATUS_MASK_REG;
            #if (uart_pc_RXHW_ADDRESS_ENABLED)
                uart_pc_backup.rx_addr1 = uart_pc_RXADDRESS1_REG;
                uart_pc_backup.rx_addr2 = uart_pc_RXADDRESS2_REG;
            #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */
        #endif /* End uart_pc_RX_ENABLED | uart_pc_HD_ENABLED*/

        #if(uart_pc_TX_ENABLED)
            #if(uart_pc_TXCLKGEN_DP)
                uart_pc_backup.tx_clk_ctr = uart_pc_TXBITCLKGEN_CTR_REG;
                uart_pc_backup.tx_clk_compl = uart_pc_TXBITCLKTX_COMPLETE_REG;
            #else
                uart_pc_backup.tx_period = uart_pc_TXBITCTR_PERIOD_REG;
            #endif /*End uart_pc_TXCLKGEN_DP */
            uart_pc_backup.tx_mask = uart_pc_TXSTATUS_MASK_REG;
        #endif /*End uart_pc_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (uart_pc_PSOC3_ES3 || uart_pc_PSOC5_ES2)

        #if(uart_pc_CONTROL_REG_REMOVED == 0u)
            uart_pc_backup.cr = uart_pc_CONTROL_REG;
        #endif /* End uart_pc_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: uart_pc_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_RestoreConfig(void)
{
    /* PSoC3 ES2 or early, PSoC5 ES1*/
    #if (uart_pc_PSOC3_ES2 || uart_pc_PSOC5_ES1)

        #if(uart_pc_CONTROL_REG_REMOVED == 0u)
            uart_pc_CONTROL_REG = uart_pc_backup.cr;
        #endif /* End uart_pc_CONTROL_REG_REMOVED */

        #if( (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) )
            uart_pc_RXBITCTR_PERIOD_REG = uart_pc_backup.rx_period;
            uart_pc_RXSTATUS_MASK_REG = uart_pc_backup.rx_mask;
            #if (uart_pc_RXHW_ADDRESS_ENABLED)
                uart_pc_RXADDRESS1_REG = uart_pc_backup.rx_addr1;
                uart_pc_RXADDRESS2_REG = uart_pc_backup.rx_addr2;
            #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */
        #endif  /* End (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) */

        #if(uart_pc_TX_ENABLED)
            #if(uart_pc_TXCLKGEN_DP)
                uart_pc_TXBITCLKGEN_CTR_REG = uart_pc_backup.tx_clk_ctr;
                uart_pc_TXBITCLKTX_COMPLETE_REG = uart_pc_backup.tx_clk_compl;
            #else
                uart_pc_TXBITCTR_PERIOD_REG = uart_pc_backup.tx_period;
            #endif /*End uart_pc_TXCLKGEN_DP */
            uart_pc_TXSTATUS_MASK_REG = uart_pc_backup.tx_mask;
        #endif /*End uart_pc_TX_ENABLED */

    /* PSoC3 ES3 or later, PSoC5 ES2 or later*/
    #elif (uart_pc_PSOC3_ES3 || uart_pc_PSOC5_ES2)

        #if(uart_pc_CONTROL_REG_REMOVED == 0u)
            uart_pc_CONTROL_REG = uart_pc_backup.cr;
        #endif /* End uart_pc_CONTROL_REG_REMOVED */

    #endif  /* End PSOC3_ES3 || PSOC5_ES2 */
}


/*******************************************************************************
* Function Name: uart_pc_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Sleep(void)
{

    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        if((uart_pc_RXSTATUS_ACTL_REG  & uart_pc_INT_ENABLE) != 0u) 
        {
            uart_pc_backup.enableState = 1u;
        }
        else
        {
            uart_pc_backup.enableState = 0u;
        }
    #else
        if((uart_pc_TXSTATUS_ACTL_REG  & uart_pc_INT_ENABLE) !=0u)
        {
            uart_pc_backup.enableState = 1u;
        }
        else
        {
            uart_pc_backup.enableState = 0u;
        }
    #endif /* End uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/

    uart_pc_Stop();
    uart_pc_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_pc_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Wakeup(void)
{
    uart_pc_RestoreConfig();
    #if( (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) )
        uart_pc_ClearRxBuffer();
    #endif /* End (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) */
    #if(uart_pc_TX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_ClearTxBuffer();
    #endif /* End uart_pc_TX_ENABLED || uart_pc_HD_ENABLED */

    if(uart_pc_backup.enableState != 0u)
    {
        uart_pc_Enable();
    } 
}


/* [] END OF FILE */

/*******************************************************************************
* File Name: uart_pc_INT.c
* Version 2.0
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "uart_pc.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED) && \
     (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH))

    extern volatile uint8 uart_pc_rxBuffer[];
    extern volatile uint8 uart_pc_rxBufferRead;
    extern volatile uint8 uart_pc_rxBufferWrite;
    extern volatile uint8 uart_pc_rxBufferLoopDetect;
    extern volatile uint8 uart_pc_rxBufferOverflow;


    /*******************************************************************************
    * Function Name: uart_pc_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     increments after each byte saved to buffer.
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer, 
    *     checked to detect overflow condition.
    *  uart_pc_rxBufferOverflow - software overflow flag. Set to one
    *     when uart_pc_rxBufferWrite index overtakes 
    *     uart_pc_rxBufferRead index.
    *  uart_pc_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when uart_pc_rxBufferWrite is equal to 
    *    uart_pc_rxBufferRead
    *
    *******************************************************************************/
    CY_ISR(uart_pc_RXISR)
    {
        uint8 readData;

        /* User code required at start of ISR */
        /* `#START uart_pc_RXISR_START` */

        /* `#END` */

        readData = uart_pc_RXSTATUS_REG;

        if(readData & (uart_pc_RX_STS_BREAK | uart_pc_RX_STS_PAR_ERROR | \
                       uart_pc_RX_STS_STOP_ERROR | uart_pc_RX_STS_OVERRUN))
        {
            /* ERROR handling. */
            /* `#START uart_pc_RXISR_ERROR` */

            /* `#END` */
        }

        while(readData & uart_pc_RX_STS_FIFO_NOTEMPTY)
        {
            /* Check pointer. */
            if(uart_pc_rxBufferWrite >= uart_pc_RXBUFFERSIZE)
            {
                uart_pc_rxBufferWrite = 0u;
                if(uart_pc_rxBufferWrite == uart_pc_rxBufferRead)
                {   /* Set Software Buffer status Overflow */
                    uart_pc_rxBufferOverflow = 1u;
                }
            }

            uart_pc_rxBuffer[uart_pc_rxBufferWrite] = uart_pc_RXDATA_REG;

            if(uart_pc_rxBufferLoopDetect)
            {   /* Set Software Buffer status Overflow */
                uart_pc_rxBufferOverflow = 1u;
            }
            /* Set next pointer. */
            uart_pc_rxBufferWrite++;

            if(uart_pc_rxBufferWrite == uart_pc_rxBufferRead)
            {
                uart_pc_rxBufferLoopDetect = 1u;
            }

            /* Check again if there is data. */
            readData = uart_pc_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_pc_RXISR_END` */

        /* `#END` */

        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(uart_pc_PSOC3_ES2 && (uart_pc_RXInternalInterrupt__ES2_PATCH))
            uart_pc_ISR_PATCH();
        #endif /* End uart_pc_PSOC3_ES2*/
    }

#endif /* End uart_pc_RX_ENABLED && (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH) */


#if(uart_pc_TX_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))

    extern volatile uint8 uart_pc_txBuffer[];
    extern volatile uint8 uart_pc_txBufferRead;
    extern uint8 uart_pc_txBufferWrite;


    /*******************************************************************************
    * Function Name: uart_pc_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for transmit data from.
    *  uart_pc_txBufferRead - cyclic index for read and transmit data 
    *     from txBuffer, increments after each transmited byte.
    *  uart_pc_rxBufferWrite - cyclic index for write to txBuffer, 
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_pc_TXISR)
    {

        /* User code required at start of ISR */
        /* `#START uart_pc_TXISR_START` */

        /* `#END` */

        while((uart_pc_txBufferRead != uart_pc_txBufferWrite) && \
             !(uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL))
        {
            /* Check pointer. */
            if(uart_pc_txBufferRead >= uart_pc_TXBUFFERSIZE)
            {
                uart_pc_txBufferRead = 0u;
            }

            uart_pc_TXDATA_REG = uart_pc_txBuffer[uart_pc_txBufferRead];

            /* Set next pointer. */
            uart_pc_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_pc_TXISR_END` */

        /* `#END` */
        
        /* PSoC3 ES1, ES2 RTC ISR PATCH  */
        #if(uart_pc_PSOC3_ES2 && (uart_pc_TXInternalInterrupt__ES2_PATCH))
            uart_pc_ISR_PATCH();
        #endif /* End uart_pc_PSOC3_ES2*/
    }

#endif /* End uart_pc_TX_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH) */


/* [] END OF FILE */

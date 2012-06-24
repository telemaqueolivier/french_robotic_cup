/*******************************************************************************
* File Name: uart_pc.c
* Version 2.0
*
* Description:
*  This file provides all API functionality of the UART component
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
#include "CyLib.h"


/***************************************
* Global data allocation
***************************************/

#if( uart_pc_TX_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))
    volatile uint8 uart_pc_txBuffer[uart_pc_TXBUFFERSIZE];
    volatile uint8 uart_pc_txBufferRead = 0u;
    uint8 uart_pc_txBufferWrite = 0u;
#endif /* End uart_pc_TX_ENABLED */
#if( ( uart_pc_RX_ENABLED || uart_pc_HD_ENABLED ) && \
     (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH) )
    volatile uint8 uart_pc_rxBuffer[uart_pc_RXBUFFERSIZE];
    volatile uint8 uart_pc_rxBufferRead = 0u;
    volatile uint8 uart_pc_rxBufferWrite = 0u;
    volatile uint8 uart_pc_rxBufferLoopDetect = 0u;
    volatile uint8 uart_pc_rxBufferOverflow = 0u;
#endif /* End uart_pc_RX_ENABLED */


/***************************************
* Local data allocation
***************************************/

uint8 uart_pc_initVar = 0u;


/*******************************************************************************
* Function Name: uart_pc_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the UART component.
*  Enable the clock input to enable operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The uart_pc_intiVar variable is used to indicate initial 
*  configuration of this component. The variable is initialized to zero (0u) 
*  and set to one (1u) the first time UART_Start() is called. This allows for 
*  component initialization without re-initialization in all subsequent calls 
*  to the uart_pc_Start() routine. 
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Start(void)
{
    /* If not Initialized then initialize all required hardware and software */
    if(uart_pc_initVar == 0u)
    {
        uart_pc_Init();
        uart_pc_initVar = 1u;
    }
    uart_pc_Enable();
}


/*******************************************************************************
* Function Name: uart_pc_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  uart_pc_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void uart_pc_Init(void) 
{
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)

        #if(uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            /* Set the RX Interrupt. */
            CyIntSetVector(uart_pc_RX_VECT_NUM,   uart_pc_RXISR);
            CyIntSetPriority(uart_pc_RX_VECT_NUM, uart_pc_RX_PRIOR_NUM);
        #endif /* End uart_pc_RX_INTERRUPT_ENABLED */

        #if (uart_pc_RXHW_ADDRESS_ENABLED)
            uart_pc_SetRxAddressMode(uart_pc_RXAddressMode);
            uart_pc_SetRxAddress1(uart_pc_RXHWADDRESS1);
            uart_pc_SetRxAddress2(uart_pc_RXHWADDRESS2);
        #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */

        /* Configure the Initial RX interrupt mask */
        uart_pc_RXSTATUS_MASK_REG  = uart_pc_INIT_RX_INTERRUPTS_MASK;
    #endif /* End uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/

    #if(uart_pc_TX_ENABLED)
        #if(uart_pc_TX_INTERRUPT_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            /* Set the TX Interrupt. */
            CyIntSetVector(uart_pc_TX_VECT_NUM,   uart_pc_TXISR);
            CyIntSetPriority(uart_pc_TX_VECT_NUM, uart_pc_TX_PRIOR_NUM);
        #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if(uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCLKGEN_CTR_REG = uart_pc_BIT_CENTER;
            uart_pc_TXBITCLKTX_COMPLETE_REG = (uart_pc_NUMBER_OF_DATA_BITS + \
                                                    uart_pc_NUMBER_OF_START_BIT) * \
                                                    uart_pc_OVER_SAMPLE_COUNT;
        #else
            uart_pc_TXBITCTR_COUNTER_REG = (uart_pc_NUMBER_OF_DATA_BITS + \
                                                    uart_pc_NUMBER_OF_START_BIT) * \
                                                    uart_pc_OVER_SAMPLE_8;
        #endif /* End uart_pc_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if(uart_pc_TX_INTERRUPT_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            uart_pc_TXSTATUS_MASK_REG = uart_pc_TX_STS_FIFO_EMPTY;
        #else
            uart_pc_TXSTATUS_MASK_REG = uart_pc_INIT_TX_INTERRUPTS_MASK;
        #endif /*End uart_pc_TX_INTERRUPT_ENABLED*/
        
    #endif /* End uart_pc_TX_ENABLED */

    #if(uart_pc_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        uart_pc_WriteControlRegister( \
            (uart_pc_ReadControlRegister() & ~uart_pc_CTRL_PARITY_TYPE_MASK) | \
            (uart_pc_PARITY_TYPE << uart_pc_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End uart_pc_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: uart_pc_Enable
********************************************************************************
*
* Summary:
*  Enables the UART block operation
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void uart_pc_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();
    
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        /*RX Counter (Count7) Enable */
        uart_pc_RXBITCTR_CONTROL_REG |= uart_pc_CNTR_ENABLE;
        /* Enable the RX Interrupt. */
        uart_pc_RXSTATUS_ACTL_REG  |= uart_pc_INT_ENABLE;
        #if(uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            CyIntEnable(uart_pc_RX_VECT_NUM);
        #endif /* End uart_pc_RX_INTERRUPT_ENABLED */
    #endif /* End uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/

    #if(uart_pc_TX_ENABLED)
        /*TX Counter (DP/Count7) Enable */
        #if(!uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCTR_CONTROL_REG |= uart_pc_CNTR_ENABLE;
        #endif /* End uart_pc_TXCLKGEN_DP */
        /* Enable the TX Interrupt. */
        uart_pc_TXSTATUS_ACTL_REG |= uart_pc_INT_ENABLE;
        #if(uart_pc_TX_INTERRUPT_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            CyIntEnable(uart_pc_TX_VECT_NUM);
        #endif /* End uart_pc_TX_INTERRUPT_ENABLED*/
     #endif /* End uart_pc_TX_ENABLED */

    #if(uart_pc_INTERNAL_CLOCK_USED)
        /* Set the bit to enable the clock. */
        uart_pc_INTCLOCK_CLKEN_REG |= uart_pc_INTCLOCK_CLKEN_MASK;
    #endif /* End uart_pc_INTERNAL_CLOCK_USED */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: uart_pc_Stop
********************************************************************************
*
* Summary:
*  Disable the UART component
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void uart_pc_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /*Write Bit Counter Disable */
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_RXBITCTR_CONTROL_REG &= ~uart_pc_CNTR_ENABLE;
    #endif /* End uart_pc_RX_ENABLED */

    #if(uart_pc_TX_ENABLED)
        #if(!uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCTR_CONTROL_REG &= ~uart_pc_CNTR_ENABLE;
        #endif /* End uart_pc_TXCLKGEN_DP */
    #endif /* uart_pc_TX_ENABLED */

    #if(uart_pc_INTERNAL_CLOCK_USED)
        /* Clear the bit to enable the clock. */
        uart_pc_INTCLOCK_CLKEN_REG &= ~uart_pc_INTCLOCK_CLKEN_MASK;
    #endif /* End uart_pc_INTERNAL_CLOCK_USED */
    
    /*Disable internal interrupt component*/
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_RXSTATUS_ACTL_REG  &= ~uart_pc_INT_ENABLE;
        #if(uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            uart_pc_DisableRxInt();
        #endif /* End uart_pc_RX_INTERRUPT_ENABLED */
    #endif /* End uart_pc_RX_ENABLED */
    
    #if(uart_pc_TX_ENABLED)
        uart_pc_TXSTATUS_ACTL_REG &= ~uart_pc_INT_ENABLE;
        #if(uart_pc_TX_INTERRUPT_ENABLED && (uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH))
            uart_pc_DisableTxInt();
        #endif /* End uart_pc_TX_INTERRUPT_ENABLED */
    #endif /* End uart_pc_TX_ENABLED */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: uart_pc_ReadControlRegister
********************************************************************************
*
* Summary:
*  Read the current state of the control register
*
* Parameters:
*  None.
*
* Return:
*  Current state of the control register.
*
*******************************************************************************/
uint8 uart_pc_ReadControlRegister(void) 
{
    #if( uart_pc_CONTROL_REG_REMOVED )
        return(0u);
    #else
        return(uart_pc_CONTROL_REG);
    #endif /* End uart_pc_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: uart_pc_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  uart_pc_WriteControlRegister(uint8 control) 
{
    #if( uart_pc_CONTROL_REG_REMOVED )
        control = control;      /* Reassigning to release compiler warning */ 
    #else
       uart_pc_CONTROL_REG = control;
    #endif /* End uart_pc_CONTROL_REG_REMOVED */
}


#if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)

    #if(uart_pc_RX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: uart_pc_EnableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void uart_pc_EnableRxInt(void) 
        {
            CyIntEnable(uart_pc_RX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: uart_pc_DisableRxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable RX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void uart_pc_DisableRxInt(void) 
        {
            CyIntDisable(uart_pc_RX_VECT_NUM);
        }

    #endif /* uart_pc_RX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: uart_pc_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  IntSrc:  An or'd combination of the desired status bit masks (defined in
    *           the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void uart_pc_SetRxInterruptMode(uint8 intSrc) 
    {
        uart_pc_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns data in RX Data register without checking status register to 
    *  determine if data is valid
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  uart_pc_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 uart_pc_ReadRxData(void)
    {
        uint8 rxData;

        #if(uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_DisableRxInt();
            #endif /* End uart_pc_RX_INTERRUPT_ENABLED */

            if( (uart_pc_rxBufferRead != uart_pc_rxBufferWrite) || \
                (uart_pc_rxBufferLoopDetect > 0u) )
            {
                if(uart_pc_rxBufferLoopDetect > 0u ) 
                {
                    uart_pc_rxBufferLoopDetect = 0u;
                }

                if(uart_pc_rxBufferRead >= uart_pc_RXBUFFERSIZE)
                {
                    uart_pc_rxBufferRead = 0u;
                }

                rxData = uart_pc_rxBuffer[uart_pc_rxBufferRead];

                uart_pc_rxBufferRead++;
            }
            else
            {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
                rxData = uart_pc_RXDATA_REG;
            }

            /* Enable Rx interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_EnableRxInt();
            #endif /* End uart_pc_RX_INTERRUPT_ENABLED */

        #else /* uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

            /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit*/
            rxData = uart_pc_RXDATA_REG;

        #endif /* uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the current state of the status register
    *  And detect software buffer overflow.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Global Variables:
    *  uart_pc_rxBufferOverflow - used to indicate overload condition. 
    *   It set to one in RX interrupt when there isn?t free space in 
    *   uart_pc_rxBufferRead to write new data. This condition returned 
    *   and cleared to zero by this API as an 
    *   uart_pc_RX_STS_SOFT_BUFF_OVER bit along with RX Status register 
    *   bits.
    *
    *******************************************************************************/
    uint8 uart_pc_ReadRxStatus(void) 
    {
        uint8 status;

        status = uart_pc_RXSTATUS_REG;
        status &= uart_pc_RX_HW_MASK;

        #if(uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH)
            if( uart_pc_rxBufferOverflow )
            {
                status |= uart_pc_RX_STS_SOFT_BUFF_OVER;
                uart_pc_rxBufferOverflow = 0u;
            }
        #endif /* uart_pc_RXBUFFERSIZE */

        return(status);
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, if data is not available or an error 
    *  condition exists, zero is returned; otherwise, character is read and 
    *  returned.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer, 
    *     checked to identify new data. 
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer, 
    *     incremented after each byte has been read from buffer.
    *  uart_pc_rxBufferLoopDetect - creared if loop condition was detected
    *     in RX ISR. 
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 uart_pc_GetChar(void)
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

        #if(uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_DisableRxInt();
            #endif /* uart_pc_RX_INTERRUPT_ENABLED */

            if( (uart_pc_rxBufferRead != uart_pc_rxBufferWrite) || \
                (uart_pc_rxBufferLoopDetect > 0u) )
            {
                if(uart_pc_rxBufferLoopDetect > 0u ) 
                {
                    uart_pc_rxBufferLoopDetect = 0u;
                }

                if(uart_pc_rxBufferRead >= uart_pc_RXBUFFERSIZE)
                {
                    uart_pc_rxBufferRead = 0u;
                }

                rxData = uart_pc_rxBuffer[uart_pc_rxBufferRead];

                uart_pc_rxBufferRead++;
            }
            else
            {   rxStatus =uart_pc_RXSTATUS_REG;
                if(rxStatus & uart_pc_RX_STS_FIFO_NOTEMPTY)
                {   /* Read received data from FIFO*/
                    rxData = uart_pc_RXDATA_REG;
                    /*Check status on error*/
                    if(rxStatus & (uart_pc_RX_STS_BREAK | uart_pc_RX_STS_PAR_ERROR | \
                                   uart_pc_RX_STS_STOP_ERROR | uart_pc_RX_STS_OVERRUN))
                    {
                        rxData = 0u;
                    }    
                }
            }

            /* Enable Rx interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_EnableRxInt();
            #endif /* uart_pc_RX_INTERRUPT_ENABLED */

        #else /* uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

            rxStatus =uart_pc_RXSTATUS_REG;
            if(rxStatus & uart_pc_RX_STS_FIFO_NOTEMPTY)
            {   /* Read received data from FIFO*/
                rxData = uart_pc_RXDATA_REG;
                /*Check status on error*/
                if(rxStatus & (uart_pc_RX_STS_BREAK | uart_pc_RX_STS_PAR_ERROR | \
                               uart_pc_RX_STS_STOP_ERROR | uart_pc_RX_STS_OVERRUN))
                {
                    rxData = 0u;
                }
            }
        #endif /* uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Grab the next available byte of data from the recieve FIFO
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains Status Register and LSB contains UART RX data
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 uart_pc_GetByte(void)
    {
        return ( ((uint16)uart_pc_ReadRxStatus() << 8u) | uart_pc_ReadRxData() );
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of bytes left in the RX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Integer count of the number of bytes left 
    *  in the RX buffer
    *
    * Global Variables:
    *  uart_pc_rxBufferWrite - used to calculate left bytes. 
    *  uart_pc_rxBufferRead - used to calculate left bytes.
    *  uart_pc_rxBufferLoopDetect - checked to decide left bytes amount. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 uart_pc_GetRxBufferSize(void)
    {
        uint8 size;

        #if(uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH)

            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_DisableRxInt();
            #endif /* uart_pc_RX_INTERRUPT_ENABLED */

            if(uart_pc_rxBufferRead == uart_pc_rxBufferWrite)
            {
                if(uart_pc_rxBufferLoopDetect > 0u)
                {
                    size = uart_pc_RXBUFFERSIZE;
                }
                else
                {
                    size = 0u;
                }
            }
            else if(uart_pc_rxBufferRead < uart_pc_rxBufferWrite)
            {
                size = (uart_pc_rxBufferWrite - uart_pc_rxBufferRead);
            }
            else
            {
                size = (uart_pc_RXBUFFERSIZE - uart_pc_rxBufferRead) + uart_pc_rxBufferWrite;
            }

            /* Enable Rx interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_EnableRxInt();
            #endif /* End uart_pc_RX_INTERRUPT_ENABLED */

        #else /* uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

            /* We can only know if there is data in the fifo. */
            size = (uart_pc_RXSTATUS_REG & uart_pc_RX_STS_FIFO_NOTEMPTY) ? 1u : 0u;

        #endif /* End uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clear the RX RAM buffer by setting the read and write pointers both to zero.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_rxBufferWrite - cleared to zero. 
    *  uart_pc_rxBufferRead - cleared to zero.
    *  uart_pc_rxBufferLoopDetect - cleared to zero. 
    *  uart_pc_rxBufferOverflow - cleared to zero. 
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may 
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *******************************************************************************/
    void uart_pc_ClearRxBuffer(void)
    {
        #if(uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH)
            /* Disable Rx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_DisableRxInt();
            #endif /* End uart_pc_RX_INTERRUPT_ENABLED */

            uart_pc_rxBufferRead = 0u;
            uart_pc_rxBufferWrite = 0u;
            uart_pc_rxBufferLoopDetect = 0u;
            uart_pc_rxBufferOverflow = 0u;

            /* Enable Rx interrupt. */
            #if(uart_pc_RX_INTERRUPT_ENABLED)
                uart_pc_EnableRxInt();
            #endif /* End uart_pc_RX_INTERRUPT_ENABLED */
        #endif /* End uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the receive addressing mode
    *
    * Parameters:
    *  addressMode: Use one of the Enumerated Types listed below
    *              #define uart_pc__B_UART__AM_SW_BYTE_BYTE 1
#define uart_pc__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define uart_pc__B_UART__AM_HW_BYTE_BY_BYTE 3
#define uart_pc__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define uart_pc__B_UART__AM_NONE 0

    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetRxAddressMode(uint8 addressMode)  
    {
        #if(uart_pc_RXHW_ADDRESS_ENABLED)
            #if(uart_pc_CONTROL_REG_REMOVED)
                addressMode = addressMode;
            #else /* uart_pc_CONTROL_REG_REMOVED */
                uint8 tmpCtrl = 0u;
                tmpCtrl = uart_pc_CONTROL_REG & ~uart_pc_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= ((addressMode << uart_pc_CTRL_RXADDR_MODE0_SHIFT) & \
                           uart_pc_CTRL_RXADDR_MODE_MASK);
                uart_pc_CONTROL_REG = tmpCtrl;
            #endif /* End uart_pc_CONTROL_REG_REMOVED */
        #else /* uart_pc_RXHW_ADDRESS_ENABLED */
            addressMode = addressMode;
        #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Set the first hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetRxAddress1(uint8 address) 

    {
        uart_pc_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Set the second hardware address compare value
    *
    * Parameters:
    *  address
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetRxAddress2(uint8 address) 
    {
        uart_pc_RXADDRESS2_REG = address;
    }

#endif  /* uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/


#if( (uart_pc_TX_ENABLED) || (uart_pc_HD_ENABLED) )

    #if(uart_pc_TX_INTERRUPT_ENABLED)

        /*******************************************************************************
        * Function Name: uart_pc_EnableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Enable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Enable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void uart_pc_EnableTxInt(void) 
        {
            CyIntEnable(uart_pc_TX_VECT_NUM);
        }


        /*******************************************************************************
        * Function Name: uart_pc_DisableTxInt
        ********************************************************************************
        *
        * Summary:
        *  Disable TX interrupt generation
        *
        * Parameters:
        *  None.
        *
        * Return:
        *  None.
        *
        * Theory:
        *  Disable the interrupt output -or- the interrupt component itself
        *
        *******************************************************************************/
        void uart_pc_DisableTxInt(void) 
        {
            CyIntDisable(uart_pc_TX_VECT_NUM);
        }

    #endif /* uart_pc_TX_INTERRUPT_ENABLED */


    /*******************************************************************************
    * Function Name: uart_pc_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *  intSrc: An or'd combination of the desired status bit masks (defined in
    *          the header file)
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void uart_pc_SetTxInterruptMode(uint8 intSrc) 
    {
        uart_pc_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: uart_pc_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Write a byte of data to the Transmit FIFO or TX buffer to be sent when the 
    *  bus is available. WriteTxData sends a byte without checking for buffer room 
    *  or status. It is up to the user to separately check status.    
    *
    * Parameters:
    *  TXDataByte: byte of data to place in the transmit FIFO
    *
    * Return:
    * void
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for save data for transmission
    *  uart_pc_txBufferWrite - cyclic index for write to txBuffer, 
    *    incremented after each byte saved to buffer.
    *  uart_pc_txBufferRead - cyclic index for read from txBuffer, 
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  uart_pc_initVar - checked to identify that the component has been  
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void uart_pc_WriteTxData(uint8 txDataByte)
    {
        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            #if(uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH)

                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(uart_pc_TX_INTERRUPT_ENABLED)
                    uart_pc_DisableTxInt();
                #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

                if( (uart_pc_txBufferRead == uart_pc_txBufferWrite) && \
                   !(uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    uart_pc_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(uart_pc_txBufferWrite >= uart_pc_TXBUFFERSIZE)
                    {
                        uart_pc_txBufferWrite = 0;
                    }

                    uart_pc_txBuffer[uart_pc_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    uart_pc_txBufferWrite++;

                }

                /* Enable Tx interrupt. */
                #if(uart_pc_TX_INTERRUPT_ENABLED)
                    uart_pc_EnableTxInt();
                #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

            #else /* uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */

                /* Add directly to the FIFO. */
                uart_pc_TXDATA_REG = txDataByte;

            #endif /* End uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Read the status register for the component
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the status register which is clear on read. It is up to 
    *  the user to handle all bits in this return value accordingly, even if the bit 
    *  was not enabled as an interrupt source the event happened and must be handled
    *  accordingly.    
    *
    *******************************************************************************/
    uint8 uart_pc_ReadTxStatus(void) 
    {
        return(uart_pc_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Wait to send byte until TX register or buffer has room.
    *
    * Parameters:
    *  txDataByte: The 8-bit data value to send across the UART.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for save data for transmission
    *  uart_pc_txBufferWrite - cyclic index for write to txBuffer, 
    *     checked to identify free space in txBuffer and incremented after each byte 
    *     saved to buffer.
    *  uart_pc_txBufferRead - cyclic index for read from txBuffer, 
    *     checked to identify free space in txBuffer.
    *  uart_pc_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void uart_pc_PutChar(uint8 txDataByte)
    {
            #if(uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH)

                /* Block if buffer is full, so we dont overwrite. */
                while( uart_pc_txBufferWrite == (uart_pc_txBufferRead - 1u) || \
                    (uint8)(uart_pc_txBufferWrite - uart_pc_txBufferRead) ==
                    (uint8)(uart_pc_TXBUFFERSIZE - 1u) )
                {
                    /* Software buffer is full. */
                }
                /* Disable Tx interrupt. */
                /* Protect variables that could change on interrupt. */
                #if(uart_pc_TX_INTERRUPT_ENABLED)
                    uart_pc_DisableTxInt();
                #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

                if( (uart_pc_txBufferRead == uart_pc_txBufferWrite) && \
                   !(uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) )
                {
                    /* Add directly to the FIFO. */
                    uart_pc_TXDATA_REG = txDataByte;
                }
                else
                {
                    if(uart_pc_txBufferWrite >= uart_pc_TXBUFFERSIZE)
                    {
                        uart_pc_txBufferWrite = 0;
                    }

                    uart_pc_txBuffer[uart_pc_txBufferWrite] = txDataByte;

                    /* Add to the software buffer. */
                    uart_pc_txBufferWrite++;

                }

                /* Enable Rx interrupt. */
                #if(uart_pc_TX_INTERRUPT_ENABLED)
                    uart_pc_EnableTxInt();
                #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

            #else /* uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */

                /* Block if there isnt room. */
                while(uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL);

                /* Add directly to the FIFO. */
                uart_pc_TXDATA_REG = txDataByte;

            #endif /* End uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutString
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: uint8 pointer to character string of Data to Send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole 
    *  string, it will block until the entire string has been written to the 
    *  transmit buffer.
    *
    *******************************************************************************/
    void uart_pc_PutString(uint8* string)
    {
        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent*/
            while(*string != 0u)
            {
                uart_pc_PutChar(*string++);
            }
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
    *
    * Parameters:
    *  string: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of Bytes to be transmitted.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void uart_pc_PutArray(uint8* string, uint8 byteCount)
    {
        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            while(byteCount > 0u)
            {
                uart_pc_PutChar(*string++);
                byteCount--;
            }
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Write a character and then carriage return and line feed.
    *
    * Parameters:
    *  txDataByte: uint8 Character to send.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been  
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void uart_pc_PutCRLF(uint8 txDataByte)
    {
        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            uart_pc_PutChar(txDataByte);
            uart_pc_PutChar(0x0Du);
            uart_pc_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Determine the amount of space left in the TX buffer and return the count in
    *  bytes
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Integer count of the number of bytes left in the TX buffer
    *
    * Global Variables:
    *  uart_pc_txBufferWrite - used to calculate left space. 
    *  uart_pc_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 uart_pc_GetTxBufferSize(void)
    {
        uint8 size;

        #if(uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_TX_INTERRUPT_ENABLED)
                uart_pc_DisableTxInt();
            #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

            if(uart_pc_txBufferRead == uart_pc_txBufferWrite)
            {
                size = 0u;
            }
            else if(uart_pc_txBufferRead < uart_pc_txBufferWrite)
            {
                size = (uart_pc_txBufferWrite - uart_pc_txBufferRead);
            }
            else
            {
                size = (uart_pc_TXBUFFERSIZE - uart_pc_txBufferRead) + uart_pc_txBufferWrite;
            }

            /* Enable Tx interrupt. */
            #if(uart_pc_TX_INTERRUPT_ENABLED)
                uart_pc_EnableTxInt();
            #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

        #else /* uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */

            size = uart_pc_TXSTATUS_REG;

            /* Is the fifo is full. */
            if(size & uart_pc_TX_STS_FIFO_FULL)
            {
                size = uart_pc_FIFO_LENGTH;
            }
            else if(size & uart_pc_TX_STS_FIFO_EMPTY)
            {
                size = 0u;
            }
            else
            {
                /* We only know there is data in the fifo. */
                size = 1u;
            }

        #endif /* End uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */

        return(size);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clear the TX RAM buffer by setting the read and write pointers both to zero.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBufferWrite - cleared to zero. 
    *  uart_pc_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to 
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM buffer will be lost when overwritten.
    *
    *******************************************************************************/
    void uart_pc_ClearTxBuffer(void)
    {
        #if(uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH)

            /* Disable Tx interrupt. */
            /* Protect variables that could change on interrupt. */
            #if(uart_pc_TX_INTERRUPT_ENABLED)
                uart_pc_DisableTxInt();
            #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

            uart_pc_txBufferRead = 0u;
            uart_pc_txBufferWrite = 0u;

            /* Enable Tx interrupt. */
            #if(uart_pc_TX_INTERRUPT_ENABLED)
                uart_pc_EnableTxInt();
            #endif /* End uart_pc_TX_INTERRUPT_ENABLED */

        #endif /* End uart_pc_TXBUFFERSIZE > uart_pc_FIFO_LENGTH */
    }


    /*******************************************************************************
    * Function Name: uart_pc_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Write a Break command to the UART
    *
    * Parameters:
    *  uint8 retMode:  Wait mode,
    *   0 - Initialize registers for Break, sends the Break signal and return 
    *       imediately.
    *   1 - Wait until Break sending is complete, reinitialize registers to normal
    *       transmission mode then return.
    *   2 - Reinitialize registers to normal transmission mode then return.
    *   3 - both steps: 0 and 1
    *       init registers for Break, send Break signal
    *       wait until Break sending is complete, reinit registers to normal
    *       transmission mode then return.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been  
    *     initialized.
    *  tx_period - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  Trere are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Funcition will block CPU untill transmition 
    *     complete.
    *  2) User may want to use bloking time if UART configured to the low speed 
    *     operation
    *     Emample for this case:
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to init and use the interrupt for complete 
    *     break operation.
    *     Example for this case:
    *     Init TX interrupt whith "TX - On TX Complete" parameter
    *     SendBreak(0);     - init Break signal transmition
    *         Add your code here to use CPU time
    *     When interrupt appear with UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *   Uses static variable to keep registers configuration.
    *
    *******************************************************************************/
    void uart_pc_SendBreak(uint8 retMode)
    {

        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            /*Set the Counter to 13-bits and transmit a 00 byte*/
            /*When that is done then reset the counter value back*/
            uint8 tmpStat;

            #if(uart_pc_HD_ENABLED) /* Half Duplex mode*/

                if( (retMode == uart_pc_SEND_BREAK) ||
                    (retMode == uart_pc_SEND_WAIT_REINIT ) )
                {
                    /* CTRL_HD_SEND_BREAK - sends break bits in HD mode*/
                    uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() | \
                                                          uart_pc_CTRL_HD_SEND_BREAK);
                    /* Send zeros*/
                    uart_pc_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = uart_pc_TXSTATUS_REG;
                    }while(tmpStat & uart_pc_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == uart_pc_WAIT_FOR_COMLETE_REINIT) || \
                    (retMode == uart_pc_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = uart_pc_TXSTATUS_REG;
                    }while(~tmpStat & uart_pc_TX_STS_COMPLETE);
                }

                if( (retMode == uart_pc_WAIT_FOR_COMLETE_REINIT) || \
                    (retMode == uart_pc_REINIT) || \
                    (retMode == uart_pc_SEND_WAIT_REINIT) )
                {
                    uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() & \
                                                         ~uart_pc_CTRL_HD_SEND_BREAK);
                }

            #else /* uart_pc_HD_ENABLED Full Duplex mode */

                static uint8 tx_period; 
                
                if( (retMode == uart_pc_SEND_BREAK) || \
                    (retMode == uart_pc_SEND_WAIT_REINIT) )
                {
                    /* CTRL_HD_SEND_BREAK - skip to send parity bit @ Break signal in Full Duplex mode*/
                    if( (uart_pc_PARITY_TYPE != uart_pc__B_UART__NONE_REVB) || \
                         uart_pc_PARITY_TYPE_SW )
                    {
                        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() | \
                                                              uart_pc_CTRL_HD_SEND_BREAK);
                    }                                                          

                    #if(uart_pc_TXCLKGEN_DP)
                        tx_period = uart_pc_TXBITCLKTX_COMPLETE_REG;
                        uart_pc_TXBITCLKTX_COMPLETE_REG = uart_pc_TXBITCTR_BREAKBITS;
                    #else
                        tx_period = uart_pc_TXBITCTR_PERIOD_REG;
                        uart_pc_TXBITCTR_PERIOD_REG = uart_pc_TXBITCTR_BREAKBITS8X;
                    #endif /* End uart_pc_TXCLKGEN_DP */

                    /* Send zeros*/
                    uart_pc_TXDATA_REG = 0u;

                    do /*wait until transmit starts*/
                    {
                        tmpStat = uart_pc_TXSTATUS_REG;
                    }while(tmpStat & uart_pc_TX_STS_FIFO_EMPTY);
                }

                if( (retMode == uart_pc_WAIT_FOR_COMLETE_REINIT) || \
                    (retMode == uart_pc_SEND_WAIT_REINIT) )
                {
                    do /*wait until transmit complete*/
                    {
                        tmpStat = uart_pc_TXSTATUS_REG;
                    }while(~tmpStat & uart_pc_TX_STS_COMPLETE);
                }

                if( (retMode == uart_pc_WAIT_FOR_COMLETE_REINIT) || \
                    (retMode == uart_pc_REINIT) || \
                    (retMode == uart_pc_SEND_WAIT_REINIT) )
                {

                    #if(uart_pc_TXCLKGEN_DP)
                        uart_pc_TXBITCLKTX_COMPLETE_REG = tx_period;
                    #else
                        uart_pc_TXBITCTR_PERIOD_REG = tx_period;
                    #endif /* End uart_pc_TXCLKGEN_DP */

                    if( (uart_pc_PARITY_TYPE != uart_pc__B_UART__NONE_REVB) || 
                         uart_pc_PARITY_TYPE_SW )
                    {
                        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() & \
                                                             ~uart_pc_CTRL_HD_SEND_BREAK);
                    }                                     
                }
            #endif    /* End uart_pc_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Set the transmit addressing mode
    *
    * Parameters:
    *  addressMode: 0 -> Space
    *               1 -> Mark
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable*/
        if(addressMode != 0)
        {
            uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() | uart_pc_CTRL_MARK);
        }
        else
        {
            uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() & ~uart_pc_CTRL_MARK);
        }
    }

#endif  /* Enduart_pc_TX_ENABLED */

#if(uart_pc_HD_ENABLED)


    /*******************************************************************************
    * Function Name: uart_pc_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Rx configuration if required and loads the
    *  Tx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Tx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART. 
    *
    *******************************************************************************/
    void uart_pc_LoadTxConfig(void) 
    {
        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() | uart_pc_CTRL_HD_SEND);
        uart_pc_RXBITCTR_PERIOD_REG = uart_pc_HD_TXBITCTR_INIT;
    }


    /*******************************************************************************
    * Function Name: uart_pc_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Unloads the Tx configuration if required and loads the
    *  Rx configuration. It is the users responsibility to ensure that any
    *  transaction is complete and it is safe to unload the Rx
    *  configuration.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Valid only for half duplex UART
    *
    *******************************************************************************/
    void uart_pc_LoadRxConfig(void) 
    {
        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() & ~uart_pc_CTRL_HD_SEND);
        uart_pc_RXBITCTR_PERIOD_REG = uart_pc_HD_RXBITCTR_INIT;
    }

#endif  /* uart_pc_HD_ENABLED */


/* [] END OF FILE */

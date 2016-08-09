/*******************************************************************************
* Title                 :   MCP2542 HAL
* Filename              :   mcp2542_hal.c
* Author                :   MSV
* Origin Date           :   02/12/2015
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  02/12/15    XXXXXXXXXXX         MSV      Module Created.
*
*******************************************************************************/

/**
 * @file mcp2542_hal.c
 *
 * @brief This module contains the HAL layer for Mikroelektronika's MCP2542
 *  click board.
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "mcp2542_hal.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )

static void         ( *write_uart_p )           ( unsigned int data_out );
#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )

static void         ( *write_uart_p )           ( unsigned char data_out );
#endif

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

#if defined( __MIKROC_PRO_FOR_ARM__ )      || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_PIC__ )   || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit MCP2542_STB;
#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/

extern void mcp2542_rx_isr( char ch );

/******************************************************************************
* Function Definitions
*******************************************************************************/

void mcp2542_hal_stb
(
        int state
)
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_PIC__ )   || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
    if( state )
        MCP2542_STB = 1;
    else
        MCP2542_STB = 0;
#endif
}

void mcp2542_hal_init
(
        void
)
{
#if defined( __MIKROC_PRO_FOR_ARM__ )

    write_uart_p = UART_Wr_Ptr;
    RXNEIE_USART3_CR1_bit = 1;
    NVIC_IntEnable( IVT_INT_USART3 );
    EnableInterrupts();
#elif defined( __MIKROC_PRO_FOR_AVR__ )

    write_uart_p = UART_Wr_Ptr;
    UCSRB |= ( 1 << RXCIE );
    SREG  |= ( 1 << SREG_I );
#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

    write_uart_p = UART_Wr_Ptr;
#elif defined( __MIKROC_PRO_FOR_PIC32__ )

    write_uart_p = UART_Wr_Ptr;
    AD1PCFG = 0xFFFF;
    U2IP0_bit = 0;
    U2IP1_bit = 1;
    U2IP2_bit = 1;
    U2RXIE_bit = 1;
    EnableInterrupts();
#elif defined( __MIKROC_PRO_FOR_8051__ )

    write_uart_p = UART_Wr_Ptr;
#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    write_uart_p = UART_Wr_Ptr;
    UART2_FCR |= ( 1 << FIFO_EN ) | ( 1 << RCVR_RST );
    UART2_INT_ENABLE |= ( 1 << RX_AVL_EN );
    IRQ_CTRL &= ~( 1 << GLOBAL_INTERRUPT_MASK );
#elif defined( __MIKROC_PRO_FOR_PIC__ )

    write_uart_p = UART_Wr_Ptr;
    RC1IE_bit = 1;
    RC1IF_bit = 0;
    PEIE_bit  = 1;
    GIE_bit   = 1;
#endif
}

void mcp2542_hal_write
(
        char ch
)
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    write_uart_p( ch );
#endif
}

#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined ( __STM32__ )

void UART_RX_ISR() iv IVT_INT_USART3 ics ICS_AUTO
{
    if( RXNE_USART3_SR_bit )
    {
        char tmp = USART3_DR;
        mcp2542_rx_isr( tmp );
    }
}
    #elif defined ( __TM__ )

    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )

void UART_RX_ISR() iv IVT_ADDR_USART__RXC ics ICS_AUTO
{
    char tmp = UART_Read();
    mcp2542_rx_isr( tmp );
}
#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

void UART2interrupt() iv IVT_UART_2 ilevel 6 ics ICS_AUTO
{
      if( IFS1 & ( 1 << U2RXIF ))
      {
           char tmp = UART2_Read();
           mcp2542_rx_isr( tmp );
           U2RXIF_bit = 0;
      }
}

#elif defined( __MIKROC_PRO_FOR_8051__ )

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

void UART_RX_ISR() iv IVT_UART2_IRQ ics ICS_AUTO
{
    if( UART2_LSR & ( 1 << DATA_RDY ) )
    {
        char tmp = UART2_RBR;
        mcp2542_rx_isr( tmp );
    }
}
#elif defined( __MIKROC_PRO_FOR_PIC__ )

void interrupt()
{
    if( RC1IF_bit == 1 )
    {
        char tmp = UART1_Read();
        mcp2542_rx_isr( tmp );
    }
}
#endif

/*************** END OF FUNCTIONS ***************************************************************************/
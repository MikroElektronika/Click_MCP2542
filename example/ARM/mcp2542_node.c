#include "mcp2542.h"

/* MODULE PINS
 ******************************************************************************/
sbit MCP2542_STB at GPIOA_ODR.B4;

/* VARS
 ******************************************************************************/
char read_buffer[ BFR_SIZE ] = { 0 };                                           /* RX buffer */
char write_buffer[ BFR_SIZE ] = { 'H', 'E', 'L', 'L', 'O', '!' };               /* TX message */

/* PROTOTYPES
 ******************************************************************************/
void system_init( void );

/* FUNCTIONS
 ******************************************************************************/
void system_init()
{
    GPIO_Digital_Input( &GPIOB_BASE, _GPIO_PINMASK_1 );                         /* Button pin */
    GPIO_Digital_Output( &GPIOA_BASE, _GPIO_PINMASK_4 );                        /* STB pin */
    Delay_ms( 200 );
                                                                                /* DBG UART */
    UART1_Init_Advanced( 115200, _UART_8_BIT_DATA,
                                 _UART_NOPARITY,
                                 _UART_ONE_STOPBIT,
                                 &_GPIO_MODULE_USART1_PA9_10 );
    Delay_ms( 200 );
                                                                                /* MODULE UART */
    UART3_Init_Advanced( 115200, _UART_8_BIT_DATA,
                                 _UART_NOPARITY,
                                 _UART_ONE_STOPBIT,
                                 &_GPIO_MODULE_USART3_PD89 );
    Delay_ms( 200 );
    
    UART1_Write_Text( "System Initialized\r\n" );
}

/* MAIN
 ******************************************************************************/
void main()
{
    system_init();
    mcp2542_init();
    mcp2542_delimiter_set( "\r\n" );

    while( 1 )
    {
        if( Button( &GPIOB_IDR, 1, 100, 1 ) )
        {
            mcp2542_send( write_buffer );
            UART1_Write_Text( "\r\n< SENT >\r\n" );
        }
        
        if( mcp2542_rdy() )
        {
            mcp2542_read( read_buffer );
            UART1_Write_Text( "\r\n< RECEIVED >\r\n" );
            UART1_Write_Text( read_buffer );
        }
    }
}
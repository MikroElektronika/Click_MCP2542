#include "mcp2542.h"

/* MODULE PINS
 ******************************************************************************/
sbit MCP2542_STB at GPIO_PIN9_bit;

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
    GPIO_Digital_Input( &GPIO_PORT_24_31, _GPIO_PINMASK_4 );                    /* Button pin */
    GPIO_Digital_Output( &GPIO_PORT_08_15, _GPIO_PINMASK_1 );                   /* STB pin */
    Delay_ms( 200 );
                                                                                /* DBG UART */
    UART1_Init( 115200 );
    Delay_ms( 200 );
                                                                                /* MODULE UART */
    UART2_Init( 115200 );
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
        if( Button( &GPIO_PORT_24_31, 4, 100, 1 ) )
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
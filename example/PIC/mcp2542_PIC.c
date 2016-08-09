#include "mcp2542.h"

/* MODULE PINS
 ******************************************************************************/
sbit MCP2542_STB at LATA2_bit;

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
    TRISA2_bit = 0;
    TRISE0_bit = 1;
    Delay_ms( 200 );
                                                                                /* Module UART */
    UART1_Init( 57600 );
    Delay_ms( 200 );
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
        if( Button( &PORTE, 0, 100, 1 ) )
        {
            mcp2542_send( write_buffer );
        }

        if( mcp2542_rdy() )
        {
            mcp2542_read( read_buffer );
            // Display message
            // read buffer populated with message content
        }
    }
}
/****************************************************************************
* Title                 :   MCP2542 CLICK
* Filename              :   mcp2542.h
* Author                :   MSV
* Origin Date           :   30/01/2016
* Notes                 :   Hardware layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  30/01/16     .1                  MSV     Interface Created.
*
*****************************************************************************/
/**
 * @file mcp2542.c
 * @brief <h3> Hardware Layer </h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/

#include "mcp2542.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

static volatile bool             send_proc;
static volatile bool             msg_rdy_f;
static volatile uint16_t         rx_cnt;
static volatile char             rx_bfr[ BFR_SIZE ];

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void mcp2542_init
(
                void
)
{
        send_proc = false;
        msg_rdy_f = false;
        rx_cnt = 0;

        memset( rx_bfr, 0, BFR_SIZE );

        mcp2542_hal_init();
        mcp2542_hal_stb( 0 );
}

void mcp2542_mode_set
(
                mcp2542_mode mode
)
{
        mcp2542_hal_stb( mode );
}

void mcp2542_send
(
                char *msg
)
{
        uint8_t *ptr = msg;

        send_proc = true;

        while( *ptr != '\0' )
                mcp2542_hal_write( *ptr++ );

        mcp2542_hal_write( '\r' );
        mcp2542_hal_write( '\n' );
        
        Delay_ms( 5 );
        
        send_proc = false;
}

void mcp2542_read
(
                char *msg
)
{
        char *ptr    = msg;
        
        msg_rdy_f    = false;
        rx_cnt       = 0;

        strcpy( ptr, rx_bfr );
        memset( rx_bfr, 0, BFR_SIZE );
}

bool mcp2542_rdy
(
                void
)
{
        return msg_rdy_f;
}

void mcp2542_rx_isr
(
                char ch
)
{
    static bool sent_f;
    
        if( !send_proc )
        {
                if( !rx_cnt )
                    msg_rdy_f = false;

                if( ch == '\r' )
                {
                    sent_f = true;
                }
                else if( ch == '\n' && sent_f )
                {
                    sent_f = false;
                    msg_rdy_f = true;
                    rx_bfr[ rx_cnt ] = '\0';
                    //rx_cnt = 0;
                    
                } else {

                    rx_bfr[ rx_cnt ] = ch;
                    rx_cnt++;
                }
        }
}

/*************** END OF FUNCTIONS *********************************************/
![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

![MCP2542_click]()

---
[Product Page](http://www.mikroe.com/click/mcp2542)

[Manual Page](http://docs.mikroe.com/MCP_2542_click)

[Learn Page](http://learn.mikroe.com/mcp2542/)

---

### General Description

The MCP2542FD/4FD and MCP2542WFD/4WFD CAN
transceiver family is designed for high-speed CAN FD
applications up to 8 Mbps communication speed. The
maximum propagation delay was improved to support longer
bus length.
The device meets the automotive requirements for CAN FD bit
rates exceeding 2 Mbps, low quiescent current,
electromagnetic compatibility (EMC) and electrostatic
discharge (ESD).

---

### Features

- Supports CAN 2.0 and CAN with Flexible Data Rate (CAN FD) Physical Layer Transceiver Requirements
- Optimized for CAN FD at 2, 5 and 8 Mbps Operation
	+ Maximum propagation delay: 120 ns
	+ Loop delay symmetry: -10%/+10% (2 Mbps)
- Wake-up on CAN activity, 3.6 μs filter time
- Implements ISO11898-2:2003, ISO11898-5:2007, and ISO/DIS11898-2:2015
- Very Low Standby Current (4 μA, typical)
- CAN Bus Pins are Disconnected when Device is Unpowered
	+ An unpowered node or brown-out event will not load the CAN bus
	+ Device is unpowered if V DD or V IO drop below its POR level
- Detection of Ground Fault:
	+ Permanent Dominant detection on Txd
	+ Permanent Dominant detection on bus
- Automatic Thermal Shutdown Protection
- Suitable for 12V and 24V Systems

---

### Example

#### Configuration
* MCU:             PIC32MX795F512L
* Dev.Board:       EasyPIC Fusion v7
* Oscillator:      80 Mhz
* Ext. Modules:    MCP2542 click
* SW:              MikroC PRO for PIC32 3.6.0

```
#include "mcp2542.h"

/* MODULE PINS
 ******************************************************************************/
sbit MCP2542_STB at LATB8_bit;

/* VARS
 ******************************************************************************/
char read_buffer[ BFR_SIZE ] = { 0 };                                           /* RX buffer */
char write_buffer[ BFR_SIZE ] = "MikroElektronika"               		/* TX message */

/* PROTOTYPES
 ******************************************************************************/
void system_init( void );

/* FUNCTIONS
 ******************************************************************************/
void system_init()
{
    TRISB8_bit = 0;                                                             /* Button pin */
    TRISD8_bit = 1;                                                             /* STB pin */
    Delay_ms( 200 );
                                                                                /* DBG UART */
    UART5_Init( 115200 );
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

    while( 1 )
    {
        if( Button( &PORTD, 8, 100, 1 ) )
        {
            mcp2542_send( write_buffer );
            UART5_Write_Text( "\r\n< SENT >\r\n" );
        }

        if( mcp2542_rdy() )
        {
            mcp2542_read( read_buffer );
            UART5_Write_Text( "\r\n< RECEIVED >\r\n" );
            UART5_Write_Text( read_buffer );
        }
    }
}
```

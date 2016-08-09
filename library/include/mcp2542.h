/****************************************************************************
* Title                 :   MCP2542 CLICK
* Filename              :   mcp2542.h
* Author                :   MSV
* Origin Date           :   28/01/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  28/01/16    XXXXXXXXXXX         MSV      Interface Created.
*
*****************************************************************************/
/**
 * @file mcp2542.h
 * @brief <h3> Hardware Layer </h3>
 *
 * @par
 * Low level functions for
 * <a href="http://www.mikroe.com">MikroElektronika's</a> MCP2542 click
 * board.
 */

/**
 * @page LIB_INFO Library Info
 * @date 28 Jan 2016
 * @author Milos Vidojevic
 * @copyright GNU Public License
 * @version 1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 *
 * ### Test configuration STM : ###
 * @par
 * -<b> MCU           </b> :      STM32F107VC
 * -<b> Dev. Board    </b> :      EasyMx Pro v7
 * -<b> Oscillator    </b> :      72 Mhz internal
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for ARM 4.7.1
 *
 * ### Test configuration PIC32 : ###
 * @par
 * -<b> MCU           </b> :      PIC32MX795F512L
 * -<b> Dev. Board    </b> :      EasyPIC Fusion v7
 * -<b> Oscillator    </b> :      80 Mhz internal
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for PIC 3.6.0
 *
 * ### Test configuration FT90x : ###
 * @par
 * -<b> MCU           </b> :      FT900Q
 * -<b> Dev. Board    </b> :      EasyFT90x v7
 * -<b> Oscillator    </b> :      100 Mhz internal
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for FT90x 1.2.1
 *
 * ### Test configuration PIC : ###
 * @par
 * -<b> MCU           </b> :      PIC18F87K22
 * -<b> Dev. Board    </b> :      EasyPIC Pro v7
 * -<b> Oscillator    </b> :      16 Mhz external
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for PIC 6.6.3
 *
 * ### Test configuration dsPIC : ###
 * @par
 * -<b> MCU           </b> :      dsPIC33EJ256GP710A
 * -<b> Dev. Board    </b> :      EasyPIC Fusion v7
 * -<b> Oscillator    </b> :      8 Mhz internal
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for dsPIC 6.2.1
 *
 * ### Test configuration AVR : ###
 * @par
 * -<b> MCU           </b> :      ATMEGA32
 * -<b> Dev. Board    </b> :      EasyAVR v7
 * -<b> Oscillator    </b> :      8 Mhz external
 * -<b> Ext. Modules  </b> :      MCP2542 Click
 * -<b> SW            </b> :      MikroC PRO for FT90x 6.1.1
 */

/**
 * @mainpage
 * <h3> General Description </h3>
 * @par
 * The MCP2542FD/4FD and MCP2542WFD/4WFD CAN transceiver family is designed
 * for high-speed CAN FD applications up to 8 Mbps communication speed. The
 * maximum propagation delay was improved to support longer bus length. The
 * device meets the automotive requirements for CAN FD bit rates exceeding 2
 * Mbps, low quiescent current, electromagnetic compatibility (EMC) and
 * electrostatic discharge (ESD).
 *
 * <h3> Features </h3>
 * @par
 * - Supports CAN 2.0 and CAN with Flexible Data Rate (CAN FD) Physical Layer
 *          Transceiver Requirements
 * - Optimized for CAN FD at 2, 5 and 8 Mbps Operation
 *                 + Maximum propagation delay: 120 ns
 *                 + Loop delay symmetry: -10%/+10% (2 Mbps)
 * - Implements ISO11898-2:2003, ISO11898-5:2007, and ISO/DIS11898-2:2015
 * - Very Low Standby Current (4 μA, typical)
 * - Automatic Thermal Shutdown Protection
 * - Suitable for 12V and 24V Systems
 */

#ifndef MCP2542_H
#define MCP2542_H

/******************************************************************************
* Includes
*******************************************************************************/

#include <string.h>
#include <stdbool.h>
#include "mcp2542_hal.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

#define BFR_SIZE                        256

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum {

        MCP2542_NORMAL,
        MCP2542_STBY

}mcp2542_mode;

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> HW Layer Initialization </h3>
 *
 * @par
 * Prepares library for usage and sets needed values to default.
 *
 * @note
 * This function must be called first.
 */
void mcp2542_init
(
                void
);

/**
 * @brief <h3> Work Mode </h3>
 *
 * @par
 * Switches device work mode using STB pin.
 */
void mcp2542_mode_set
(
                mcp2542_mode mode
);

/**
 * @brief <h3> Send Message </h3>
 *
 * @par
 * Provided message should not have delimiter which will be added at the end of
 * message provided.
 *
 * @note
 * Provided message should be closed with '\0\ character.
 */
void mcp2542_send
(
                char *msg
);

/**
 * @brief <h3> Read Message </h3>
 *
 * @par
 * Read received message from the buffer.
 *
 * @note
 * This function clears the new message flag.
 */
void mcp2542_read
(
                char *msg
);

/**
 * @brief <h3> Checks for a new message </h3>
 *
 * @par
 * Checks the flag for existence of a new message inside the buffer.
 */
bool mcp2542_rdy
(
                void
);

void mcp2542_rx_isr( char ch );

#ifdef __cplusplus
}
#endif

#endif

/*** End of File **************************************************************/

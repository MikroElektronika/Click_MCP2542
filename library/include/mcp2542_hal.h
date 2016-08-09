/****************************************************************************
* Title                 :   MCP2542 HAL
* Filename              :   mcp2542_hal.h
* Author                :   MSV
* Origin Date           :   02/12/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  02/12/15    XXXXXXXXXXX         MSV      Interface Created.
*
*****************************************************************************/
/**
 * @file mcp2542_hal.h
 *
 * @brief HAL layer for the Mikroelektronika's MCP2542 board.
 *
 * @note
 * HAL layer requires declaration of mcp2542_rx_isr function which will
 * handle data received from UART bus.
 *
 * @warning
 * Init function perform initialization of interrupts for :
 * - ARM - UART3
 * - AVR - UART1
 * - PIC - UART1
 * - PIC32 - UART2
 * - FT90x - UART2
 *
 * which are UART buses for mikroBUS slot 1. Usage on any other UART bus
 * requires editing of HAL layer depend on you platform and used UART bus.
 */

#ifndef MCP2542_HAL_H_
#define MCP2542_HAL_H_

/******************************************************************************
* Includes
*******************************************************************************/

#include <stdint.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief HAL Layer Initialization.
 *
 * @par
 * Initialization of the HAL layer. Function is used by higher layer.
 */
void mcp2542_hal_init
(
        void
);

/**
 * @brief Standby Control
 *
 * @par
 * Sets STB pin to provided logic state.
 *
 * @param[in] state ( 1 / 0 )
 */
void mcp2542_hal_stb
(
        int state
);

/**
 * @brief Write Function
 *
 * @par
 * Writes character through the UART bus.
 *
 * @param[in] ch
 */
void mcp2542_hal_write
(
        char ch
);

#ifdef __cplusplus
}
#endif

#endif /*LORA_RF_HAL_H_*/

/*** End of File **************************************************************/

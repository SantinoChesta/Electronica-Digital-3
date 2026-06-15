/*
 * Comunicacion_UART.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef COMUNICACION_UART_H_
#define COMUNICACION_UART_H_

#include "lpc17xx_uart.h"
#include "lpc17xx_gpdma.h"
#include "Mapa.h"

void UART_DMA_Send(void);

void cfgUART0(void);

#endif /* COMUNICACION_UART_H_ */

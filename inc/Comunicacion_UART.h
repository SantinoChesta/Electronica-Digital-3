/*
 * Comunicacion_UART.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef COMUNICACION_UART_H_
#define COMUNICACION_UART_H_

#include <stdint.h>
#include <lpc17xx_gpdma.h>

void UART0_DMA_Init(void);
Status UART0_DMA_Send(const uint8_t *buffer, uint32_t length);
uint8_t UART0_DMA_IsBusy(void);

#endif

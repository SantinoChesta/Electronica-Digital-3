/*
 * Comunicacion_UART.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef COMUNICACION_UART_H_
#define COMUNICACION_UART_H_

#include "lpc17xx_gpdma.h"
#include <stdint.h>

/**
 * @brief Inicia y configura el uart para transmitir, inicia el dma y habilita
 * interrupciones
 */
void UART0_DMA_Init(void);

/**
 * @brief Configura el dma para pasarle datos al uart
 * @param *buffer Posicion de memoria del array a enviar
 * @param length Tamano del array
 * @return SUCCESS si logra configurar el dma para enviar,
 * ERROR si no hay datos para enviar o el uart esta ocupado
 */
Status UART0_DMA_Send(const uint8_t *buffer, uint32_t length);

/**
 * @breif Devuelve el estado del uart
 *
 * @return 1 si todavia esta mandando datos, 0 si esta disponible
 */
uint8_t UART0_DMA_IsBusy(void);

#endif /* COMUNICACION_UART_H_ */

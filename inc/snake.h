/*
 * snake.h
 *
 *  Created on: 15 jun. 2026
 *      Author: santi
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdint.h>
#include "Joystick.h"
#include "Comunicacion_UART.h"
#include <lpc17xx_timer.h>

#define MAPA_X 10
#define MAPA_Y 10
#define MAX_SNAKE (MAPA_X * MAPA_Y)

#define FRAME_BUFFER_SIZE 256

typedef struct
{
    uint8_t x;
    uint8_t y;
} POS;

extern POS snake[MAX_SNAKE];
extern POS fruta;

extern uint8_t longitud;
extern uint8_t gameOver;
extern DIR direccionActual;

/**
 * @brief Posiciona una serpiente de tamano 3 en el mapa
 */
void Snake_Init(void);

/**
 * @brief Actualiza la posicion de la serpiente respecto
 * a la direccion obtenida y detecta colisiones contra las paredes
 * y la fruta
 */
void Snake_Update(void);

/**
 * @brief Configura e inicia el timer para interrupir cada 250ms
 */
void Snake_Timer0Init(void);

/**
 * @brief Genera un array de caracteres representando el mapa, en caso
 * de derrota, el array contiente texto indicativo de esta
 */
uint16_t Snake_Render(uint8_t *buffer, uint16_t maxLen);

#endif /* SNAKE_H_ */
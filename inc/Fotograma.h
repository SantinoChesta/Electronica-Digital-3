/*
 * Fotograma.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef FOTOGRAMA_H_
#define FOTOGRAMA_H_

#include "Joystick.h"
#include "lpc17xx_timer.h"

#define MAPA_X 10
#define MAPA_Y 10
#define MAX_SNAKE 100

typedef struct
{
    uint8_t x;
    uint8_t y;
} POS;

POS snake[MAX_SNAKE];
POS fruta;

uint8_t longitud = 3;
uint8_t gameOver = 0;

DIR direccionActual = DERECHA;

uint32_t seed = 1;

void Snake_Init(void);
void GenerarFruta(void);
void ActualizarSnake(DIR dir);
void TIMER0_IRQHandler(void);
void cfgTIMER0(void);

#endif /* FOTOGRAMA_H_ */

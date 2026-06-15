/*
 * Fotograma.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdint.h>
#include "Joystick.h"

#define MAPA_X 10
#define MAPA_Y 10
#define MAX_SNAKE (MAPA_X * MAPA_Y)

#define FRAME_BUFFER_SIZE 600

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

void Snake_Init(void);
void Snake_Update(void);
void Snake_Timer0Init(void);
uint16_t Snake_Render(uint8_t *buffer, uint16_t maxLen);

#endif
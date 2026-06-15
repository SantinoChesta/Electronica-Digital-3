/*
 * Mapa.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef MAPA_H_
#define MAPA_H_

#include "Joystick.h"
#include <stdlib.h>

#define MAPA_X 10
#define MAPA_Y 10
#define MAX_SNAKE 100
#define FRAME_SIZE ((MAPA_X + 2) * MAPA_Y + 3)


typedef struct{
    uint8_t x;
    uint8_t y;
} POS;

extern POS snake[MAX_SNAKE];
extern POS fruta;

extern uint8_t longitud;
extern uint8_t gameOver;

extern DIR direccionActual;

extern uint32_t seed;

extern uint16_t frameLength;
extern char frameBuffer[FRAME_SIZE];


void ActualizarSnake(DIR dir);
void Snake_Init(void);
void GenerarFruta(void);
void DibujarMapaASCII(void);
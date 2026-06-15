/*
 * Joystick.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>

#define JOY_CENTER 2048
#define JOY_DEADZONE 400

typedef enum
{
    ABAJO,
    DERECHA,
    IZQUIERDA,
    ARRIBA,
    CENTRO
} DIR;

void Joystick_Init(void);
uint16_t Joystick_GetX(void);
uint16_t Joystick_GetY(void);
DIR Joystick_GetXDir(uint16_t x);
DIR Joystick_GetYDir(uint16_t y);
DIR Joystick_GetDirection(void);

#endif
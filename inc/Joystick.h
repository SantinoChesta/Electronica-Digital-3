/*
 * Joystick.h
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <lpc17xx_adc.h>
#include <stdlib.h>

#define CENTER 2048
#define DEADZONE 400
#define ADC_BUFFER_SIZE 16

typedef enum
{
    ABAJO,
    DERECHA,
    IZQUIERDA,
    ARRIBA,
    CENTRO
} DIR;

typedef struct
{
    DIR xDir;
    uint16_t xValue;
    DIR yDir;
    uint16_t yValue;
} AXIS;

void cfgADC(void);
uint16_t getADCXValue();
uint16_t getADCYValue();
DIR getXDir(int x);
DIR getYDir(int y);
DIR getAxialDir(AXIS *axis);

#endif /* JOYSTICK_H_ */

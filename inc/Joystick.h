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

/**
 * @brief Configura y habilita el ADC para que muestree dos senales
 * en modo burst
 */
void Joystick_Init(void);

/**
 * @brief Getter del valor de la senal muestreada en el canal 0
 * @return Conversion de una senal con rango 0v-3,3v con una resolucion
 * de 12 bits
 */
uint16_t Joystick_GetX();

/**
 * @brief Getter del valor de la senal muestreada en el canal 1
 * @return Conversion de una senal con rango 0v-3,3v con una resolucion
 * de 12 bits
 */
uint16_t Joystick_GetY();

/**
 * @brief Define en que sentido se encuentra el joystick en el eje
 * horizontal
 * @return IZQUIERDA Si el valor es menor a 1648, DERECHA Si el valor es mayor
 * a 2448
 */
DIR Joystick_GetXDir(uint16_t x);

/**
 * @brief Define en que sentido se encuentra el joystick en el eje
 * vertical
 * @return ARRIBA Si el valor es menor a 1648, ABAJO Si el valor es mayor
 * a 2448
 */
DIR Joystick_GetYDir(uint16_t y);

/**
 * @brief Define en que sentido se encuentra el joystick
 * @return La direccion cuyo valor absoluto dado por sus getters sea el mayor
 */
DIR Joystick_GetDirection(void);

#endif /* JOYSTICK_H_ */

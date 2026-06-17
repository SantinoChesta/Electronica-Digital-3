/*
 * Teclado_matricial.h
 *
 *  Created on: 15 jun. 2026
 *      Author: santi
 */

#ifndef TECLADO_MATRICIAL_H_
#define TECLADO_MATRICIAL_H_

#include <cr_section_macros.h>
#include <stdio.h>

#include "LPC17xx_GPIO.h"
#include "LPC17xx_PINSEL.h"

uint8_t tecla;

/**
 * @brief Configura los pines utilizados por el teclado matricial
 */
void cfgGPIO(void);

/**
 * @brief Lee el boton presionado
 * @return 1 Si el boton es el uno, 0 si no lo es
 */
uint8_t TeclaSupIzq(void);

#endif /* TECLADO_MATRICIAL_H_ */

/*
 * Teclado_matricial.c
 *
 *  Created on: 15 jun 2026
 *      Author: santi
 */

#include "Teclado_matricial.h"
void cfgGPIO(void)
{
    PINSEL_CFG_T pinCfg;

    pinCfg.port = PORT_2;
    pinCfg.func = PINSEL_FUNC_00;
    pinCfg.mode = PINSEL_PULLUP;
    pinCfg.openDrain = DISABLE;

    for (pinCfg.pin = PIN_0; pinCfg.pin <= PIN_7; pinCfg.pin++)
    {
        PINSEL_ConfigPin(&pinCfg);
    }

    GPIO_SetDir(PORT_2, 0x0F, GPIO_OUTPUT);  // filas P2.0 a P2.3
    GPIO_SetDir(PORT_2, 0xF0, GPIO_INPUT);   // columnas P2.4 a P2.7

    GPIO_SetPins(PORT_2, 0x0F);
}

uint8_t TeclaSupIzq(void)
{
    GPIO_SetPins(PORT_2, 0x0F);        // Todas las filas en 1
    GPIO_ClearPins(PORT_2, (1 << 0));  // Fila 0 en 0

    if ((GPIO_ReadValue(PORT_2) & (1 << 4)) == 0)
    {
        return 1;
    }

    return 0;
}

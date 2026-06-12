/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "LPC17xx_GPIO.h"
#include "LPC17xx_PINSEL.h"

uint8_t tecla;

void cfgGPIO(void);
uint8_t TeclaSupIzq(void);

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
    cfgGPIO();
    while (1)
    {
        tecla = TeclaSupIzq();
        if (tecla == 1)
        {
            GPIO_SetPinState(PORT_0, PIN_22, RESET);
        }
    };
    return 0;
}

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

    GPIO_SetDir(PORT_2, 0x0F, GPIO_OUTPUT); // filas
    GPIO_SetDir(PORT_2, 0xF0, GPIO_INPUT);  // columnas

    GPIO_SetPins(PORT_2, 0x0F);
}
uint8_t TeclaSupIzq(void)
{
    GPIO_SetPins(PORT_2, 0x0F);

    GPIO_ClearPins(PORT_2, (1 << 0));

    if ((GPIO_ReadValue(PORT_2) & (1 << 4)) == 0)
    {
        return 1;
    }

    return 0;
}

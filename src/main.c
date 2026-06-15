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

#include "Joystick.h"
#include "Snake.h"
#include "Comunicacion_UART.h"
#include "Teclado_matricial.h"

int main(void)
{
	cfgGPIO();

	while (TeclaSupIzq() == 0)
	{
	}

    Joystick_Init();
    UART0_DMA_Init();

    Snake_Init();
    Snake_Timer0Init();

    while (1)
    {
        __WFI();
    }
}
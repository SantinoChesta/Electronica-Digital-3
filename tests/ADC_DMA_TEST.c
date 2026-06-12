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

#include <lpc17xx_gpdma.h>
#include <lpc17xx_adc.h>
#include <lpc17xx_gpio.h>
#include <stdlib.h>

#define CENTER 2048
#define DEADZONE 400
#define ADC_BUFFER_SIZE 16

typedef enum
{
    ABAJO = 0x5E,
    DERECHA = 0x50,
    IZQUIERDA = 0x38,
    ARRIBA = 0x3E,
    CENTRO = 0x3F
} DIR;

typedef struct
{
    DIR xDir;
    uint16_t xValue;
    DIR yDir;
    uint16_t yValue;
} AXIS;

volatile uint16_t xValue = CENTER;
volatile uint16_t yValue = CENTER;

// asd

void cfgADC(void);
void cfgDisplay(void);
DIR getXDir(int x);
DIR getYDir(int y);
DIR getAxialDir(AXIS *axis);

void displayWrite(DIR displayDir);

int main(void)
{
    cfgDisplay();
    cfgADC();

    while (1)
    {
        xValue = (LPC_ADC->ADDR0 >> 4) & 0xFFF;
        yValue = (LPC_ADC->ADDR1 >> 4) & 0xFFF;
        AXIS axis = {
            .xDir = getXDir(xValue), .xValue = xValue, .yDir = getYDir(yValue), .yValue = yValue};

        displayWrite(getAxialDir(&axis));
    }
}

void cfgADC()
{
    ADC_Init(10000);
    ADC_PowerUp();
    ADC_BurstEnable();

    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);

    ADC_IntEnable(ADC_INT_CH0); // Int habilitadas en registros pero no
    ADC_IntEnable(ADC_INT_CH1); // en NVIC habilita las req de DMA

    ADC_StartCmd(ADC_START_CONTINUOUS);
}

void cfgDisplay(void)
{
    GPIO_SetDir(PORT_0, (1 << 22), GPIO_OUTPUT);
    GPIO_SetDir(PORT_3, (1 << 26), GPIO_OUTPUT);
}

void displayWrite(DIR displayDir)
{

    // Clear segments
    switch (displayDir)
    {
    case ABAJO:
        GPIO_SetPins(PORT_0, (1 << 22));
        GPIO_SetPins(PORT_3, (1 << 26));
        break;
    case ARRIBA:
        GPIO_ClearPins(PORT_0, (1 << 22));
        GPIO_ClearPins(PORT_3, (1 << 26));
        break;
    case DERECHA:
        GPIO_SetPins(PORT_0, (1 << 22));
        GPIO_ClearPins(PORT_3, (1 << 26));
        break;
    case IZQUIERDA:
        GPIO_ClearPins(PORT_0, (1 << 22));
        GPIO_SetPins(PORT_3, (1 << 26));
        break;
    case CENTRO:
        GPIO_SetPins(PORT_0, (1 << 22));
        GPIO_SetPins(PORT_3, (1 << 26));
        break;
    }
}

DIR getXDir(int x)
{
    if ((x) > (CENTER + DEADZONE))
    {
        return DERECHA;
    }
    else if ((x) < (CENTER - DEADZONE))
    {
        return IZQUIERDA;
    }
    else
        return CENTRO;
}
DIR getYDir(int y)
{
    if ((y) > (CENTER + DEADZONE))
    {
        return ABAJO;
    }
    else if ((y) < (CENTER - DEADZONE))
    {
        return ARRIBA;
    }
    else
        return CENTRO;
}
DIR getAxialDir(AXIS *axis)
{

    uint32_t dx = abs((int)axis->xValue - CENTER);
    uint32_t dy = abs((int)axis->yValue - CENTER);

    if (dx < DEADZONE && dy < DEADZONE)
    {
        return CENTRO;
    }

    if (dx > dy)
    {
        return axis->xDir;
    }

    return axis->yDir;
}

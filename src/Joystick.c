#include "Joystick.h"

#include <stdlib.h>
#include <lpc17xx_adc.h>

void Joystick_Init(void)
{
    ADC_Init(10000);
    ADC_PowerUp();

    ADC_PinConfig(ADC_CHANNEL_0);
    ADC_PinConfig(ADC_CHANNEL_1);

    ADC_ChannelEnable(ADC_CHANNEL_0);
    ADC_ChannelEnable(ADC_CHANNEL_1);

    ADC_BurstEnable();
    ADC_StartCmd(ADC_START_CONTINUOUS);
}

uint16_t Joystick_GetX(void)
{
    return ADC_ChannelGetData(ADC_CHANNEL_0);
}

uint16_t Joystick_GetY(void)
{
    return ADC_ChannelGetData(ADC_CHANNEL_1);
}

DIR Joystick_GetXDir(uint16_t x)
{
    if (x > JOY_CENTER + JOY_DEADZONE)
    {
        return DERECHA;
    }

    if (x < JOY_CENTER - JOY_DEADZONE)
    {
        return IZQUIERDA;
    }

    return CENTRO;
}

DIR Joystick_GetYDir(uint16_t y)
{
    if (y > JOY_CENTER + JOY_DEADZONE)
    {
        return ABAJO;
    }

    if (y < JOY_CENTER - JOY_DEADZONE)
    {
        return ARRIBA;
    }

    return CENTRO;
}

DIR Joystick_GetDirection(void)
{
    uint16_t x = Joystick_GetX();
    uint16_t y = Joystick_GetY();

    uint32_t dx = abs((int)x - JOY_CENTER);
    uint32_t dy = abs((int)y - JOY_CENTER);

    if (dx < JOY_DEADZONE && dy < JOY_DEADZONE)
    {
        return CENTRO;
    }

    if (dx > dy)
    {
        return Joystick_GetXDir(x);
    }

    return Joystick_GetYDir(y);
}

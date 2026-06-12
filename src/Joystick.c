#include "Joystick.h"

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
uint16_t getADCXValue()
{
    return (LPC_ADC->ADDR0 >> 4) & 0xFFF;
}
uint16_t getADCYValue()
{
    return (LPC_ADC->ADDR1 >> 4) & 0xFFF;
}

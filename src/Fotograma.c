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

#include "Fotograma.h"

void cfgTIMER0(void)
{
    TIM_TIMERCFG_T timerCfg;
    TIM_MATCHCFG_T matchCfg;

    timerCfg.prescaleOpt = TIM_US;
    timerCfg.prescaleValue = 1;

    TIM_InitTimer(LPC_TIM0, &timerCfg);

    matchCfg.channel = 0;
    matchCfg.intEn = ENABLE;
    matchCfg.resetEn = ENABLE;
    matchCfg.stopEn = DISABLE;
    matchCfg.extOpt = TIM_NOTHING;
    matchCfg.matchValue = 250000; // 250 ms

    TIM_ConfigMatch(LPC_TIM0, &matchCfg);

    NVIC_EnableIRQ(TIMER0_IRQn);

    TIM_Enable(LPC_TIM0);
}
void TIMER0_IRQHandler(void)
{
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

    if (gameOver)
        return;

    uint16_t xADC = getADCXValue();
    uint16_t yADC = getADCYValue();

    AXIS axis = {.xDir = getXDir(xADC), .xValue = xADC, .yDir = getYDir(yADC), .yValue = yADC};

    DIR nuevaDir = getAxialDir(&axis);

    if (nuevaDir != CENTRO)
    {
        if (!(direccionActual == ARRIBA && nuevaDir == ABAJO) &&
            !(direccionActual == ABAJO && nuevaDir == ARRIBA) &&
            !(direccionActual == DERECHA && nuevaDir == IZQUIERDA) &&
            !(direccionActual == IZQUIERDA && nuevaDir == DERECHA))
        {
            direccionActual = nuevaDir;
        }
    }

    ActualizarSnake(direccionActual);
}
int main(void)
{

    return 0;
}
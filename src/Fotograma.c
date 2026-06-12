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

void Snake_Init(void)
{
    snake[0].x = 5;
    snake[0].y = 5;

    snake[1].x = 4;
    snake[1].y = 5;

    snake[2].x = 3;
    snake[2].y = 5;

    longitud = 3;

    fruta.x = 8;
    fruta.y = 8;
}
void GenerarFruta(void)
{
    uint8_t libre;
    uint8_t i;

    do
    {
        libre = 1;

        fruta.x = seed % MAPA_X;
        fruta.y = (seed / 7) % MAPA_Y;

        seed += 13;

        for (i = 0; i < longitud; i++)
        {
            if (snake[i].x == fruta.x && snake[i].y == fruta.y)
            {
                libre = 0;
                break;
            }
        }

    } while (!libre);
}
void ActualizarSnake(DIR dir)
{
    POS nuevaCabeza;

    nuevaCabeza = snake[0];

    switch (dir)
    {
    case ARRIBA:
        nuevaCabeza.y--;
        break;

    case ABAJO:
        nuevaCabeza.y++;
        break;

    case IZQUIERDA:
        nuevaCabeza.x--;
        break;

    case DERECHA:
        nuevaCabeza.x++;
        break;

    default:
        break;
    }

    if (nuevaCabeza.x >= MAPA_X || nuevaCabeza.y >= MAPA_Y)
    {
        gameOver = 1;
        return;
    }

    for (uint8_t i = 0; i < longitud; i++)
    {
        if (nuevaCabeza.x == snake[i].x && nuevaCabeza.y == snake[i].y)
        {
            gameOver = 1;
            return;
        }
    }

    if (nuevaCabeza.x == fruta.x && nuevaCabeza.y == fruta.y)
    {
        for (int i = longitud; i > 0; i--)
            snake[i] = snake[i - 1];

        snake[0] = nuevaCabeza;

        longitud++;

        GenerarFruta();
    }
    else
    {
        for (int i = longitud - 1; i > 0; i--)
            snake[i] = snake[i - 1];

        snake[0] = nuevaCabeza;
    }
}
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

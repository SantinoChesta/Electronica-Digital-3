#include "Snake.h"
#include "Comunicacion_UART.h"

#include <lpc17xx_timer.h>

POS snake[MAX_SNAKE];
POS fruta;

uint8_t longitud = 3;
uint8_t gameOver = 0;
DIR direccionActual = DERECHA;

static uint32_t seed = 1;
static uint8_t frameBuffer[FRAME_BUFFER_SIZE];

static uint8_t EsDireccionOpuesta(DIR actual, DIR nueva)
{
    return (actual == ARRIBA && nueva == ABAJO) ||
           (actual == ABAJO && nueva == ARRIBA) ||
           (actual == DERECHA && nueva == IZQUIERDA) ||
           (actual == IZQUIERDA && nueva == DERECHA);
}

static uint8_t PosIgual(POS a, POS b)
{
    return a.x == b.x && a.y == b.y;
}

static void GenerarFruta(void)
{
    uint8_t libre;

    if (longitud >= MAX_SNAKE)
    {
        gameOver = 1;
        return;
    }

    do
    {
        libre = 1;

        seed = seed * 1103515245u + 12345u;
        fruta.x = (seed >> 16) % MAPA_X;

        seed = seed * 1103515245u + 12345u;
        fruta.y = (seed >> 16) % MAPA_Y;

        for (uint8_t i = 0; i < longitud; i++)
        {
            if (snake[i].x == fruta.x && snake[i].y == fruta.y)
            {
                libre = 0;
                break;
            }
        }

    } while (!libre);
}

void Snake_Init(void)
{
    snake[0].x = 5;
    snake[0].y = 5;

    snake[1].x = 4;
    snake[1].y = 5;

    snake[2].x = 3;
    snake[2].y = 5;

    longitud = 3;
    gameOver = 0;
    direccionActual = DERECHA;

    GenerarFruta();
}

static void Snake_CambiarDireccion(DIR nuevaDir)
{
    if (nuevaDir == CENTRO)
    {
        return;
    }

    if (EsDireccionOpuesta(direccionActual, nuevaDir))
    {
        return;
    }

    direccionActual = nuevaDir;
}

void Snake_Update(void)
{
    if (gameOver)
    {
        return;
    }

    DIR nuevaDir = Joystick_GetDirection();
    Snake_CambiarDireccion(nuevaDir);

    POS nuevaCabeza = snake[0];

    switch (direccionActual)
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

    uint8_t comioFruta = PosIgual(nuevaCabeza, fruta);

    uint8_t limiteChoque = longitud;

    if (!comioFruta)
    {
        limiteChoque = longitud - 1;
    }

    for (uint8_t i = 0; i < limiteChoque; i++)
    {
        if (PosIgual(nuevaCabeza, snake[i]))
        {
            gameOver = 1;
            return;
        }
    }

    if (comioFruta)
    {
        if (longitud < MAX_SNAKE)
        {
            longitud++;
        }
        else
        {
            gameOver = 1;
            return;
        }
    }

    for (int i = longitud - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    snake[0] = nuevaCabeza;

    if (comioFruta)
    {
        GenerarFruta();
    }
}

static char Celda(uint8_t x, uint8_t y)
{
    if (snake[0].x == x && snake[0].y == y)
    {
        return 'O';
    }

    for (uint8_t i = 1; i < longitud; i++)
    {
        if (snake[i].x == x && snake[i].y == y)
        {
            return 'o';
        }
    }

    if (fruta.x == x && fruta.y == y)
    {
        return '*';
    }

    return '.';
}

uint16_t Snake_Render(uint8_t *buffer, uint16_t maxLen)
{
    uint16_t i = 0;

#define PUT_CHAR(c)               \
    do                            \
    {                             \
        if (i < maxLen)           \
        {                         \
            buffer[i++] = (c);    \
        }                         \
    } while (0)

#define PUT_STR(s)                \
    do                            \
    {                             \
        const char *p = (s);      \
        while (*p != '\0')        \
        {                         \
            PUT_CHAR(*p);         \
            p++;                  \
        }                         \
    } while (0)

    PUT_STR("\033[H\033[2J");

    PUT_STR("SNAKE LPC1769\r\n");
    PUT_STR("O cabeza | o cuerpo | * fruta\r\n\r\n");

    for (uint8_t y = 0; y < MAPA_Y; y++)
    {
        for (uint8_t x = 0; x < MAPA_X; x++)
        {
            PUT_CHAR(Celda(x, y));
            PUT_CHAR(' ');
        }

        PUT_STR("\r\n");
    }

    if (gameOver)
    {
        PUT_STR("\r\nGAME OVER\r\n");
    }

#undef PUT_CHAR
#undef PUT_STR

    return i;
}

void Snake_Timer0Init(void)
{
    TIM_TIMERCFG_T timerCfg;
    TIM_MATCHCFG_T matchCfg;

    timerCfg.prescaleOpt = TIM_US;
    timerCfg.prescaleValue = 1;

    TIM_InitTimer(LPC_TIM0, &timerCfg);

    matchCfg.channel = TIM_MATCH_0;
    matchCfg.intEn = ENABLE;
    matchCfg.resetEn = ENABLE;
    matchCfg.stopEn = DISABLE;
    matchCfg.extOpt = TIM_NOTHING;
    matchCfg.matchValue = 250000;

    TIM_ConfigMatch(LPC_TIM0, &matchCfg);

    NVIC_EnableIRQ(TIMER0_IRQn);

    TIM_Enable(LPC_TIM0);
}

void TIMER0_IRQHandler(void)
{
    if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT))
    {
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);

        Snake_Update();

        if (!UART0_DMA_IsBusy())
        {
            uint16_t len = Snake_Render(frameBuffer, FRAME_BUFFER_SIZE);
            UART0_DMA_Send(frameBuffer, len);
        }
    }
}

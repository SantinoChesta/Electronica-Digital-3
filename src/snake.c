/*
 * Mapa.c
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */
#include "Mapa.h"
POS snake[MAX_SNAKE];
 POS fruta;

 uint8_t longitud = 3;
 uint8_t gameOver = 0;

 DIR direccionActual = DERECHA;

 uint32_t seed = 1;
 uint16_t frameLength = 0;

 char frameBuffer[FRAME_SIZE];

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

    do{
        libre = 1;

        fruta.x = seed % MAPA_X;
        fruta.y = (seed / 7) % MAPA_Y;

        seed += 13;

        for(i=0;i<longitud;i++)
        {
            if(snake[i].x == fruta.x &&
               snake[i].y == fruta.y)
            {
                libre = 0;
                break;
            }
        }

    }while(!libre);
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

        DibujarMapaASCII();
    }
}
void DibujarMapaASCII(void)
{
    char mapa[MAPA_Y][MAPA_X];
    uint8_t x,y,i;
    uint16_t idx = 0;

    for(y=0;y<MAPA_Y;y++)
    {
        for(x=0;x<MAPA_X;x++)
        {
            mapa[y][x]='.';
        }
    }

    mapa[fruta.y][fruta.x]='*';

    for(i=1;i<longitud;i++)
    {
        mapa[snake[i].y][snake[i].x]='O';
    }

    mapa[snake[0].y][snake[0].x]='@';

    idx = 0;

    frameBuffer[idx++] = '\r';
    frameBuffer[idx++] = '\n';

    for(y=0;y<MAPA_Y;y++)
    {
        for(x=0;x<MAPA_X;x++)
        {
            frameBuffer[idx++] = mapa[y][x];
        }

        frameBuffer[idx++] = '\r';
        frameBuffer[idx++] = '\n';
    }

    frameBuffer[idx] = '\0';
    frameLength = idx;
}


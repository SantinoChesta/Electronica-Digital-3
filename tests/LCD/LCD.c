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
#include "LCD.h"

static void delay_ms(uint32_t ms)
{
    volatile uint32_t i, j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 25000; j++)
        {
            __NOP();
        }
    }
}

static void LCD_EnablePulse(void)
{
    GPIO_SetPins(PORT_0, LCD_E);
    delay_ms(1);
    GPIO_ClearPins(PORT_0, LCD_E);
    delay_ms(1);
}

static void LCD_SendNibble(uint8_t nibble)
{
    GPIO_ClearPins(PORT_0, (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7));

    GPIO_SetPins(PORT_0, nibble << LCD_D4);

    LCD_EnablePulse();
}

static void LCD_SendByte(uint8_t value, uint8_t isData)
{
    if (isData)
    {
        GPIO_SetPins(PORT_0, LCD_RS);
    }
    else
    {
        GPIO_ClearPins(PORT_0, LCD_RS);
    }

    LCD_SendNibble(value >> 4);
    LCD_SendNibble(value & 0x0F);

    delay_ms(2);
}

void LCD_Command(uint8_t cmd)
{
    LCD_SendByte(cmd, 0);
}

void LCD_Data(uint8_t data)
{
    LCD_SendByte(data, 1);
}

void LCD_Init(void)
{
    GPIO_SetDir(PORT_0, LCD_RS | LCD_E | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7, GPIO_OUTPUT);
    GPIO_ClearPins(PORT_0, LCD_RS | LCD_E | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);

    LCD_SendNibble(0x03);
    delay_ms(5);

    LCD_SendNibble(0x03);
    delay_ms(5);

    LCD_SendNibble(0x03);
    delay_ms(5);

    LCD_SendNibble(0x02); // modo 4 bits

    LCD_Command(0x28); // 4 bits, 2 líneas, matriz 5x8
    LCD_Command(0x0C); // display ON, cursor OFF
    LCD_Command(0x06); // cursor avanza a la derecha
    LCD_Command(0x01); // limpiar display

    delay_ms(5);
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
    delay_ms(5);
}
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address = row * 0x40 + col;

    LCD_Command(0x80 | address);
}
void LCD_Print(const char *text)
{
    while (*text)
    {
        LCD_Data(*text);
        text++;
    }
}
void LCD_PrintNumber(uint32_t num)
{
    char buffer[11];
    int i = 0;

    if (num == 0)
    {
        LCD_Data('0');
        return;
    }

    while (num > 0)
    {
        buffer[i] = '0' + (num % 10);
        num /= 10;
        i++;
    }

    while (i > 0)
    {
        i--;
        LCD_Data(buffer[i]);
    }
}
int main()
{
    uint32_t puntuacion = 0;

    LCD_Init();

    LCD_Clear();

    LCD_SetCursor(0, 0);
    LCD_Print("Puntuacion:");

    // LCD_SetCursor(1, 0);
    LCD_PrintNumber(puntuacion);
};
/*
 * LCD.h
 *
 *  Created on: 16 jun. 2026
 *      Author: santi
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "LPC17xx_GPIO.h"

#define LCD_RS_PIN 0
#define LCD_E_PIN 1
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

#define LCD_RS (1 << LCD_RS_PIN)
#define LCD_E (1 << LCD_E_PIN)
#define LCD_D4 (1 << LCD_D4_PIN)
#define LCD_D5 (1 << LCD_D5_PIN)
#define LCD_D6 (1 << LCD_D6_PIN)
#define LCD_D7 (1 << LCD_D7_PIN)

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(const char *text);
void LCD_PrintNumber(uint32_t num);

#endif /* LCD_H_ */
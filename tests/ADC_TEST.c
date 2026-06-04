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

#include <cr_section_macros.h>
#include <lpc17xx_adc.h>
#include <lpc17xx_gpio.h>
#include <stdio.h>

volatile uint16_t buffer[2];

void cfgADC(void);
void ADC_IRQHandler();

int main(void) {
  cfgADC();
  GPIO_SetDir(PORT_0, (1 << 22), GPIO_OUTPUT);
  GPIO_SetDir(PORT_3, (1 << 26), GPIO_OUTPUT);

  while (1) {
    if (buffer[0] > 2048) {
      GPIO_SetPinState(PORT_0, PIN_22, RESET);
    } else {
      GPIO_SetPinState(PORT_0, PIN_22, SET);
    }
    if (buffer[1] > 2048) {
      GPIO_SetPinState(PORT_3, PIN_26, RESET);
    } else {
      GPIO_SetPinState(PORT_3, PIN_26, SET);
    }
  }
}

void cfgADC(void) {
  ADC_Init(40000);
  ADC_PinConfig(ADC_CHANNEL_0);
  // ADC_PinConfig(ADC_CHANNEL_1);

  ADC_ChannelEnable(ADC_CHANNEL_0);
  // ADC_ChannelEnable(ADC_CHANNEL_1);

  ADC_BurstEnable();

  ADC_IntEnable(ADC_INT_CH0);
  // ADC_IntEnable(ADC_INT_CH1);

  NVIC_EnableIRQ(ADC_IRQn);

  ADC_StartCmd(ADC_START_CONTINUOUS);
  ADC_PowerUp();
}
void ADC_IRQHandler() {
  buffer[0] = ADC_ChannelGetData(ADC_CHANNEL_0);
  buffer[1] = ADC_ChannelGetData(ADC_CHANNEL_1);
}

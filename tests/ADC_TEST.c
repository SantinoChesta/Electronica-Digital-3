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
#include <stdio.h>
#include <lpc17xx_adc.h>
#include <lpc17xx_gpio.h>

volatile uint16_t buffer[2];

void cfgADC(void);
void ADC_IRQHandler();

int main(void) {
	GPIO_SetDir(PORT_0, (1<<22), GPIO_OUTPUT);
	GPIO_SetDir(PORT_3, (1<<26), GPIO_OUTPUT);
	cfgADC();
	while(1){
		buffer[0]= ADC_ChannelGetData(ADC_CHANNEL_0);
		buffer[1]= ADC_ChannelGetData(ADC_CHANNEL_1);
		if(buffer[0]>3900){
			GPIO_ClearPins(PORT_0, (1<<22));
		}else if(buffer[0]<300){
			GPIO_SetPins(PORT_0,(1<<22));
		}
		if(buffer[1]>3900){
			GPIO_SetPinState(PORT_3, PIN_26, RESET);
		}else if(buffer[1]< 300){
			GPIO_SetPinState(PORT_3, PIN_26, SET);
		}
	}
}
void cfgADC(void){
	ADC_Init(1000);
	ADC_PowerUp();

	ADC_BurstEnable();
	ADC_PinConfig(ADC_CHANNEL_0);
	ADC_PinConfig(ADC_CHANNEL_1);

	ADC_ChannelEnable(ADC_CHANNEL_0);
	ADC_ChannelEnable(ADC_CHANNEL_1);

	ADC_StartCmd(ADC_START_CONTINUOUS);
}

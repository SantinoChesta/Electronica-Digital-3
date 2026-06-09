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
#include <lpc17xx_gpdma.h>
#include <lpc17xx_gpio.h>
#include <stdio.h>

volatile uint16_t src[8] = {1,2,3,4,5,6,7,8};
volatile uint16_t dst[8] = {0};

void cfgDMA(void);
void DMA_IRQHandler(void);

int main(void) {
	GPIO_SetDir(PORT_0, (1<<22), GPIO_OUTPUT);

	cfgDMA();

	while(1){
		__NOP();
	}
}

void cfgDMA(void){
	GPDMA_Channel_CFG_T dmaCfg;

	dmaCfg.channelNum = GPDMA_CH_0;
	dmaCfg.transferSize = 8;
	dmaCfg.type = GPDMA_M2M;

	dmaCfg.srcMemAddr = (uint32_t)src;
	dmaCfg.dstMemAddr = (uint32_t)dst;

	dmaCfg.src.width = GPDMA_HALFWORD;
	dmaCfg.dst.width = GPDMA_HALFWORD;

	dmaCfg.srcConn = 0;
	dmaCfg.dstConn = 0;

	dmaCfg.src.increment = ENABLE;
	dmaCfg.dst.increment = ENABLE;

	dmaCfg.intTC = ENABLE;
	dmaCfg.intErr = 0;

	GPDMA_Init();
	GPDMA_SetupChannel(&dmaCfg);
	NVIC_EnableIRQ(DMA_IRQn);
	GPDMA_ChannelStart(GPDMA_CH_0);
}
void DMA_IRQHandler(void)
{
    if(GPDMA_IntGetStatus(GPDMA_INTTC, GPDMA_CH_0))
    {
        GPIO_SetPinState(PORT_0, PIN_22, RESET);

        GPDMA_ClearIntPending(GPDMA_INTTC, GPDMA_CH_0);
    }
}

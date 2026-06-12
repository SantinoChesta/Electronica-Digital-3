/*
 * Comunicacion_UART.c
 *
 *  Created on: 12 jun. 2026
 *      Author: santi
 */

#include "Comunicacion_UART.h"

extern char frameBuffer[FRAME_SIZE];

void cfgUART0(void)
{
    UART_CFG_T uartCfg;

    uartCfg.baudRate = 115200;
    uartCfg.parity = UART_PARITY_NONE;
    uartCfg.dataBits = UART_DBITS_8;
    uartCfg.stopBits = UART_STOPBIT_1;

    UART_FIFO_CFG_T fifoCfg;

    fifoCfg.resetRxBuf = DISABLE;
    fifoCfg.resetTxBuf = DISABLE;
    fifoCfg.dmaMode = ENABLE;
    fifoCfg.level = UART_FIFO_TRGLEV0;

    UART_PinConfig(UART_TX0_P0_2);

    UART_Init(UART0, &uartCfg);

    UART_FIFOConfig(UART0, &fifoCfg);

    UART_TxEnable(UART0);
}

void UART_DMA_Send()
{
    GPDMA_Channel_CFG_T dmaCfg;

    GPDMA_Init();

    dmaCfg.channelNum = GPDMA_CH_0;

    dmaCfg.type = GPDMA_M2P; // Memoria -> Periférico

    dmaCfg.srcMemAddr = (uint32_t)frameBuffer;
    dmaCfg.dstMemAddr = 0;

    dmaCfg.srcConn = 0;              // No usado en M2P
    dmaCfg.dstConn = GPDMA_UART0_Tx; // UART0 TX

    dmaCfg.transferSize = FRAME_SIZE;

    dmaCfg.linkedList = 0;

    dmaCfg.src.increment = ENABLE;
    dmaCfg.dst.increment = DISABLE;

    dmaCfg.src.width = GPDMA_BYTE;
    dmaCfg.dst.width = GPDMA_BYTE;

    dmaCfg.src.burst = GPDMA_BSIZE_1;
    dmaCfg.dst.burst = GPDMA_BSIZE_1;

    dmaCfg.intTC = DISABLE;
    dmaCfg.intErr = DISABLE;

    GPDMA_SetupChannel(&dmaCfg);
    GPDMA_ChannelStart(GPDMA_CH_0);
}

#include "Comunicacion_UART.h"

#include <lpc17xx_uart.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_gpdma.h>

#define UART_TX_DMA_CH GPDMA_CH_1

static volatile uint8_t uartTxBusy = 0;

void UART0_DMA_Init(void)
{
    PINSEL_CFG_T txPin;

    txPin.port = PORT_0;
    txPin.pin = PIN_2;
    txPin.func = PINSEL_FUNC_01;
    txPin.mode = PINSEL_TRISTATE;
    txPin.openDrain = DISABLE;

    PINSEL_ConfigPin(&txPin);

    UART_CFG_T uartCfg;
    uartCfg.baudRate = 115200;
    uartCfg.dataBits = UART_DBITS_8;
    uartCfg.stopBits = UART_STOPBIT_1;
    uartCfg.parity = UART_PARITY_NONE;

    UART_Init(UART0, &uartCfg);

    UART_FIFO_CFG_T fifoCfg;
    fifoCfg.level = UART_FIFO_TRGLEV0;
    fifoCfg.resetTxBuf = ENABLE;
    fifoCfg.resetRxBuf = ENABLE;
    fifoCfg.dmaMode = ENABLE;

    UART_FIFOConfig(UART0, &fifoCfg);
    UART_TxEnable(UART0);

    GPDMA_Init();

    NVIC_EnableIRQ(DMA_IRQn);
}

uint8_t UART0_DMA_IsBusy(void)
{
    return uartTxBusy;
}

Status UART0_DMA_Send(const uint8_t *buffer, uint32_t length)
{
    if (buffer == 0 || length == 0 || uartTxBusy)
    {
        return ERROR;
    }

    uartTxBusy = 1;

    GPDMA_Channel_CFG_T dmaCfg;

    dmaCfg.channelNum = UART_TX_DMA_CH;
    dmaCfg.transferSize = length;
    dmaCfg.type = GPDMA_M2P;

    dmaCfg.srcMemAddr = (uint32_t)buffer;
    dmaCfg.dstMemAddr = 0;

    dmaCfg.srcConn = 0;
    dmaCfg.dstConn = GPDMA_UART0_Tx;

    dmaCfg.src.width = GPDMA_BYTE;
    dmaCfg.src.burst = GPDMA_BSIZE_1;
    dmaCfg.src.increment = ENABLE;

    dmaCfg.dst.width = GPDMA_BYTE;
    dmaCfg.dst.burst = GPDMA_BSIZE_1;
    dmaCfg.dst.increment = DISABLE;

    dmaCfg.intTC = ENABLE;
    dmaCfg.intErr = ENABLE;
    dmaCfg.linkedList = 0;

    if (GPDMA_SetupChannel(&dmaCfg) == ERROR)
    {
        uartTxBusy = 0;
        return ERROR;
    }

    GPDMA_ChannelStart(UART_TX_DMA_CH);

    return SUCCESS;
}

void DMA_IRQHandler(void)
{
    if (GPDMA_IntGetStatus(GPDMA_INTTC, UART_TX_DMA_CH))
    {
        GPDMA_ClearIntPending(GPDMA_CLR_INTTC, UART_TX_DMA_CH);
        uartTxBusy = 0;
    }

    if (GPDMA_IntGetStatus(GPDMA_INTERR, UART_TX_DMA_CH))
    {
        GPDMA_ClearIntPending(GPDMA_CLR_INTERR, UART_TX_DMA_CH);
        uartTxBusy = 0;
    }
}

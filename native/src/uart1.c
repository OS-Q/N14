/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include <string.h>
#include <stdint.h>

#include "stm8s.h"
#include "uart1.h"

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void uart1_init(uint8_t buad,uint8_t pair)
{
    /* Configure RX and TX pins */
    GPIOD->DDR = 0xBF;
    GPIOD->CR1 = 0xFF;
    /* Enable TX & RX */
    UART1->CR2 = (1 << 3) | (1 << 2);
    /* 1 stop bit */
    UART1->CR3 &= ~((1 << 5) | (1 << 4));
    /* 115200 baud, 16MHz, Error:0.08%   */
    UART1->BRR2 = 0x0B;
    UART1->BRR1 = 0x08;
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
uint8_t uart1_put(const char *s)
{
    uint8_t i;
    for(i = 0; i < strlen(s); i++)
    {
        while(!(UART1->SR & (1<<7)));
        UART1->DR = s[i];
    }
    return(i);
}

void uart1_set(uint8_t data)
{
    // while(!(UART1->SR & (1<<7)));
    UART1->DR = data;
    while(!(UART1->SR & (1<<6)));
}

uint8_t uart1_get(void)
{
    while (!(UART1->SR & (1<<5)));
    return UART1->DR;
}

// void uart1_isr(void) __interrupt(18)
// {
//     // Clear interrupt flag
//     UART1->SR = 0xDF;
// }

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/

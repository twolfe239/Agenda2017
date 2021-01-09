#ifndef KB_H
#define KB_H
#include "stm32f10x.h"

#define B0_RCC_FUNC RCC_APB2PeriphClockCmd
#define B0_RCC RCC_APB2Periph_GPIOB
#define B0_PIN GPIO_Pin_0
#define B0_PORT GPIOB

#define B1_RCC_FUNC RCC_APB2PeriphClockCmd
#define B1_RCC RCC_APB2Periph_GPIOB
#define B1_PIN GPIO_Pin_1
#define B1_PORT GPIOB

#define B2_RCC_FUNC RCC_APB2PeriphClockCmd
#define B2_RCC RCC_APB2Periph_GPIOB
#define B2_PIN GPIO_Pin_2
#define B2_PORT GPIOB

#define C0_RCC_FUNC RCC_APB2PeriphClockCmd
#define C0_RCC RCC_APB2Periph_GPIOB
#define C0_PIN GPIO_Pin_10
#define C0_PORT GPIOB

#define C1_RCC_FUNC RCC_APB2PeriphClockCmd
#define C1_RCC RCC_APB2Periph_GPIOB
#define C1_PIN GPIO_Pin_11
#define C1_PORT GPIOB

#define B0_HIGH GPIO_SetBits(B0_PORT, B0_PIN);
#define B1_HIGH GPIO_SetBits(B1_PORT, B1_PIN);
#define B2_HIGH GPIO_SetBits(B2_PORT, B2_PIN);
#define B0_LOW GPIO_ResetBits(B0_PORT, B0_PIN);
#define B1_LOW GPIO_ResetBits(B1_PORT, B1_PIN);
#define B2_LOW GPIO_ResetBits(B2_PORT, B2_PIN);
#define C0_INP GPIO_ReadInputDataBit (C0_PORT, C0_PIN)
#define C1_INP GPIO_ReadInputDataBit (C1_PORT, C1_PIN)


#define KEY_SENSE 5



void kb_ini(void);
uint8_t read_keyboard (void);
#endif


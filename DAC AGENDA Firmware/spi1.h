#ifndef __SPI1_H
#define __SPI1_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define CON() GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define COFF() GPIO_SetBits(GPIOA, GPIO_Pin_4)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void spi1_ini(void);
#endif

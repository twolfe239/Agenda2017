#include "stm32f10x.h"
#include "spi1.h"

void spi1_ini(void) {
		GPIO_InitTypeDef	CS;
		GPIO_InitTypeDef	uRCCSPI1;
		SPI_InitTypeDef		uSPI1;
		//------------------------------------------------------------------ RCC CS AD1955
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  CS.GPIO_Pin = GPIO_Pin_4;
  CS.GPIO_Mode = GPIO_Mode_Out_OD;
  CS.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &CS);
		//------------------------------------------------------------------ RCC SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);   
	uRCCSPI1.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	uRCCSPI1.GPIO_Mode = GPIO_Mode_AF_OD;
	uRCCSPI1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &uRCCSPI1);
		//------------------------------------------------------------------ SPI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	uSPI1.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	uSPI1.SPI_Mode = SPI_Mode_Master;
	uSPI1.SPI_DataSize = SPI_DataSize_16b;
	uSPI1.SPI_CPOL = SPI_CPOL_High;
	uSPI1.SPI_CPHA = SPI_CPHA_2Edge;
	uSPI1.SPI_NSS = SPI_NSS_Soft;
	uSPI1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	uSPI1.SPI_FirstBit = SPI_FirstBit_MSB;
	uSPI1.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &uSPI1);
	SPI_Cmd(SPI1, ENABLE); }

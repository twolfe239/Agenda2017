/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C1_H
#define __I2C1_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C_ByteWrite(uint8_t val, uint16_t WriteAddr);
uint8_t I2C_ByteRead( uint16_t ReadAddr);
void EEPWrite(uint8_t val, uint16_t WriteAddr);
uint8_t EEPRead( uint16_t ReadAddr);
void i2c1_ini(void);
uint8_t rtc_sec(void);
uint8_t rtc_min(void);
uint8_t rtc_hour(void);
uint8_t rtc_year(void);
uint8_t rtc_day(void);
uint8_t rtc_month(void);
#endif


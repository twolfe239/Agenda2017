#include "stm32f10x.h"
#include "i2c1.h"

#define RTC_adr 0xD0 //write
#define RTCeep_adr 0xAE
#define eep_adr 0xA0
#define HW_ADDRESS      0xD0
#define I2C_EE             I2C1//interface number


void i2c1_ini(void)
{
	GPIO_InitTypeDef uRCCI2C1;
	I2C_InitTypeDef uI2C1;
	//------------------------------------------------------------------ RCC I2C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);   
	uRCCI2C1.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	uRCCI2C1.GPIO_Mode = GPIO_Mode_AF_OD;
	uRCCI2C1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &uRCCI2C1);
	//------------------------------------------------------------------ I2C
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	uI2C1.I2C_ClockSpeed = 100000;
	uI2C1.I2C_Mode = I2C_Mode_I2C;
	uI2C1.I2C_DutyCycle = I2C_DutyCycle_16_9;
	uI2C1.I2C_OwnAddress1 = 1;
	uI2C1.I2C_Ack = I2C_Ack_Enable;
	uI2C1.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &uI2C1);
	I2C_Cmd(I2C1, ENABLE);
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}

uint8_t rtc_sec(void)
{	
uint8_t sec=0;
 sec = I2C_ByteRead(0x00);
  return sec;
}
uint8_t rtc_min(void)
{	
uint8_t min=0;
min = I2C_ByteRead(0x01);  
  return min;
}
uint8_t rtc_hour(void)
{	
uint8_t hour=0;
hour = I2C_ByteRead(0x02);
  return hour;
}
uint8_t rtc_day(void)
{	
uint8_t day=0;
day = I2C_ByteRead(0x04); 
  return day;
}
uint8_t rtc_month(void)
{	
uint8_t month=0;
month = I2C_ByteRead(0x05);
  return month;
}
uint8_t rtc_year(void)
{	
uint8_t year=0;
year = I2C_ByteRead(0x06);  
  return year;
}









void I2C_ByteWrite(uint8_t val, uint16_t WriteAddr)
{
    /* Send START condition */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C_EE, HW_ADDRESS, I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the EEPROM's internal address to write to : MSB of the address first */
 //   I2C_SendData(I2C_EE, (uint8_t)((WriteAddr & 0xFF00) >> 8));
    /* Test on EV8 and clear it */
  //  while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send the EEPROM's internal address to write to : LSB of the address */
    I2C_SendData(I2C_EE, (uint8_t)(WriteAddr & 0x00FF));
    /* Test on EV8 and clear it */
    while(! I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
     I2C_SendData(I2C_EE, val);
        /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C_EE, ENABLE);
    //delay between write and read...not less 4ms
    delay_ms(5);
}
//*********************************************************************************
uint8_t I2C_ByteRead( uint16_t ReadAddr)
{
    uint8_t tmp;
	/* While the bus is busy */
    while(I2C_GetFlagStatus(I2C_EE, I2C_FLAG_BUSY));
    /* Send START condition */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C_EE, HW_ADDRESS, I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the EEPROM's internal address to read from: MSB of the address first */
//    I2C_SendData(I2C_EE, (uint8_t)((ReadAddr & 0xFF00) >> 8));
    /* Test on EV8 and clear it */
//    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send the EEPROM's internal address to read from: LSB of the address */
    I2C_SendData(I2C_EE, (uint8_t)(ReadAddr & 0x00FF));
    /* Test on EV8 and clear it */
   while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send STRAT condition a second time */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for read */
    I2C_Send7bitAddress(I2C_EE, HW_ADDRESS, I2C_Direction_Receiver);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE,I2C_EVENT_MASTER_BYTE_RECEIVED));//I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    tmp=I2C_ReceiveData(I2C_EE);
    I2C_AcknowledgeConfig(I2C_EE, DISABLE);
    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C_EE, ENABLE);
	delay_ms(5);
    return tmp;
    }


uint8_t EEPRead( uint16_t ReadAddr)
{
    uint8_t tmp1;
	/* While the bus is busy */
    while(I2C_GetFlagStatus(I2C_EE, I2C_FLAG_BUSY));
    /* Send START condition */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C_EE, eep_adr, I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the EEPROM's internal address to read from: MSB of the address first */
//    I2C_SendData(I2C_EE, (uint8_t)((ReadAddr & 0xFF00) >> 8));
    /* Test on EV8 and clear it */
//    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send the EEPROM's internal address to read from: LSB of the address */
    I2C_SendData(I2C_EE, (uint8_t)(ReadAddr & 0x00FF));
    /* Test on EV8 and clear it */
   while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send STRAT condition a second time */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for read */
    I2C_Send7bitAddress(I2C_EE, eep_adr, I2C_Direction_Receiver);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE,I2C_EVENT_MASTER_BYTE_RECEIVED));//I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    tmp1=I2C_ReceiveData(I2C_EE);
    I2C_AcknowledgeConfig(I2C_EE, DISABLE);
    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C_EE, ENABLE);
	delay_ms(5);
    return tmp1;
    }

void EEPWrite(uint8_t val, uint16_t WriteAddr)
{
    /* Send START condition */
    I2C_GenerateSTART(I2C_EE, ENABLE);
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C_EE, eep_adr, I2C_Direction_Transmitter);
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the EEPROM's internal address to write to : MSB of the address first */
 //   I2C_SendData(I2C_EE, (uint8_t)((WriteAddr & 0xFF00) >> 8));
    /* Test on EV8 and clear it */
  //  while(!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send the EEPROM's internal address to write to : LSB of the address */
    I2C_SendData(I2C_EE, (uint8_t)(WriteAddr & 0x00FF));
    /* Test on EV8 and clear it */
    while(! I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
     I2C_SendData(I2C_EE, val);
        /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C_EE, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C_EE, ENABLE);
    //delay between write and read...not less 4ms
    delay_ms(5);
}


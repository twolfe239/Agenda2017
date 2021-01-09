
#include "RTC3231.h"


	uint32_t sec, min,hour, wday, day, month, year, t1, t2;

void RTC_init(void){
	I2C_ByteWrite(0x20, 0x0E, RTC_adr); //tempeeature on 1hz
	I2C_ByteWrite(0x08, 0x0F, RTC_adr); //out 32 khz
}


void RTC_write_time(uint32_t hour,uint32_t  min, uint32_t sec){
	I2C_ByteWrite(hour, 0x02, RTC_adr);
	I2C_ByteWrite(min, 0x01, RTC_adr);	
	I2C_ByteWrite(sec, 0x00, RTC_adr);	

}

void RTC_write_date(uint32_t wday, uint32_t day, uint32_t month, uint32_t year){
	I2C_ByteWrite(wday, 0x03, RTC_adr);
	I2C_ByteWrite(day, 0x04, RTC_adr);	
	I2C_ByteWrite(month, 0x05, RTC_adr);
	I2C_ByteWrite(year, 0x06, RTC_adr);	
}

void RTC_read(void){
	sec = I2C_ByteRead(0x00,RTC_adr);
	min = I2C_ByteRead(0x01,RTC_adr);
	hour = I2C_ByteRead(0x02,RTC_adr);
	wday = I2C_ByteRead(0x03,RTC_adr);
	day = I2C_ByteRead(0x04,RTC_adr);
	month = I2C_ByteRead(0x05,RTC_adr);
	year = I2C_ByteRead(0x06,RTC_adr);
	t1 = I2C_ByteRead(0x11,RTC_adr);
	t2 = I2C_ByteRead(0x12,RTC_adr);	
	t2=(t2/128);
	t2=t2*5;
}

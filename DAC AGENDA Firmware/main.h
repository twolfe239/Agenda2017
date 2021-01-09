/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "kb.h"
#include "i2c1.h"
#include "i2c_lcd.h"
/* Exported types ------------------------------------------------------------*/
uint8_t sample70 = 0x00;
uint8_t bitrate71 = 0x00;
uint8_t mute72 = 0x00;
uint8_t input73 = 0x00;
uint8_t CODA = 0x00;
uint8_t menu = 0;	
uint8_t menuend = 0;
uint32_t timer_menu;
uint16_t AD1955SETTINGS = 0x00;
uint16_t LSET = 0x00;
uint16_t LLSET = 0x00;
uint16_t LLLSET = 0x00;
uint8_t buf[20];
uint8_t buf1[20];
uint8_t buf2[20];
uint8_t min, hour, day, year, month, sec;
uint16_t delay_count=0;
uint8_t key_num = 0;
uint8_t chsr = 0;
uint8_t chic = 0;
uint8_t chmm = 0;
uint8_t chbr = 0;
uint8_t chtime = 0;
/* Exported constants --------------------------------------------------------*/
#define RSTOFF() GPIO_SetBits(GPIOA, GPIO_Pin_3) //CS8413 rst PIN
#define RSTON() GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define ROFF() GPIO_SetBits(GPIOA, GPIO_Pin_2) //relay PIN
#define RON() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define FS128() GPIO_SetBits(GPIOA, GPIO_Pin_8)  //FS PIN
#define FS256() GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define Sample48 0
#define Sample96 1
#define Sample192 2
#define INP1 0
#define INP2 1
#define INP3 2
#define INP4 3
#define delaymenu 18
#define SEL0_1() GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define SEL0_0() GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define SEL1_1() GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define SEL1_0() GPIO_ResetBits(GPIOA, GPIO_Pin_10)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void time_main(void) {
sec = rtc_sec();
min = rtc_min();
hour = rtc_hour();
year = rtc_year();
day = rtc_day();
month = rtc_month();
lcd_Goto(0, 12);
sprintf(buf1,"%02x.%02x.%02x", day, month,year);
lcd_PrintC((uint8_t *)buf1);
lcd_Goto(1, 12);
sprintf(buf,"%02x:%02x:%02x", hour,min,sec);
lcd_PrintC((uint8_t *)buf);	
}
void SysTick_Handler(void) {
	if (delay_count > 0) { delay_count--; }
	key_num = read_keyboard();}
void delay_ms(uint16_t delay_temp) { delay_count = delay_temp; while(delay_count){} }
void ctrl_pin_ini(void) {
	GPIO_InitTypeDef				ctrl;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  ctrl.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  ctrl.GPIO_Mode = GPIO_Mode_Out_PP;
  ctrl.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &ctrl);
}
void status_main_lcd(void) {
	   switch(chic) {
      case 0 :
		lcd_Goto(2, 0);
		lcd_PrintC("S/PDIF 1  ");		
         break;
      case 1 :
		lcd_Goto(2, 0);
		lcd_PrintC("S/PDIF 2  ");				
         break;
      case 2 :
		lcd_Goto(2, 0);
		lcd_PrintC("USB       ");				
         break;
	case 3 :
		lcd_Goto(2, 0);
		lcd_PrintC("TOSLINK   ");			
         break;
    default :
    break;
   }	 
	    switch(chsr) {
      case 0 :
		lcd_Goto(3, 0);
		lcd_PrintC("48000 Hz  ");		
         break;
      case 1 :
		lcd_Goto(3, 0);
		lcd_PrintC("96000 Hz  ");				
         break;
      case 2 :
		lcd_Goto(3, 0);
		lcd_PrintC("192000 Hz ");				
         break;
    default :
    break;
   }	 
   switch(chmm) {
      case 0 :
		lcd_Goto(2, 11);
		lcd_PrintC("PLAY");		
         break;
      case 1 :
		lcd_Goto(2, 11);
		lcd_PrintC("MUTE");				
         break;
    default :
    break;
   }	 
   switch(chbr) {
      case 0 :
		lcd_Goto(3, 11);
		lcd_PrintC("24 BIT");		
         break;
      case 1 :
		lcd_Goto(3, 11);
		lcd_PrintC("16 BIT");				
         break;
    default :
    break;
   }
}

void key_to_menu(void) {
	switch(key_num) {
      case 1 :
			menu = 1;
         break;
      case 2 :
			menu = 2;	
         break;
      case 3 :
			menu = 3;	
         break;
      case 4 :
			menu = 4;	
         break;
      case 5 :
			menu = 5;	
         break;
      case 6 :
			menu = 6;	
         break;
    default :
    break;
   }	 
 }
 void time_standby(void) {
sec = rtc_sec();
min = rtc_min();
hour = rtc_hour();
year = rtc_year();
day = rtc_day();
month = rtc_month();			
lcd_Goto(2, 6);
sprintf(buf,"%02x:%02x:%02x", hour,min,sec);
lcd_PrintC((uint8_t *)buf);	
lcd_Goto(1, 6);
sprintf(buf1,"%02x.%02x.%02x", day, month,year);
lcd_PrintC((uint8_t *)buf1);	
 }
 void rst_cs8416(void) {
		delay_ms(10);
	 RSTON();
	 delay_ms(10);
	 RSTOFF(); 
 }
#endif /* __MAIN_H */

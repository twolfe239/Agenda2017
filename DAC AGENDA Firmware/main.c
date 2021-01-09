#include "stm32f10x.h"
#include "main.h"
#include "i2c_lcd.h"
#include "i2c1.h"
#include "kb.h"
#include "spi1.h"
int main(void)
{

	//------------------------------------------------------------------ SysTick def
SysTick_Config(SystemCoreClock/1000); //1ms
	//------------------------------------------------------------------ Init forms
		ctrl_pin_ini();
		ROFF();
		i2c1_ini();
		lcd_Init();
    kb_ini();
    spi1_ini();
		lcd_Clear();	
		delay_ms(100);
		RON();
		delay_ms(500);
rst_cs8416();
	//------------------------------------------------------------------ READ SETTING FROM EEPROM			 
sample70 = EEPRead(0x70);
bitrate71 = EEPRead(0x71);
mute72 = EEPRead(0x72);
input73 = EEPRead(0x73);
CODA = EEPRead(0x03);
if (CODA == 0xEF) {
if ((sample70 > 0x02) || (bitrate71 > 0x01) || (mute72 > 0x01) || (input73 > 0x03)) {
EEPWrite(0x00, 0x70);
EEPWrite(0x00, 0x71);
EEPWrite(0x00, 0x72);
EEPWrite(0x00, 0x73);
	AD1955SETTINGS = 0x00;
	CON();
	SPI_I2S_SendData(SPI1, AD1955SETTINGS);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	COFF();
	FS256();
	SEL1_0();
	SEL0_0();
rst_cs8416();
} //end ifa more 0x04
else 
{
//(CODA GOOD) AND (70/71/72/73 GOOD) -> SET SETTINGS
//////////////////////////////SET SAMPLE RATE
	   switch(sample70) {
      case 0x00 :
AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x00);
chsr = Sample48;
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
 FS256();
rst_cs8416();
LSET = 0x0;
         break;
      case 0x01 :
		chsr = Sample96;
	 AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x100);			
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	FS256();
rst_cs8416();
LSET = 0x100;	
         break;
      case 0x02 :
chsr = Sample192;
AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x200);
CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
COFF();
FS128();
rst_cs8416();
LSET = 0x200;			
         break;
    default :
    break;
   }
//////////////////////////////SET BITRATE  
   switch(bitrate71) {
      case 0x00 :
chbr = 0;
	 	AD1955SETTINGS = ((AD1955SETTINGS  - LLLSET) + 0x00);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
 LLLSET = 0x0;					
         break;
      case 0x01 :
chbr = 1;
	AD1955SETTINGS = ((AD1955SETTINGS  - LLLSET) + 0xC);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
LLLSET = 0xC;				
         break;

    default :
    break;
   }	 
//////////////////////////////SET INPUT
   switch(input73) {
      case 0x00 :
chic = 0;
	SEL1_0();
	SEL0_0();			
         break;
      case 0x01 :
chic = 1;
	SEL1_1();
	SEL0_0();			
         break;
      case 0x02 :
chic = 2;	
	SEL1_0();
	SEL0_1();			
         break;
			case 0x03 :
chic = 3;	
	SEL0_1();
	SEL1_1();			
         break;
    default :
    break;
   }	 
//////////////////////////////SET MUTE  
   switch(mute72) {
      case 0x00 :
chmm = 0;
AD1955SETTINGS = ((AD1955SETTINGS  - LLSET) + 0x00);
CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
LLSET = 0x0;				
         break;
      case 0x01 :
chmm = 1;
AD1955SETTINGS = ((AD1955SETTINGS  - LLSET) + 0x4000);
CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
LLSET = 0x4000;					
         break;
    default :
    break;
   }	 
} // end else ifa more 0x04
} //end ifa EF po adr 0x03
else 
{
//OTHER EEPROM
AD1955SETTINGS = 0x00;
EEPWrite(0x00, 0x70);
EEPWrite(0x00, 0x71);
EEPWrite(0x00, 0x72);
EEPWrite(0x00, 0x73);
EEPWrite(CODA, 0x03);	
	CON();
	SPI_I2S_SendData(SPI1, AD1955SETTINGS);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
	COFF();
	FS256();
	SEL1_0();
	SEL0_0();
rst_cs8416();
} // end else ifa EF po adr 0x03
//I2C_ByteWrite(0x52, 0x01);
	//------------------------------------------------------------------ !!!MAIN WHILE!!!
  while (1)
  {
//-----------------------------------------------------------------------------------------------------MENU MAIN	
		if (menu == 0) {
		lcd_Goto(0, 0);
		lcd_PrintC("AGENDA");
		lcd_Goto(1, 0);
		lcd_PrintC("MAIN        ");
sample70 = EEPRead(0x70);
bitrate71 = EEPRead(0x71);
mute72 = EEPRead(0x72);
input73 = EEPRead(0x73);
CODA = EEPRead(0x03);
time_main();
status_main_lcd();
key_to_menu();
	}//menu 0 end
//-----------------------------------------------------------------------------------------------------MENU STAND BY
	else if (menu == 1)	{
		lcd_Clear();
		lcd_Goto(0, 0);
		lcd_PrintC("   Stand-by MODE.   ");
		delay_ms(300);
    while (menuend<1){
		ROFF(); //RELAY OFF
		time_standby();			
		if (key_num == 1) 
		{
			menuend = 2;	
			menu = 0;
			RON();
			delay_ms(500);
rst_cs8416();
		}		
		}//end while
	menuend = 0;	
	lcd_Clear();
}//menu 1 end
//-----------------------------------------------------------------------------------------------------MENU SAMPLE
	else if (menu == 2)	{
				timer_menu = 0;
				lcd_Clear();
				lcd_Goto(0, 0);
				lcd_PrintC("AGENDA");
				lcd_Goto(1, 0);
		lcd_PrintC("Sample Rate");
		while (menuend<1){
time_main();
		if (key_num == 2) 
		{
			timer_menu = 0; //reset timer_menu
		chsr = chsr + 1;
		if (chsr == 3) { chsr=0;} //if over then zero
		}
		if (chsr == Sample48) 
		{
		lcd_Goto(2, 0);
		lcd_PrintC("48000 Hz ");
		} 
		else if (chsr == Sample96) 
		{		
		lcd_Goto(2, 0);
		lcd_PrintC("96000 Hz ");
		} else { 		
		lcd_Goto(2, 0);
		lcd_PrintC("192000 Hz");}
timer_menu++;
if (timer_menu==delaymenu) {
menuend = 2;
menu = 0;
if (chsr == Sample48) 
		{
	 AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x00);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
 FS256();
rst_cs8416();
	 LSET = 0x0;			
	 EEPWrite(0x00, 0x70);
		} 
		else if (chsr == Sample96) 
		{	
	 AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x100);			

	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	FS256();
rst_cs8416();
	 	 	 LSET = 0x100;			
	 EEPWrite(0x01, 0x70);
		} 
		else	{ 		
			
	 AD1955SETTINGS = ((AD1955SETTINGS  - LSET) + 0x200);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
FS128();
rst_cs8416();
	 		 	 LSET = 0x200;		
	 EEPWrite(0x02, 0x70);
					}
		} //timer end
	}//end while
timer_menu = 0;	
menuend = 0;		
lcd_Clear();	
}//menu 2 end	
//-----------------------------------------------------------------------------------------------------MENU INPUT
	else if (menu == 3)	{
				timer_menu = 0;
				lcd_Clear();
				lcd_Goto(0, 0);
				lcd_PrintC("AGENDA");
				lcd_Goto(1, 0);
		lcd_PrintC("Input Ch.");
		while (menuend<1){
time_main();
		if (key_num == 3) 
		{
			timer_menu = 0; //reset timer_menu
		chic = chic + 1;
		if (chic == 4) { chic=0;} //if over then zero
		}
		if (chic == INP1) 
		{
		lcd_Goto(2, 0);
		lcd_PrintC("S/PDIF 1");
		} 
		else if (chic == INP2) 
		{		
		lcd_Goto(2, 0);
			lcd_PrintC("S/PDIF 2");
		} 
		else if (chic == INP3) 
		{		
		lcd_Goto(2, 0);
		lcd_PrintC("USB     ");
		} 
		else { 		
		lcd_Goto(2, 0);
		lcd_PrintC("TOSLINK ");}
timer_menu++;
if (timer_menu==delaymenu) {
menuend = 2;
menu = 0;
if (chic == INP1) 
		{			SEL1_0();	SEL0_0();
				 EEPWrite(0x00, 0x73);} 
		else if (chic == INP2) 
		{			SEL1_1();	SEL0_0();
				 EEPWrite(0x01, 0x73);} 
		else if (chic == INP3) 
		{			SEL1_0();	SEL0_1();
				 EEPWrite(0x02, 0x73);} 
		else	{ SEL0_1();	SEL1_1();
				 EEPWrite(0x03, 0x73);}
		} //timer end

	}//end while
menuend = 0;	
timer_menu = 0;	
lcd_Clear();	
}//menu 3 end			
//-----------------------------------------------------------------------------------------------------MENU MUTE
	else if (menu == 4)	{
						timer_menu = 0;
							lcd_Clear();
				lcd_Goto(0, 0);
				lcd_PrintC("AGENDA");
		lcd_Goto(1, 0);
		lcd_PrintC("Mute menu");	

		    while (menuend<1){

time_main();
		if (key_num == 4) 
		{
			timer_menu = 0; //reset timer_menu
		chmm = chmm + 1;
		if (chmm == 2) { chmm=0;} //if over then zero
		}
		if (chmm == 0) 
		{
		lcd_Goto(2, 0);
		lcd_PrintC("NORMAL MODE");
		} 
		else { 		
		lcd_Goto(2, 0);
		lcd_PrintC("MUTE MODE  ");}
timer_menu++;
if (timer_menu==delaymenu) {
menuend = 2;
menu = 0;
if (chmm == 0) 
		{
	 	AD1955SETTINGS = ((AD1955SETTINGS  - LLSET) + 0x00);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	 		 	 LLSET = 0x0;		
	 	 EEPWrite(0x00, 0x72);
		} 

		else	{ 		
	AD1955SETTINGS = ((AD1955SETTINGS  - LLSET) + 0x4000);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	 		 	 LLSET = 0x4000;		
	 	 EEPWrite(0x01, 0x72);
					}
		} //timer end

	}//end while
menuend = 0;	
timer_menu = 0;	
lcd_Clear();			
  } //menu 4 end
//-----------------------------------------------------------------------------------------------------MENU BIT
	else if (menu == 5) {
					lcd_Clear();
				timer_menu = 0;
		
		lcd_Goto(0, 0);
		lcd_PrintC("AGENDA");
		lcd_Goto(1, 0);
		lcd_PrintC("Bit Rate");
		
while (menuend<1){


time_main();
		if (key_num == 5) 
		{
			timer_menu = 0; //reset timer_menu
		chbr = chbr + 1;
		if (chbr == 2) { chbr=0;} //if over then zero
		}
		if (chbr == 0) 
		{
		lcd_Goto(2, 0);
			lcd_PrintC("Data Width: 24Bit");
		} 
		else { 		
		lcd_Goto(2, 0);
		lcd_PrintC("Data Width: 16Bit");}
timer_menu++;
if (timer_menu==delaymenu) {
menuend = 2;
menu = 0;
if (chbr == 0) 
		{
	 	AD1955SETTINGS = ((AD1955SETTINGS  - LLLSET) + 0x00);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	 		 	 LLLSET = 0x0;		
	  EEPWrite(0x00, 0x71);
		} 

		else	{ 		
	AD1955SETTINGS = ((AD1955SETTINGS  - LLLSET) + 0xC);
	CON();
SPI_I2S_SendData(SPI1, AD1955SETTINGS);
 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {}
 COFF();
	 		 	 LLLSET = 0xC;		
	 	  EEPWrite(0x01, 0x71);
					}
		} //timer end

	}//end while
menuend = 0;	
timer_menu = 0;	
lcd_Clear();			
	}//menu 5 end
	//-----------------------------------------------------------------------------------------------------TIME
	else  {
				timer_menu = 0;
				lcd_Clear();
				lcd_Goto(0, 0);
		while (menuend<1){
time_main();
timer_menu++;
if (timer_menu==delaymenu) {
menuend = 2;
menu = 0;
hour = hour + 1;
if (hour > 0x23) {I2C_ByteWrite(0x00, 0x02);} else {
if (hour == 0x0a) {I2C_ByteWrite(0x10, 0x02);} else  {
if (hour == 0x1a) {I2C_ByteWrite(0x20, 0x02);} else  {
I2C_ByteWrite(hour, 0x02);}}}
} //timer end

	lcd_Goto(3, 0);
	sprintf(buf2,"%d>", timer_menu);
	lcd_PrintC((uint8_t *)buf2);		
	}//end while
menuend = 0;	
timer_menu = 0;	
lcd_Clear();	

}//menu 6 end
}//main end
}//total end

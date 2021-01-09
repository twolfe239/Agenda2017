#include "stm32f10x.h"
#include "kb.h"
uint8_t Key_Count=0;
uint8_t Key_Input[3][2] = {0};
uint8_t Key_Input_Filter[3][2] = {0};
uint8_t Key_Input_Count[3][2] = {0};



void kb_ini(void) {
	GPIO_InitTypeDef				kbtd;
	B0_RCC_FUNC(B0_RCC, ENABLE);
  kbtd.GPIO_Pin = B0_PIN;
  kbtd.GPIO_Mode = GPIO_Mode_Out_PP;
  kbtd.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(B0_PORT, &kbtd);
	
	B1_RCC_FUNC(B1_RCC, ENABLE);
  kbtd.GPIO_Pin = B1_PIN;
  kbtd.GPIO_Mode = GPIO_Mode_Out_PP;
  kbtd.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(B0_PORT, &kbtd);
	
	B2_RCC_FUNC(B2_RCC, ENABLE);
  kbtd.GPIO_Pin = B2_PIN;
  kbtd.GPIO_Mode = GPIO_Mode_Out_PP;
  kbtd.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(B0_PORT, &kbtd);
	
	
	C0_RCC_FUNC(C0_RCC, ENABLE);
  kbtd.GPIO_Pin = C0_PIN;
  kbtd.GPIO_Mode = GPIO_Mode_IPD;
  kbtd.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(B0_PORT, &kbtd);
	
	C1_RCC_FUNC(C1_RCC, ENABLE);
  kbtd.GPIO_Pin = C1_PIN;
  kbtd.GPIO_Mode = GPIO_Mode_IPD;
  kbtd.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(B0_PORT, &kbtd);
}
void ChPins (void) {
	Key_Count = (Key_Count+1)%3;
	if (Key_Count == 0) 
{ //green 
	B0_HIGH;
	B1_LOW;
	B2_LOW;
} 
else 	if (Key_Count == 1) 
{ //yellow
	B1_HIGH;
	B0_LOW;
	B2_LOW;
} 
else 	
{//nebeski
	B2_HIGH;
	B1_LOW;
	B0_LOW;
}
}
void kb_read(void) {
Key_Input[Key_Count][0] = C0_INP;
Key_Input[Key_Count][1] = C1_INP;
}

void kb_one_filter(uint8_t x, uint8_t y) {
if 	(Key_Input[x][y]==1) {
if 	(Key_Input_Count[x][y] < KEY_SENSE)	
{
	Key_Input_Count[x][y]++;
} else {Key_Input_Filter[x][y] = 1;}
}else if 	(Key_Input_Count[x][y] > 0 )	
{
	Key_Input_Count[x][y]--;
} else {Key_Input_Filter[x][y] = 0;}

} 

void all_buttons_filter (void) {

uint8_t i, j;
	for (i = 0 ; i<3; i++)
	{
			for (j = 0 ; j<2; j++)
	{
		kb_one_filter(i,j);
	}
	}

}

uint8_t read_button(void) {



uint8_t i, j, k=0;
	for (i = 0 ; i<3; i++)
	{
	for (j = 0 ; j<2; j++)
	{
k++;
if (Key_Input_Filter[i][j] == 1)
{
return k;
}
	}
	}
return 0;
}
uint8_t read_keyboard (void)
{
	uint8_t kb_answer=0;
kb_read();
	if (Key_Count==2) {all_buttons_filter();}
ChPins();
	kb_answer = read_button();
	return kb_answer;
}


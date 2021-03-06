#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

#include "../APP/app_cfg.h"

//#ifndef UC_GUI_SURRPORT

#define uint unsigned int
#define uchar unsinged char

#define LCD_RST_PIN    GPIO_Pin_8	 //RST 对应单片机引脚定义 P3^2 / 对应STM32的 PA8

#define LCD_WR_PIN     GPIO_Pin_2	 //WR  对应单片机引脚定义 P2^5 / 对应STM32的 PB2
#define LCD_RS_PIN     GPIO_Pin_1	 //RD  对应单片机引脚定义 P2^6 / 对应STM32的 PB1
#define LCD_CS_PIN     GPIO_Pin_0	 //CS  对应单片机引脚定义 P2^7 / 对应STM32的 PB0

#define LCD_DB17_PIN   GPIO_Pin_12   //DB17	 对应单片机引脚定义 P3^4 / 对应STM32的 PA12
#define LCD_DB16_PIN   GPIO_Pin_11   //DB16	 对应单片机引脚定义 P3^3 / 对应STM32的 PA11

#define    LCD_RST(x)  x ? GPIO_SetBits(GPIOA, LCD_RST_PIN):   GPIO_ResetBits(GPIOA, LCD_RST_PIN) //自己定义位操作函数

#define    LCD_WR(x)   x ? GPIO_SetBits(GPIOB, LCD_WR_PIN) :   GPIO_ResetBits(GPIOB, LCD_WR_PIN)
#define    LCD_RS(x)   x ? GPIO_SetBits(GPIOB, LCD_RS_PIN) :   GPIO_ResetBits(GPIOB, LCD_RS_PIN)
#define    LCD_CS(x)   x ? GPIO_SetBits(GPIOB, LCD_CS_PIN) :   GPIO_ResetBits(GPIOB, LCD_CS_PIN)

#define    LCD_DB17(x)   x ? GPIO_SetBits(GPIOA, LCD_DB17_PIN) :   GPIO_ResetBits(GPIOA, LCD_DB17_PIN)
#define    LCD_DB16(x)   x ? GPIO_SetBits(GPIOA, LCD_DB16_PIN) :   GPIO_ResetBits(GPIOA, LCD_DB16_PIN)
#define  LCD_SIZE_X		320
#define  LCD_SIZE_Y		480

extern  uint colors[];

void Drv_LCD_Init(void);
void Drv_LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p);
void Drv_LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch);
void Drv_ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c);
static void Drv_delayms(int count) ;
void Drv_LCD_Write_DATA18(char x,char y ,char VH,char VL);
void Drv_LCD_Writ_Bus(char VH,char VL);
void Drv_LCD_Writ_Bus(char VH,char VL);
void Drv_LCD_Write_COM(char VH,char VL);
void Drv_LCD_Write_DATA(char VH,char VL);
void Drv_LCD_Write_COLOR(char V1,char V2,char V3);
void Drv_Pant(char VH,char VL);
void Drv_Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);


void Drv_LCD_SetPixel(uint x, uint y, uint color);
uint Drv_LCD_GetPixel(uint x, uint y);

//#endif//UC_GUI_SURRPORT


#endif//__LCD_DRIVER_H__



#ifndef __ILI_9486_H__
#define __ILI_9486_H__


#include "../APP/app_cfg.h"


typedef unsigned int uint ;
typedef unsigned char uchar;

#define ILI9486_RST_PIN    GPIO_Pin_8	 //RST 对应单片机引脚定义 P3^2 / 对应STM32的 PA8

#define ILI9486_WR_PIN     GPIO_Pin_2	 //WR  对应单片机引脚定义 P2^5 / 对应STM32的 PB2
#define ILI9486_RS_PIN     GPIO_Pin_1	 //RD  对应单片机引脚定义 P2^6 / 对应STM32的 PB1
#define ILI9486_CS_PIN     GPIO_Pin_0	 //CS  对应单片机引脚定义 P2^7 / 对应STM32的 PB0

#define ILI9486_DB17_PIN   GPIO_Pin_12   //DB17	 对应单片机引脚定义 P3^4 / 对应STM32的 PA12
#define ILI9486_DB16_PIN   GPIO_Pin_11   //DB16	 对应单片机引脚定义 P3^3 / 对应STM32的 PA11

#define    ILI9486_RST(x)  x ? GPIO_SetBits(GPIOA, ILI9486_RST_PIN):   GPIO_ResetBits(GPIOA, ILI9486_RST_PIN) //自己定义位操作函数

#define    ILI9486_WR(x)   x ? GPIO_SetBits(GPIOB, ILI9486_WR_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_WR_PIN)
#define    ILI9486_RS(x)   x ? GPIO_SetBits(GPIOB, ILI9486_RS_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_RS_PIN)
#define    ILI9486_CS(x)   x ? GPIO_SetBits(GPIOB, ILI9486_CS_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_CS_PIN)

#define    ILI9486_DB17(x)   x ? GPIO_SetBits(GPIOA, ILI9486_DB17_PIN) :   GPIO_ResetBits(GPIOA, ILI9486_DB17_PIN)
#define    ILI9486_DB16(x)   x ? GPIO_SetBits(GPIOA, ILI9486_DB16_PIN) :   GPIO_ResetBits(GPIOA, ILI9486_DB16_PIN)

#define    ILI9486_SIZE_X		320
#define    ILI9486_SIZE_Y		480



void ili9486_Initializtion(void);


/**
 * 画点
*/
void ili9486_SetPixel(uint x, uint y, uint color);
uint ili9486_GetPixel(uint x, uint y);

/**
 * 画线
*/
void ili9486_DrawHLine(uint x0 , uint Ypos ,uint x1 , uint color);
void ili9486_DrawVLine(uint Xpos, uint y0, uint y1 , uint color);


/**
 * 画图
*/
void ili9486_DrawBitmap(uint x0, uint y0, uint xSize, uint ySize, uchar * pImage);


/**
* 名    称：static void ili9486_WriteBus(uchar valueH ,uchar valueL );
* 功    能：写 ili8486 总线(spi)
* 入口参数：valueH 写入数据高8位 , valueL 写入数据低8位
* 出口参数：无
*
*/
static void ili9486_WriteBus(uchar valueH ,uchar valueL );


/**
* 名    称：void ili9486_SendCmd(uint regIndex)
* 功    能：ili8486 寄存器 regIndex 选择
* 入口参数：regIndex 寄存器地址
* 出口参数：无
*
*/
static void ili9486_WriteReg(uint regIndex);

/**
* 名    称：static void ili9486_WriteData(uint value);
* 功    能：向 ili8486 发送数据
* 入口参数：value 发送的值
* 出口参数：无
*
*/
static void ili9486_WriteData(uint value);


/**
* 名    称：static uint ili9486_ReadData(void);
* 功    能：从 ili8486 发送数据
* 入口参数：
* 出口参数：无
* 返回值:  读到的数据
*/
//static uint ili9486_ReadData(void);

/**
 *  打开写 gram
*/
static void ili9486_GRAMWrite(void);

static void ili9486_GRAMRead(void);

/**
 * 指定图片显示位置
*/
static void ili9486_SetDispArea(uint Xpos1,uint Ypos1,uint Xpos2,uint Ypos2);

static void ili9486_SetCursor(uint Xpos, uint Ypos);

static void ili9486_Delayms(uint nCount);


#endif//__ILI_9486_H__



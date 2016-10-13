
#ifndef __ILI_9486_H__
#define __ILI_9486_H__


#include "../APP/app_cfg.h"


typedef unsigned int uint ;
typedef unsigned char uchar;

#define ILI9486_RST_PIN    GPIO_Pin_8	 //RST ��Ӧ��Ƭ�����Ŷ��� P3^2 / ��ӦSTM32�� PA8

#define ILI9486_WR_PIN     GPIO_Pin_2	 //WR  ��Ӧ��Ƭ�����Ŷ��� P2^5 / ��ӦSTM32�� PB2
#define ILI9486_RS_PIN     GPIO_Pin_1	 //RD  ��Ӧ��Ƭ�����Ŷ��� P2^6 / ��ӦSTM32�� PB1
#define ILI9486_CS_PIN     GPIO_Pin_0	 //CS  ��Ӧ��Ƭ�����Ŷ��� P2^7 / ��ӦSTM32�� PB0

#define ILI9486_DB17_PIN   GPIO_Pin_12   //DB17	 ��Ӧ��Ƭ�����Ŷ��� P3^4 / ��ӦSTM32�� PA12
#define ILI9486_DB16_PIN   GPIO_Pin_11   //DB16	 ��Ӧ��Ƭ�����Ŷ��� P3^3 / ��ӦSTM32�� PA11

#define    ILI9486_RST(x)  x ? GPIO_SetBits(GPIOA, ILI9486_RST_PIN):   GPIO_ResetBits(GPIOA, ILI9486_RST_PIN) //�Լ�����λ��������

#define    ILI9486_WR(x)   x ? GPIO_SetBits(GPIOB, ILI9486_WR_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_WR_PIN)
#define    ILI9486_RS(x)   x ? GPIO_SetBits(GPIOB, ILI9486_RS_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_RS_PIN)
#define    ILI9486_CS(x)   x ? GPIO_SetBits(GPIOB, ILI9486_CS_PIN) :   GPIO_ResetBits(GPIOB, ILI9486_CS_PIN)

#define    ILI9486_DB17(x)   x ? GPIO_SetBits(GPIOA, ILI9486_DB17_PIN) :   GPIO_ResetBits(GPIOA, ILI9486_DB17_PIN)
#define    ILI9486_DB16(x)   x ? GPIO_SetBits(GPIOA, ILI9486_DB16_PIN) :   GPIO_ResetBits(GPIOA, ILI9486_DB16_PIN)

#define    ILI9486_SIZE_X		320
#define    ILI9486_SIZE_Y		480



void ili9486_Initializtion(void);


/**
 * ����
*/
void ili9486_SetPixel(uint x, uint y, uint color);
uint ili9486_GetPixel(uint x, uint y);

/**
 * ����
*/
void ili9486_DrawHLine(uint x0 , uint Ypos ,uint x1 , uint color);
void ili9486_DrawVLine(uint Xpos, uint y0, uint y1 , uint color);


/**
 * ��ͼ
*/
void ili9486_DrawBitmap(uint x0, uint y0, uint xSize, uint ySize, uchar * pImage);


/**
* ��    �ƣ�static void ili9486_WriteBus(uchar valueH ,uchar valueL );
* ��    �ܣ�д ili8486 ����(spi)
* ��ڲ�����valueH д�����ݸ�8λ , valueL д�����ݵ�8λ
* ���ڲ�������
*
*/
static void ili9486_WriteBus(uchar valueH ,uchar valueL );


/**
* ��    �ƣ�void ili9486_SendCmd(uint regIndex)
* ��    �ܣ�ili8486 �Ĵ��� regIndex ѡ��
* ��ڲ�����regIndex �Ĵ�����ַ
* ���ڲ�������
*
*/
static void ili9486_WriteReg(uint regIndex);

/**
* ��    �ƣ�static void ili9486_WriteData(uint value);
* ��    �ܣ��� ili8486 ��������
* ��ڲ�����value ���͵�ֵ
* ���ڲ�������
*
*/
static void ili9486_WriteData(uint value);


/**
* ��    �ƣ�static uint ili9486_ReadData(void);
* ��    �ܣ��� ili8486 ��������
* ��ڲ�����
* ���ڲ�������
* ����ֵ:  ����������
*/
//static uint ili9486_ReadData(void);

/**
 *  ��д gram
*/
static void ili9486_GRAMWrite(void);

static void ili9486_GRAMRead(void);

/**
 * ָ��ͼƬ��ʾλ��
*/
static void ili9486_SetDispArea(uint Xpos1,uint Ypos1,uint Xpos2,uint Ypos2);

static void ili9486_SetCursor(uint Xpos, uint Ypos);

static void ili9486_Delayms(uint nCount);


#endif//__ILI_9486_H__



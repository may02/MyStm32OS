

#include "ili9486_driver.h"
#include  "stm32f10x_conf.h"
#include "stm32f10x_lib.h"


static void ili9486_Delayms(uint nCount)
{
	int i, j;
	for (i = 0; i<nCount; i++)
		for (j = 0; j<5000; j++);
}

static void ili9486_WriteBus(uchar valueH ,uchar valueL )
{
	GPIOA->BSRR = valueH & 0x00ff;   	 
    GPIOA->BRR  = (~valueH) & 0x00ff;
	
    GPIOB->BSRR = (valueL<<8) & 0xff00;   	
    GPIOB->BRR  = (~(valueL)<<8) & 0xff00;
	
	ILI9486_WR(0);
	ILI9486_WR(1); 
	
}

static uint ili9486_ReadBus(void)
{
	//1. 将GPIO 口设置为输入
	uint tempA, tempB, temp;

	ILI9486_RS(0);
	ILI9486_RS(1); 
	
	tempA = GPIO_ReadInputData(GPIOA);
	tempB = GPIO_ReadInputData(GPIOB);
	
	temp = (tempB &0xff00) | (tempA & 0x00ff) ;
	
	return temp;
}

/**
 * 发送命令
*/
static void ili9486_WriteReg(uint regIndex)
{
	ILI9486_RS(0);
	
	ili9486_WriteBus(regIndex >> 8 , regIndex & 0xff);
	
}


/**
 * 发送数据
*/
static void ili9486_WriteData(uint value)
{
	ILI9486_RS(1);
	ili9486_WriteBus(value >> 8 , value & 0xff);	
}



/**
 * 打开写 gram
*/
static void ili9486_GRAMWrite()
{
	ili9486_WriteReg(0x002c);	
}

/**
 * 打开读 gram
*/
static void ili9486_GRAMRead(void)
{
	ili9486_WriteReg(0x002e);	
	
}

/**
 * 指定图片显示位置
*/
static void ili9486_SetDispArea(uint Xpos1, uint Ypos1, uint Xpos2, uint Ypos2)
{

	ili9486_WriteReg(0x002a);
	ili9486_WriteData(Xpos1 >> 8);	   //x1高位
	ili9486_WriteData(Xpos1 & 0x00ff);  //x1低位
	ili9486_WriteData(Xpos2 >> 8);	   //x2高位
	ili9486_WriteData(Xpos2 & 0x00ff);  //x2低位

	ili9486_WriteReg(0x002b);
	ili9486_WriteData(Ypos1 >> 8);       //y1高位        
	ili9486_WriteData(Ypos1 & 0x00ff);   //y1低位
	ili9486_WriteData(Ypos2 >> 8);       //y2高位        
	ili9486_WriteData(Ypos2 & 0x00ff);   //y2低位

	ili9486_WriteReg(0x003A);    // 16/18 bits
	ili9486_WriteData(0x0055);

}

static void ili9486_SetCursor(uint Xpos, uint Ypos)
{
	
	ili9486_WriteReg(0x002a);  
	ili9486_WriteData(Xpos >> 8);	   //x高位
	ili9486_WriteData(Xpos & 0x00ff);  //x低位

    ili9486_WriteReg(0x002b);       
	ili9486_WriteData(Ypos >> 8);       //y高位        
	ili9486_WriteData(Ypos & 0x00ff);   //y低位
		
    ili9486_WriteReg(0x003A);    // 16/18 bits
	ili9486_WriteData(0x0055);
	
}


void ili9486_Initializtion()
{
	ILI9486_RST(1);
	ili9486_Delayms(50);
	ILI9486_RST(0);
	ili9486_Delayms(50);
	ILI9486_RST(1);
	ili9486_Delayms(50);

	ILI9486_CS(0);  //打开片选使能


	ili9486_WriteReg(0x00F1);
	ili9486_WriteData(0x0036);
	ili9486_WriteData(0x0004);
    ili9486_WriteData(0x0000);
    ili9486_WriteData(0x003c);
	ili9486_WriteData(0x000f);
	ili9486_WriteData(0x008f);
    
    ili9486_WriteReg(0x00F2);
	ili9486_WriteData(0x0018);
	ili9486_WriteData(0x00a3);
	ili9486_WriteData(0x0012);
	ili9486_WriteData(0x0002);
	ili9486_WriteData(0x00b2);
	ili9486_WriteData(0x0012);
	ili9486_WriteData(0x00ff);
	ili9486_WriteData(0x0010);
	ili9486_WriteData(0x0000);
	
	ili9486_WriteReg(0x00F8);	
	ili9486_WriteData(0x0021);
	ili9486_WriteData(0x0004);
	
	ili9486_WriteReg(0x00F9);
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x0008);

	ili9486_WriteReg(0x00C0);
	ili9486_WriteData(0x0013);
	ili9486_WriteData(0x0010);
	
	ili9486_WriteReg(0x00C1);
	ili9486_WriteData(0x0043);
	ili9486_WriteData(0x0000);
		
	ili9486_WriteReg(0x00C2);
	ili9486_WriteData(0x0022);
	
	ili9486_WriteReg(0x00C5);
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x004d);
	ili9486_WriteData(0x0080);
	    
	ili9486_WriteReg(0x00B1);	
	ili9486_WriteData(0x00c0);
	ili9486_WriteData(0x0011);
    
	ili9486_WriteReg(0x00B4);		
	ili9486_WriteData(0x0001);
    
	ili9486_WriteReg(0x00B6);		
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x0042);
	ili9486_WriteData(0x003b);
    
//WriteComm(0xB7);
//WriteData(0x07);

	ili9486_WriteReg(0x00E0);	
	ili9486_WriteData(0x000f);
	ili9486_WriteData(0x001b);
	ili9486_WriteData(0x0019);
	ili9486_WriteData(0x000b);
	ili9486_WriteData(0x000f);
	ili9486_WriteData(0x000b);
	ili9486_WriteData(0x0046);
	ili9486_WriteData(0x00b9);
	ili9486_WriteData(0x0033);
	ili9486_WriteData(0x0008);
    ili9486_WriteData(0x0003);
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x0000);
	ili9486_WriteData(0x0000);
    
    ili9486_WriteReg(0x00E1);	
	ili9486_WriteData(0x000f);
	ili9486_WriteData(0x003f);
	ili9486_WriteData(0x003f);
	ili9486_WriteData(0x000f);
	ili9486_WriteData(0x001c);
	ili9486_WriteData(0x0007);
	ili9486_WriteData(0x004c);
	ili9486_WriteData(0x0074);
	ili9486_WriteData(0x0038);
	ili9486_WriteData(0x0007);
	ili9486_WriteData(0x0010);
	ili9486_WriteData(0x0004);
	ili9486_WriteData(0x0026);
	ili9486_WriteData(0x0024);
	ili9486_WriteData(0x0000);
    
	ili9486_WriteReg(0x0036);
	ili9486_WriteData(0x0008);
    
	ili9486_WriteReg(0x003A);
	ili9486_WriteData(0x0066);
    
	ili9486_WriteReg(0x0020);
	ili9486_WriteReg(0x0011);
	
    ili9486_Delayms(120);
	ili9486_WriteReg(0x0029);
	
	ILI9486_CS(1);  //关闭片选使能
}

void ili9486_SetPixel(uint x, uint y, uint color)
{
	ili9486_SetCursor(x , y);
	
	ili9486_GRAMWrite();	
	ili9486_WriteData(color);
		
}

uint ili9486_GetPixel(uint x, uint y)
{
	ili9486_SetCursor(x , y);
	ili9486_GRAMRead();
		
	return ili9486_ReadBus();	
}

/**
 * 横线
*/
void ili9486_DrawHLine(uint x0, uint Ypos, uint x1, uint color)
{
	u16 index = 0;
	if (x0 > x1)
	{
		ili9486_SetCursor(x1, Ypos);
		
		ili9486_GRAMWrite();
		for (index = x1; index < x0; index++) 
			ili9486_WriteData(color);
	}
	else if (x1 >= x0)
	{
		ili9486_SetCursor(x0, Ypos);

		ili9486_GRAMWrite();
		for (index = x0; index < x1; index++)
			ili9486_WriteData(color);

	}
}

/**
 * 竖线  ????
*/
void ili9486_DrawVLine(uint Xpos, uint y0, uint y1, uint color)
{
	u16 index = 0;
	if (y0 > y1)
	{
		ili9486_SetCursor(Xpos,y1);

		ili9486_GRAMWrite();
		for (index = y1; index < y0; index++)
			ili9486_WriteData(color);
	}
	else if (y1 >= y0)
	{
		ili9486_SetCursor(Xpos ,y0);

		ili9486_GRAMWrite();
		for (index = y0; index < y1; index++)
			ili9486_WriteData(color);

	}
}


void ili9486_DrawBitmap(uint x0, uint y0, uint xSize, uint ySize, uchar * pImage)
{
	uint j = 0 , Image = 0;
	
	ili9486_SetDispArea(x0, y0, x0 + xSize , y0 + ySize);
	
	ili9486_GRAMWrite();
	for (j = 0; j<33496 / 2; j++)	   //显示 60552个像素点
	{
		Image = pImage[j * 2 + 1] << 8 | pImage[j * 2];
		ili9486_WriteData(Image);
		
	}
}
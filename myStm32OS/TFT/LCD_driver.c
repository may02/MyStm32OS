#include "stm32f10x_lib.h"
#include"LCD_driver.h"
#include"chinese.h"
#include"char.h"

unsigned int colors[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff};  //颜色数据 

 
//#ifndef UC_GUI_SURRPORT

static void Drv_delayms(int count)  // /* X1ms */
{
	int i, j;
	for (i = 0; i<count; i++)
		for (j = 0; j<5000; j++);
}


void Drv_LCD_Init(void)
{

    LCD_RST(1);
	Drv_delayms(50);
	LCD_RST(0);
	Drv_delayms(50);
	LCD_RST(1);
	Drv_delayms(50);

	LCD_CS(0);  //打开片选使能


	Drv_LCD_Write_COM(0x00,0xF1);
    Drv_LCD_Write_DATA(0x00,0x36);
    Drv_LCD_Write_DATA(0x00,0x04);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x3C);
    Drv_LCD_Write_DATA(0x00,0x0F);
    Drv_LCD_Write_DATA(0x00,0x8F);

	Drv_LCD_Write_COM(0x00,0xF2);
    Drv_LCD_Write_DATA(0x00,0x18);
    Drv_LCD_Write_DATA(0x00,0xA3);
    Drv_LCD_Write_DATA(0x00,0x12);
    Drv_LCD_Write_DATA(0x00,0x02);
    Drv_LCD_Write_DATA(0x00,0xB2);//32
    Drv_LCD_Write_DATA(0x00,0x12);
    Drv_LCD_Write_DATA(0x00,0xFF);
    Drv_LCD_Write_DATA(0x00,0x10);
    Drv_LCD_Write_DATA(0x00,0x00);

	Drv_LCD_Write_COM(0x00,0xF8);
    Drv_LCD_Write_DATA(0x00,0x21);
    Drv_LCD_Write_DATA(0x00,0x04);


	Drv_LCD_Write_COM(0x00,0xF9);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x08);


	Drv_LCD_Write_COM(0x00,0xC0);
    Drv_LCD_Write_DATA(0x00,0x13);
    Drv_LCD_Write_DATA(0x00,0x10);

	Drv_LCD_Write_COM(0x00,0xC1);
    Drv_LCD_Write_DATA(0x00,0x43);
    Drv_LCD_Write_DATA(0x00,0x00);

	Drv_LCD_Write_COM(0x00,0xC2);
    Drv_LCD_Write_DATA(0x00,0x22);

	Drv_LCD_Write_COM(0x00,0xC5);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x4D);
    Drv_LCD_Write_DATA(0x00,0x80);

	Drv_LCD_Write_COM(0x00,0xB1);
    Drv_LCD_Write_DATA(0x00,0xC0);
    Drv_LCD_Write_DATA(0x00,0x11);

	Drv_LCD_Write_COM(0x00,0xB4);
    Drv_LCD_Write_DATA(0x00,0x01);//02,03

	Drv_LCD_Write_COM(0x00,0xB6);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x42);
    Drv_LCD_Write_DATA(0x00,0x3B);

//WriteComm(0xB7);
//WriteData(0x07);

	Drv_LCD_Write_COM(0x00,0xE0);
    Drv_LCD_Write_DATA(0x00,0x0F);
    Drv_LCD_Write_DATA(0x00,0x1B);
    Drv_LCD_Write_DATA(0x00,0x19);
    Drv_LCD_Write_DATA(0x00,0x0B);
    Drv_LCD_Write_DATA(0x00,0x0F);
    Drv_LCD_Write_DATA(0x00,0x08);
    Drv_LCD_Write_DATA(0x00,0x46);
    Drv_LCD_Write_DATA(0x00,0xB9);
    Drv_LCD_Write_DATA(0x00,0x33);
    Drv_LCD_Write_DATA(0x00,0x08);
    Drv_LCD_Write_DATA(0x00,0x03);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x00);
    Drv_LCD_Write_DATA(0x00,0x00);

	Drv_LCD_Write_COM(0x00,0xE1);
    Drv_LCD_Write_DATA(0x00,0x0F);
    Drv_LCD_Write_DATA(0x00,0x3F);
    Drv_LCD_Write_DATA(0x00,0x3F);
    Drv_LCD_Write_DATA(0x00,0x0F);
    Drv_LCD_Write_DATA(0x00,0x1C);
    Drv_LCD_Write_DATA(0x00,0x07);
    Drv_LCD_Write_DATA(0x00,0x4C);
    Drv_LCD_Write_DATA(0x00,0x74);
    Drv_LCD_Write_DATA(0x00,0x38);
    Drv_LCD_Write_DATA(0x00,0x07);
    Drv_LCD_Write_DATA(0x00,0x10);
    Drv_LCD_Write_DATA(0x00,0x04);
    Drv_LCD_Write_DATA(0x00,0x26);
    Drv_LCD_Write_DATA(0x00,0x24);
    Drv_LCD_Write_DATA(0x00,0x00);

	Drv_LCD_Write_COM(0x00,0x36);
    Drv_LCD_Write_DATA(0x00,0x08);//08

	Drv_LCD_Write_COM(0x00,0x3A);
    Drv_LCD_Write_DATA(0x00,0x66);//66

	Drv_LCD_Write_COM(0x00,0x20);
	Drv_LCD_Write_COM(0x00,0x11);
    Drv_delayms(120);
	Drv_LCD_Write_COM(0x00,0x29);


	LCD_CS(1);  //关闭片选使能

}  






void Drv_LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
    GPIOA->BSRR = VH & 0x00ff;   	 //高位P1口
    GPIOA->BRR  = (~VH) & 0x00ff;
    GPIOB->BSRR = (VL<<8) & 0xff00;   	 //低位P0口
    GPIOB->BRR  = (~(VL)<<8) & 0xff00;
	LCD_WR(0);
	LCD_WR(1); 
}



void Drv_LCD_Write_COM(char VH,char VL)	 //发送命令
{	
    LCD_RS(0);
	Drv_LCD_Writ_Bus(VH,VL);
}


void Drv_LCD_Write_DATA(char VH,char VL)	//发送数据
{
    LCD_RS(1);
	Drv_LCD_Writ_Bus(VH,VL);
}



void Drv_Pant(char VH,char VL)
{
	int i,j;
	LCD_CS(0);  //打开片选使能
	Drv_Address_set(0,0,319,479);
    for(i=0;i<480;i++)
	{
		for (j=0;j<320;j++)
	   	{
			Drv_LCD_Write_DATA(VH,VL);
	    }

	 }
     LCD_CS(1);  //关闭片选使能
}	

void Drv_Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{		
    Drv_LCD_Write_COM(0x00,0x2a);  
	Drv_LCD_Write_DATA(0x00,x1 >> 8);	 
	Drv_LCD_Write_DATA(0x00,x1);
	Drv_LCD_Write_DATA(0x00,x2 >> 8);
	Drv_LCD_Write_DATA(0x00,x2);

    Drv_LCD_Write_COM(0x00,0x2b);  
	Drv_LCD_Write_DATA(0x00,y1 >> 8);
	Drv_LCD_Write_DATA(0x00,y1);
	Drv_LCD_Write_DATA(0x00,y2 >> 8);
	Drv_LCD_Write_DATA(0x00,y2);

    Drv_LCD_Write_COM(0x00,0x3A);    // 16/18 bits
	Drv_LCD_Write_DATA(0x00,0x55);

	Drv_LCD_Write_COM(0x00,0x2c);
}



/**********************************************************

  写汉字子函数

**********************************************************/
void Drv_ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c)
{
   int e=0,i,j;
   int  ed;
   
   unsigned int  ncols;
   unsigned int  nrows;
   unsigned int  nbytes;

   unsigned char *pfont;
   unsigned char *pchar;
   unsigned char *fonttable[]={(unsigned char *)hz16,(unsigned char *)hz24 , (unsigned char *)hz32};
   
   pfont=(unsigned char *)fonttable[size];

   if(size==0)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;	 //(16*16)/8
   }
   else
   if(size==1)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;  //(24*24)/8
   }
   else
   if(size==2)
   {
     ncols =32-1;
     nrows =32-1;
     nbytes =132;   //(32*32)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   Drv_Address_set(x,  y, x+nrows,y+ncols);
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
		e=8;
     
     for(j=0;j<e;j++)
     {// unsigned char temp;
	  if((ed>>j)&0x01)
      { 
       	//temp = 	For_color&0x00ff
		  Drv_LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	  }
     else
     {
		 Drv_LCD_Write_DATA( Bk_color>>8 ,  Bk_color);  //backcolor
	 }
	}
  }
}

/*********************************************************/

/**********************************************************

  字符显示子函数

**********************************************************/
void Drv_LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch)
{       
   unsigned char temp , Bytes;
   unsigned char pos,t;
   unsigned int  CHAR_W,CHAR_H;

   
   //CHAR_W = 8;         //8*16
   //CHAR_H = 16;

     CHAR_W = 16;         //16*24
     CHAR_H = 24;

   if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
   return;
   
   Drv_Address_set(x, y, x+CHAR_W-1, y+CHAR_H-1);
   ch = ch-32;                       //按照ASCII编码顺序的到相应字母的编码
   Bytes = (CHAR_W*CHAR_H)/8;
   for(pos=0;pos<Bytes;pos++)  //CHAR_H 	(CHAR_W*CHAR_H)/8
   {
     // temp= Font8x16[ch][pos];

	  //temp= Font16x24[ch][pos];
	  temp= Font16x24[ch][pos];
      
      for(t=0;t<8;t++) //CHAR_W
      {                 
	    if(temp&0x80)
			Drv_LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	    else 
			Drv_LCD_Write_DATA(Bk_color>>8 , Bk_color );  //backcolor
        temp<<=1; 
      }
	  
   }
}  

/**********************************************************
 显示字符串子函数

 x,y:起点坐标  
 *p:字符串起始地址

**********************************************************/

void Drv_LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p)
{         
   while(*p!='\0')
   {       
	   Drv_LCD_ShowChar(x,y,For_color,Bk_color,*p);
    // x+=8;
	 x+=16;
     p++;
   }
}



/**
 * 功能: 在坐标x,y 处设置颜色 color
*/
void Drv_LCD_SetPixel(uint x, uint y, uint color)
{
	Drv_Address_set(x,y,x+1,y+1);

	Drv_LCD_Write_DATA(color >> 8, color);  
}

/**
 * 功能: 获取坐标 x,y 处得颜色值
*/
uint Drv_LCD_GetPixel(uint x, uint y)
{
	return 0;
}








//#endif//UC_GUI_SURRPORT



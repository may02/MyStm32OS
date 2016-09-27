#include "stm32f10x_lib.h"
#include"LCD_driver.h"
#include"chinese.h"
#include"char.h"

unsigned int colors[]={0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff};  //颜色数据 

 



void LCD_Init(void)
{

    LCD_RST(1);
    delayms(50);	
	LCD_RST(0);
	delayms(50);
	LCD_RST(1);
	delayms(50);

	LCD_CS(0);  //打开片选使能


	LCD_Write_COM(0x00,0xF1);
    LCD_Write_DATA(0x00,0x36);
    LCD_Write_DATA(0x00,0x04);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x3C);
    LCD_Write_DATA(0x00,0x0F);
    LCD_Write_DATA(0x00,0x8F);

	LCD_Write_COM(0x00,0xF2);
    LCD_Write_DATA(0x00,0x18);
    LCD_Write_DATA(0x00,0xA3);
    LCD_Write_DATA(0x00,0x12);
    LCD_Write_DATA(0x00,0x02);
    LCD_Write_DATA(0x00,0xB2);//32
    LCD_Write_DATA(0x00,0x12);
    LCD_Write_DATA(0x00,0xFF);
    LCD_Write_DATA(0x00,0x10);
    LCD_Write_DATA(0x00,0x00);

	LCD_Write_COM(0x00,0xF8);
    LCD_Write_DATA(0x00,0x21);
    LCD_Write_DATA(0x00,0x04);


	LCD_Write_COM(0x00,0xF9);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x08);


	LCD_Write_COM(0x00,0xC0);
    LCD_Write_DATA(0x00,0x13);
    LCD_Write_DATA(0x00,0x10);

	LCD_Write_COM(0x00,0xC1);
    LCD_Write_DATA(0x00,0x43);
    LCD_Write_DATA(0x00,0x00);

	LCD_Write_COM(0x00,0xC2);
    LCD_Write_DATA(0x00,0x22);

	LCD_Write_COM(0x00,0xC5);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x4D);
    LCD_Write_DATA(0x00,0x80);

	LCD_Write_COM(0x00,0xB1);
    LCD_Write_DATA(0x00,0xC0);
    LCD_Write_DATA(0x00,0x11);

	LCD_Write_COM(0x00,0xB4);
    LCD_Write_DATA(0x00,0x01);//02,03

	LCD_Write_COM(0x00,0xB6);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x42);
    LCD_Write_DATA(0x00,0x3B);

//WriteComm(0xB7);
//WriteData(0x07);

	LCD_Write_COM(0x00,0xE0);
    LCD_Write_DATA(0x00,0x0F);
    LCD_Write_DATA(0x00,0x1B);
    LCD_Write_DATA(0x00,0x19);
    LCD_Write_DATA(0x00,0x0B);
    LCD_Write_DATA(0x00,0x0F);
    LCD_Write_DATA(0x00,0x08);
    LCD_Write_DATA(0x00,0x46);
    LCD_Write_DATA(0x00,0xB9);
    LCD_Write_DATA(0x00,0x33);
    LCD_Write_DATA(0x00,0x08);
    LCD_Write_DATA(0x00,0x03);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x00);
    LCD_Write_DATA(0x00,0x00);

	LCD_Write_COM(0x00,0xE1);
    LCD_Write_DATA(0x00,0x0F);
    LCD_Write_DATA(0x00,0x3F);
    LCD_Write_DATA(0x00,0x3F);
    LCD_Write_DATA(0x00,0x0F);
    LCD_Write_DATA(0x00,0x1C);
    LCD_Write_DATA(0x00,0x07);
    LCD_Write_DATA(0x00,0x4C);
    LCD_Write_DATA(0x00,0x74);
    LCD_Write_DATA(0x00,0x38);
    LCD_Write_DATA(0x00,0x07);
    LCD_Write_DATA(0x00,0x10);
    LCD_Write_DATA(0x00,0x04);
    LCD_Write_DATA(0x00,0x26);
    LCD_Write_DATA(0x00,0x24);
    LCD_Write_DATA(0x00,0x00);

	LCD_Write_COM(0x00,0x36);
    LCD_Write_DATA(0x00,0x08);//08

	LCD_Write_COM(0x00,0x3A);
    LCD_Write_DATA(0x00,0x66);//66

	LCD_Write_COM(0x00,0x20);
	LCD_Write_COM(0x00,0x11);
    delayms(120);
	LCD_Write_COM(0x00,0x29);


	LCD_CS(1);  //关闭片选使能

}  



static void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<5000;j++);
}




void LCD_Writ_Bus(char VH,char VL)   //并行数据写入函数
{
    GPIOA->BSRR = VH & 0x00ff;   	 //高位P1口
    GPIOA->BRR  = (~VH) & 0x00ff;
    GPIOB->BSRR = (VL<<8) & 0xff00;   	 //低位P0口
    GPIOB->BRR  = (~(VL)<<8) & 0xff00;
	LCD_WR(0);
	LCD_WR(1); 
}



void LCD_Write_COM(char VH,char VL)	 //发送命令
{	
    LCD_RS(0);
	LCD_Writ_Bus(VH,VL);
}


void LCD_Write_DATA(char VH,char VL)	//发送数据
{
    LCD_RS(1);
	LCD_Writ_Bus(VH,VL);
}



void Pant(char VH,char VL)
{
	int i,j;
	LCD_CS(0);  //打开片选使能
	Address_set(0,0,319,479);
    for(i=0;i<480;i++)
	 {
	  for (j=0;j<320;j++)
	   	{
        	 LCD_Write_DATA(VH,VL);
	    }

	  }
     LCD_CS(1);  //关闭片选使能
}	

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	
	
    LCD_Write_COM(0x00,0x2a);  
	LCD_Write_DATA(0x00,x1 >> 8);	 
	LCD_Write_DATA(0x00,x1);
	LCD_Write_DATA(0x00,x2 >> 8);
	LCD_Write_DATA(0x00,x2);

    LCD_Write_COM(0x00,0x2b);  
	LCD_Write_DATA(0x00,y1 >> 8);
	LCD_Write_DATA(0x00,y1);
	LCD_Write_DATA(0x00,y2 >> 8);
	LCD_Write_DATA(0x00,y2);

    LCD_Write_COM(0x00,0x3A);    // 16/18 bits
	LCD_Write_DATA(0x00,0x55);

    LCD_Write_COM(0x00,0x2c);					 
}



/**********************************************************

  写汉字子函数

**********************************************************/
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c)
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

   Address_set(x,  y, x+nrows,y+ncols);
   
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
	   LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	  }
     else
     {
       LCD_Write_DATA( Bk_color>>8 ,  Bk_color);  //backcolor
	 }
	}
  }
}

/*********************************************************/

/**********************************************************

  字符显示子函数

**********************************************************/
void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch)
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
   
   Address_set(x, y, x+CHAR_W-1, y+CHAR_H-1);
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
	    LCD_Write_DATA(For_color>>8 , For_color  );  //textcolor
	    else 
	    LCD_Write_DATA(Bk_color>>8 , Bk_color );  //backcolor
        temp<<=1; 
      }
	  
   }
}  

/**********************************************************
 显示字符串子函数

 x,y:起点坐标  
 *p:字符串起始地址

**********************************************************/

void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p)
{         
   while(*p!='\0')
   {       
     LCD_ShowChar(x,y,For_color,Bk_color,*p);
    // x+=8;
	 x+=16;
     p++;
   } }

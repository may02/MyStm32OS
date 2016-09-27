 /*********************************************************************
*                                                                     *
*          STM32- 3.2��TFTҺ�����ַ��ͺ�����ʾ����                               *
*              ��  ���пƼ�  ��                                       *
        
***********************************************************************/

#include "stm32f10x_lib.h"
#include "LCD_driver.h"
#include "touch.h"
#include "math.h"
/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void delay_ms(int count);
 void draw_circle(int xc, int yc, int r, int fill) ;
 void _draw_circle_8(int xc, int yc, int x, int y) ;
u16 TP_X,TP_Y;
double sa,sb,sc;
/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{
	unsigned int lx,ly,temp_x = 0,temp_y = 0 ,flag = 0,banjinr,banjinx,banjiny;
	unsigned long i,j;
	char X[6] = {0,0,0,0,0,0,},Y[6]= {0,0,0,0,0,0,};
	u16  X_Addata,Y_Addata;
	char ss[6];
	int TchScr_Xmax=3859,TchScr_Xmin=26,
   	TchScr_Ymax=3842,TchScr_Ymin=38;//���������ص�ѹֵ��Χ
#ifdef DEBUG
	debug();
#endif

	RCC_Configuration();      //ϵͳʱ�����ú���   

	NVIC_Configuration();     //NVIC���ú���

    //����GPIOģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //�ѵ���������ͨIO��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
                            
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	 //����GPIOΪͬһ���Ͷ˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; // ѡ��PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //��©����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�

	GPIO_Write(GPIOA,0xffff);  //��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
	GPIO_Write(GPIOB,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�ƽ
	
   LCD_Init();
   Delay(150); 
   Pant( colors[2]>>8 ,  colors[2]);

    AD7843(CMD_RDX);
	AD7843(CMD_RDY);
   LCD_CS(0);
   ChineseChar(85,20,2,colors[5],colors[2],1);	//��
   ChineseChar(115,20,2,colors[5],colors[2],2);	//��
   ChineseChar(145,20,2,colors[5],colors[2],3);//��
   ChineseChar(175,20,2,colors[5],colors[2],4);	//��
   LCD_CS(1);

 /*   LCD_ShowString(0,90,colors[0],colors[5],"WWW.PRECHIN.com");
	LCD_ShowString(0,150,colors[7],colors[2],"www.PRECHIN.net");	   
    LCD_ShowString(12,180,colors[0],colors[7],"TELL:");
    LCD_ShowString(12,210,colors[2],colors[7],"0755-61190227");	
    LCD_ShowString(12,240,colors[2],colors[7],"abcdefJhiJKLMNOP"); 
    LCD_ShowString(12,265,colors[2],colors[7],"pqrstuvwxyz!@#$"); 
    LCD_ShowString(12,290,colors[2],colors[7],"<>CDEF^&*()/,[]"); 	 */
	while(1)	   
	{	
		 LCD_CS (0);  //��Ƭѡʹ��
		 if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))
		{		
			 Read_ADS2(&X_Addata,&Y_Addata);
			 inttostr(X_Addata,ss);
			 LCD_ShowString(0,445,0xf800,0xfff0,"X:");
             LCD_ShowString(32,445,0xf800,0xfff0,ss); //��ʾ�ַ��� 	
			
			 inttostr(Y_Addata,ss);
 		 	 LCD_ShowString(120,445,0xf800,0xfff0,"Y:");
             LCD_ShowString(152,445,0xf800,0xfff0,ss);  //��ʾ�ַ��� 	
	        
			//�Բ����������ת��
	    	//lx=(X_Addata)*LCDWIDTH/(TchScr_Xmax-TchScr_Xmin);
			
			j = X_Addata;
			j = j*310;
			i = TchScr_Xmax-TchScr_Xmin	;
	    	lx= j/i;
			if(lx >  320)  lx = 320;

			X[0] =	(lx%100000)/1000 + 0x30;
		    X[1] =	(lx%10000)/1000 + 0x30;
			X[2] =	(lx%1000)/100 + 0x30;
			X[3] =	(lx%100)/10 + 0x30;
			X[4] =	lx%10 + 0x30;
			LCD_ShowString(0,420,0xf800,0xfff0,"x:"); //��ʾLCD���ص�X����
		    LCD_ShowString(32,420,0xf800,0xfff0,X);  //��ʾ�ַ��� 	
			
		//	Y_Addata = 3634;
		    j = Y_Addata;
			j = (j*470);
			i = TchScr_Ymax-TchScr_Ymin;
			ly=j/i;
			if(ly >  480)  ly = 480;

		
			
			Y[0] =	(ly%100000)/10000 + 0x30;
			Y[1] =	(ly%10000)/1000 + 0x30;
			Y[2] =	(ly%1000)/100 + 0x30;
			Y[3] =	(ly%100)/10 + 0x30;
			Y[4] =	ly%10 + 0x30;
			LCD_ShowString(120,420,0xf800,0xfff0,"y:");//��ʾLCD���ص�Y����
			LCD_ShowString(152,420,0xf800,0xfff0,Y);  //��ʾ�ַ��� 	



				if(lx>temp_x) {	 banjinx= (lx-temp_x); }
			    if(lx<=temp_x) {  banjinx= (temp_x-lx);	}//Ϊ�����ӳ���ĸ����� ��ѡ����X��ĸı�ֵ ��Ϊ�뾶��Բ
				if(ly>temp_y) {	 banjiny= (ly-temp_y); }
			    if(ly<=temp_y) {  banjiny= (temp_y-ly);	}
				sa= (double)(banjinx);
				sb= (double)(banjiny);
				sc= (double)(banjinr);
				sc=sqrt(pow(sa,2)+pow(sb,2));
				banjinr= (unsigned int)(sc);
			 if (flag)
			 {
                draw_circle(temp_x,temp_y,banjinr,0);	//���û�Բ����  ���������� 0 Ϊ����Բ 1Ϊʵ��Բ
				flag = 0;
			 }

		   flag = 1;	
		   temp_x = lx;
		   temp_y = ly;

		}
		
		
	LCD_CS (1);  //�ر�Ƭѡʹ��	

   	 }
    
}	 

 void _draw_circle_8(int xc, int yc, int x, int y) 
{  

 

	 Address_set(xc + x,yc + y,xc + x+1,yc + y+1);
	 LCD_Write_DATA(0,255);   //���ص���Ϊ��ɫ

	Address_set(xc - x,yc + y,xc - x+1,yc + y+1);
    LCD_Write_DATA(0,255); // ���ص���Ϊ��ɫ

	 Address_set(xc + x,yc - y,xc + x+1,yc - y+1);
     LCD_Write_DATA(0,255); // ���ص���Ϊ��ɫ

	Address_set(xc - x,yc - y,xc - x+1,yc - y+1);
     LCD_Write_DATA(0,255); // ���ص���Ϊ��ɫ 

	Address_set(xc + y,yc + x ,xc + y+1,yc + x+1);
    LCD_Write_DATA(0,255); 	// ���ص���Ϊ��ɫ

	 Address_set(xc - y,yc + x,xc - y+1,yc + x+1);
     LCD_Write_DATA(0,255);	// ���ص���Ϊ��ɫ

	 Address_set(xc + y,yc - x,xc + y+1,yc - x+1);
	 LCD_Write_DATA(0,255);	// ���ص���Ϊ��ɫ

	 Address_set(xc - y,yc - x,xc - y+1,yc - x+1);
   	LCD_Write_DATA(0,255); // ���ص���Ϊ��ɫ

 }  

    

 //Bresenham's circle algorithm  
//Bresenham��Բ�㷨�ֳ��е㻭Բ�㷨,������ķ����������б�������ж�ѡ����������ص㣬
//�б��������ֵ������һЩ�ӡ�������λ����Ϳ��Լ��������Ϊ�˼�����������һ��Բ����
//����ԭ���Բ������ֻ����˷�Բ���ϵĵ㣬����Բ���ϵĵ����öԳ��ԾͿɵõ���

 void draw_circle(int xc, int yc, int r, int fill) 
 {  

    // (xc, yc) ΪԲ�ģ�r Ϊ�뾶  

     // fill Ϊ�Ƿ����  

    // c Ϊ��ɫֵ  
    


     int x = 0, y = r, d;  

     d = 3 - 2 * r;  

    

     if (!fill) {  


         // �������䣨������Բ��  

        while (x <= y) {  

             _draw_circle_8(xc, yc, x, y);  

    

             if (d < 0) {  

                d = d + 4 * x + 6;  

             } else {  

                 d = d + 4 * (x - y) + 10;  

                 y --;  

             }  

            x ++;  

         }  

     }  

 } 



/*******************************************************************************
*                           ����RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
	//��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //ʹ��PLLʱ��
    RCC_PLLCmd(ENABLE);

   //�ȴ�PLLʱ�Ӿ���
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //����ϵͳʱ�� = PLLʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //���PLLʱ���Ƿ���Ϊϵͳʱ��
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
*                             NVIC���ú���
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
*                              ��ʱ����
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}



#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

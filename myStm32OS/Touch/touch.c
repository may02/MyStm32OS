
#include "stm32f10x_lib.h"
#include "touch.h"

/**
* �Զ�����ʱ,����ucOS ����ʱ,��ֹ�����л�
*/

static void Delay(vu32 nCount)
{
	for (; nCount != 0; nCount--);
}

/**
 * ģ��spi ��ʼ
*/
static void SpiStart()                                     
{
	DCLK(0);
	Delay(100);
	CS(1);
	Delay(150); 
	DIN(1);
	Delay(100);
	DCLK(1);
	Delay(200);
	CS(0);
	Delay(150); 

}

static void SpiStop()
{
	/**
	 * �ر�Ƭѡ,���͹���
	*/
	CS(1);
	Delay(150);
}

/**
 * SPI �� XTP2046 ��������
*/
static void WriteCharToXTP2046(u8 num)
{
	u8 count=0;
	DCLK(0);
	for(count=0;count<8;count++)
	{
		if((num<<count)&0x80)DIN(1);   /*�жϷ���λ*/
		else  DIN(0);   

		DCLK(0); Delay(150);                //��������Ч
		DCLK(1); Delay(150);
	}
}

/**
 * SPI �� XTP2046 ��������
*/
static u16 ReadFromCharFromXTP2046()
{
	u8 count=0;
	u16 Num=0;
	
	for(count=0;count<12;count++)
	{
		Num<<=1;
		DCLK(1); Delay(150);                //�½�����Ч
		DCLK(0); Delay(150);

		if (IS_DOUT_H)
		{
			Num |= 0x01;
		}
		else
		{
			Num |= 0x00;
		}
		
	}

	return(Num);
}

#if 0
void inttostr(int dd, char *str)
{
	str[0]=dd/10000+48;	    //��λ  48����˼�ǣ�����IC��12λ��AD�� ��48�����λ��4λ��ȡ��12λ������
	str[1]=(dd/1000)-((dd/10000)*10)+48; //ʮλ
	str[2]=(dd/100)-((dd/1000)*10)+48;	//��λ
	str[3]=(dd/10)-((dd/100)*10)+48; //ǧλ
	str[4]=dd-((dd/10)*10)+48; //��λ
	str[5]=0;
}
#endif

/**
* ��    �ƣ�u16 XPT2046_GetData(u8 CMD) 
* ��    �ܣ���ȡ������ѹֵ(�Բ�ַ�ʽ)
* ��ڲ�����ָ����ȡX,��Y ��ֵ(��x ����CMD_RDX ����y ����CMD_RDY)
* ���ڲ�����������ֵ
* ˵    ����
* ���÷�������
*/
static u16 XPT2046_GetData(u8 CMD)              
{
	u16 AD_Data;
	
	//delayms(1);                     //�жϺ���ʱ������������ʹ�ò������ݸ�׼ȷ
	
	SpiStart();                       //����SPI
	//while(BUSY);                //���BUSY�źŲ���ʹ����ɾ������
	//delayms(1);

	WriteCharToXTP2046(CMD);        
	
	//while(BUSY);               //���BUSY�źŲ���ʹ����ɾ������
	//delayms(1);

	DCLK(1); Delay(200);
	DCLK(0); Delay(200);
	AD_Data = ReadFromCharFromXTP2046();

	Delay(150); 

	SpiStop();

	return  AD_Data	;
}


/**
* ��    �ƣ�u16 XPT2046_ReadXY(u8 xy)
* ��    �ܣ���ȡ��ѹ����ֵ, ȡƽ��ֵ
* ��ڲ�����ָ����ȡX,��Y ��ֵ(��x ����CMD_RDX ����y ����CMD_RDY)
* ���ڲ�����������ֵ
* ˵    ����
* ���÷�������
*/
static u16 XPT2046_ReadXY(u8 xy)
{
	u16  i, j;
	u16  buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
	  	buf[i]= XPT2046_GetData(xy);
	}				    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 


/**
* ��    �ƣ�unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY)
* ��    �ܣ����˲��������ȡ,��Сֵ��������100
* ��ڲ��������x ,y ��ѹֵ��ַ
* ���ڲ������ɹ�����1
* ˵    ����
* ���÷�������
*/
unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY)
{
	u16  xtemp, ytemp;
	xtemp = XPT2046_ReadXY(CMD_RDX);
	ytemp = XPT2046_ReadXY(CMD_RDY);
	if (xtemp<100 || ytemp<100)return 0;//����ʧ��
	*pX = xtemp;
	*pY = ytemp;
	return 1;//�����ɹ�;
}

/**
* ��    �ƣ�unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY)
* ��    �ܣ����˲��������ȡ,��Сֵ��������100,����ȡ����,���С��50��Ϊ��Ч
* ��ڲ��������x ,y ��ѹֵ��ַ
* ���ڲ������ɹ�����1
* ˵    ����
* ���÷�������
*/
unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY)
{
	u16  x1, y1;
	u16  x2, y2;
	
	//1. ����һ��
	if (!XPT2046_Read(&x1, &y1)) return 0;

	//2. ���ڶ���
	if (!XPT2046_Read(&x2, &y2)) return 0;
		
	if (((x2 <= x1&&x1<x2 + ERR_RANGE) || (x1 <= x2&&x2<x1 + ERR_RANGE))//ǰ�����β�����+-50��
		&& ((y2 <= y1&&y1<y2 + ERR_RANGE) || (y1 <= y2&&y2<y1 + ERR_RANGE)))
	{
		*pX = (x1 + x2) / 2;
		*pY = (y1 + y2) / 2;
		return 1;
	}
	else 
		return 0;

}
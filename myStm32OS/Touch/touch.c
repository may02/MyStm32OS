
#include "stm32f10x_lib.h"
#include "touch.h"

/**
* 自定义延时,不用ucOS 的延时,防止任务切换
*/

static void Delay(vu32 nCount)
{
	for (; nCount != 0; nCount--);
}

/**
 * 模拟spi 开始
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
	 * 关闭片选,降低功耗
	*/
	CS(1);
	Delay(150);
}

/**
 * SPI 向 XTP2046 发送数据
*/
static void WriteCharToXTP2046(u8 num)
{
	u8 count=0;
	DCLK(0);
	for(count=0;count<8;count++)
	{
		if((num<<count)&0x80)DIN(1);   /*判断发送位*/
		else  DIN(0);   

		DCLK(0); Delay(150);                //上升沿有效
		DCLK(1); Delay(150);
	}
}

/**
 * SPI 从 XTP2046 读出数据
*/
static u16 ReadFromCharFromXTP2046()
{
	u8 count=0;
	u16 Num=0;
	
	for(count=0;count<12;count++)
	{
		Num<<=1;
		DCLK(1); Delay(150);                //下降沿有效
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
	str[0]=dd/10000+48;	    //个位  48的意思是，触摸IC是12位的AD， 加48是向高位移4位，取高12位的数据
	str[1]=(dd/1000)-((dd/10000)*10)+48; //十位
	str[2]=(dd/100)-((dd/1000)*10)+48;	//百位
	str[3]=(dd/10)-((dd/100)*10)+48; //千位
	str[4]=dd-((dd/10)*10)+48; //万位
	str[5]=0;
}
#endif

/**
* 名    称：u16 XPT2046_GetData(u8 CMD) 
* 功    能：读取触摸电压值(以差分方式)
* 入口参数：指定读取X,或Y 的值(读x 发送CMD_RDX ，读y 发送CMD_RDY)
* 出口参数：读到的值
* 说    明：
* 调用方法：无
*/
static u16 XPT2046_GetData(u8 CMD)              
{
	u16 AD_Data;
	
	//delayms(1);                     //中断后延时以消除抖动，使得采样数据更准确
	
	SpiStart();                       //启动SPI
	//while(BUSY);                //如果BUSY信号不好使可以删除不用
	//delayms(1);

	WriteCharToXTP2046(CMD);        
	
	//while(BUSY);               //如果BUSY信号不好使可以删除不用
	//delayms(1);

	DCLK(1); Delay(200);
	DCLK(0); Delay(200);
	AD_Data = ReadFromCharFromXTP2046();

	Delay(150); 

	SpiStop();

	return  AD_Data	;
}


/**
* 名    称：u16 XPT2046_ReadXY(u8 xy)
* 功    能：读取电压坐标值, 取平均值
* 入口参数：指定读取X,或Y 的值(读x 发送CMD_RDX ，读y 发送CMD_RDY)
* 出口参数：读到的值
* 说    明：
* 调用方法：无
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
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
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
* 名    称：unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY)
* 功    能：带滤波的坐标读取,最小值不能少于100
* 入口参数：输出x ,y 电压值地址
* 出口参数：成功返回1
* 说    明：
* 调用方法：无
*/
unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY)
{
	u16  xtemp, ytemp;
	xtemp = XPT2046_ReadXY(CMD_RDX);
	ytemp = XPT2046_ReadXY(CMD_RDY);
	if (xtemp<100 || ytemp<100)return 0;//读数失败
	*pX = xtemp;
	*pY = ytemp;
	return 1;//读数成功;
}

/**
* 名    称：unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY)
* 功    能：带滤波的坐标读取,最小值不能少于100,连读取两次,误差小于50视为有效
* 入口参数：输出x ,y 电压值地址
* 出口参数：成功返回1
* 说    明：
* 调用方法：无
*/
unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY)
{
	u16  x1, y1;
	u16  x2, y2;
	
	//1. 读第一次
	if (!XPT2046_Read(&x1, &y1)) return 0;

	//2. 读第二次
	if (!XPT2046_Read(&x2, &y2)) return 0;
		
	if (((x2 <= x1&&x1<x2 + ERR_RANGE) || (x1 <= x2&&x2<x1 + ERR_RANGE))//前后两次采样在+-50内
		&& ((y2 <= y1&&y1<y2 + ERR_RANGE) || (y1 <= y2&&y2<y1 + ERR_RANGE)))
	{
		*pX = (x1 + x2) / 2;
		*pY = (y1 + y2) / 2;
		return 1;
	}
	else 
		return 0;

}
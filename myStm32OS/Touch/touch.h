
#ifndef __TOUCH_H__
#define __TOUCH_H__

#define u16   unsigned int
#define u8    unsigned char



#define CS_PIN      GPIO_Pin_4	 //CS 片选脚
#define DIN_PIN     GPIO_Pin_5	 //RD  串行数据输入脚,DCLK 上升沿锁存
#define DCLK_PIN    GPIO_Pin_6	 //WR  外部时钟信号输入
#define DOUT_PIN    GPIO_Pin_7   //RS  串行数据输出,DCLK 下降沿锁存
#define IRQ_PIN     GPIO_Pin_3	 //CS  笔接触中断引脚

#define    CS(x)     x ? GPIO_SetBits(GPIOB,   CS_PIN):   GPIO_ResetBits(GPIOB, CS_PIN) //自己定义位操作函数
#define    DIN(x)    x ? GPIO_SetBits(GPIOB,  DIN_PIN) :   GPIO_ResetBits(GPIOB, DIN_PIN)
#define    DCLK(x)   x ? GPIO_SetBits(GPIOB, DCLK_PIN) :   GPIO_ResetBits(GPIOB, DCLK_PIN)
#define    DOUT(x)   x ? GPIO_SetBits(GPIOB, DOUT_PIN) :   GPIO_ResetBits(GPIOB, DOUT_PIN)
#define    IRQ(x)    x ? GPIO_SetBits(GPIOB,  IRQ_PIN) :   GPIO_ResetBits(GPIOB, IRQ_PIN)

#define    IS_TOUCHED     (!GPIO_ReadInputDataBit(GPIOB, IRQ_PIN))
#define    IS_DOUT_H      (GPIO_ReadInputDataBit(GPIOB,DOUT_PIN))

// A/D 通道选择命令字和工作寄存器
#define	CMD_RDX 	0xD0
#define	CMD_RDY 	0x90
#define READ_TIMES 12 //读取次数
#define LOST_VAL    2    //丢弃值
#define ERR_RANGE 50 //误差范围 



//u16 XPT2046_GetData(u8 CMD) ;

 void inttostr(int dd, char *str);

 //unsigned int ReadFromCharFrom7843(void);
 //void WriteCharTo7843(unsigned char num) ;


//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//unsigned int ADS_Read_AD(u8 CMD);

//unsigned int ADS_Read_XY(u8 xy);//

static u16 XPT2046_ReadXY(u8);


/**
 * 对外部接口
*/
unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY);

unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY);

//unsigned char Read_ADS(u16 *x,u16 *y);////最小值不能少于100.

unsigned char Read_ADS2(u16 *x,u16 *y);//2次读取ADS7846,连续读取2次有效的AD值,且这两次的偏差不能超过ERR_RANGE




#endif//__TOUCH_H__



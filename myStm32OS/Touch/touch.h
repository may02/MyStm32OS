
#ifndef __TOUCH_H__
#define __TOUCH_H__

#define u16   unsigned int
#define u8    unsigned char



#define CS_PIN      GPIO_Pin_4	 //CS Ƭѡ��
#define DIN_PIN     GPIO_Pin_5	 //RD  �������������,DCLK ����������
#define DCLK_PIN    GPIO_Pin_6	 //WR  �ⲿʱ���ź�����
#define DOUT_PIN    GPIO_Pin_7   //RS  �����������,DCLK �½�������
#define IRQ_PIN     GPIO_Pin_3	 //CS  �ʽӴ��ж�����

#define    CS(x)     x ? GPIO_SetBits(GPIOB,   CS_PIN):   GPIO_ResetBits(GPIOB, CS_PIN) //�Լ�����λ��������
#define    DIN(x)    x ? GPIO_SetBits(GPIOB,  DIN_PIN) :   GPIO_ResetBits(GPIOB, DIN_PIN)
#define    DCLK(x)   x ? GPIO_SetBits(GPIOB, DCLK_PIN) :   GPIO_ResetBits(GPIOB, DCLK_PIN)
#define    DOUT(x)   x ? GPIO_SetBits(GPIOB, DOUT_PIN) :   GPIO_ResetBits(GPIOB, DOUT_PIN)
#define    IRQ(x)    x ? GPIO_SetBits(GPIOB,  IRQ_PIN) :   GPIO_ResetBits(GPIOB, IRQ_PIN)

#define    IS_TOUCHED     (!GPIO_ReadInputDataBit(GPIOB, IRQ_PIN))
#define    IS_DOUT_H      (GPIO_ReadInputDataBit(GPIOB,DOUT_PIN))

// A/D ͨ��ѡ�������ֺ͹����Ĵ���
#define	CMD_RDX 	0xD0
#define	CMD_RDY 	0x90
#define READ_TIMES 12 //��ȡ����
#define LOST_VAL    2    //����ֵ
#define ERR_RANGE 50 //��Χ 



//u16 XPT2046_GetData(u8 CMD) ;

 void inttostr(int dd, char *str);

 //unsigned int ReadFromCharFrom7843(void);
 //void WriteCharTo7843(unsigned char num) ;


//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//unsigned int ADS_Read_AD(u8 CMD);

//unsigned int ADS_Read_XY(u8 xy);//

static u16 XPT2046_ReadXY(u8);


/**
 * ���ⲿ�ӿ�
*/
unsigned char XPT2046_Read(unsigned int * pX, unsigned int * pY);

unsigned char XPT2046_ReadEx(unsigned int * pX, unsigned int * pY);

//unsigned char Read_ADS(u16 *x,u16 *y);////��Сֵ��������100.

unsigned char Read_ADS2(u16 *x,u16 *y);//2�ζ�ȡADS7846,������ȡ2����Ч��ADֵ,�������ε�ƫ��ܳ���ERR_RANGE




#endif//__TOUCH_H__



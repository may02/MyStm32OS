#define uint unsigned int
#define uchar unsinged char

#define LCD_RST_PIN    GPIO_Pin_8	 //RST ��Ӧ��Ƭ�����Ŷ��� P3^2 / ��ӦSTM32�� PA8

#define LCD_WR_PIN     GPIO_Pin_2	 //WR  ��Ӧ��Ƭ�����Ŷ��� P2^5 / ��ӦSTM32�� PB2
#define LCD_RS_PIN     GPIO_Pin_1	 //RD  ��Ӧ��Ƭ�����Ŷ��� P2^6 / ��ӦSTM32�� PB1
#define LCD_CS_PIN     GPIO_Pin_0	 //CS  ��Ӧ��Ƭ�����Ŷ��� P2^7 / ��ӦSTM32�� PB0

#define LCD_DB17_PIN   GPIO_Pin_12   //DB17	 ��Ӧ��Ƭ�����Ŷ��� P3^4 / ��ӦSTM32�� PA12
#define LCD_DB16_PIN   GPIO_Pin_11   //DB16	 ��Ӧ��Ƭ�����Ŷ��� P3^3 / ��ӦSTM32�� PA11

#define    LCD_RST(x)  x ? GPIO_SetBits(GPIOA, LCD_RST_PIN):   GPIO_ResetBits(GPIOA, LCD_RST_PIN) //�Լ�����λ��������

#define    LCD_WR(x)   x ? GPIO_SetBits(GPIOB, LCD_WR_PIN) :   GPIO_ResetBits(GPIOB, LCD_WR_PIN)
#define    LCD_RS(x)   x ? GPIO_SetBits(GPIOB, LCD_RS_PIN) :   GPIO_ResetBits(GPIOB, LCD_RS_PIN)
#define    LCD_CS(x)   x ? GPIO_SetBits(GPIOB, LCD_CS_PIN) :   GPIO_ResetBits(GPIOB, LCD_CS_PIN)

#define    LCD_DB17(x)   x ? GPIO_SetBits(GPIOA, LCD_DB17_PIN) :   GPIO_ResetBits(GPIOA, LCD_DB17_PIN)
#define    LCD_DB16(x)   x ? GPIO_SetBits(GPIOA, LCD_DB16_PIN) :   GPIO_ResetBits(GPIOA, LCD_DB16_PIN)
#define  LCD_SIZE_X		320
#define  LCD_SIZE_Y		480

extern  uint colors[];

void LCD_Init(void);
void LCD_ShowString(uint x,uint y,uint For_color,uint Bk_color,char *p);
void LCD_ShowChar(uint x,uint y,uint For_color,uint Bk_color, char ch);
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c);
static void delayms(int count) ;
void LCD_Write_DATA18(char x,char y ,char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Writ_Bus(char VH,char VL);
void LCD_Write_COM(char VH,char VL);
void LCD_Write_DATA(char VH,char VL);
void LCD_Write_COLOR(char V1,char V2,char V3);
void Pant(char VH,char VL);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);




/**************
 *					EXAMPLE CODE
 *
 *   Copyright 2003-2006; Micrium, Inc.; Weston, FL
 *
 *   All rights reserved.  Protected by international copyright laws.
 *   Knowledge of the source code may NOT be used to develop a similar product.
 *   Please help us continue to provide the Embedded community with the finest
 *   software available.  Your honesty is greatly appreciated.
 *
***************/

/***************
 * ������ MDK3.5
 *
 * Ӳ��ƽ̨:
 *
 * ����汾: OS-2.0.0
 *
 * Ӳ���汾:
 *
 * Ŀǰ��ֲ���ܣ�
 *	 1.����1 ������Ϣ��ӡ,���ڲ�����57600
 *	 2.TFT LCD ��ʾ��ͼƬչʾ
 *	 3.���Ӵ�������
 *
***************/


#include "../APP/includes.h"
                                

static  OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE]; //�������ջ

static  OS_STK AppTaskLcdStk[APP_TASK_LCD_STK_SIZE];     //LCD ��ʾ�����ջ

static  OS_STK AppTaskTouchStk[APP_TASK_TOUCH_STK_SIZE]; //���������ջ


//static  OS_STK App_TaskJoystickStk[APP_TASK_Joystick_STK_SIZE];

//static  OS_EVENT* InfoSem;                      
//static  OS_EVENT* Disp_Box;                  
//static  char* dp;


static  void App_TaskCreate(void);

static  void App_DispScr_SignOn(void);

static  void App_TaskStart(void* p_arg);

static  void App_TaskLCD(void* p_arg);  //LCD ��ʾ����

static  void App_TaskTouch(void* p_arg);//touch ����


//static  void App_TaskJoystick(void* p_arg);


int main(void)
{
	CPU_INT08U os_err;

	//BSP_IntDisAll(); /* Disable all ints until we are ready to accept them.  */
	//1.���ж�
	CPU_IntDis();
   
	//2.OS��ʼ��
	OSInit();  

	//3.�忨��ʼ��
	BSP_Init(); 
    
	//4.��ʼ��ucosIIʱ�ӽ���
	OS_CPU_SysTickInit();  

#if (OS_TASK_STAT_EN > 0)
	OSStatInit();    /* Determine CPU capacity.*/
#endif

	//5.��ʼ��LCD
	LCD_Init();
   
	//6.��ӡϵͳ��Ϣ
	App_DispScr_SignOn();

	printf("OS Init OK��\r\n");

	//7.������������ 
	os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,				//����ص���ַ
                          (void *) 0,										//�������
               (OS_STK *) &AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],   //����ջ��ָ��
               (INT8U) APP_TASK_START_PRIO);								//�������ȼ�

	printf("Creat App_TaskStart��\r\n");

#if (OS_TASK_NAME_SIZE >= 11)
	OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *) "Start Task", &os_err);
#endif

//   InfoSem = OSSemCreate(0); 
//   Disp_Box = OSMboxCreate((void *) 0);  

	OSTimeSet(0);	//ucosII�Ľ��ļ�������0    ���ļ�������0-4294967295  
	OSStart();		//����ucosII�ں�    

   return (0);
}


/**
 * ��    �ƣ�static  void App_TaskStart(void* p_arg)
 * ��    �ܣ���ʼ������,ָ��LED ����˸,����ϵͳ�ĺ�����
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����
 * ���÷�������
*/
static  void App_TaskStart(void* p_arg)
{
	//CPU_INT32U i;
	//CPU_INT32U j;
	//CPU_INT32U dly;

	(void) p_arg;

	printf("the main task has been Created!");

	App_TaskCreate();			//��������������

	while (DEF_TRUE)
	{
	    LED_Green_ON();
		OSTimeDlyHMSM(0, 0, 0, 100);
      
		LED_Green_OFF();
		OSTimeDlyHMSM(0, 0, 0, 100);

	}
}


/**
 * ��    �ƣ�static  void App_TaskCreate(void)
 * ��    �ܣ�����Ӧ�ó�������
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����
 * ���÷�������
*/
static  void App_TaskCreate(void)
{

   /*  ����LCD�������� */
	OSTaskCreateExt(App_TaskLCD,								   //����ص���ַ
		(void *)0,												   //�������
		(OS_STK *)&AppTaskLcdStk[APP_TASK_LCD_STK_SIZE - 1],       //����ջ��ָ��
		APP_TASK_LCD_PRIO,										   //�������ȼ�
		APP_TASK_LCD_PRIO,									       //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
		(OS_STK *)&AppTaskLcdStk[0],							   //����ջ�׵�ָ�룬���ڶ�ջ�ļ���
		APP_TASK_LCD_STK_SIZE,								       //ָ����ջ�����������ڶ�ջ�ļ���
		(void *)0,												   //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);				   //ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ���и�������ȵȡ�


	/* ����touch ����  */
	OSTaskCreateExt(App_TaskTouch,								   //����ص���ַ
		(void *)0,												   //�������
		(OS_STK *)&AppTaskTouchStk[APP_TASK_TOUCH_STK_SIZE - 1],   //����ջ��ָ��
		APP_TASK_TOUCH_PRIO,									   //�������ȼ�
		APP_TASK_TOUCH_PRIO,									   //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
		(OS_STK *)&AppTaskTouchStk[0],							   //����ջ�׵�ָ�룬���ڶ�ջ�ļ���
		APP_TASK_TOUCH_STK_SIZE,								   //ָ����ջ�����������ڶ�ջ�ļ���
		(void *)0,												   //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);				   //ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ���и�������ȵȡ�


}

/**
 * ��    �ƣ�static  void  App_TaskLCD (void *p_arg)
 * ��    �ܣ�LCD��������
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����
 * ���÷�������
*/
static  void App_TaskLCD(void* p_arg)
{
	Pant(0x1f, 0x00); //��ɫ 

	LCD_CS(0);  //��Ƭѡʹ��

	ChineseChar(14 + 46, 10, 2, colors[2], colors[7], 1);	//��
	ChineseChar(46 + 46, 10, 2, colors[2], colors[7], 2);	//��
	ChineseChar(78 + 46, 10, 2, colors[2], colors[7], 3);	//��
	ChineseChar(110 + 46, 10, 2, colors[2], colors[7], 4);	//��

	while (DEF_TRUE)
	{
		OSTimeDlyHMSM(0, 0, 10, 0);
	}

}

/**
* ��    �ƣ�static  void  App_TaskTouch (void *p_arg)
* ��    �ܣ�����û�����
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�������
*/
static  void App_TaskTouch(void* p_arg)
{	
	u16  X_Addata, Y_Addata;
	unsigned int lx, ly;
	
	int TchScr_Xmax = 3859, TchScr_Xmin = 26,
	TchScr_Ymax = 3842, TchScr_Ymin = 38;//���������ص�ѹֵ��Χ

	(void)p_arg;
	//AD7843(CMD_RDX);
	//AD7843(CMD_RDY);

	while (1)
	{
		//��������
		if (IS_TOUCHED)
		{
			XPT2046_ReadEx(&X_Addata, &Y_Addata);

			printf("touch sampling X-Y: %d - %d \r\n", X_Addata,Y_Addata);
			
			/**
			 * ��ѹֵת��Ϊ���ص�λ
			*/
			lx = (LCD_SIZE_X - 10 ) * (X_Addata / (TchScr_Xmax - TchScr_Xmin));
			if (lx > LCD_SIZE_X)
			{
				lx = LCD_SIZE_X;
			}
			
			ly = (LCD_SIZE_Y - 10) * (Y_Addata / (TchScr_Ymax - TchScr_Ymin));
			if (ly > LCD_SIZE_Y)
			{
				ly = LCD_SIZE_Y;
			}

			printf("touch sampling pix X-Y: %d - %d \r\n", lx, ly);

		}

		/* ��ʱ10ms���ȡһ�δ�������	*/
		OSTimeDlyHMSM(0, 0, 0, 10);
		
	}
}

/**
 * ��    �ƣ�static  void App_DispScr_SignOn(void)
 * ��    �ܣ���ӡϵͳ��Ϣ
 * ��ڲ�������
 * ���ڲ�������
 * ˵    ����
 * ���÷�������
*/
static  void App_DispScr_SignOn(void)
{
   printf("\r\n  Micrium uC/OS-II  \r\n");
   printf("  ST STM32 (Cortex-M3)\r\n\r\n");

   printf("  uC/OS-II:  V%ld.%ld%ld\r\n", OSVersion() / 100,(OSVersion() % 100) / 10, (OSVersion() % 10));
   printf("  TickRate: %ld  \r\n", OS_TICKS_PER_SEC);
   printf("  CPU Usage: %ld%    \r\n", OSCPUUsage);
   printf("  CPU Speed:%ld MHz  \r\n", BSP_CPU_ClkFreq() / 1000000L);
   printf("  #Ticks: %ld  \r\n", OSTime);
   printf("  #CtxSw: %ld  \r\n\r\n", OSCtxSwCtr);

}



/**
 * uC/OS-II APP HOOKS
*/

#if (OS_APP_HOOKS_EN > 0)

/**
 * TASK CREATION HOOK (APPLICATION)
 *
 * Description : This function is called when a task is created.
 *
 * Argument    : ptcb   is a pointer to the task control block of the task being created.
 *
 * Note        : (1) Interrupts are disabled during this call.
 *
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/**
 *
 * TASK DELETION HOOK (APPLICATION)
 *
 * Description : This function is called when a task is deleted.
 *
 * Argument    : ptcb   is a pointer to the task control block of the task being deleted.
 *
 * Note        : (1) Interrupts are disabled during this call.
 *
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/**
 *
 * IDLE TASK HOOK (APPLICATION)
 *
 * Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
 *               has been added to allow you to do such things as STOP the CPU to conserve power.
 *
 * Argument : none.
 *
 * Note     : (1) Interrupts are enabled during this call.
 *
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/**
 *
 *	STATISTIC TASK HOOK (APPLICATION)
 *
 * Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
 *               statistics task.  This allows your application to add functionality to the statistics task.
 *
 * Argument : none.
 *
*/

void App_TaskStatHook(void)
{
}

/**
 *
 *	TASK SWITCH HOOK (APPLICATION)
 *
 * Description : This function is called when a task switch is performed.  This allows you to perform other
 *               operations during a context switch.
 *
 * Argument : none.
 *
 * Note     : 1 Interrupts are disabled during this call.
 *
 *            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
 *                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
 *                  task being switched out (i.e. the preempted task).
 *
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/**
 *
 *	OS_TCBInit() HOOK (APPLICATION)
 *
 * Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
 *               up most of the TCB.
 *
 * Argument : ptcb    is a pointer to the TCB of the task being created.
 *
 * Note     : (1) Interrupts may or may not be ENABLED during this call.
 *
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif

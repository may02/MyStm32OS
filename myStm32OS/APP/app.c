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
 * 编译器 MDK3.5
 *
 * 硬件平台:
 *
 * 软件版本: OS-2.0.0
 *
 * 硬件版本:
 *
 * 目前移植功能：
 *	 1.串口1 调试信息打印,串口波特率57600
 *	 2.TFT LCD 显示屏图片展示
 *	 3.增加触摸功能
 *
***************/


#include "../APP/includes.h"
                                

static  OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE]; //主任务堆栈

static  OS_STK AppTaskLcdStk[APP_TASK_LCD_STK_SIZE];     //LCD 显示任务堆栈

static  OS_STK AppTaskTouchStk[APP_TASK_TOUCH_STK_SIZE]; //触摸任务堆栈


//static  OS_STK App_TaskJoystickStk[APP_TASK_Joystick_STK_SIZE];

//static  OS_EVENT* InfoSem;                      
//static  OS_EVENT* Disp_Box;                  
//static  char* dp;


static  void App_TaskCreate(void);

static  void App_DispScr_SignOn(void);

static  void App_TaskStart(void* p_arg);

static  void App_TaskLCD(void* p_arg);  //LCD 显示任务

static  void App_TaskTouch(void* p_arg);//touch 任务


//static  void App_TaskJoystick(void* p_arg);


int main(void)
{
	CPU_INT08U os_err;

	//BSP_IntDisAll(); /* Disable all ints until we are ready to accept them.  */
	//1.关中断
	CPU_IntDis();
   
	//2.OS初始化
	OSInit();  

	//3.板卡初始化
	BSP_Init(); 
    
	//4.初始化ucosII时钟节拍
	OS_CPU_SysTickInit();  

#if (OS_TASK_STAT_EN > 0)
	OSStatInit();    /* Determine CPU capacity.*/
#endif

	//5.初始化LCD
	LCD_Init();
   
	//6.打印系统信息
	App_DispScr_SignOn();

	printf("OS Init OK！\r\n");

	//7.创建启动任务 
	os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,				//任务回调地址
                          (void *) 0,										//任务参数
               (OS_STK *) &AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],   //任务栈顶指针
               (INT8U) APP_TASK_START_PRIO);								//任务优先级

	printf("Creat App_TaskStart！\r\n");

#if (OS_TASK_NAME_SIZE >= 11)
	OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *) "Start Task", &os_err);
#endif

//   InfoSem = OSSemCreate(0); 
//   Disp_Box = OSMboxCreate((void *) 0);  

	OSTimeSet(0);	//ucosII的节拍计数器清0    节拍计数器是0-4294967295  
	OSStart();		//启动ucosII内核    

   return (0);
}


/**
 * 名    称：static  void App_TaskStart(void* p_arg)
 * 功    能：开始任务建立,指定LED 的闪烁,当做系统的呼吸灯
 * 入口参数：无
 * 出口参数：无
 * 说    明：
 * 调用方法：无
*/
static  void App_TaskStart(void* p_arg)
{
	//CPU_INT32U i;
	//CPU_INT32U j;
	//CPU_INT32U dly;

	(void) p_arg;

	printf("the main task has been Created!");

	App_TaskCreate();			//建立其他的任务

	while (DEF_TRUE)
	{
	    LED_Green_ON();
		OSTimeDlyHMSM(0, 0, 0, 100);
      
		LED_Green_OFF();
		OSTimeDlyHMSM(0, 0, 0, 100);

	}
}


/**
 * 名    称：static  void App_TaskCreate(void)
 * 功    能：建立应用程序任务
 * 入口参数：无
 * 出口参数：无
 * 说    明：
 * 调用方法：无
*/
static  void App_TaskCreate(void)
{

   /*  建立LCD界面任务 */
	OSTaskCreateExt(App_TaskLCD,								   //任务回调地址
		(void *)0,												   //任务参数
		(OS_STK *)&AppTaskLcdStk[APP_TASK_LCD_STK_SIZE - 1],       //任务栈顶指针
		APP_TASK_LCD_PRIO,										   //任务优先级
		APP_TASK_LCD_PRIO,									       //预备给以后版本的特殊标识符，在现行版本同任务优先级
		(OS_STK *)&AppTaskLcdStk[0],							   //任务栈底的指针，用于堆栈的检验
		APP_TASK_LCD_STK_SIZE,								       //指定堆栈的容量，用于堆栈的检验
		(void *)0,												   //指向用户附加的数据域的指针，用来扩展任务的任务控制块
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);				   //选项，指定是否允许堆栈检验，是否将堆栈清0,任务是否要进行浮点运算等等。


	/* 建立touch 任务  */
	OSTaskCreateExt(App_TaskTouch,								   //任务回调地址
		(void *)0,												   //任务参数
		(OS_STK *)&AppTaskTouchStk[APP_TASK_TOUCH_STK_SIZE - 1],   //任务栈顶指针
		APP_TASK_TOUCH_PRIO,									   //任务优先级
		APP_TASK_TOUCH_PRIO,									   //预备给以后版本的特殊标识符，在现行版本同任务优先级
		(OS_STK *)&AppTaskTouchStk[0],							   //任务栈底的指针，用于堆栈的检验
		APP_TASK_TOUCH_STK_SIZE,								   //指定堆栈的容量，用于堆栈的检验
		(void *)0,												   //指向用户附加的数据域的指针，用来扩展任务的任务控制块
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);				   //选项，指定是否允许堆栈检验，是否将堆栈清0,任务是否要进行浮点运算等等。


}

/**
 * 名    称：static  void  App_TaskLCD (void *p_arg)
 * 功    能：LCD界面任务
 * 入口参数：无
 * 出口参数：无
 * 说    明：
 * 调用方法：无
*/
static  void App_TaskLCD(void* p_arg)
{
	Pant(0x1f, 0x00); //绿色 

	LCD_CS(0);  //打开片选使能

	ChineseChar(14 + 46, 10, 2, colors[2], colors[7], 1);	//普
	ChineseChar(46 + 46, 10, 2, colors[2], colors[7], 2);	//中
	ChineseChar(78 + 46, 10, 2, colors[2], colors[7], 3);	//科
	ChineseChar(110 + 46, 10, 2, colors[2], colors[7], 4);	//技

	while (DEF_TRUE)
	{
		OSTimeDlyHMSM(0, 0, 10, 0);
	}

}

/**
* 名    称：static  void  App_TaskTouch (void *p_arg)
* 功    能：检测用户触摸
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无
*/
static  void App_TaskTouch(void* p_arg)
{	
	u16  X_Addata, Y_Addata;
	unsigned int lx, ly;
	
	int TchScr_Xmax = 3859, TchScr_Xmin = 26,
	TchScr_Ymax = 3842, TchScr_Ymin = 38;//触摸屏返回电压值范围

	(void)p_arg;
	//AD7843(CMD_RDX);
	//AD7843(CMD_RDY);

	while (1)
	{
		//触摸产生
		if (IS_TOUCHED)
		{
			XPT2046_ReadEx(&X_Addata, &Y_Addata);

			printf("touch sampling X-Y: %d - %d \r\n", X_Addata,Y_Addata);
			
			/**
			 * 电压值转换为像素单位
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

		/* 延时10ms会读取一次触摸坐标	*/
		OSTimeDlyHMSM(0, 0, 0, 10);
		
	}
}

/**
 * 名    称：static  void App_DispScr_SignOn(void)
 * 功    能：打印系统信息
 * 入口参数：无
 * 出口参数：无
 * 说    明：
 * 调用方法：无
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

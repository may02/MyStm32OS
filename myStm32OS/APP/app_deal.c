
#include "../GUIinc/GUI.h"
#include "../TFT/ili9486_driver.h"

#include "app_deal.h"
#include "SysIconBMP.h"

void APP_ShowSysIcon(void )
{
	GUI_SetColor(GUI_BLUE);		 		//设置笔画颜色
	GUI_SetBkColor(GUI_WHITE);	 		//设置背景颜色
	
	GUI_Clear();
	
	ili9486_DrawBitmap(40, 10, 100, 100, (uchar *)g_SysIconImage);
}







#include "../GUIinc/GUI.h"
#include "../TFT/ili9486_driver.h"

#include "app_deal.h"
#include "SysIconBMP.h"

void APP_ShowSysIcon(void )
{
	GUI_SetColor(GUI_BLUE);		 		//���ñʻ���ɫ
	GUI_SetBkColor(GUI_WHITE);	 		//���ñ�����ɫ
	
	GUI_Clear();
	
	ili9486_DrawBitmap(40, 10, 100, 100, (uchar *)g_SysIconImage);
}






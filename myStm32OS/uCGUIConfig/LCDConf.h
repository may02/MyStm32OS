#ifndef LCDCONF_H
#define LCDCONF_H

/**
 * LCD 大小和 LCD_driver.h 中保持一致
*/
#define LCD_XSIZE          (320)
#define LCD_YSIZE          (480)

#define LCD_CONTROLLER     (9320)

#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)
//#define LCD_SWAP_XY        (1)
#define LCD_INIT_CONTROLLER()  ili9486_Initializtion();
#endif /* LCDCONF_H */

/**
 * 直接采用GPIO 操作
*/
//#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ram
//#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ram


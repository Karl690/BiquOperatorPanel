#include "main.h"
#include <math.h>
#include "font.h"


void GUI_Clear(uint16_t color)
{
	uint32_t index = 0;
	LCD_SetWindow(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	for (index = 0; index < LCD_WIDTH*LCD_HEIGHT; index++)
	{
		LCD_WR_16BITS_DATA(color);
	}
}

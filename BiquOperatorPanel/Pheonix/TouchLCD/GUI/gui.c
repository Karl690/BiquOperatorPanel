#include "main.h"
#include <math.h>
#include "gui.h"

void GUI_Clear(uint16_t color)
{
	uint32_t index = 0;
	LCD_SetWindow(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	for (index = 0; index < LCD_WIDTH*LCD_HEIGHT; index++)
	{
		LCD_WR_16BITS_DATA(color);
	}
}

void GUI_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_SetWindow(x, y, x, y);
	LCD_WR_16BITS_DATA(color);
}

/** @brief Draw a horiontal line
 * @param x1 - x point of line start
 * @param y - y point of line start
 * @param x2 - x point of line end
*/
void GUI_HLine(uint16_t x1, uint16_t y, uint16_t x2, uint16_t color)
{
	uint16_t i = 0;
	LCD_SetWindow(x1, y, x2 - 1, y);
	for (i = x1; i < x2; i++)
	{
		LCD_WR_16BITS_DATA(color);
	}
}

/** @brief Draw a vertical line
 * @param x - x point of line start
 * @param y1 - y point of line start
 * @param y2 - y point of line end
*/
void GUI_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color)
{
	uint16_t i = 0;
	LCD_SetWindow(x, y1, x, y2 - 1);
	for (i = y1; i < y2; i++)
	{
		LCD_WR_16BITS_DATA(color);
	}
}

/** @brief Draw a rectangle
 * @param x1 - x point of top left corner
 * @param y1 - y point of top left corner
 * @param x2 - x point of bottom right corner
 * @param y2 - y point of bottom right corner
*/
void GUI_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	GUI_HLine(x1, y1, x2, color);
	GUI_HLine(x1, y2 - 1, x2, color);
	GUI_VLine(x1, y1, y2, color);
	GUI_VLine(x2 - 1, y1, y2, color);
}
void GUI_FillRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
	uint16_t i = 0, j = 0;
	LCD_SetWindow(sx, sy, ex - 1, ey - 1);
	
	for (i = sx; i < ex; i++)
	{
		for (j = sy; j < ey; j++)
		{
			LCD_WR_16BITS_DATA(color);
		}
	}
}

void GUI_WriteBuffer(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t* data)
{
	uint16_t i = 0, j = 0;
	LCD_SetWindow(sx, sy, sx + ex - 1, sy + ey - 1);
	uint16_t color;
	for (i = sy; i < sy + ey; i++)
	{
		for (j = sx; j < sx + ex; j++)
		{
			color = data[0] + (data[1] << 8);
			LCD_WR_16BITS_DATA(color);
			data += 2;
		}
	}
}
void GUI_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;
	if (delta_x > 0)
		incx = 1;
	else if (delta_x == 0)
		incx = 0;
	else
	{ incx = -1; delta_x = -delta_x; }

	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0;
	else
	{ incy = -1; delta_y = -delta_y; }

	if (delta_x > delta_y)
		distance = delta_x;
	else
		distance = delta_y;

	for (t = 0; t <= distance + 1; t++)  // draw all point on line
	{
		GUI_DrawPoint(uRow, uCol, color); // draw calculated point
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}

void GUI_DrawChar(uint16_t X, uint16_t Y, uint8_t chr, Font* font, uint16_t color, uint16_t bgcolor)
{
	if (!font) return;
	uint8_t width = font->Width;
	uint8_t height = font->Height;	
	uint8_t offset =  8 *((width + 7)/8) -  width ;
	uint32_t counterh = 0, counterw = 0, index = 0;
	
	uint8_t* pChar = &font->pFontData[(chr - ' ') * height * ((width + 7) / 8)];
	uint8_t *pchar = NULL;
	uint32_t line = 0;
	for (counterh = 0; counterh < height; counterh++)
	{
		pchar = (pChar + (width + 7) / 8 * counterh);
		// REPLACE: little-endian swapping
		int bytes = ((width + 7) / 8);
		line = 0;
		for (int i = 0; i < bytes; i++) {
			line <<= 8;
			line |= pchar[i];
		}
		
		for (counterw = 0; counterw < width; counterw++)
		{
			
			if (line & (1 << (width - counterw + offset - 1))) 
			{
				GUI_DrawPoint(X + counterw, Y + counterh, color);
			}
			else
			{
				GUI_DrawPoint(X + counterw, Y + counterh, bgcolor);
			} 
		}
	}
}

void GUI_DrawString(uint16_t X, uint16_t Y, char *str, Font* font, uint16_t color, uint16_t bgcolor)
{
	uint16_t x0 = X;
	while ((*str <= '~')&&(*str >= ' '))
	{
		if (X >= LCD_WIDTH){X = x0; Y += font->Height; }
		if (Y >= LCD_HEIGHT) break;//�˳�
		GUI_DrawChar(X, Y, *str, font, color, bgcolor);
		X += font->Width;//fontSize / 2;
		str++;
	}
}
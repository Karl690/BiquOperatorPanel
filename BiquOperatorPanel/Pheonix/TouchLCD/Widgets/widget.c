#include <ctype.h>
#include "widget.h"
#include "panel.h"
#include "button.h"
#include "label.h"


//get the absolute condination of Control
void widget_get_control_coodination(Widget* widget, Point* pos) 
{
	if (widget->Parent != NULL)
	{
		pos->x += widget->Location.x;
		pos->y += widget->Location.y;
		widget_get_control_coodination(widget->Parent, pos);
	}
}

void widget_update_value_string(Widget* widget, uint32_t value)
{
	strcpy(widget->Text, value);
	widget->RedrawMe = 1;
}
void widget_update_value_int(Widget* widget, uint32_t value)
{
	sprintf(widget->Text, "%d", value);
	widget->RedrawMe = 1;
}
void widget_ToggleVisible(Widget* widget)
{
	widget->Visible++;
	widget->Visible &= 1;
	widget->RedrawMe = 1;
}
void widget_show(Widget* widget, uint8_t isShow)
{
	widget->Visible = isShow;
	widget->RedrawMe = 1;
}
uint8_t Refresh_Widget(Widget* widget, uint8_t forceRedraw)
{
	if (widget->Visible == 0)return 0;
		if(forceRedraw || widget->RedrawMe) return 1;
	return 0;
}

void widget_draw_string(char* string, uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
							PADDING* padding, Font* font, TEXT_ALIGN align, 
							Color16 foreColor, Color16 backColor )
{
	uint8_t len = strlen(string);
	uint8_t char_width = font->Width - 2;
	switch (align)
	{
	case TopLeft:
		x += padding->left;
		y += padding->top;
		break;
	case TopCenter:
		x += (w - len * char_width) / 2;
		y += padding->top;
		break;
	case TopRight:
		x += w - padding->right - len * char_width;
		y += padding->top;
		break;
	case MiddleLeft:
		x += padding->left;
		y += (h - font->Height) / 2;
		break;
	case MiddleCenter:
		x += (w - len * char_width) / 2;
		y += (h - font->Height) / 2;
		break;
	case MiddleRight:
		x += w - padding->right - len * char_width;
		y += (h - font->Height) / 2;
		break;
	case BottomLeft:
		x += padding->left;
		y += h - padding->bottom - font->Height;
		break;
	case BottomCenter:
		x += (w - len * char_width) / 2;
		y += h- padding->bottom - font->Height;
		break;
	case BottomRight:
		x += w - padding->right - len * char_width;
		y += h - padding->bottom - font->Height;
		break;
	default:
		x += padding->left;
		y += padding->top;
		break;
	}
	GUI_DrawString(x, y, string, font, foreColor, backColor);
	
}

uint8_t widget_is_point_in_rect(uint32_t x, uint32_t y, uint16_t rx, uint16_t ry, uint16_t rw, uint16_t rh)
{
	if (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh) return 1;
	return 0;
}


/*
 *format: //0x11 0x22 0x33 0x44  0x55 0x66 0x77 0x88	12345667
 **/
void buffer2hexstring(uint8_t* buf, uint8_t* hexstring, uint16_t bufsize) 
{
	uint16_t count = 0;
	uint16_t writ_bytes = 0;
	uint8_t* temp = hexstring;
	sprintf(temp, "%08X  ", buf);
	temp += 10;
	while (count < bufsize)
	{
		if (writ_bytes + 3 > WIDGET_MAX_TEXT_LENGTH) break; // return if hexstring's length is more than WIDGET_MAX_LENGTH(32)
		sprintf(temp, "%02X ", buf[count]); 
		writ_bytes += 3; // 
		temp += 3; //incress 3 because of writting 3 byte
		count++;
		
	}
	
	int fill = 3 * (8 - count) + 3; //lets see how many characters we need
	for (count = 0; count < fill; count++)
	{
		*temp = ' ';
		temp++;
	}
	
	for (count = 0; count < bufsize; count ++)
	{	
		if(isascii(buf[count]))
			*temp = buf[count];
		else 
			*temp = '.';
		temp ++;
	}
}
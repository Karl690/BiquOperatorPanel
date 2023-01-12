#pragma once
#include <stdint.h>
#include "../GUI/gui.h"


typedef enum
{
	PANEL,
	BUTTON,
	LABEL,
	EDIT,
	LISTBOX,
	CHECKBOX,
}WIDGETTYPE;

typedef enum
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight,
}TEXT_ALIGN;

typedef void(*CallbackTouchEventFunction)(uint32_t, uint32_t);

typedef struct tagWidget
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[32];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	Point Location;
	Size	Size;	
	Color16 BackColor;
	Color16 ForeColor;
	uint16_t BorderWidth;
	Color16 BorderColor;
	PADDING		Padding;
	char Text[32];
	Font* Font;
	TEXT_ALIGN	TextAlign;	
	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
}Widget;

#define NULL 0

uint8_t Refresh_Widget(Widget* widget, uint8_t forceRedraw);
void widget_update_value_int(Widget* widget, uint32_t value);
void widget_update_value_string(Widget* widget, uint32_t value);
void widget_ToggleVisible(Widget* widget);
void widget_draw_string(char* string, uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
	PADDING* padding,Font* font,TEXT_ALIGN align, Color16 foreColor,Color16 backColor);
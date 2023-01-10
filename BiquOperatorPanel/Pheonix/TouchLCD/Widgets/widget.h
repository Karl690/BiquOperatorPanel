#pragma once
#include <stdint.h>
#include "../GUI/gui.h"


typedef enum
{
	PANEL,
	BUTTON,
	LABEL,
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
	uint16_t BackColor;
	uint16_t ForeColor;
	//
	uint16_t BorderWidth;
	uint16_t BorderColor;
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
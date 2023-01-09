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
	Point Location;
	Size	Size;
	uint16_t BackColor;
	uint16_t ForeColor;
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

typedef struct
{
	uint32_t cur_value;
	uint32_t* point_for_value;
	char control_name[32];
}ControlUpdateInfo;

#define NULL 0

void widget_update_value(Widget* widget, char* value);
#pragma once
#include <stdint.h>
#include "../GUI/gui.h"


typedef enum
{
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

typedef void(*CallbackEventFunction)();

typedef struct tagWidget
{
	WIDGETTYPE Type;
	Point Location;
	Size	Size;
	uint16_t BackColor;
	uint16_t ForeColor;
	uint16_t BorderWidth;
	uint16_t BorderColor;	
}Widget;


#define NULL 0
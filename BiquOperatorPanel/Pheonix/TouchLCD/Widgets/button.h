#pragma once
#include <stdint.h>
#include "widget.h"

typedef struct tagButton
{
	WIDGETTYPE Type;
	Point Location;
	Size	Size;
	uint16_t BackColor;
	uint16_t ForeColor;
	uint16_t BorderWidth;
	uint16_t BorderColor;
	uint16_t CornerRadius;
	
	char Text[32];
	Font* Font;
	TEXT_ALIGN	TextAlign;
	PADDING		Padding;
	
	//Custtom properties
	uint16_t	CheckedColor;
	CallbackEventFunction	Event_Down;
	CallbackEventFunction	Event_Hold;
	CallbackEventFunction	Event_Up;
}Button;


void button_on_paint(Button*, Point);
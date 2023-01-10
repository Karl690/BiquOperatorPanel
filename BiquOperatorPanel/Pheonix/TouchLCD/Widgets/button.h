#pragma once
#include <stdint.h>
#include "widget.h"

typedef struct tagButton
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
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	
	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	
	
	//Button properties
	uint16_t CornerRadius;
	
	uint16_t	CheckedColor;
	
}Button;

Button* button_init(Widget* parent);
void button_on_paint(Button*, Point);
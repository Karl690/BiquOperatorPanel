#pragma once
#include <stdint.h>
#include "widget.h"

typedef struct tagLabel
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
	
	
	//Label properties
	uint16_t CornerRadius;
	
	
	
}Label;
Label* label_init();
void label_destory(Label* label);

void label_on_paint(Label*, Point);
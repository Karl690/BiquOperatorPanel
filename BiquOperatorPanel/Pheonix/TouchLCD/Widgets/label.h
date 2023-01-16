#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

typedef struct tagLabel
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[WIDGET_MAX_TEXT_LENGTH];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	Point Location;
	Size	Size;	
	Color16 BackColor;
	Color16 ForeColor;
	uint16_t BorderWidth;
	Color16 BorderColor;
	PADDING		Padding;
	
	char Text[WIDGET_MAX_TEXT_LENGTH];
	Font* Font;
	TEXT_ALIGN	TextAlign;	

	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	
	
	//Label properties
	uint16_t CornerRadius;
	
	
	
}Label;
Label* label_init();
void label_destory(Label* label);

void label_on_paint(Label* label, Point offset, Color16  backcolor);
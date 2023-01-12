#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

typedef struct tagListbox
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
	Color16 BorderWidth;
	Color16 BorderColor;
	PADDING		Padding;
	
	char Text[32];
	Font* Font;
	TEXT_ALIGN	TextAlign;	

	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	//Listbox properties
}Listbox;

void listbox_destory(Listbox* edit);

void listbox_on_paint(Listbox*, Panel*);
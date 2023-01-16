#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

#define LISTBOX_MAX_ROWS 256
typedef struct tagListbox
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
	Color16 BorderWidth;
	Color16 BorderColor;
	PADDING		Padding;
	
	char Text[WIDGET_MAX_TEXT_LENGTH];
	Font* Font;
	TEXT_ALIGN	TextAlign;	

	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	
	//Listbox properties	
	Color16 RowOddColor;
	Color16 RowEvenColor;
	char RowData[LISTBOX_MAX_ROWS][WIDGET_MAX_TEXT_LENGTH];
	uint16_t CurrentDrawYPos; //when scrolling, 
	uint16_t RowCount;
}Listbox;

void listbox_destory(Listbox* );
void listbox_update(Listbox* );
void listbox_on_paint(Listbox* listbox, Point offset, Color16  backcolor);
void listbox_append_row(Listbox*, char*);
void listbox_remove_row(Listbox* listbox, uint16_t index);
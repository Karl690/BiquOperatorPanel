#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagPanel
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
	
	//Panel properties
	uint16_t CornerRadius;
	Point	CornerPoints[10];
	
	void* Children[64];
	uint16_t ChildrenNum;
	uint16_t StackIndex;
	
}Panel;

Panel* panel_init();
void panel_destory(Panel* panel);
void panel_add_child(Panel* panel, void* child);
void panel_on_paint(Panel* panel, Panel* Parent, uint8_t);

void panel_touch_event_to_control(Panel* panel);
void panel_update_control_value(Panel* panel, char* name, char* value);
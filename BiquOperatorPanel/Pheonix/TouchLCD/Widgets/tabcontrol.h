#pragma once
#include <stdint.h>
#include "widget.h"

#define TAB_MAX_PANEL_NUM 8

typedef struct tagTabControl
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
	
	//Panel properties
	uint16_t CornerRadius;
	Point	CornerPoints[10];
	
	void* Buttons[TAB_MAX_PANEL_NUM];
	void* Panels[TAB_MAX_PANEL_NUM];
	Size ItemSize;
	uint16_t ChildrenNum;
	uint16_t StackIndex; //that means the selected panel's index.
	
}TabControl;

TabControl* tabcontrol_init();
void tabcontrol_update(TabControl* obj);
void tabcontrol_destory(TabControl* obj);
void tabcontrol_add_child(TabControl* obj, void* button, void* panel);
void tabcontrol_on_paint(TabControl* obj, Point offset, Color16  backcolor, uint8_t forceRedraw);

void tabcontrol_select_panel(TabControl* obj, uint16_t  New_index);
void* tabcontrol_get_active_panel(TabControl* obj);
void tabcontrol_touch_event_to_control(TabControl* obj, Point offset);
#pragma once
#include <stdint.h>
#include "widget.h"

#define TAB_MAX_PANEL_NUM 8

typedef struct tagTabControl
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
	uint16_t ChildrenNum;
	uint16_t StackIndex; //that means the selected panel's index.
	
}TabControl;

TabControl* tabcontrol_init();
void tabcontrol_update(TabControl* tab);
void tabcontrol_destory(TabControl* tab);
void tabcontrol_add_child(TabControl* tab, void* button, void* panel);
void tabcontrol_on_paint(TabControl* tab, Point offset, Color16  backcolor, uint8_t forceRedraw);

void tabcontrol_select_panel(TabControl* tab, uint16_t  index);
void* tabcontrol_get_active_panel(TabControl* tab);
void tabcontrol_touch_event_to_control(TabControl* tab, Point offset);
#pragma once
#include <stdint.h>
#include "widget.h"

#define PANEL_MAX_CHILDREN 64

typedef struct tagPanel
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[WIDGET_MAX_TEXT_LENGTH];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	uint8_t HasFocus;
	uint8_t Checked;
	Point Location;
	Size	Size;	
	Color16 BackColor;
	Color16 ForeColor;
	Color16 FocusBackColor;
	Color16 FocusForeColor;
	uint16_t BorderWidth;
	Color16 BorderColor;
	Color16 FocusBorderColor;
	PADDING		Padding;
	
	char Text[WIDGET_MAX_TEXT_LENGTH];
	Font* Font;
	TEXT_ALIGN	TextAlign;	
	
	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	CallbackEncoderEventFunction Event_Encoder;
	
	//Panel properties
	uint16_t CornerRadius;
	Point	CornerPoints[10];
	
	void* Children[PANEL_MAX_CHILDREN];
	uint16_t ChildrenNum;
	uint16_t StackIndex;
	
}Panel;

extern Widget* FocusedWidget;
Panel* panel_init();
void panel_destory(Panel* obj);
void panel_add_child(Panel* obj, void* child);
void panel_on_paint(Panel* obj, Point offset, Color16  backcolor, uint8_t forceRedraw);

void panel_touch_event_to_control(Panel* obj, Point offset);
void panel_update_control_value(Panel* obj, char* name, char* value);
void panel_set_focus_widget(Widget* widget, uint8_t isForce);
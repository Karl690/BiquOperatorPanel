#pragma once
#include <stdint.h>
#include "../GUI/gui.h"

#define NULL 0
#define WIDGET_MAX_TEXT_LENGTH 50
#define LIST_MAX_LENGH		30
typedef enum
{
	PANEL,
	BUTTON,
	LABEL,
	EDIT,
	LISTBOX,
	TABCONTROL,
	NUMERIC,
	DROPDOWNLIST,
}WIDGETTYPE;

typedef enum
{
	TopLeft,
	TopCenter,
	TopRight,
	MiddleLeft,
	MiddleCenter,
	MiddleRight,
	BottomLeft,
	BottomCenter,
	BottomRight,
}TEXT_ALIGN;


#define	DISPLAYMODE_ASCII      0
#define	DISPLAYMODE_Raw_ASCII  1
#define	DISPLAYMODE_HEX        2


typedef void(*CallbackTouchEventFunction)(void*, uint32_t, uint32_t);

typedef struct tagWidget
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[WIDGET_MAX_TEXT_LENGTH];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	uint16_t HasFocus;
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
}Widget;


typedef struct tagBlinkWidgetInfo
{
	Widget *widget;
	uint8_t blinkRate; //blinkRate is how blink interval in .1 sec, so 5 would blink 1 x per second, .5 on, and .5 off
	uint32_t blinkCount; //blinkCount is a number that count down.
	uint8_t numberOfTimesToblink; //numberOfTimesToblink is how many times it will turn on and off if set to -1 or 0xff,it is continous
}BlinkWidgetInfo;


extern BlinkWidgetInfo BlinkWidgetsList[LIST_MAX_LENGH];
uint8_t Refresh_Widget(Widget* widget, uint8_t forceRedraw);
void widget_update_value_int(Widget* widget, uint32_t value);
void widget_update_value_string(Widget* widget, uint32_t value);
void widget_ToggleVisible(Widget* widget);
void widget_draw_string(char* string, uint16_t x, uint16_t y, uint16_t w, uint16_t h, 
	PADDING* padding,Font* font,TEXT_ALIGN align, Color16 foreColor,Color16 backColor);
uint8_t widget_is_point_in_rect(uint32_t x, uint32_t y, uint16_t rx, uint16_t ry, uint16_t rw, uint16_t rh);

void widget_add_blink_widget(Widget* widget, uint8_t rate, uint8_t numberOfTime); //if widget is exit, it would update 
void widget_delete_blink_widget(Widget* widget); //remove the widget from list..
void BlinkStartWidget(Widget* widget, uint8_t rate, uint8_t numberOfTime);
void BlinkStopWidget(Widget* widget);
void buffer2hexstring(uint8_t* buf, uint8_t* hexstring, uint16_t bufsize);
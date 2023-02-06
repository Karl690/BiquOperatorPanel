#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

typedef struct tagNumeric
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
	
	
	//Label properties
	uint16_t CornerRadius;
	Point	CornerPoints[9];
	
	float	Value;
	float		Step;
	float		MinValue;
	float 	MaxValue;
}Numeric;
Numeric* numeric_init();
void numeric_update(Numeric* );
void numeric_destory(Numeric* );
void numeric_on_paint(Numeric* , Point , Color16 );
void numeric_increment(Numeric* );
void numeric_decrement(Numeric* );

void numeric_set_value(Numeric* , float );
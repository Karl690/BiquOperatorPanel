#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"


typedef struct tagButton
{
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
	
	
	//Button properties
	uint16_t CornerRadius;
	
	Color16	CheckedBackColor;
	Color16	CheckedForeColor;
	Color16	CheckedBorderColor;	
	char		CheckedText[WIDGET_MAX_TEXT_LENGTH];
	
	
}Button;

Button* button_init(Widget* parent);
void button_on_paint(Button* obj, Point offset, Color16  backcolor);
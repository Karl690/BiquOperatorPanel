#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagButton
{
	WIDGETTYPE Type;
	Point Location;
	Size	Size;
	uint16_t BackgroundColor;
	uint16_t ForegroundColor;
	uint16_t BorderWidth;
	uint16_t BorderColor;
	char Text[32];
}Button;


void button_on_paint(Button* button);
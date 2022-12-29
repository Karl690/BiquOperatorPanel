#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagButton
{
	Point Location;
	Size	Size;
	uint16_t BackgroundColor;
	uint16_t ForegroundColor;
	uint16_t Boarder;
	uint16_t BorderColor;
	uint16_t CornerRadius;
	char* Text;
}Button;


void button_draw(Button* button);
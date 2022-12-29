#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagLabel
{
	Point Location;
	Size	Size;	
	uint16_t ForegroundColor;
	uint16_t Boarder;
	uint16_t BorderColor;
	uint16_t CornerRadius;
	char* Text;
}Label;


void label_draw(Label* button);
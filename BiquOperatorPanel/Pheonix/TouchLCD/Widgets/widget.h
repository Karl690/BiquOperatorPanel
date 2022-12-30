#pragma once
#include <stdint.h>


typedef struct
{
	float x, y;
}Point;

typedef struct
{
	float width, height;
}Size;

typedef enum
{
	BUTTON,
	LABEL,
	CHECKBOX,
}WIDGETTYPE;


typedef struct tagWidget
{
	WIDGETTYPE Type;
	Point Location;
	Size	Size;
	uint16_t BackgroundColor;
	uint16_t ForegroundColor;
	uint16_t BorderWidth;
	uint16_t BorderColor;	
}Widget;

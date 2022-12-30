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
	Point Location;
	Size	Size;
	uint16_t BackgroundColor;
	uint16_t ForegroundColor;
	uint16_t Boarder;
	uint16_t BorderColor;
	uint16_t CornerRadius;
	char* Text;
	WIDGETTYPE Type;
}Widget;

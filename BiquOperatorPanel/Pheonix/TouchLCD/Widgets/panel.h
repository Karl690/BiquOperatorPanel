#pragma once
#include <stdint.h>

typedef struct tagPanel
{
	WIDGETTYPE Type;
	Point Location;
	Size	Size;
	uint16_t BackColor;
	uint16_t ForeColor;
	uint16_t BorderWidth;
	uint16_t BorderColor;
	char Text[24];
	Font* Font;
	void* Children[64];
	uint16_t ChildrenNum;
}Panel;

void panel_init(Panel* panel);
void panel_add_child(Panel* panel, void* child);
void panel_on_paint(Panel* panel, Point);



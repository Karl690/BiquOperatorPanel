#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagPanel
{
	Widget Parent;
	Widget* Children[256];
	uint16_t ChildrenNum;
}Panel;

void panel_init(Panel* panel);
void panel_add_child(Panel* panel, void* child);
void panel_on_paint(Panel* panel);



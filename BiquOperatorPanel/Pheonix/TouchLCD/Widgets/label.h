#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagLabel
{
	Widget Parent;
}Label;


void label_on_paint(Label* button);
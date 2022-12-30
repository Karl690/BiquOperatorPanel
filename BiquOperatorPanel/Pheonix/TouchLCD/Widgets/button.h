#pragma once
#include <stdint.h>
#include "widget.h"
typedef struct tagButton
{
	Widget Parent;
}Button;


void button_on_paint(Button* button);
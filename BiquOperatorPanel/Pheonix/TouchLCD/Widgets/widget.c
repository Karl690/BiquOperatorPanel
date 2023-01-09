#include "widget.h"
#include "panel.h"
#include "button.h"
#include "label.h"


//get the absolute condination of Control
void widget_get_control_coodination(Widget* widget, Point* pos) 
{
	if (widget->Parent != NULL)
	{
		pos->x += widget->Location.x;
		pos->y += widget->Location.y;
		widget_get_control_coodination(widget->Parent, pos);
	}
}
void widget_update_value(Widget* widget, char* value)
{
	strcpy(widget->Text, value);
	
	Point pos = { 0, 0 };
	widget_get_control_coodination(widget, &pos);
	switch (widget->Type)
	{
	case BUTTON:
		button_on_paint((Button*)widget, pos);
		break;
	case LABEL:
		label_on_paint((Label*)widget, pos);
		break;
	default:
		break;
	}
}
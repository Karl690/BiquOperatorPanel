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

void widget_update_value_string(Widget* widget, uint32_t value)
{
	strcpy(widget->Text, value);
	widget->RedrawMe = 1;
}
void widget_update_value_int(Widget* widget, uint32_t value)
{
	sprintf(widget->Text, "%d", value);
	widget->RedrawMe = 1;
}

uint8_t Refresh_Widget(Widget* widget, uint8_t forceRedraw)
{
	if (widget->Visible == 0)return 0;
		if(forceRedraw || widget->RedrawMe) return 1;
	return 0;
}
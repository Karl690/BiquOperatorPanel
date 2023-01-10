#include "widget.h"
#include "panel.h"
#include "label.h"
#include "button.h"

#include "../lcd_touch.h"


Panel* panel_init(Widget* parent)
{
	Panel* panel = (Panel*)malloc(sizeof(Panel));
	panel->Type = PANEL;
	panel->Location = (Point) { 0, 0 };
	panel->Size = (Size) { 0, 0};
	panel->Parent = parent;
	panel->ChildrenNum = 0;
	return panel;
}
void panel_destory(Panel* panel)
{
	for (uint16_t i = 0; i < panel->ChildrenNum; i++)
	{
		
	}
	free(panel);
}
void panel_add_child(Panel* panel, void* child)
{
	panel->Children[panel->ChildrenNum] = child;
	panel->ChildrenNum++;
}




void panel_on_paint(Panel* panel, Point posParent, uint8_t forceRedraw) 
{
	uint16_t ChildIndex = 0;
	Point pos = (Point) { panel->Location.x + posParent.x, panel->Location.y + posParent.y };
	//at this point we have been asked to paint a Panel and all children in the panel
	if (!panel->Visible)return;//dont draw unless we have permission

	if (panel->RedrawMe||forceRedraw)
	{//going to rdraw the entire panel, so go ahead and paint the background first

		if (Refresh_Widget((Widget*)panel, forceRedraw)) {		
			GUI_FillRect(pos.x, pos.y, pos.x + panel->Size.width, pos.y + panel->Size.height, panel->BackColor);
			panel->RedrawMe = 0;
		}
		forceRedraw = 1;
	}
	
	for (ChildIndex = 0; ChildIndex < panel->ChildrenNum; ChildIndex ++)
	{
		Widget* child = panel->Children[ChildIndex];
		if (!Refresh_Widget(child, forceRedraw)) continue;
		child->RedrawMe = 0;
		switch (child->Type)
		{
		case BUTTON:
			button_on_paint((Button*)child, pos);
			break;
		case LABEL:
			label_on_paint((Label*)child, pos);
			break;
		case PANEL:
			panel_on_paint((Panel*)child, pos, forceRedraw);
			break;

		default:
			break;
		}
		
	}
}

uint8_t IsPointInRect(uint32_t x, uint32_t y, uint16_t rx, uint16_t ry, uint16_t rw, uint16_t rh)
{
	if (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh) return 1;
	return 0;
}
void panel_touch_event_to_control(Panel* panel)
{
	if (!touchScreenIsPress) return;
	for (int i = 0; i < panel->ChildrenNum; i++)
	{
		Widget* widget = panel->Children[i];
		if (IsPointInRect(TouchPointX, TouchPointY, panel->Location.x +  widget->Location.x, panel->Location.y + widget->Location.y, widget->Size.width, widget->Size.height))
		{
			if (widget->Event_Down) widget->Event_Down(TouchPointX, TouchPointY);
		}
	}
	//touchScreenIsPress = 0;
}

void panel_update_control_value(Panel* panel, char* name, char* value)
{
	uint16_t ChildIndex = 0;
	for (ChildIndex = 0; ChildIndex < panel->ChildrenNum; ChildIndex++)
	{
		Widget* child = panel->Children[ChildIndex];
		if(strcmp(name, child->Name) == 0)
			widget_update_value(child, value);
		
	}
}
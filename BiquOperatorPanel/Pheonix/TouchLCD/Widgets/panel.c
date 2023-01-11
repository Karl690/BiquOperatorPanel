#include "widget.h"
#include "panel.h"
#include "label.h"
#include "button.h"
#include "panel.h"
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




void panel_on_paint(Panel* panel, Panel* Parent, uint8_t forceRedraw) 
{
	uint16_t ChildIndex = 0;
	Point pos = (Point) { panel->Location.x + Parent->Location.x, panel->Location.y + Parent->Location.y };
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
	//
//	if (widget->Visible == 0)return 0;
//	if (forceRedraw || widget->RedrawMe) return 1;
//	return 0;
	
	//there are several possibilitys
	//1. we want to refresh the whole screen, that is forceRedraw flag
	//2. we want to redraw just this component, that is the redraw screen
	//3. we want to hide this component, set the .visible=0, redraw to 1;
	for (ChildIndex = 0; ChildIndex < panel->ChildrenNum; ChildIndex ++)
	{
		Widget* child = panel->Children[ChildIndex];
		//if (child->Type != PANEL && !Refresh_Widget(child, forceRedraw)) continue;
		//if (child->Type != PANEL && !Refresh_Widget(child, forceRedraw)) continue;
		if (child->Type == PANEL)
		{
			panel_on_paint((Panel*)child, panel, forceRedraw);
			continue;
		}
		if (child->RedrawMe || forceRedraw)
		{

			//ok so we need to redraw here, but if it is 
			switch (child->Type)
			{
			case BUTTON:
				button_on_paint((Button*)child, panel);
				break;
			case LABEL:
				label_on_paint((Label*)child, panel);
				break;
//			case PANEL:
//				panel_on_paint((Panel*)child, panel, forceRedraw);
//				break;
			default:
				break;
			}
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
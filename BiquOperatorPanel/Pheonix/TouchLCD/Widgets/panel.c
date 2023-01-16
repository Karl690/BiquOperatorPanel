#include "widget.h"
#include "panel.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "listbox.h"
#include "panel.h"
#include "tabcontrol.h"
#include "../lcd_touch.h"

void panel_destory(Panel* panel)
{
	
	free(panel);
}
void panel_add_child(Panel* panel, void* child)
{
	panel->Children[panel->ChildrenNum] = child;
	panel->ChildrenNum++;
}

void panel_update(Panel* panel)
{
	uint16_t ypos = 0;
	if (panel->Font) ypos = panel->Font->Height / 2;	
	//update corner points.
	panel->CornerPoints[0] = (Point) { 3* panel->CornerRadius, ypos };
	panel->CornerPoints[1] = (Point) { panel->CornerRadius, ypos };
	panel->CornerPoints[2] = (Point) { 0, panel->CornerRadius + ypos};
	panel->CornerPoints[3] = (Point){ 0, panel->Size.height - panel->CornerRadius - 1 };
	panel->CornerPoints[4] = (Point) { panel->CornerRadius, panel->Size.height-1};
	panel->CornerPoints[5] = (Point) { panel->Size.width - panel->CornerRadius -1, panel->Size.height - 1 };
	panel->CornerPoints[6] = (Point) { panel->Size.width - 1, panel->Size.height - panel->CornerRadius - 1 };
	panel->CornerPoints[7] = (Point) { panel->Size.width - 1, panel->CornerRadius + ypos};
	panel->CornerPoints[8] = (Point) { panel->Size.width - panel->CornerRadius - 1, ypos};
	
	uint8_t len = strlen(panel->Text);	
	uint8_t char_width = 0;
	if (panel->Font) char_width = panel->Font->Width - 2;	
	
	uint16_t end_pos = char_width* len;
	if (len > 0) end_pos += char_width;
	
	panel->CornerPoints[9] = (Point) { 3* panel->CornerRadius + end_pos, ypos };
}
void panel_on_paint(Panel* panel, Point offset, Color16  backcolor, uint8_t forceRedraw)
{
	uint16_t ChildIndex = 0;
	Point pos = (Point) { panel->Location.x + offset.x, panel->Location.y + offset.y };
	
	if (!panel->Visible || panel->RedrawMe) {
		GUI_FillRect(pos.x, pos.y, pos.x + panel->Size.width, pos.y + panel->Size.height, backcolor);
		
	}
	//at this point we have been asked to paint a Panel and all children in the panel
	if (!panel->Visible) return;//dont draw unless we have permission

	if (panel->RedrawMe||forceRedraw)
	{//going to rdraw the entire panel, so go ahead and paint the background first

		if (Refresh_Widget((Widget*)panel, forceRedraw)) {		
			GUI_FillRect(pos.x, pos.y, pos.x + panel->Size.width, pos.y + panel->Size.height, panel->BackColor);
			
			if (panel->BorderWidth > 0)
			{
				//GUI_DrawRect(pos.x, pos.y, pos.x + panel->Size.width, pos.y + panel->Size.height, panel->BorderColor);
				GUI_DrawPolygon(panel->CornerPoints, sizeof(panel->CornerPoints) / sizeof(Point), panel->BorderColor, pos);
				if(strlen(panel->Text) > 0)
					GUI_DrawString(pos.x + panel->CornerPoints[0].x + panel->CornerRadius, pos.y, panel->Text, panel->Font, panel->ForeColor, panel->BackColor);
				
			}
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
			panel_on_paint((Panel*)child, offset, backcolor, forceRedraw);
			continue;
		}
		if (child->RedrawMe || forceRedraw)
		{

			//ok so we need to redraw here, but if it is 
			switch (child->Type)
			{
			case BUTTON:
				button_on_paint((Button*)child, pos, panel->BackColor);
				break;
			case LABEL:
				label_on_paint((Label*)child, pos, panel->BackColor);
				break;
			case EDIT:
				edit_on_paint((Edit*)child, pos, panel->BackColor);
				break;
			case LISTBOX:
				listbox_on_paint((Listbox*)child, pos, panel->BackColor);
				break;
			case TABCONTROL:
				tabcontrol_on_paint((TabControl*)child, pos, panel->BackColor, forceRedraw);
				break;
			default:
				break;
			}
		}
		
	}
	
	panel->RedrawMe = 0;
}


void panel_touch_event_to_control(Panel* panel, Point offset)
{
	if (!touchScreenIsPress) return;
	Point pos = (Point) { panel->Location.x + offset.x, panel->Location.y + offset.y};
	for (int i = 0; i < panel->ChildrenNum; i++)
	{
		Widget* widget = panel->Children[i];
		if (!widget->Visible) continue;
		if (widget_is_point_in_rect(TouchPointX, TouchPointY, pos.x +  widget->Location.x, pos.y + widget->Location.y, widget->Size.width, widget->Size.height))
		{
			if (widget->Type == PANEL) panel_touch_event_to_control((Panel*)widget, pos);
			else if (widget->Type == TABCONTROL) tabcontrol_touch_event_to_control((TabControl*)widget, pos);
			else if (widget->Event_Down) widget->Event_Down(TouchPointX - offset.x, TouchPointY - offset.y);
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
#include "widget.h"
#include "panel.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "listbox.h"
#include "panel.h"
#include "tabcontrol.h"
#include "numeric.h"
#include "dropdownlist.h"
#include "../lcd_touch.h"

Widget* FocusedWidget = NULL;

void panel_destory(Panel* obj)
{
	
	free(obj);
}
void panel_add_child(Panel* obj, void* child)
{
	obj->Children[obj->ChildrenNum] = child;
	obj->ChildrenNum++;
}

void panel_update(Panel* obj)
{
	uint16_t ypos = 0;
	if (strlen(obj->Text) == 0) ypos = 0;
	else if (obj->Font) ypos = obj->Font->Height / 2;	
	//update corner points.
	obj->CornerPoints[0] = (Point) { 3* obj->CornerRadius, ypos };
	obj->CornerPoints[1] = (Point) { obj->CornerRadius, ypos };
	obj->CornerPoints[2] = (Point) { 0, obj->CornerRadius + ypos};
	obj->CornerPoints[3] = (Point){ 0, obj->Size.height - obj->CornerRadius - 1 };
	obj->CornerPoints[4] = (Point) { obj->CornerRadius, obj->Size.height-1};
	obj->CornerPoints[5] = (Point) { obj->Size.width - obj->CornerRadius -1, obj->Size.height - 1 };
	obj->CornerPoints[6] = (Point) { obj->Size.width - 1, obj->Size.height - obj->CornerRadius - 1 };
	obj->CornerPoints[7] = (Point) { obj->Size.width - 1, obj->CornerRadius + ypos};
	obj->CornerPoints[8] = (Point) { obj->Size.width - obj->CornerRadius - 1, ypos};
	
	uint8_t len = strlen(obj->Text);	
	uint8_t char_width = 0;
	if (obj->Font) char_width = obj->Font->Width - 2;	
	
	uint16_t end_pos = char_width* len;
	if (len > 0) end_pos += char_width;
	
	obj->CornerPoints[9] = (Point) { 3* obj->CornerRadius + end_pos, ypos };
}
void panel_on_paint(Panel* obj, Point offset, Color16  backcolor, uint8_t forceRedraw)
{
	uint16_t ChildIndex = 0;
	Point pos = (Point) { obj->Location.x + offset.x, obj->Location.y + offset.y };
	
	if (!obj->Visible || obj->RedrawMe) {
		GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, backcolor);
		
	}
	//at this point we have been asked to paint a Panel and all children in the panel
	if (!obj->Visible) return;//dont draw unless we have permission

	if (obj->RedrawMe||forceRedraw)
	{//going to rdraw the entire panel, so go ahead and paint the background first

		if (Refresh_Widget((Widget*)obj, forceRedraw)) {		
			GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BackColor);
			
			if (obj->BorderWidth > 0)
			{
				//GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
				GUI_DrawPolygon(obj->CornerPoints, sizeof(obj->CornerPoints) / sizeof(Point), obj->BorderColor, pos);
				if(strlen(obj->Text) > 0)
					GUI_DrawString(pos.x + obj->CornerPoints[0].x + obj->CornerRadius, pos.y, obj->Text, obj->Font, obj->ForeColor, obj->BackColor);
				
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
	for (ChildIndex = 0; ChildIndex < obj->ChildrenNum; ChildIndex ++)
	{
		Widget* child = obj->Children[ChildIndex];
		//if (child->Type != PANEL && !Refresh_Widget(child, forceRedraw)) continue;
		//if (child->Type != PANEL && !Refresh_Widget(child, forceRedraw)) continue;
		if (child->Type == PANEL)
		{
			panel_on_paint((Panel*)child, pos, backcolor, forceRedraw);
			continue;
		}
		else if (child->Type == TABCONTROL)
		{
			tabcontrol_on_paint((TabControl*)child, pos, obj->BackColor, forceRedraw);
			continue;
		}
		if (child->RedrawMe || forceRedraw)
		{

			//ok so we need to redraw here, but if it is 
			switch (child->Type)
			{
			case BUTTON:
				button_on_paint((Button*)child, pos, obj->BackColor);
				break;
			case LABEL:
				label_on_paint((Label*)child, pos, obj->BackColor);
				break;
			case EDIT:
				edit_on_paint((Edit*)child, pos, obj->BackColor);
				break;
			case NUMERIC:
				numeric_on_paint((Numeric*)child, pos, obj->BackColor);
				break;
			case LISTBOX:
				listbox_on_paint((Listbox*)child, pos, obj->BackColor);
				break;
			case DROPDOWNLIST:
				dropdownlist_on_paint((DropdownList*)child, pos, obj->BackColor);
				break;
			default:
				break;
			}
		}
		
	}
	
	obj->RedrawMe = 0;
}

void panel_set_focus_widget(Widget* widget, uint8_t isForce)
{
	//if widget == NULL, it meens that previous focused widget is released.
	if (widget == NULL || (widget && (widget->Type == NUMERIC || widget->Type == DROPDOWNLIST || widget->Type == LISTBOX)))
	{
		if (FocusedWidget)
		{	
			//old widget's focus flag release
			switch (FocusedWidget->Type)
			{
			case DROPDOWNLIST:
				((DropdownList*)FocusedWidget)->HasFocus = 0;
				((DropdownList*)FocusedWidget)->RedrawMe = 1;
				break;
			case NUMERIC:
				((Numeric*)FocusedWidget)->HasFocus = 0;
				((Numeric*)FocusedWidget)->RedrawMe = 1;
				break;
			case LISTBOX:
				((Listbox*)FocusedWidget)->HasFocus = 0;
				((Listbox*)FocusedWidget)->RedrawMe = 1;
				break;
							
			}
		}		
		//if Force flag is set or the previous one is different with selected one, 
		if ((isForce || FocusedWidget != widget) && widget)
		{
			FocusedWidget = NULL;
			//the case of the different focus
			switch (widget->Type)
			{
			case DROPDOWNLIST:
				FocusedWidget = widget;
				((DropdownList*)FocusedWidget)->HasFocus = 1;
				((DropdownList*)FocusedWidget)->RedrawMe = 1;
				break;
			case NUMERIC:
				FocusedWidget = widget;
				((Numeric*)FocusedWidget)->HasFocus = 1;
				((Numeric*)FocusedWidget)->RedrawMe = 1;
				break;
			case LISTBOX:
				FocusedWidget = widget;
				((Listbox*)FocusedWidget)->HasFocus = 1;
				((Listbox*)FocusedWidget)->RedrawMe = 1;
				break;
			}		
		}
		else
		{
			FocusedWidget = NULL;
		}
	}
	
}

void panel_touch_event_to_control(Panel* obj, Point offset)
{
	if (TouchEventStatus == TOUCH_EVENT_NONE) return; //do nothing before getting touch event.
	Point pos = (Point) { obj->Location.x + offset.x, obj->Location.y + offset.y};
	for (int i = 0; i < obj->ChildrenNum; i++)
	{
		Widget* widget = obj->Children[i];
		if (!widget->Visible) continue;
		if (widget_is_point_in_rect(TouchPointX, TouchPointY, pos.x +  widget->Location.x, pos.y + widget->Location.y, widget->Size.width, widget->Size.height))
		{
			if (widget->Type == PANEL) panel_touch_event_to_control((Panel*)widget, pos);
			else if (widget->Type == TABCONTROL) tabcontrol_touch_event_to_control((TabControl*)widget, pos);
			else
			{
				if(TouchEventStatus == TOUCH_EVENT_DOWN) panel_set_focus_widget(widget, 0);
			}
			
			switch (TouchEventStatus)			
			{
			case TOUCH_EVENT_DOWN:
				if (widget->Event_Down) {
					widget->Event_Down(widget, TouchPointX - offset.x, TouchPointY - offset.y);
				}
				break;
			case TOUCH_EVENT_HOLD:
				if (widget->Event_Hold) {
					widget->Event_Hold(widget, TouchPointX - offset.x, TouchPointY - offset.y);
				}
				break;
			case TOUCH_EVENT_UP:
				if (widget->Event_Up) {
					widget->Event_Up(widget, TouchPointX - offset.x, TouchPointY - offset.y);
				}
				break;
			}
			
			
		}
	}
	//touchScreenIsPress = 0;
}

void panel_update_control_value(Panel* obj, char* name, char* value)
{
	uint16_t ChildIndex = 0;
	for (ChildIndex = 0; ChildIndex < obj->ChildrenNum; ChildIndex++)
	{
		Widget* child = obj->Children[ChildIndex];
		if(strcmp(name, child->Name) == 0)
			widget_update_value(child, value);
	}
}
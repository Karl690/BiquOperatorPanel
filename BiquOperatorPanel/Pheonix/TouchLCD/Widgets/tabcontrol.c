#include "widget.h"
#include "panel.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "listbox.h"
#include "panel.h"
#include "tabcontrol.h"
#include "../lcd_touch.h"

void tabcontrol_destory(TabControl* obj)
{	
	free(obj);
}
void tabcontrol_add_child(TabControl* obj, void* button, void* panel)
{
	if (obj->ChildrenNum >= TAB_MAX_PANEL_NUM) return; //do nothing in this case.
	obj->Buttons[obj->ChildrenNum] = button;
	obj->Panels[obj->ChildrenNum] = panel;
	obj->ChildrenNum++;
}

void tabcontrol_update(TabControl* obj)
{	
	obj->StackIndex = 0xff;
}
void tabcontrol_on_paint(TabControl* obj, Point offset, Color16  backcolor, uint8_t forceRedraw)
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
			obj->RedrawMe = 0;
		}
		forceRedraw = 1;
	}
	
	//there are several possibilitys
	//1. we want to refresh the whole screen, that is forceRedraw flag
	//2. we want to redraw just this component, that is the redraw screen
	//3. we want to hide this component, set the .visible=0, redraw to 1;
	for (ChildIndex = 0; ChildIndex < obj->ChildrenNum; ChildIndex ++)
	{
		if (obj->RedrawMe || forceRedraw)
			button_on_paint(obj->Buttons[ChildIndex], pos, obj->BackColor);
		
		if (ChildIndex == obj->StackIndex) // draw only the selected panel
			panel_on_paint(obj->Panels[ChildIndex], pos, obj->BackColor, forceRedraw);
	}
	obj->RedrawMe = 0;
}

void tabcontrol_select_panel(TabControl* obj, uint16_t New_index)
{
	uint16_t old_index = obj->StackIndex;
	if (New_index == old_index) return;//if the same as before,return without processing.
	if (old_index < TAB_MAX_PANEL_NUM)
	{
		((Button*)obj->Buttons[old_index])->Checked = 0; //turn off previous selection button
		((Button*)obj->Buttons[old_index])->RedrawMe = 1;
		
	}
	((Button*)obj->Buttons[New_index])->Checked = 1; //turn off previous selection button
	((Button*)obj->Buttons[New_index])->RedrawMe = 1;	
	
	if (old_index < TAB_MAX_PANEL_NUM)
		((Panel*)obj->Panels[old_index])->Visible =  0; //turn off old panel refresh
	((Panel*)obj->Panels[New_index])->Visible = 1;
	((Panel*)obj->Panels[New_index])->RedrawMe = 1;
	
	obj->StackIndex = New_index;
	obj->RedrawMe = 1;
}

void* tabcontrol_get_active_panel(TabControl* obj)
{
	return obj->Panels[obj->StackIndex];
}

void tabcontrol_touch_event_to_control(TabControl* obj, Point offset)
{
	if (!touchScreenIsPress) return;
	Point pos = (Point) { obj->Location.x + offset.x, obj->Location.y + offset.y };
	for (uint16_t i = 0; i < obj->ChildrenNum; i++)
	{
		Widget* widget = obj->Buttons[i];
		if (widget_is_point_in_rect(TouchPointX, TouchPointY, pos.x +  widget->Location.x, pos.y + widget->Location.y, widget->Size.width, widget->Size.height))
		{
			tabcontrol_select_panel(obj, i);
			break;
		}
	}
	
	panel_touch_event_to_control(tabcontrol_get_active_panel(obj), pos);
}

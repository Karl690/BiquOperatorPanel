#include "widget.h"
#include "panel.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "listbox.h"
#include "panel.h"
#include "tabcontrol.h"
#include "../lcd_touch.h"

void tabcontrol_destory(TabControl* tab)
{	
	free(tab);
}
void tabcontrol_add_child(TabControl* tab, void* button, void* panel)
{
	tab->Buttons[tab->ChildrenNum] = button;
	tab->Panels[tab->ChildrenNum] = panel;
	tab->ChildrenNum++;
}

void tabcontrol_update(TabControl* tab)
{	
	tab->StackIndex = 0xffff;
}
void tabcontrol_on_paint(TabControl* tab, Point offset, Color16  backcolor, uint8_t forceRedraw)
{
	uint16_t ChildIndex = 0;
	Point pos = (Point) { tab->Location.x + offset.x, tab->Location.y + offset.y };
	
	if (!tab->Visible || tab->RedrawMe) {
		GUI_FillRect(pos.x, pos.y, pos.x + tab->Size.width, pos.y + tab->Size.height, backcolor);
		
		tab->RedrawMe = 0;
	}
	//at this point we have been asked to paint a Panel and all children in the panel
	if (!tab->Visible) return;//dont draw unless we have permission

	if (tab->RedrawMe||forceRedraw)
	{//going to rdraw the entire panel, so go ahead and paint the background first

		if (Refresh_Widget((Widget*)tab, forceRedraw)) {		
			GUI_FillRect(pos.x, pos.y, pos.x + tab->Size.width, pos.y + tab->Size.height, tab->BackColor);
			
			if (tab->BorderWidth > 0)
			{	
				GUI_DrawRect(pos.x, pos.y, pos.x + tab->Size.width, pos.y + tab->Size.height, tab->BorderColor);
			}
			tab->RedrawMe = 0;
			
			
		}
		forceRedraw = 1;
	}
	
	//there are several possibilitys
	//1. we want to refresh the whole screen, that is forceRedraw flag
	//2. we want to redraw just this component, that is the redraw screen
	//3. we want to hide this component, set the .visible=0, redraw to 1;
	for (ChildIndex = 0; ChildIndex < tab->ChildrenNum; ChildIndex ++)
	{
		button_on_paint(tab->Buttons[ChildIndex], pos, tab->BackColor);
		
		if(ChildIndex == tab->StackIndex) // draw only the selected panel
			panel_on_paint(tab->Panels[ChildIndex], pos, tab->BackColor, forceRedraw);
	}
	tab->RedrawMe = 0;
}

void tabcontrol_select_panel(TabControl* tab, uint16_t  index)
{
	if (index == tab->StackIndex) return;
	for (uint16_t i = 0; i < tab->ChildrenNum; i++)
	{
		((Button*)tab->Buttons[i])->Checked = index == i ? 1 : 0;
		((Button*)tab->Buttons[i])->RedrawMe = 1;
		((Panel*)tab->Panels[i])->Visible = index == i? 1: 0;
		((Panel*)tab->Panels[i])->RedrawMe = 1;
		
	}
	tab->StackIndex = index;
	tab->RedrawMe = 1;
}

void* tabcontrol_get_active_panel(TabControl* tab)
{
	return tab->Panels[tab->StackIndex];
}

void tabcontrol_touch_event_to_control(TabControl* tab, Point offset)
{
	if (!touchScreenIsPress) return;
	Point pos = (Point) { tab->Location.x + offset.x, tab->Location.y + offset.y };
	for (uint16_t i = 0; i < tab->ChildrenNum; i++)
	{
		Widget* widget = tab->Buttons[i];
		if (widget_is_point_in_rect(TouchPointX, TouchPointY, pos.x +  widget->Location.x, pos.y + widget->Location.y, widget->Size.width, widget->Size.height))
		{
			tabcontrol_select_panel(tab, i);
			break;
		}
	}
	
	panel_touch_event_to_control(tabcontrol_get_active_panel(tab), pos);
}

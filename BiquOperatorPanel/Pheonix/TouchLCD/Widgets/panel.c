#include "widget.h"
#include "panel.h"
#include "label.h"
#include "button.h"
void panel_init(Panel* panel)
{
	panel->Location = (Point) { 0, 0 };
	panel->Size = (Size) { 0, 0};
	panel->ChildrenNum = 0;
}
void panel_add_child(Panel* panel, void* child)
{
	panel->Children[panel->ChildrenNum] = child;
	panel->ChildrenNum++;
}

void panel_on_paint(Panel* panel, Point posParent) 
{
	Point pos = { panel->Location.x + posParent.x, panel->Location.y + posParent.y };
	GUI_FillRect(pos.x, pos.y, pos.x + panel->Size.width, pos.y + panel->Size.height, panel->BackColor);
	
	
	uint16_t ChildIndex = 0;
	for (ChildIndex = 0; ChildIndex < panel->ChildrenNum; ChildIndex ++)
	{
		Widget* child = panel->Children[ChildIndex];
		
		switch (child->Type)
		{
		case BUTTON:
			button_on_paint((Button*)child, pos);
			break;
		case LABEL:
			label_on_paint((Label*)child, pos);
			break;
		default:
			break;
		}
		
	}
}
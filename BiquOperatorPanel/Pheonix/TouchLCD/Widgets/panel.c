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

void panel_on_paint(Panel* panel) 
{
	GUI_FillRect(panel->Location.x, panel->Location.y, panel->Location.x + panel->Size.width, panel->Location.y + panel->Size.height, panel->BackgroundColor);
	
	
	uint16_t ChildIndex = 0;
	for (ChildIndex = 0; ChildIndex < panel->ChildrenNum; ChildIndex++)
	{
		Widget* child = panel->Children[ChildIndex];
		
		switch (child->Type)
		{
		case BUTTON:
			button_on_paint((Button*)child);
			break;
		case LABEL:
			label_on_paint((Label*)child);
			break;
		default:
			break;
		}
		
	}
}
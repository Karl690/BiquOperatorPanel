#include "panel.h"
#include "label.h"
#include "button.h"
void panel_init(Panel* panel)
{
	panel->Parent.Location = (Point) { 0, 0 };
	panel->Parent.Size = (Size) { 0, 0};
	panel->ChildrenNum = 0;
}
void panel_add_child(Panel* panel, void* child)
{
	panel->Children[panel->ChildrenNum] = child;
	panel->ChildrenNum++;
}

void panel_on_paint(Panel* panel) 
{
	Widget* parent = (Widget*)panel;
	GUI_FillRect(parent->Location.x, parent->Location.y, parent->Location.x + parent->Size.width, parent->Location.y + parent->Size.height, parent->BackgroundColor);
	
	
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
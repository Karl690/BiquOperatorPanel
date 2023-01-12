#include "../GUI/gui.h"
#include "listbox.h"
#include "Panel.h"

void listbox_destory(Listbox* listbox)
{
	free(listbox);
}
void listbox_update(Listbox* listbox)
{
	//update corner points.

}
void listbox_on_paint(Listbox* listbox, Panel* Parent)
{	
	listbox->RedrawMe = 0;
	Point pos = { Parent->Location.x + listbox->Location.x, Parent->Location.y + listbox->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + listbox->Size.width, pos.y + listbox->Size.height, listbox->BackColor);
}
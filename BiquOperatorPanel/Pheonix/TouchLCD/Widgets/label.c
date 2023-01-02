#include "../GUI/gui.h"
#include "label.h"

void label_on_paint(Label* label, Point posParent)
{	
	Point pos = { posParent.x + label->Location.x, posParent.y + label->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BackColor);
	if (label->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BorderColor);
	}
	GUI_DrawString(pos.x, pos.y, label->Text, label->Font, label->ForeColor);
		
}
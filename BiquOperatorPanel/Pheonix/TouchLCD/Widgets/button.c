#include "../GUI/gui.h"
#include "button.h"

void button_on_paint(Button* button, Point posParent)
{
	Point pos = { posParent.x + button->Location.x, posParent.y + button->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->BackColor);
	if (button->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->BorderColor);
	}
	GUI_DrawString(pos.x, pos.y, button->Text, button->Font, button->ForeColor);
		
}
#include "../GUI/gui.h"
#include "button.h"

void button_on_paint(Button* button)
{
	Widget* parent = (Widget*)button;
	GUI_FillRect(button->Location.x, button->Location.y, button->Location.x + button->Size.width, button->Location.y + button->Size.height, button->BackgroundColor);
	if (button->BorderWidth > 0)
	{
		GUI_DrawRect(button->Location.x, button->Location.y, button->Location.x + button->Size.width, button->Location.y + button->Size.height, button->BorderColor);
	}
	GUI_DrawString(button->Location.x + 2, button->Location.y + 2, button->Text, button->ForegroundColor);
		
}
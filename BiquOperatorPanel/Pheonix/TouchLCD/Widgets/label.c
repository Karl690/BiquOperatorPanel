#include "../GUI/gui.h"
#include "label.h"

void label_draw(Label* button)
{	
	if (button->Boarder > 0)
	{
		GUI_DrawRect(button->Location.x, button->Location.y, button->Location.x + button->Size.width, button->Location.y + button->Size.height, button->BorderColor);
	}
	GUI_DrawString(button->Location.x + 2, button->Location.y + 2, button->Text, button->ForegroundColor);
		
}
#include "../GUI/gui.h"
#include "label.h"

void label_on_paint(Label* button)
{	
	Widget* parent = (Widget*)button;
	//GUI_FillRect(parent->Location.x, parent->Location.y, parent->Location.x + parent->Size.width, parent->Location.y + parent->Size.height, parent->BackgroundColor);
	if (parent->Boarder > 0)
	{
		GUI_DrawRect(parent->Location.x, parent->Location.y, parent->Location.x + parent->Size.width, parent->Location.y + parent->Size.height, parent->BorderColor);
	}
	GUI_DrawString(parent->Location.x + 2, parent->Location.y + 2, parent->Text, parent->ForegroundColor);
		
}
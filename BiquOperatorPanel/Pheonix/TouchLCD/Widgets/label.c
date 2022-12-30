#include "../GUI/gui.h"
#include "label.h"

void label_on_paint(Label* label)
{	
	//GUI_FillRect(parent->Location.x, parent->Location.y, parent->Location.x + parent->Size.width, parent->Location.y + parent->Size.height, parent->BackgroundColor);
	if (label->BorderWidth > 0)
	{
		GUI_DrawRect(label->Location.x, label->Location.y, label->Location.x + label->Size.width, label->Location.y + label->Size.height, label->BorderColor);
	}
	GUI_DrawString(label->Location.x + 2, label->Location.y + 2, label->Text, label->ForegroundColor);
		
}
#include "../GUI/gui.h"
#include "label.h"
#include "Panel.h"

void label_destory(Label* label)
{
	free(label);
}

void label_on_paint(Label* label, Point offset, Color16  backcolor)
{	
	label->RedrawMe = 0;
	Point pos = { offset.x + label->Location.x, offset.y + label->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BackColor);
	if (label->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BorderColor);
	}
	if (!label->Text) return;
	widget_draw_string(label->Text,
		pos.x,
		pos.y,
		label->Size.width,
		label->Size.height,
		&label->Padding,
		label->Font,
		label->TextAlign, 
		label->ForeColor,
		label->BackColor);
		
}
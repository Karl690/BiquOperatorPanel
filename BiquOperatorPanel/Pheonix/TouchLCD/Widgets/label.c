#include "../GUI/gui.h"
#include "label.h"
#include "Panel.h"

Label* label_init(Widget* parent)
{
	Label* label = (Label*)malloc(sizeof(Label));
	label->Type = LABEL;
	label->Location = (Point) { 0, 0 };
	label->Size = (Size) { 0, 0 };
	label->Parent = parent;
	return label;
}
void label_destory(Label* label)
{
	free(label);
}

void label_on_paint(Label* label, Panel* Parent)
{	
	label->RedrawMe = 0;
	Point pos = { Parent->Location.x + label->Location.x, Parent->Location.y + label->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BackColor);
	if (label->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + label->Size.width, pos.y + label->Size.height, label->BorderColor);
	}
	if (!label->Text) return;
	uint8_t len = strlen(label->Text);
	switch (label->TextAlign)
	{
	case TopLeft:
		pos.x += label->Padding.left;
		pos.y += label->Padding.top;
		break;
	case TopCenter:
		pos.x += (label->Size.width - len * label->Font->Width) /2;
		pos.y += label->Padding.top;
		break;
	case TopRight:
		pos.x += label->Size.width - label->Padding.right - len * label->Font->Width;
		pos.y += label->Padding.top;
		break;
	case MiddleLeft:
		pos.x += label->Padding.left;
		pos.y += (label->Size.height - label->Font->Height) /2;
		break;
	case MiddleCenter:
		pos.x += (label->Size.width - len * label->Font->Width) / 2;
		pos.y += (label->Size.height - label->Font->Height) / 2;
		break;
	case MiddleRight:
		pos.x += label->Size.width - label->Padding.right - len * label->Font->Width;
		pos.y += (label->Size.height - label->Font->Height) / 2;
		break;
	case BottomLeft:
		pos.x += label->Padding.left;
		pos.y += label->Size.height - label->Padding.bottom - label->Font->Height;
		break;
	case BottomCenter:
		pos.x += (label->Size.width - len * label->Font->Width) / 2;
		pos.y += label->Size.height - label->Padding.bottom - label->Font->Height;
		break;
	case BottomRight:
		pos.x += label->Size.width - label->Padding.right - len * label->Font->Width;
		pos.y += label->Size.height - label->Padding.bottom - label->Font->Height;
		break;
	default:
		pos.x += label->Padding.left;
		pos.y += label->Padding.top;
		break;
	}
	GUI_DrawString(pos.x, pos.y, label->Text, label->Font, label->ForeColor, label->BackColor);
		
}
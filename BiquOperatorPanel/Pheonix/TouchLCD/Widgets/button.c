#include "../GUI/gui.h"
#include "button.h"

Button* button_init(Widget* parent)
{
	Button* button = (Button*)malloc(sizeof(Button));
	button->Type = LABEL;
	button->Location = (Point) { 0, 0 };
	button->Size = (Size) { 0, 0 };
	button->Parent = parent;
	return button;
}
void button_destory(Button* button)
{
	free(button);
}

void button_on_paint(Button* button, Point posParent)
{
	button->RedrawMe = 0;//we are repainting this, so turn off the redraw property
	Point pos = { posParent.x + button->Location.x, posParent.y + button->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->BackColor);
	if (button->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->BorderColor);
	}
	uint8_t len = strlen(button->Text);
	switch (button->TextAlign)
	{
	case TopLeft:
		pos.x += button->Padding.left;
		pos.y += button->Padding.top;
		break;
	case TopCenter:
		pos.x += (button->Size.width - len * button->Font->Width) / 2;
		pos.y += button->Padding.top;
		break;
	case TopRight:
		pos.x += button->Size.width - button->Padding.right - len * button->Font->Width;
		pos.y += button->Padding.top;
		break;
	case MiddleLeft:
		pos.x += button->Padding.left;
		pos.y += (button->Size.height - button->Font->Height) / 2;
		break;
	case MiddleCenter:
		pos.x += (button->Size.width - len * button->Font->Width) / 2;
		pos.y += (button->Size.height - button->Font->Height) / 2;
		break;
	case MiddleRight:
		pos.x += button->Size.width - button->Padding.right - len * button->Font->Width;
		pos.y += (button->Size.height - button->Font->Height) / 2;
		break;
	case BottomLeft:
		pos.x += button->Padding.left;
		pos.y += button->Size.height - button->Padding.bottom - button->Font->Height;
		break;
	case BottomCenter:
		pos.x += (button->Size.width - len * button->Font->Width) / 2;
		pos.y += button->Size.height - button->Padding.bottom - button->Font->Height;
		break;
	case BottomRight:
		pos.x += button->Size.width - button->Padding.right - len * button->Font->Width;
		pos.y += button->Size.height - button->Padding.bottom - button->Font->Height;
		break;
	default:
		pos.x += button->Padding.left;
		pos.y += button->Padding.top;
		break;
	}
	GUI_DrawString(pos.x, pos.y, button->Text, button->Font, button->ForeColor, button->BackColor);
		
}
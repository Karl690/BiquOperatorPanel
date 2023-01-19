#include "../GUI/gui.h"
#include "numeric.h"
#include "Panel.h"

void numeric_update(Numeric* numeric)
{
	//update corner points.
	numeric->CornerPoints[0] = (Point) { 0, numeric->CornerRadius };
	numeric->CornerPoints[1] = (Point){ 0, numeric->Size.height - numeric->CornerRadius - 1 };
	numeric->CornerPoints[2] = (Point) { numeric->CornerRadius, numeric->Size.height - 1 };
	numeric->CornerPoints[3] = (Point) { numeric->Size.width - numeric->CornerRadius - 1, numeric->Size.height - 1 };
	numeric->CornerPoints[4] = (Point) { numeric->Size.width - 1, numeric->Size.height - numeric->CornerRadius - 1 };
	numeric->CornerPoints[5] = (Point) { numeric->Size.width - 1, numeric->CornerRadius };
	numeric->CornerPoints[6] = (Point) { numeric->Size.width - numeric->CornerRadius - 1, 0 };
	numeric->CornerPoints[7] = (Point) { numeric->CornerRadius, 0 };
	numeric->CornerPoints[8] = (Point) { 0, numeric->CornerRadius };
	sprintf(numeric->Text, "%d", numeric->Value);
}
void numeric_on_paint(Numeric* numeric, Point offset, Color16  backcolor)
{	
	numeric->RedrawMe = 0;
	Point pos = { offset.x + numeric->Location.x, offset.y + numeric->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + numeric->Size.width, pos.y + numeric->Size.height, numeric->IsFocus?numeric->FocusBackColor: numeric->BackColor);
	if (numeric->BorderWidth > 0)
	{
		//GUI_DrawRect(pos.x, pos.y, pos.x + edit->Size.width, pos.y + edit->Size.height, edit->BorderColor);
		GUI_DrawPolygon(numeric->CornerPoints, sizeof(numeric->CornerPoints) / sizeof(Point), numeric->IsFocus?numeric->FocusBorderColor: numeric->BorderColor, pos);
	}
	
	widget_draw_string(numeric->Text,
		pos.x,
		pos.y,
		numeric->Size.width,
		numeric->Size.height,
		&numeric->Padding,
		numeric->Font,
		numeric->TextAlign, 
		numeric->IsFocus?numeric->FocusForeColor: numeric->ForeColor,
		numeric->IsFocus?numeric->FocusBackColor: numeric->BackColor);
}

void numeric_set_min_max(Numeric* numeric, int min, int max)
{
	numeric->MaxValue = max;
	numeric->MinValue = min;
}

void numeric_increment(Numeric* numeric)
{
	if (numeric->Value + 1<= numeric->MaxValue)
	{
		numeric->Value++;
		sprintf(numeric->Text, "%d", numeric->Value);
		numeric->RedrawMe = 1;
	}
}

void numeric_decrement(Numeric* numeric)
{
	if (numeric->Value -1>= numeric->MinValue)
	{
		numeric->Value--;
		sprintf(numeric->Text, "%d", numeric->Value);
		numeric->RedrawMe = 1;
	}
}

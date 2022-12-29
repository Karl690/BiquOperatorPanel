#include "gui.h"
#include "icons.h"
#include "../Widgets/Widget.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"
void Init_MainView()
{
	
	Label XPosLabel;
	XPosLabel.ForegroundColor = RGB16(255, 255, 255);
	XPosLabel.Boarder = 1;
	XPosLabel.BorderColor = RGB16(255, 255, 255);
	XPosLabel.Location = (Point){ .x = 20, .y = 20 };
	XPosLabel.Size = (Size) { .width = 70, .height = 30 };
	XPosLabel.Text = "X: ";
	
	label_draw(&XPosLabel);
	
	Button StartButton;
	StartButton.BackgroundColor = RGB16(255, 0, 0);
	StartButton.ForegroundColor = RGB16(255, 255, 255);
	StartButton.Boarder = 1;
	StartButton.BorderColor = RGB16(255, 255, 255);
	StartButton.Location = (Point){ .x = 20, .y = 100 };
	StartButton.Size = (Size) { .width = 70, .height = 30 };
	StartButton.Text = "Start";
	StartButton.CornerRadius = 2;
	button_draw(&StartButton);
	
	
	//GUI_WriteBuffer(100, 100, IconStart.width, IconStart.height, IconStart.buffer);
}
#include "gui.h"
#include "icons.h"
#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"
void Init_MainView()
{
	
	Panel MainPanel;
	panel_init(&MainPanel);
	MainPanel.Parent.Location = (Point){ .x = 20, .y = 20 };
	
	Label XPosLabel;
	XPosLabel.Parent.Type = LABEL;
	XPosLabel.Parent.ForegroundColor = RGB16(255, 255, 255);
	XPosLabel.Parent.Boarder = 1;
	XPosLabel.Parent.BorderColor = RGB16(255, 255, 255);
	XPosLabel.Parent.Location = (Point){ .x = 20, .y = 20 };
	XPosLabel.Parent.Size = (Size) { .width = 70, .height = 30 };
	XPosLabel.Parent.Text = "X: ";
	
	panel_add_child(&MainPanel, &XPosLabel);
	//label_draw(&XPosLabel);
	
	Button StartButton;
	StartButton.Parent.Type = BUTTON;
	StartButton.Parent.BackgroundColor = RGB16(0, 255, 0);
	StartButton.Parent.ForegroundColor = RGB16(255, 255, 255);
	StartButton.Parent.Boarder = 1;
	StartButton.Parent.BorderColor = RGB16(255, 255, 255);
	StartButton.Parent.Location = (Point){ .x = 20, .y = 100 };
	StartButton.Parent.Size = (Size) { .width = 70, .height = 30 };
	StartButton.Parent.Text = "Start";
	StartButton.Parent.CornerRadius = 2;
	
	panel_add_child(&MainPanel, &StartButton);
	
	Button StopButton;
	StopButton.Parent.Type = BUTTON;
	StopButton.Parent.BackgroundColor = RGB16(255, 0, 0);
	StopButton.Parent.ForegroundColor = RGB16(255, 255, 255);
	StopButton.Parent.Boarder = 1;
	StopButton.Parent.BorderColor = RGB16(255, 255, 255);
	StopButton.Parent.Location = (Point){ .x = 100, .y = 100 };
	StopButton.Parent.Size = (Size) { .width = 70, .height = 30 };
	StopButton.Parent.Text = "Stop";
	StopButton.Parent.CornerRadius = 2;
	
	panel_add_child(&MainPanel, &StopButton);
	
	panel_on_paint(&MainPanel);
	
	//GUI_WriteBuffer(100, 100, IconStart.width, IconStart.height, IconStart.buffer);
}
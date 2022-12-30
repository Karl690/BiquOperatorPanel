#include "gui.h"
#include "icons.h"
#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"
void InitPanelMain()
{
	
	Panel MainPanel;
	panel_init(&MainPanel);
	MainPanel.Location = (Point){ .x = 50, .y = 20 };
	MainPanel.Size = (Size){ .width = 700, .height = 400};
	MainPanel.BackgroundColor = COLOR_GREEN;
	
	Label XPosLabel;
	XPosLabel.Type = LABEL;
	XPosLabel.ForegroundColor = RGB16(255, 255, 255);
	XPosLabel.BorderWidth  = 1;
	XPosLabel.BorderColor = RGB16(255, 255, 255);
	XPosLabel.Location = (Point){ .x = 20, .y = 20 };
	XPosLabel.Size = (Size) { .width = 70, .height = 30 };
	strcpy(XPosLabel.Text , "X: ");
	
	
	panel_add_child(&MainPanel, &XPosLabel);
	//label_draw(&XPosLabel);
	
	Button StartButton;
	StartButton.Type = BUTTON;
	StartButton.BackgroundColor = RGB16(0, 255, 0);
	StartButton.ForegroundColor = RGB16(255, 255, 255);
	StartButton.BorderWidth = 1;
	StartButton.BorderColor = RGB16(255, 255, 255);
	StartButton.Location = (Point){ .x = 20, .y = 100 };
	StartButton.Size = (Size) { .width = 70, .height = 30 };
	strcpy(StartButton.Text, "Start");
	
	
	panel_add_child(&MainPanel, &StartButton);
	
	Button StopButton;
	StopButton.Type = BUTTON;
	StopButton.BackgroundColor = RGB16(255, 0, 0);
	StopButton.ForegroundColor = RGB16(255, 255, 255);
	StopButton.BorderWidth = 1;
	StopButton.BorderColor = RGB16(255, 255, 255);
	StopButton.Location = (Point){ .x = 100, .y = 100 };
	StopButton.Size = (Size) { .width = 70, .height = 30 };
	strcpy(StopButton.Text, "Stop");
	
	panel_add_child(&MainPanel, &StopButton);
	
	panel_on_paint(&MainPanel, (Point){0,0});
	
	//GUI_WriteBuffer(100, 100, IconStart.width, IconStart.height, IconStart.buffer);
}
#include "gui.h"
#include "icons.h"
#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"

#include "font.h"


void InitPanelMain()
{
	Panel panelMain;
	panel_init(&panelMain); 
	panelMain.BackColor = RGB16(24, 63, 31);
	panelMain.Location = (Point){ .x = 80, .y = 45 };
	panelMain.Size = (Size){ .width = 720, .height = 435 };
	//Components in this panel

	Panel panelHeader;
	panel_init(&panelHeader); 
	panelHeader.BackColor = RGB16(8, 16, 8);
	panelHeader.Location = (Point){ .x = 80, .y = 0 };
	panelHeader.Size = (Size){ .width = 720, .height = 45 };
	
	//Components in this panel
	Label label1;
	label1.Type = LABEL;
	label1.BackColor = RGB16(8, 16, 8);
	label1.ForeColor = RGB16(24, 63, 31);
	label1.BorderWidth = 0;
	label1.BorderColor = COLOR_BLACK;
	label1.Location = (Point){ .x = 206, .y = 0 };
	label1.Size = (Size){ .width = 357, .height = 44 };
	label1.Font = &Font24;
	label1.Padding = (PADDING) { 2, 2, 2, 2};
	label1.TextAlign = MiddleCenter;
	strcpy(label1.Text, "PCT Megaconic 23000");
	panel_add_child(&panelHeader, &label1); //add to the panel


	Panel panelTabSelect;
	panel_init(&panelTabSelect); 
	panelTabSelect.BackColor = RGB16(0, 0, 0);
	panelTabSelect.Location = (Point){ .x = 0, .y = 0 };
	panelTabSelect.Size = (Size){ .width = 80, .height = 480 };
	//Components in this panel
	Button button7;
	button7.Type = BUTTON;
	button7.BackColor = RGB16(0, 63, 31);
	button7.ForeColor = RGB16(0, 0, 0);
	button7.BorderWidth = 1;
	button7.BorderColor = COLOR_BLACK;
	button7.Location = (Point){ .x = 0, .y = 313 };
	button7.Size = (Size){ .width = 80, .height = 50 };
	button7.Font = &Font16;
	button7.Padding = (PADDING) { 2, 2, 2, 2 };
	button7.TextAlign = MiddleCenter;
	strcpy(button7.Text, "<<<");
	panel_add_child(&panelTabSelect, &button7); //add to the panel

	Button button6;
	button6.Type = BUTTON;
	button6.BackColor = RGB16(0, 63, 31);
	button6.ForeColor = RGB16(0, 0, 0);
	button6.BorderWidth = 1;
	button6.BorderColor = COLOR_BLACK;
	button6.Location = (Point){ .x = 0, .y = 366 };
	button6.Size = (Size){ .width = 80, .height = 50 };
	button6.Font = &Font16;
	button6.TextAlign = MiddleCenter;
	strcpy(button6.Text, "<<<");
	panel_add_child(&panelTabSelect, &button6); //add to the panel

	Button button5;
	button5.Type = BUTTON;
	button5.BackColor = RGB16(0, 63, 31);
	button5.ForeColor = RGB16(0, 0, 0);
	button5.BorderWidth = 1;
	button5.BorderColor = COLOR_BLACK;
	button5.Location = (Point){ .x = 0, .y = 419 };
	button5.Size = (Size){ .width = 80, .height = 50 };
	button5.Font = &Font16;
	button5.TextAlign = MiddleCenter;
	strcpy(button5.Text, "<<<");
	panel_add_child(&panelTabSelect, &button5); //add to the panel

	Button buttonFreqncies;
	buttonFreqncies.Type = BUTTON;
	buttonFreqncies.BackColor = RGB16(0, 63, 31);
	buttonFreqncies.ForeColor = RGB16(0, 0, 0);
	buttonFreqncies.BorderWidth = 1;
	buttonFreqncies.BorderColor = COLOR_BLACK;
	buttonFreqncies.Location = (Point){ .x = 0, .y = 101 };
	buttonFreqncies.Size = (Size){ .width = 80, .height = 50 };
	buttonFreqncies.Font = &Font16;
	buttonFreqncies.TextAlign = MiddleCenter;
	strcpy(buttonFreqncies.Text, "<<<");
	panel_add_child(&panelTabSelect, &buttonFreqncies); //add to the panel

	Button buttonDiangositcs;
	buttonDiangositcs.Type = BUTTON;
	buttonDiangositcs.BackColor = RGB16(0, 63, 31);
	buttonDiangositcs.ForeColor = RGB16(0, 0, 0);
	buttonDiangositcs.BorderWidth = 1;
	buttonDiangositcs.BorderColor = COLOR_BLACK;
	buttonDiangositcs.Location = (Point){ .x = 0, .y = 154 };
	buttonDiangositcs.Size = (Size){ .width = 80, .height = 50 };
	buttonDiangositcs.Font = &Font16;
	buttonDiangositcs.TextAlign = MiddleCenter;
	strcpy(buttonDiangositcs.Text, "<<<");
	panel_add_child(&panelTabSelect, &buttonDiangositcs); //add to the panel

	Button buttonManualControl;
	buttonManualControl.Type = BUTTON;
	buttonManualControl.BackColor = RGB16(0, 63, 31);
	buttonManualControl.ForeColor = RGB16(0, 0, 0);
	buttonManualControl.BorderWidth = 1;
	buttonManualControl.BorderColor = COLOR_BLACK;
	buttonManualControl.Location = (Point){ .x = 0, .y = 260 };
	buttonManualControl.Size = (Size){ .width = 80, .height = 50 };
	buttonManualControl.Font = &Font16;
	buttonManualControl.TextAlign = MiddleCenter;
	strcpy(buttonManualControl.Text, "<<<");
	panel_add_child(&panelTabSelect, &buttonManualControl); //add to the panel

	Button buttonTune;
	buttonTune.Type = BUTTON;
	buttonTune.BackColor = RGB16(0, 63, 31);
	buttonTune.ForeColor = RGB16(0, 0, 0);
	buttonTune.BorderWidth = 1;
	buttonTune.BorderColor = COLOR_BLACK;
	buttonTune.Location = (Point){ .x = 0, .y = 207 };
	buttonTune.Size = (Size){ .width = 80, .height = 50 };
	buttonTune.Font = &Font16;
	buttonTune.TextAlign = MiddleCenter;
	strcpy(buttonTune.Text, "<<<");
	panel_add_child(&panelTabSelect, &buttonTune); //add to the panel

	Button buttonLSecs;
	buttonLSecs.Type = BUTTON;
	buttonLSecs.BackColor = RGB16(0, 63, 31);
	buttonLSecs.ForeColor = RGB16(0, 0, 0);
	buttonLSecs.BorderWidth = 1;
	buttonLSecs.BorderColor = COLOR_BLACK;
	buttonLSecs.Location = (Point){ .x = 0, .y = 48 };
	buttonLSecs.Size = (Size){ .width = 80, .height = 50 };
	buttonLSecs.Font = &Font16;
	buttonLSecs.TextAlign = MiddleCenter;
	strcpy(buttonLSecs.Text, "<<<");
	panel_add_child(&panelTabSelect, &buttonLSecs); //add to the panel

	Button buttonHome;
	buttonHome.Type = BUTTON;
	buttonHome.BackColor = RGB16(31, 0, 0);
	buttonHome.ForeColor = RGB16(0, 0, 0);
	buttonHome.BorderWidth = 1;
	buttonHome.BorderColor = COLOR_BLACK;
	buttonHome.Location = (Point){ .x = 0, .y = -5 };
	buttonHome.Size = (Size){ .width = 80, .height = 50 };
	buttonHome.Font = &Font16;
	buttonHome.TextAlign = MiddleCenter;
	strcpy(buttonHome.Text, ">>>");
	panel_add_child(&panelTabSelect, &buttonHome); //add to the panel


	// now we insert the paint events
	panel_on_paint(&panelMain, (Point){ 0, 0 });
	panel_on_paint(&panelHeader, (Point){ 0, 0 });
	panel_on_paint(&panelTabSelect, (Point){ 0, 0 });
}
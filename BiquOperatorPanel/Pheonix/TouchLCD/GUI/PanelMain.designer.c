#include "main.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
ControlUpdateInfo MainCtrlUpdateInfo[] = { 
	{ 0, &counter, "gL_Label5" }, 
	{ 0, &encoderSt, "gL_Label4" },
	{0, NULL, ""},
};

Panel * MainPanel = NULL;
void onCallback_gl_Button2_Up(uint32_t x, uint32_t y)
{
}
void onCallback_gl_Button2_Down(uint32_t x, uint32_t y)
{
	sprintf(logtext, "onCallback_gl_Button2_Down( %d %d)", x, y);
	GUI_DrawString(10, 10, logtext, &Font16, COLOR_LIME, COLOR_BLACK);
}

Panel* InitPanelMain()
{	
	Panel *gL_Panel1 = panel_init(NULL);
	gL_Panel1->Type = PANEL;
	strcpy(gL_Panel1->Name, "gL_Panel1");
	gL_Panel1->BackColor = RGB16(240, 240, 240);
	gL_Panel1->ForeColor = RGB16(0, 0, 0);
	gL_Panel1->BorderColor = RGB16(0, 139, 139);
	gL_Panel1->BorderWidth = 2;
	gL_Panel1->Location = (Point){ .x = 3, .y = 3 };
	gL_Panel1->Size = (Size){ .width = 600, .height = 480 };
	gL_Panel1->StackIndex = -1;
	//Components in this panel

	Label *gL_Label5 = label_init(gL_Panel1);
	gL_Label5->Type = LABEL;
	strcpy(gL_Label5->Name, "gL_Label5");
	gL_Label5->BackColor = RGB16(240, 240, 240);
	gL_Label5->ForeColor = RGB16(0, 0, 0);
	gL_Label5->BorderColor = RGB16(0, 139, 139);
	gL_Label5->BorderWidth = 0;
	gL_Label5->CornerRadius = 0;
	gL_Label5->Font = &Font24;
	gL_Label5->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5->TextAlign = TopLeft;
	gL_Label5->Location = (Point){ .x = 12, .y = 150 };
	gL_Label5->Size = (Size){ .width = 157, .height = 44 };
	strcpy(gL_Label5->Text, "24 POINT");
	panel_add_child(gL_Panel1, gL_Label5); //add to the panel

	Label *gL_Label4 = label_init(gL_Panel1);
	gL_Label4->Type = LABEL;
	strcpy(gL_Label4->Name, "gL_Label4");
	gL_Label4->BackColor = RGB16(240, 240, 240);
	gL_Label4->ForeColor = RGB16(0, 0, 0);
	gL_Label4->BorderColor = RGB16(0, 139, 139);
	gL_Label4->BorderWidth = 0;
	gL_Label4->CornerRadius = 0;
	gL_Label4->Font = &Font20;
	gL_Label4->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4->TextAlign = TopLeft;
	gL_Label4->Location = (Point){ .x = 37, .y = 108 };
	gL_Label4->Size = (Size){ .width = 108, .height = 37 };
	strcpy(gL_Label4->Text, "20 point");
	panel_add_child(gL_Panel1, gL_Label4); //add to the panel

	Label *gL_Label3 = label_init(gL_Panel1);
	gL_Label3->Type = LABEL;
	strcpy(gL_Label3->Name, "gL_Label3");
	gL_Label3->BackColor = RGB16(240, 240, 240);
	gL_Label3->ForeColor = RGB16(0, 0, 0);
	gL_Label3->BorderColor = RGB16(0, 139, 139);
	gL_Label3->BorderWidth = 0;
	gL_Label3->CornerRadius = 0;
	gL_Label3->Font = &Font16;
	gL_Label3->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3->TextAlign = TopLeft;
	gL_Label3->Location = (Point){ .x = 47, .y = 72 };
	gL_Label3->Size = (Size){ .width = 87, .height = 30 };
	strcpy(gL_Label3->Text, "16 Point");
	panel_add_child(gL_Panel1, gL_Label3); //add to the panel

	Label *gL_Label2 = label_init(gL_Panel1);
	gL_Label2->Type = LABEL;
	strcpy(gL_Label2->Name, "gL_Label2");
	gL_Label2->BackColor = RGB16(240, 240, 240);
	gL_Label2->ForeColor = RGB16(0, 0, 0);
	gL_Label2->BorderColor = RGB16(0, 139, 139);
	gL_Label2->BorderWidth = 0;
	gL_Label2->CornerRadius = 0;
	gL_Label2->Font = &Font12;
	gL_Label2->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2->TextAlign = TopLeft;
	gL_Label2->Location = (Point){ .x = 59, .y = 41 };
	gL_Label2->Size = (Size){ .width = 64, .height = 24 };
	strcpy(gL_Label2->Text, "12 point");
	panel_add_child(gL_Panel1, gL_Label2); //add to the panel

	Label *gL_Label1 = label_init(gL_Panel1);
	gL_Label1->Type = LABEL;
	strcpy(gL_Label1->Name, "gL_Label1");
	gL_Label1->BackColor = RGB16(240, 240, 240);
	gL_Label1->ForeColor = RGB16(0, 0, 0);
	gL_Label1->BorderColor = RGB16(0, 139, 139);
	gL_Label1->BorderWidth = 0;
	gL_Label1->CornerRadius = 0;
	gL_Label1->Font = &Font8;
	gL_Label1->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label1->TextAlign = TopLeft;
	gL_Label1->Location = (Point){ .x = 73, .y = 17 };
	gL_Label1->Size = (Size){ .width = 38, .height = 17 };
	strcpy(gL_Label1->Text, "8 point");
	panel_add_child(gL_Panel1, gL_Label1); //add to the panel

	Button *gL_Button1 = button_init(gL_Panel1);
	gL_Button1->Type = BUTTON;
	strcpy(gL_Button1->Name, "gL_Button1");
	gL_Button1->Event_Down = NULL;
	gL_Button1->Event_Hold = NULL;
	gL_Button1->Event_Up   = NULL;
	gL_Button1->BackColor = RGB16(255, 0, 0);
	gL_Button1->ForeColor = RGB16(0, 0, 0);
	gL_Button1->BorderColor = RGB16(0, 139, 139);
	gL_Button1->CheckedColor = RGB16(255, 0, 0);
	gL_Button1->BorderWidth = 2;
	gL_Button1->CornerRadius = 0;
	gL_Button1->Font = &Font20;
	gL_Button1->Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button1->TextAlign = MiddleCenter;
	gL_Button1->Location = (Point){ .x = 19, .y = 364 };
	gL_Button1->Size = (Size){ .width = 99, .height = 89 };
	strcpy(gL_Button1->Text, "Send");
	panel_add_child(gL_Panel1, gL_Button1); //add to the panel
	MainPanel = gL_Panel1;
	return gL_Panel1;// return the intialized panel instance.
}

void main_screen_loop_update_value()
{
	uint16_t i = 0;
	char str_value[32] = { 0 };
	while (1)
	{
		if (!MainCtrlUpdateInfo[i].point_for_value) break;
		if (MainCtrlUpdateInfo[i].cur_value != *MainCtrlUpdateInfo[i].point_for_value)
		{//it need to update.
			MainCtrlUpdateInfo[i].cur_value = *MainCtrlUpdateInfo[i].point_for_value;
			sprintf(str_value, "%d", MainCtrlUpdateInfo[i].cur_value);
			panel_update_control_value(MainPanel, MainCtrlUpdateInfo[i].control_name, str_value);
		}
		i++;
	}
}
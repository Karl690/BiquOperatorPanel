#include "main.h"
#include "PanelMain.designer.h"
#include "PanelMain.event.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
uint32_t *PanelHandleList[32]; //empty panel list, pointer handles to structures

Panel Root_Panel;
Button gL_Button2;
Button gL_Button1;
Button glBtnPlus;
Button glBtnMinus;
Panel gL_Panel4;
DropdownList glDropdownDisplayMode;
Listbox gL_Listbox1;
Panel gL_Panel3;
Label lblTitle;
TabControl glTabMain;
Button glTabMainTab_0;
Panel glTabMainPanel_0;
Panel gL_Panel7;
DropdownList gL_DropdownList1;
Label gL_Label15;
Label gL_Label2;
Numeric gL_Numeric2;
Panel gL_Panel5;
DropdownList gL_DropdownList2;
Label gL_Label17;
Label gL_Label16;
Numeric glNumeric_SimplePort;
Button glTabMainTab_1;
Panel glTabMainPanel_1;
Button glBtnLoadString;
Button glBtnSaveSoapstring;
Button gL_Button6;
Button gL_Button5;
Button gL_Button4;
Button glBtnEraseStorage;
Button glTabMainTab_2;
Panel glTabMainPanel_2;
Panel gL_Panel1;
Numeric glNudVars10;
Numeric glNudVars09;
Numeric glNudVars08;
Numeric glNudVars07;
Numeric glNudVars06;
Numeric glNudVars05;
Numeric glNudVars04;
Numeric glNudVars03;
Numeric glNudVars02;
Numeric glNudVars01;
Numeric glNudVars00;
Label gL_Label1;
Label gL_Label3;
Label gL_Label14;
Label gL_Label13;
Label gL_Label12;
Label gL_Label11;
Label gL_Label10;
Label gL_Label9;
Label gL_Label8;
Label gL_Label5;
Label gL_Label4;


void  InitPanelMain()
{

	Root_Panel.Type = PANEL;
	strcpy(Root_Panel.Name, "Root_Panel");
	Root_Panel.BackColor = RGB16(0, 22, 34);
	Root_Panel.ForeColor = RGB16(105, 105, 105);
	Root_Panel.BorderColor = RGB16(255, 255, 255);
	Root_Panel.BorderWidth = 0;
	Root_Panel.Location = (Point){ .x = 0, .y = 0 };
	Root_Panel.Size = (Size){ .width = 800, .height = 480 };
	Root_Panel.StackIndex = -1;
	Root_Panel.CornerRadius = 0;
	Root_Panel.Font = &Font12;
	strcpy(Root_Panel.Text, "");
	Root_Panel.Visible = 1;
	Root_Panel.RedrawMe = 1;
	//add click event callbacks
	Root_Panel.Event_Down = NULL;
	Root_Panel.Event_Hold = NULL;
	Root_Panel.Event_Up = NULL;
	//Components in this panel
	panel_update(&Root_Panel);

	gL_Button2.Type = BUTTON;
	strcpy(gL_Button2.Name, "gL_Button2");
	gL_Button2.Event_Down = NULL;
	gL_Button2.Event_Hold = NULL;
	gL_Button2.Event_Up   = glBtnApply_TouchEvent;
	gL_Button2.BackColor = RGB16(0, 22, 34);
	gL_Button2.ForeColor = RGB16(132, 225, 255);
	gL_Button2.BorderColor = RGB16(1, 103, 137);
	gL_Button2.CheckedBackColor = RGB16(62, 209, 255);
	gL_Button2.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button2.CheckedBorderColor = RGB16(0, 0, 0);
	gL_Button2.FocusBackColor = RGB16(0, 0, 0);
	gL_Button2.FocusForeColor = RGB16(0, 0, 0);
	gL_Button2.FocusBorderColor = RGB16(0, 0, 0);
	gL_Button2.BorderWidth = 1;
	gL_Button2.CornerRadius = 0;
	gL_Button2.Font = &Font20;
	gL_Button2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button2.TextAlign = MiddleCenter;
	gL_Button2.Visible = 1;
	gL_Button2.RedrawMe = 1;
	gL_Button2.Location = (Point){ .x = 574, .y = 3 };
	gL_Button2.Size = (Size){ .width = 89, .height = 32 };
	strcpy(gL_Button2.Text, "APPLY");
	strcpy(gL_Button2.CheckedText, "");
	gL_Button2.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button2); //add to the panel




	gL_Button1.Type = BUTTON;
	strcpy(gL_Button1.Name, "gL_Button1");
	gL_Button1.Event_Down = NULL;
	gL_Button1.Event_Hold = NULL;
	gL_Button1.Event_Up   = glBtnSave_TouchEvent;
	gL_Button1.BackColor = RGB16(0, 22, 34);
	gL_Button1.ForeColor = RGB16(132, 225, 255);
	gL_Button1.BorderColor = RGB16(1, 103, 137);
	gL_Button1.CheckedBackColor = RGB16(62, 209, 255);
	gL_Button1.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button1.CheckedBorderColor = RGB16(0, 0, 0);
	gL_Button1.FocusBackColor = RGB16(0, 0, 0);
	gL_Button1.FocusForeColor = RGB16(0, 0, 0);
	gL_Button1.FocusBorderColor = RGB16(0, 0, 0);
	gL_Button1.BorderWidth = 1;
	gL_Button1.CornerRadius = 0;
	gL_Button1.Font = &Font20;
	gL_Button1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button1.TextAlign = MiddleCenter;
	gL_Button1.Visible = 1;
	gL_Button1.RedrawMe = 1;
	gL_Button1.Location = (Point){ .x = 479, .y = 3 };
	gL_Button1.Size = (Size){ .width = 89, .height = 32 };
	strcpy(gL_Button1.Text, "SAVE");
	strcpy(gL_Button1.CheckedText, "");
	gL_Button1.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button1); //add to the panel




	glBtnPlus.Type = BUTTON;
	strcpy(glBtnPlus.Name, "glBtnPlus");
	glBtnPlus.Event_Down = NULL;
	glBtnPlus.Event_Hold = glBtnPlus_TouchEvent;
	glBtnPlus.Event_Up   = NULL;
	glBtnPlus.BackColor = RGB16(0, 22, 34);
	glBtnPlus.ForeColor = RGB16(132, 225, 255);
	glBtnPlus.BorderColor = RGB16(1, 103, 137);
	glBtnPlus.CheckedBackColor = RGB16(62, 209, 255);
	glBtnPlus.CheckedForeColor = RGB16(2, 46, 61);
	glBtnPlus.CheckedBorderColor = RGB16(0, 0, 0);
	glBtnPlus.FocusBackColor = RGB16(0, 0, 0);
	glBtnPlus.FocusForeColor = RGB16(0, 0, 0);
	glBtnPlus.FocusBorderColor = RGB16(0, 0, 0);
	glBtnPlus.BorderWidth = 1;
	glBtnPlus.CornerRadius = 0;
	glBtnPlus.Font = &Font20;
	glBtnPlus.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnPlus.TextAlign = MiddleCenter;
	glBtnPlus.Visible = 1;
	glBtnPlus.RedrawMe = 1;
	glBtnPlus.Location = (Point){ .x = 679, .y = 3 };
	glBtnPlus.Size = (Size){ .width = 47, .height = 32 };
	strcpy(glBtnPlus.Text, "+");
	strcpy(glBtnPlus.CheckedText, "");
	glBtnPlus.Checked = 0;

	panel_add_child(&Root_Panel, &glBtnPlus); //add to the panel




	glBtnMinus.Type = BUTTON;
	strcpy(glBtnMinus.Name, "glBtnMinus");
	glBtnMinus.Event_Down = NULL;
	glBtnMinus.Event_Hold = glBtnMinus_TouchEvent;
	glBtnMinus.Event_Up   = NULL;
	glBtnMinus.BackColor = RGB16(0, 22, 34);
	glBtnMinus.ForeColor = RGB16(132, 225, 255);
	glBtnMinus.BorderColor = RGB16(1, 103, 137);
	glBtnMinus.CheckedBackColor = RGB16(62, 209, 255);
	glBtnMinus.CheckedForeColor = RGB16(2, 46, 61);
	glBtnMinus.CheckedBorderColor = RGB16(0, 0, 0);
	glBtnMinus.FocusBackColor = RGB16(0, 0, 0);
	glBtnMinus.FocusForeColor = RGB16(0, 0, 0);
	glBtnMinus.FocusBorderColor = RGB16(0, 0, 0);
	glBtnMinus.BorderWidth = 1;
	glBtnMinus.CornerRadius = 0;
	glBtnMinus.Font = &Font20;
	glBtnMinus.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnMinus.TextAlign = MiddleCenter;
	glBtnMinus.Visible = 1;
	glBtnMinus.RedrawMe = 1;
	glBtnMinus.Location = (Point){ .x = 732, .y = 3 };
	glBtnMinus.Size = (Size){ .width = 47, .height = 32 };
	strcpy(glBtnMinus.Text, "-");
	strcpy(glBtnMinus.CheckedText, "");
	glBtnMinus.Checked = 0;

	panel_add_child(&Root_Panel, &glBtnMinus); //add to the panel




	gL_Panel4.Type = PANEL;
	strcpy(gL_Panel4.Name, "gL_Panel4");
	gL_Panel4.BackColor = RGB16(0, 22, 34);
	gL_Panel4.ForeColor = RGB16(122, 225, 255);
	gL_Panel4.BorderColor = RGB16(37, 87, 103);
	gL_Panel4.BorderWidth = 1;
	gL_Panel4.Location = (Point){ .x = 345, .y = 42 };
	gL_Panel4.Size = (Size){ .width = 434, .height = 294 };
	gL_Panel4.StackIndex = -1;
	gL_Panel4.CornerRadius = 5;
	gL_Panel4.Font = &Font20;
	strcpy(gL_Panel4.Text, "MESSAGES");
	gL_Panel4.Visible = 1;
	gL_Panel4.RedrawMe = 1;
	//add click event callbacks
	gL_Panel4.Event_Down = NULL;
	gL_Panel4.Event_Hold = NULL;
	gL_Panel4.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel4);

	glDropdownDisplayMode.Type = DROPDOWNLIST;
	strcpy(glDropdownDisplayMode.Name, "glDropdownDisplayMode");
	glDropdownDisplayMode.BackColor = RGB16(0, 22, 34);
	glDropdownDisplayMode.ForeColor = RGB16(122, 225, 255);
	glDropdownDisplayMode.BorderColor = RGB16(1, 103, 137);
	glDropdownDisplayMode.BorderWidth = 1;
	glDropdownDisplayMode.CornerRadius = 0;
	glDropdownDisplayMode.Font = &Font16;
	glDropdownDisplayMode.Padding = (PADDING) { 0, 0, 0, 0 };
	glDropdownDisplayMode.TextAlign = MiddleCenter;
	glDropdownDisplayMode.Visible = 1;
	glDropdownDisplayMode.RedrawMe = 1;
	glDropdownDisplayMode.Location = (Point){ .x = 354, .y = 14 };
	glDropdownDisplayMode.Size = (Size){ .width = 76, .height = 25 };
	glDropdownDisplayMode.FocusBackColor = RGB16(0, 175, 255);
	glDropdownDisplayMode.FocusForeColor = RGB16(0, 0, 0); 
	glDropdownDisplayMode.FocusBorderColor = RGB16(2, 49, 72);
	glDropdownDisplayMode.HasFocus = 0;
	glDropdownDisplayMode.ValueType = DROPDOWNLIST_STRING;
	glDropdownDisplayMode.Event_ChangedValue = ChangeDisplayModeListEvent;
	dropdownlist_add_item(&glDropdownDisplayMode, "ASCII");	
	dropdownlist_add_item(&glDropdownDisplayMode, "RAW");
	dropdownlist_add_item(&glDropdownDisplayMode, "HEX");
	dropdownlist_add_item(&glDropdownDisplayMode, "VARPAIR");
	glDropdownDisplayMode.SelectedIndex = 1;
	dropdownlist_update(&glDropdownDisplayMode);

	panel_add_child(&gL_Panel4, &glDropdownDisplayMode); //add to the panel



	gL_Listbox1.Type = LISTBOX;
	strcpy(gL_Listbox1.Name, "gL_Listbox1");
	gL_Listbox1.BackColor = RGB16(0, 22, 34);
	gL_Listbox1.ForeColor = RGB16(122, 225, 255);
	gL_Listbox1.BorderColor = RGB16(0, 22, 34);
	gL_Listbox1.BorderWidth = 1;
	gL_Listbox1.Font = &Font16;
	gL_Listbox1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Listbox1.Visible = 1;
	gL_Listbox1.RedrawMe = 1;
	gL_Listbox1.HasFocus = 0;
	gL_Listbox1.FocusBorderColor = RGB16(122, 225, 255);
	gL_Listbox1.RowOddColor = RGB16(0, 22, 34);
	gL_Listbox1.RowEvenColor = RGB16(10, 32, 34);
	gL_Listbox1.Location = (Point){ .x = 7, .y = 42 };
	gL_Listbox1.Size = (Size){ .width = 423, .height = 240 };
	listbox_update(&gL_Listbox1);

	panel_add_child(&gL_Panel4, &gL_Listbox1); //add to the panel




	panel_add_child(&Root_Panel, &gL_Panel4); //add to the panel





	gL_Panel3.Type = PANEL;
	strcpy(gL_Panel3.Name, "gL_Panel3");
	gL_Panel3.BackColor = RGB16(0, 22, 34);
	gL_Panel3.ForeColor = RGB16(122, 225, 255);
	gL_Panel3.BorderColor = RGB16(37, 87, 103);
	gL_Panel3.BorderWidth = 1;
	gL_Panel3.Location = (Point){ .x = 345, .y = 344 };
	gL_Panel3.Size = (Size){ .width = 434, .height = 123 };
	gL_Panel3.StackIndex = -1;
	gL_Panel3.CornerRadius = 5;
	gL_Panel3.Font = &Font20;
	strcpy(gL_Panel3.Text, "DEVICE INFO");
	gL_Panel3.Visible = 1;
	gL_Panel3.RedrawMe = 1;
	//add click event callbacks
	gL_Panel3.Event_Down = NULL;
	gL_Panel3.Event_Hold = NULL;
	gL_Panel3.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel3);

	panel_add_child(&Root_Panel, &gL_Panel3); //add to the panel





	lblTitle.Type = LABEL;
	strcpy(lblTitle.Name, "lblTitle");
	lblTitle.BackColor = RGB16(0, 22, 34);
	lblTitle.ForeColor = RGB16(122, 225, 255);
	lblTitle.BorderColor = RGB16(0, 0, 0);
	lblTitle.BorderWidth = 0;
	lblTitle.CornerRadius = 0;
	lblTitle.Font = &Font16;
	lblTitle.Padding = (PADDING) { 0, 0, 0, 0 };
	lblTitle.TextAlign = TopLeft;
	lblTitle.Visible = 1;
	lblTitle.RedrawMe = 1;
	lblTitle.Location = (Point){ .x = 14, .y = 13 };
	lblTitle.Size = (Size){ .width = 224, .height = 21 };
	strcpy(lblTitle.Text, "MEGASONIC HYPERCLEAN v1.14");
	//add click event callbacks
	lblTitle.Event_Down = NULL;
	lblTitle.Event_Hold = NULL;
	lblTitle.Event_Up = NULL;

	panel_add_child(&Root_Panel, &lblTitle); //add to the panel




	glTabMain.Type = TABCONTROL;
	strcpy(glTabMain.Name, "glTabMain");
	glTabMain.BackColor = RGB16(0, 22, 34);
	glTabMain.BorderColor = RGB16(13, 49, 61);
	glTabMain.BorderWidth = 1;
	glTabMain.Visible = 1;
	glTabMain.RedrawMe = 1;
	glTabMain.Location = (Point){ .x = 11, .y = 42 };
	glTabMain.Size = (Size){ .width = 330, .height = 425 };
	glTabMain.ItemSize = (Size){ .width = 100, .height = 30 };
	glTabMain.StackIndex = 0;

	glTabMainTab_0.Type = BUTTON;
	strcpy(glTabMainTab_0.Name, "glTabMainTab_0");
	glTabMainTab_0.Event_Down = NULL;
	glTabMainTab_0.Event_Hold = NULL;
	glTabMainTab_0.Event_Up   = NULL;
	glTabMainTab_0.BackColor = RGB16(2, 46, 61);
	glTabMainTab_0.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_0.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_0.CheckedBackColor = RGB16(62, 209, 255);
	glTabMainTab_0.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_0.CheckedBorderColor = RGB16(0, 0, 0);
	glTabMainTab_0.FocusBackColor = RGB16(0, 0, 0);
	glTabMainTab_0.FocusForeColor = RGB16(0, 0, 0);
	glTabMainTab_0.FocusBorderColor = RGB16(0, 0, 0);
	glTabMainTab_0.BorderWidth = 1;
	glTabMainTab_0.CornerRadius = 0;
	glTabMainTab_0.Font = &Font20;
	glTabMainTab_0.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_0.TextAlign = MiddleCenter;
	glTabMainTab_0.Visible = 1;
	glTabMainTab_0.RedrawMe = 1;
	glTabMainTab_0.Location = (Point){ .x = 0, .y = 0 };
	glTabMainTab_0.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_0.Text, "CONN");
	strcpy(glTabMainTab_0.CheckedText, "");
	glTabMainTab_0.Checked = 0;


	gL_Panel7.Type = PANEL;
	strcpy(gL_Panel7.Name, "gL_Panel7");
	gL_Panel7.BackColor = RGB16(0, 22, 34);
	gL_Panel7.ForeColor = RGB16(122, 225, 255);
	gL_Panel7.BorderColor = RGB16(37, 87, 103);
	gL_Panel7.BorderWidth = 1;
	gL_Panel7.Location = (Point){ .x = 10, .y = 8 };
	gL_Panel7.Size = (Size){ .width = 316, .height = 144 };
	gL_Panel7.StackIndex = -1;
	gL_Panel7.CornerRadius = 5;
	gL_Panel7.Font = &Font20;
	strcpy(gL_Panel7.Text, "SECS SERIAL");
	gL_Panel7.Visible = 1;
	gL_Panel7.RedrawMe = 1;
	//add click event callbacks
	gL_Panel7.Event_Down = NULL;
	gL_Panel7.Event_Hold = NULL;
	gL_Panel7.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel7);

	gL_DropdownList1.Type = DROPDOWNLIST;
	strcpy(gL_DropdownList1.Name, "gL_DropdownList1");
	gL_DropdownList1.BackColor = RGB16(0, 22, 34);
	gL_DropdownList1.ForeColor = RGB16(122, 225, 255);
	gL_DropdownList1.BorderColor = RGB16(1, 103, 137);
	gL_DropdownList1.BorderWidth = 1;
	gL_DropdownList1.CornerRadius = 0;
	gL_DropdownList1.Font = &Font20;
	gL_DropdownList1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_DropdownList1.TextAlign = MiddleCenter;
	gL_DropdownList1.Visible = 1;
	gL_DropdownList1.RedrawMe = 1;
	gL_DropdownList1.Location = (Point){ .x = 170, .y = 72 };
	gL_DropdownList1.Size = (Size){ .width = 120, .height = 32 };
	gL_DropdownList1.FocusBackColor = RGB16(0, 175, 255);
	 ;
	gL_DropdownList1.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_DropdownList1.FocusBorderColor = RGB16(2, 49, 72); 
	;
	gL_DropdownList1.HasFocus = 0;
	gL_DropdownList1.ValueType = DROPDOWNLIST_INT;
	dropdownlist_add_item(&gL_DropdownList1, "9600");
	dropdownlist_add_item(&gL_DropdownList1, "14400");
	dropdownlist_add_item(&gL_DropdownList1, "19200");
	dropdownlist_add_item(&gL_DropdownList1, "38400");
	dropdownlist_add_item(&gL_DropdownList1, "57600");
	dropdownlist_add_item(&gL_DropdownList1, "115200");
	gL_DropdownList1.SelectedIndex = 0;
	dropdownlist_update(&gL_DropdownList1);

	panel_add_child(&gL_Panel7, &gL_DropdownList1); //add to the panel




	gL_Label15.Type = LABEL;
	strcpy(gL_Label15.Name, "gL_Label15");
	gL_Label15.BackColor = RGB16(0, 22, 34);
	gL_Label15.ForeColor = RGB16(122, 225, 255);
	gL_Label15.BorderColor = RGB16(0, 0, 0);
	gL_Label15.BorderWidth = 0;
	gL_Label15.CornerRadius = 0;
	gL_Label15.Font = &Font20;
	gL_Label15.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label15.TextAlign = TopLeft;
	gL_Label15.Visible = 1;
	gL_Label15.RedrawMe = 1;
	gL_Label15.Location = (Point){ .x = 23, .y = 72 };
	gL_Label15.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label15.Text, "BAUD");
	//add click event callbacks
	gL_Label15.Event_Down = NULL;
	gL_Label15.Event_Hold = NULL;
	gL_Label15.Event_Up = NULL;

	panel_add_child(&gL_Panel7, &gL_Label15); //add to the panel




	gL_Label2.Type = LABEL;
	strcpy(gL_Label2.Name, "gL_Label2");
	gL_Label2.BackColor = RGB16(0, 22, 34);
	gL_Label2.ForeColor = RGB16(122, 225, 255);
	gL_Label2.BorderColor = RGB16(0, 0, 0);
	gL_Label2.BorderWidth = 0;
	gL_Label2.CornerRadius = 0;
	gL_Label2.Font = &Font20;
	gL_Label2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2.TextAlign = TopLeft;
	gL_Label2.Visible = 1;
	gL_Label2.RedrawMe = 1;
	gL_Label2.Location = (Point){ .x = 23, .y = 33 };
	gL_Label2.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label2.Text, "PORT");
	//add click event callbacks
	gL_Label2.Event_Down = NULL;
	gL_Label2.Event_Hold = NULL;
	gL_Label2.Event_Up = NULL;

	panel_add_child(&gL_Panel7, &gL_Label2); //add to the panel




	gL_Numeric2.Type = NUMERIC;
	strcpy(gL_Numeric2.Name, "gL_Numeric2");
	gL_Numeric2.BackColor = RGB16(0, 22, 34);
	 ;
	gL_Numeric2.ForeColor = RGB16(122, 225, 255);
	 ;
	gL_Numeric2.BorderColor = RGB16(1, 103, 137); 
	;
	gL_Numeric2.FocusBackColor = RGB16(0, 175, 255);
	 ;
	gL_Numeric2.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_Numeric2.FocusBorderColor = RGB16(2, 49, 72); 
	;
	gL_Numeric2.BorderWidth = 1;
	gL_Numeric2.CornerRadius = 0;
	gL_Numeric2.Font = &Font20;
	gL_Numeric2.Padding = (PADDING) { 5, 5, 5, 5 };
	gL_Numeric2.TextAlign = MiddleRight;
	gL_Numeric2.Visible = 1;
	gL_Numeric2.RedrawMe = 1;
	gL_Numeric2.Location = (Point){ .x = 170, .y = 26 };
	gL_Numeric2.Size = (Size){ .width = 120, .height = 32 };
	gL_Numeric2.HasFocus = 0;
	gL_Numeric2.Value = 0;
	gL_Numeric2.Step = 1.5;
	gL_Numeric2.MinValue = 0;
	gL_Numeric2.MaxValue = 100;
	numeric_update(&gL_Numeric2);

	panel_add_child(&gL_Panel7, &gL_Numeric2); //add to the panel




	panel_add_child(&glTabMainPanel_0, &gL_Panel7); //add to the panel





	gL_Panel5.Type = PANEL;
	strcpy(gL_Panel5.Name, "gL_Panel5");
	gL_Panel5.BackColor = RGB16(0, 22, 34);
	gL_Panel5.ForeColor = RGB16(122, 225, 255);
	gL_Panel5.BorderColor = RGB16(37, 87, 103);
	gL_Panel5.BorderWidth = 1;
	gL_Panel5.Location = (Point){ .x = 10, .y = 175 };
	gL_Panel5.Size = (Size){ .width = 316, .height = 144 };
	gL_Panel5.StackIndex = -1;
	gL_Panel5.CornerRadius = 5;
	gL_Panel5.Font = &Font20;
	strcpy(gL_Panel5.Text, "SIMPLE SERIAL");
	gL_Panel5.Visible = 1;
	gL_Panel5.RedrawMe = 1;
	//add click event callbacks
	gL_Panel5.Event_Down = NULL;
	gL_Panel5.Event_Hold = NULL;
	gL_Panel5.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel5);

	gL_DropdownList2.Type = DROPDOWNLIST;
	strcpy(gL_DropdownList2.Name, "gL_DropdownList2");
	gL_DropdownList2.BackColor = RGB16(0, 22, 34);
	gL_DropdownList2.ForeColor = RGB16(122, 225, 255);
	gL_DropdownList2.BorderColor = RGB16(1, 103, 137);
	gL_DropdownList2.BorderWidth = 1;
	gL_DropdownList2.CornerRadius = 0;
	gL_DropdownList2.Font = &Font20;
	gL_DropdownList2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_DropdownList2.TextAlign = MiddleCenter;
	gL_DropdownList2.Visible = 1;
	gL_DropdownList2.RedrawMe = 1;
	gL_DropdownList2.Location = (Point){ .x = 172, .y = 70 };
	gL_DropdownList2.Size = (Size){ .width = 120, .height = 32 };
	gL_DropdownList2.FocusBackColor = RGB16(0, 175, 255);
	 ;
	gL_DropdownList2.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_DropdownList2.FocusBorderColor = RGB16(2, 49, 72); 
	;
	gL_DropdownList2.HasFocus = 0;
	gL_DropdownList2.ValueType = DROPDOWNLIST_INT;
	dropdownlist_add_item(&gL_DropdownList2, "9600");
	dropdownlist_add_item(&gL_DropdownList2, "14400");
	dropdownlist_add_item(&gL_DropdownList2, "19200");
	dropdownlist_add_item(&gL_DropdownList2, "38400");
	dropdownlist_add_item(&gL_DropdownList2, "57600");
	dropdownlist_add_item(&gL_DropdownList2, "115200");
	gL_DropdownList2.SelectedIndex = 0;
	dropdownlist_update(&gL_DropdownList2);

	panel_add_child(&gL_Panel5, &gL_DropdownList2); //add to the panel




	gL_Label17.Type = LABEL;
	strcpy(gL_Label17.Name, "gL_Label17");
	gL_Label17.BackColor = RGB16(0, 22, 34);
	gL_Label17.ForeColor = RGB16(122, 225, 255);
	gL_Label17.BorderColor = RGB16(0, 0, 0);
	gL_Label17.BorderWidth = 0;
	gL_Label17.CornerRadius = 0;
	gL_Label17.Font = &Font20;
	gL_Label17.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label17.TextAlign = TopLeft;
	gL_Label17.Visible = 1;
	gL_Label17.RedrawMe = 1;
	gL_Label17.Location = (Point){ .x = 23, .y = 72 };
	gL_Label17.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label17.Text, "BAUD");
	//add click event callbacks
	gL_Label17.Event_Down = NULL;
	gL_Label17.Event_Hold = NULL;
	gL_Label17.Event_Up = NULL;

	panel_add_child(&gL_Panel5, &gL_Label17); //add to the panel




	gL_Label16.Type = LABEL;
	strcpy(gL_Label16.Name, "gL_Label16");
	gL_Label16.BackColor = RGB16(0, 22, 34);
	gL_Label16.ForeColor = RGB16(122, 225, 255);
	gL_Label16.BorderColor = RGB16(0, 0, 0);
	gL_Label16.BorderWidth = 0;
	gL_Label16.CornerRadius = 0;
	gL_Label16.Font = &Font20;
	gL_Label16.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label16.TextAlign = TopLeft;
	gL_Label16.Visible = 1;
	gL_Label16.RedrawMe = 1;
	gL_Label16.Location = (Point){ .x = 23, .y = 33 };
	gL_Label16.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label16.Text, "PORT");
	//add click event callbacks
	gL_Label16.Event_Down = NULL;
	gL_Label16.Event_Hold = NULL;
	gL_Label16.Event_Up = NULL;

	panel_add_child(&gL_Panel5, &gL_Label16); //add to the panel




	glNumeric_SimplePort.Type = NUMERIC;
	strcpy(glNumeric_SimplePort.Name, "glNumeric_SimplePort");
	glNumeric_SimplePort.BackColor = RGB16(0, 22, 34); 
	;
	glNumeric_SimplePort.ForeColor = RGB16(122, 225, 255);
	 ;
	glNumeric_SimplePort.BorderColor = RGB16(1, 103, 137); 
	;
	glNumeric_SimplePort.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNumeric_SimplePort.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNumeric_SimplePort.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNumeric_SimplePort.BorderWidth = 1;
	glNumeric_SimplePort.CornerRadius = 0;
	glNumeric_SimplePort.Font = &Font20;
	glNumeric_SimplePort.Padding = (PADDING) { 5, 5, 5, 5 };
	glNumeric_SimplePort.TextAlign = MiddleRight;
	glNumeric_SimplePort.Visible = 1;
	glNumeric_SimplePort.RedrawMe = 1;
	glNumeric_SimplePort.Location = (Point){ .x = 172, .y = 26 };
	glNumeric_SimplePort.Size = (Size){ .width = 118, .height = 29 };
	glNumeric_SimplePort.HasFocus = 0;
	glNumeric_SimplePort.Value = 0;
	glNumeric_SimplePort.Step = 3.1;
	glNumeric_SimplePort.MinValue = 0;
	glNumeric_SimplePort.MaxValue = 100;
	numeric_update(&glNumeric_SimplePort);

	panel_add_child(&gL_Panel5, &glNumeric_SimplePort); //add to the panel




	panel_add_child(&glTabMainPanel_0, &gL_Panel5); //add to the panel





	glTabMainPanel_0.Type = PANEL;
	strcpy(glTabMainPanel_0.Name, "glTabMainPanel_0");
	glTabMainPanel_0.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_0.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_0.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_0.BorderWidth = 1;
	glTabMainPanel_0.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_0.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_0.StackIndex = -1;
	glTabMainPanel_0.CornerRadius = 0;
	glTabMainPanel_0.Font = &Font12;
	strcpy(glTabMainPanel_0.Text, "");
	glTabMainPanel_0.Visible = 1;
	glTabMainPanel_0.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_0.Event_Down = NULL;
	glTabMainPanel_0.Event_Hold = NULL;
	glTabMainPanel_0.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_0);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_0, &glTabMainPanel_0);

	glTabMainTab_1.Type = BUTTON;
	strcpy(glTabMainTab_1.Name, "glTabMainTab_1");
	glTabMainTab_1.Event_Down = NULL;
	glTabMainTab_1.Event_Hold = NULL;
	glTabMainTab_1.Event_Up   = NULL;
	glTabMainTab_1.BackColor = RGB16(2, 46, 61);
	glTabMainTab_1.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_1.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_1.CheckedBackColor = RGB16(62, 209, 255);
	glTabMainTab_1.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_1.CheckedBorderColor = RGB16(0, 0, 0);
	glTabMainTab_1.FocusBackColor = RGB16(0, 0, 0);
	glTabMainTab_1.FocusForeColor = RGB16(0, 0, 0);
	glTabMainTab_1.FocusBorderColor = RGB16(0, 0, 0);
	glTabMainTab_1.BorderWidth = 1;
	glTabMainTab_1.CornerRadius = 0;
	glTabMainTab_1.Font = &Font20;
	glTabMainTab_1.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_1.TextAlign = MiddleCenter;
	glTabMainTab_1.Visible = 1;
	glTabMainTab_1.RedrawMe = 1;
	glTabMainTab_1.Location = (Point){ .x = 100, .y = 0 };
	glTabMainTab_1.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_1.Text, "FUNC");
	strcpy(glTabMainTab_1.CheckedText, "");
	glTabMainTab_1.Checked = 0;


	glBtnLoadString.Type = BUTTON;
	strcpy(glBtnLoadString.Name, "glBtnLoadString");
	glBtnLoadString.Event_Down = LoadSoapstringButtonEvent;
	glBtnLoadString.Event_Hold = NULL;
	glBtnLoadString.Event_Up   = NULL;
	glBtnLoadString.BackColor = RGB16(0, 0, 0);
	glBtnLoadString.ForeColor = RGB16(132, 225, 255);
	glBtnLoadString.BorderColor = RGB16(0, 120, 180);
	glBtnLoadString.CheckedBackColor = RGB16(20, 160, 255);
	glBtnLoadString.CheckedForeColor = RGB16(0, 50, 60);
	glBtnLoadString.CheckedBorderColor = RGB16(115, 225, 255);
	glBtnLoadString.FocusBackColor = RGB16(20, 160, 255);
	glBtnLoadString.FocusForeColor = RGB16(0, 50, 60);
	glBtnLoadString.FocusBorderColor = RGB16(115, 225, 255);
	glBtnLoadString.BorderWidth = 1;
	glBtnLoadString.CornerRadius = 4;
	glBtnLoadString.Font = &Font16;
	glBtnLoadString.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnLoadString.TextAlign = MiddleCenter;
	glBtnLoadString.Visible = 1;
	glBtnLoadString.RedrawMe = 1;
	glBtnLoadString.Location = (Point){ .x = 16, .y = 332 };
	glBtnLoadString.Size = (Size){ .width = 189, .height = 48 };
	strcpy(glBtnLoadString.Text, "Load Soap string");
	strcpy(glBtnLoadString.CheckedText, "");
	glBtnLoadString.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &glBtnLoadString); //add to the panel




	glBtnSaveSoapstring.Type = BUTTON;
	strcpy(glBtnSaveSoapstring.Name, "glBtnSaveSoapstring");
	glBtnSaveSoapstring.Event_Down = SaveSoapstringButtonEvent;
	glBtnSaveSoapstring.Event_Hold = NULL;
	glBtnSaveSoapstring.Event_Up   = NULL;
	glBtnSaveSoapstring.BackColor = RGB16(0, 0, 0);
	glBtnSaveSoapstring.ForeColor = RGB16(132, 225, 255);
	glBtnSaveSoapstring.BorderColor = RGB16(0, 120, 180);
	glBtnSaveSoapstring.CheckedBackColor = RGB16(20, 160, 255);
	glBtnSaveSoapstring.CheckedForeColor = RGB16(0, 50, 60);
	glBtnSaveSoapstring.CheckedBorderColor = RGB16(115, 225, 255);
	glBtnSaveSoapstring.FocusBackColor = RGB16(20, 160, 255);
	glBtnSaveSoapstring.FocusForeColor = RGB16(0, 50, 60);
	glBtnSaveSoapstring.FocusBorderColor = RGB16(115, 225, 255);
	glBtnSaveSoapstring.BorderWidth = 1;
	glBtnSaveSoapstring.CornerRadius = 4;
	glBtnSaveSoapstring.Font = &Font16;
	glBtnSaveSoapstring.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnSaveSoapstring.TextAlign = MiddleCenter;
	glBtnSaveSoapstring.Visible = 1;
	glBtnSaveSoapstring.RedrawMe = 1;
	glBtnSaveSoapstring.Location = (Point){ .x = 16, .y = 269 };
	glBtnSaveSoapstring.Size = (Size){ .width = 189, .height = 48 };
	strcpy(glBtnSaveSoapstring.Text, "Save Soap string");
	strcpy(glBtnSaveSoapstring.CheckedText, "");
	glBtnSaveSoapstring.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &glBtnSaveSoapstring); //add to the panel




	gL_Button6.Type = BUTTON;
	strcpy(gL_Button6.Name, "gL_Button6");
	gL_Button6.Event_Down = displaySoapstringButtonEvent;
	gL_Button6.Event_Hold = NULL;
	gL_Button6.Event_Up   = NULL;
	gL_Button6.BackColor = RGB16(0, 0, 0);
	gL_Button6.ForeColor = RGB16(132, 225, 255);
	gL_Button6.BorderColor = RGB16(0, 120, 180);
	gL_Button6.CheckedBackColor = RGB16(20, 160, 255);
	gL_Button6.CheckedForeColor = RGB16(0, 50, 60);
	gL_Button6.CheckedBorderColor = RGB16(115, 225, 255);
	gL_Button6.FocusBackColor = RGB16(20, 160, 255);
	gL_Button6.FocusForeColor = RGB16(0, 50, 60);
	gL_Button6.FocusBorderColor = RGB16(115, 225, 255);
	gL_Button6.BorderWidth = 1;
	gL_Button6.CornerRadius = 4;
	gL_Button6.Font = &Font16;
	gL_Button6.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button6.TextAlign = MiddleCenter;
	gL_Button6.Visible = 1;
	gL_Button6.RedrawMe = 1;
	gL_Button6.Location = (Point){ .x = 16, .y = 206 };
	gL_Button6.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button6.Text, "Display Soap string");
	strcpy(gL_Button6.CheckedText, "");
	gL_Button6.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button6); //add to the panel




	gL_Button5.Type = BUTTON;
	strcpy(gL_Button5.Name, "gL_Button5");
	gL_Button5.Event_Down = displayCalibrationButtonEvent;
	gL_Button5.Event_Hold = NULL;
	gL_Button5.Event_Up   = NULL;
	gL_Button5.BackColor = RGB16(0, 0, 0);
	gL_Button5.ForeColor = RGB16(132, 225, 255);
	gL_Button5.BorderColor = RGB16(0, 120, 180);
	gL_Button5.CheckedBackColor = RGB16(20, 160, 255);
	gL_Button5.CheckedForeColor = RGB16(0, 50, 60);
	gL_Button5.CheckedBorderColor = RGB16(115, 225, 255);
	gL_Button5.FocusBackColor = RGB16(20, 160, 255);
	gL_Button5.FocusForeColor = RGB16(0, 50, 60);
	gL_Button5.FocusBorderColor = RGB16(115, 225, 255);
	gL_Button5.BorderWidth = 1;
	gL_Button5.CornerRadius = 4;
	gL_Button5.Font = &Font16;
	gL_Button5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button5.TextAlign = MiddleCenter;
	gL_Button5.Visible = 1;
	gL_Button5.RedrawMe = 1;
	gL_Button5.Location = (Point){ .x = 16, .y = 143 };
	gL_Button5.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button5.Text, "Display Calibration");
	strcpy(gL_Button5.CheckedText, "");
	gL_Button5.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button5); //add to the panel




	gL_Button4.Type = BUTTON;
	strcpy(gL_Button4.Name, "gL_Button4");
	gL_Button4.Event_Down = ShiftbitWritetestButtonEvent;
	gL_Button4.Event_Hold = NULL;
	gL_Button4.Event_Up   = NULL;
	gL_Button4.BackColor = RGB16(0, 0, 0);
	gL_Button4.ForeColor = RGB16(132, 225, 255);
	gL_Button4.BorderColor = RGB16(0, 120, 180);
	gL_Button4.CheckedBackColor = RGB16(20, 160, 255);
	gL_Button4.CheckedForeColor = RGB16(0, 50, 60);
	gL_Button4.CheckedBorderColor = RGB16(115, 225, 255);
	gL_Button4.FocusBackColor = RGB16(20, 160, 255);
	gL_Button4.FocusForeColor = RGB16(0, 50, 60);
	gL_Button4.FocusBorderColor = RGB16(115, 225, 255);
	gL_Button4.BorderWidth = 1;
	gL_Button4.CornerRadius = 4;
	gL_Button4.Font = &Font16;
	gL_Button4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button4.TextAlign = MiddleCenter;
	gL_Button4.Visible = 1;
	gL_Button4.RedrawMe = 1;
	gL_Button4.Location = (Point){ .x = 16, .y = 80 };
	gL_Button4.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button4.Text, "ShiftBit write test");
	strcpy(gL_Button4.CheckedText, "");
	gL_Button4.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button4); //add to the panel




	glBtnEraseStorage.Type = BUTTON;
	strcpy(glBtnEraseStorage.Name, "glBtnEraseStorage");
	glBtnEraseStorage.Event_Down = eraseFlashButonEvent;
	glBtnEraseStorage.Event_Hold = NULL;
	glBtnEraseStorage.Event_Up   = NULL;
	glBtnEraseStorage.BackColor = RGB16(0, 0, 0);
	glBtnEraseStorage.ForeColor = RGB16(132, 225, 255);
	glBtnEraseStorage.BorderColor = RGB16(0, 120, 180);
	glBtnEraseStorage.CheckedBackColor = RGB16(20, 160, 255);
	glBtnEraseStorage.CheckedForeColor = RGB16(0, 50, 60);
	glBtnEraseStorage.CheckedBorderColor = RGB16(115, 225, 255);
	glBtnEraseStorage.FocusBackColor = RGB16(20, 160, 255);
	glBtnEraseStorage.FocusForeColor = RGB16(0, 50, 60);
	glBtnEraseStorage.FocusBorderColor = RGB16(115, 225, 255);
	glBtnEraseStorage.BorderWidth = 1;
	glBtnEraseStorage.CornerRadius = 4;
	glBtnEraseStorage.Font = &Font16;
	glBtnEraseStorage.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnEraseStorage.TextAlign = MiddleCenter;
	glBtnEraseStorage.Visible = 1;
	glBtnEraseStorage.RedrawMe = 1;
	glBtnEraseStorage.Location = (Point){ .x = 16, .y = 17 };
	glBtnEraseStorage.Size = (Size){ .width = 189, .height = 48 };
	strcpy(glBtnEraseStorage.Text, "Erase Flash");
	strcpy(glBtnEraseStorage.CheckedText, "");
	glBtnEraseStorage.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &glBtnEraseStorage); //add to the panel




	glTabMainPanel_1.Type = PANEL;
	strcpy(glTabMainPanel_1.Name, "glTabMainPanel_1");
	glTabMainPanel_1.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_1.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_1.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_1.BorderWidth = 1;
	glTabMainPanel_1.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_1.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_1.StackIndex = -1;
	glTabMainPanel_1.CornerRadius = 0;
	glTabMainPanel_1.Font = &Font12;
	strcpy(glTabMainPanel_1.Text, "");
	glTabMainPanel_1.Visible = 1;
	glTabMainPanel_1.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_1.Event_Down = NULL;
	glTabMainPanel_1.Event_Hold = NULL;
	glTabMainPanel_1.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_1);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_1, &glTabMainPanel_1);

	glTabMainTab_2.Type = BUTTON;
	strcpy(glTabMainTab_2.Name, "glTabMainTab_2");
	glTabMainTab_2.Event_Down = NULL;
	glTabMainTab_2.Event_Hold = NULL;
	glTabMainTab_2.Event_Up   = NULL;
	glTabMainTab_2.BackColor = RGB16(2, 46, 61);
	glTabMainTab_2.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_2.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_2.CheckedBackColor = RGB16(62, 209, 255);
	glTabMainTab_2.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_2.CheckedBorderColor = RGB16(0, 0, 0);
	glTabMainTab_2.FocusBackColor = RGB16(0, 0, 0);
	glTabMainTab_2.FocusForeColor = RGB16(0, 0, 0);
	glTabMainTab_2.FocusBorderColor = RGB16(0, 0, 0);
	glTabMainTab_2.BorderWidth = 1;
	glTabMainTab_2.CornerRadius = 0;
	glTabMainTab_2.Font = &Font20;
	glTabMainTab_2.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_2.TextAlign = MiddleCenter;
	glTabMainTab_2.Visible = 1;
	glTabMainTab_2.RedrawMe = 1;
	glTabMainTab_2.Location = (Point){ .x = 200, .y = 0 };
	glTabMainTab_2.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_2.Text, "VARS");
	strcpy(glTabMainTab_2.CheckedText, "");
	glTabMainTab_2.Checked = 0;


	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.BackColor = RGB16(0, 22, 34);
	gL_Panel1.ForeColor = RGB16(122, 225, 255);
	gL_Panel1.BorderColor = RGB16(37, 87, 103);
	gL_Panel1.BorderWidth = 1;
	gL_Panel1.Location = (Point){ .x = 7, .y = 7 };
	gL_Panel1.Size = (Size){ .width = 311, .height = 373 };
	gL_Panel1.StackIndex = -1;
	gL_Panel1.CornerRadius = 5;
	gL_Panel1.Font = &Font16;
	strcpy(gL_Panel1.Text, "LIVE DATA");
	gL_Panel1.Visible = 1;
	gL_Panel1.RedrawMe = 1;
	//add click event callbacks
	gL_Panel1.Event_Down = NULL;
	gL_Panel1.Event_Hold = NULL;
	gL_Panel1.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel1);

	glNudVars10.Type = NUMERIC;
	strcpy(glNudVars10.Name, "glNudVars10");
	glNudVars10.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars10.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars10.BorderColor = RGB16(1, 103, 137); 
	;
	glNudVars10.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars10.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNudVars10.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars10.BorderWidth = 1;
	glNudVars10.CornerRadius = 1;
	glNudVars10.Font = &Font20;
	glNudVars10.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars10.TextAlign = MiddleRight;
	glNudVars10.Visible = 1;
	glNudVars10.RedrawMe = 1;
	glNudVars10.Location = (Point){ .x = 182, .y = 323 };
	glNudVars10.Size = (Size){ .width = 120, .height = 29 };
	glNudVars10.HasFocus = 0;
	glNudVars10.Value = 0;
	glNudVars10.Step = 1.5;
	glNudVars10.MinValue = 0;
	glNudVars10.MaxValue = 100;
	numeric_update(&glNudVars10);

	panel_add_child(&gL_Panel1, &glNudVars10); //add to the panel




	glNudVars09.Type = NUMERIC;
	strcpy(glNudVars09.Name, "glNudVars09");
	glNudVars09.BackColor = RGB16(0, 22, 34); 
	;
	glNudVars09.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars09.BorderColor = RGB16(1, 103, 137); 
	;
	glNudVars09.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars09.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNudVars09.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars09.BorderWidth = 1;
	glNudVars09.CornerRadius = 1;
	glNudVars09.Font = &Font20;
	glNudVars09.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars09.TextAlign = MiddleRight;
	glNudVars09.Visible = 1;
	glNudVars09.RedrawMe = 1;
	glNudVars09.Location = (Point){ .x = 182, .y = 292 };
	glNudVars09.Size = (Size){ .width = 120, .height = 29 };
	glNudVars09.HasFocus = 0;
	glNudVars09.Value = 0;
	glNudVars09.Step = 1.5;
	glNudVars09.MinValue = 0;
	glNudVars09.MaxValue = 100;
	numeric_update(&glNudVars09);

	panel_add_child(&gL_Panel1, &glNudVars09); //add to the panel




	glNudVars08.Type = NUMERIC;
	strcpy(glNudVars08.Name, "glNudVars08");
	glNudVars08.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars08.ForeColor = RGB16(122, 225, 255); 
	;
	glNudVars08.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars08.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars08.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNudVars08.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars08.BorderWidth = 1;
	glNudVars08.CornerRadius = 1;
	glNudVars08.Font = &Font20;
	glNudVars08.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars08.TextAlign = MiddleRight;
	glNudVars08.Visible = 1;
	glNudVars08.RedrawMe = 1;
	glNudVars08.Location = (Point){ .x = 182, .y = 261 };
	glNudVars08.Size = (Size){ .width = 120, .height = 29 };
	glNudVars08.HasFocus = 0;
	glNudVars08.Value = 0;
	glNudVars08.Step = 1.5;
	glNudVars08.MinValue = 0;
	glNudVars08.MaxValue = 100;
	numeric_update(&glNudVars08);

	panel_add_child(&gL_Panel1, &glNudVars08); //add to the panel




	glNudVars07.Type = NUMERIC;
	strcpy(glNudVars07.Name, "glNudVars07");
	glNudVars07.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars07.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars07.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars07.FocusBackColor = RGB16(0, 175, 255); 
	;
	glNudVars07.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars07.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars07.BorderWidth = 1;
	glNudVars07.CornerRadius = 1;
	glNudVars07.Font = &Font20;
	glNudVars07.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars07.TextAlign = MiddleRight;
	glNudVars07.Visible = 1;
	glNudVars07.RedrawMe = 1;
	glNudVars07.Location = (Point){ .x = 182, .y = 230 };
	glNudVars07.Size = (Size){ .width = 120, .height = 29 };
	glNudVars07.HasFocus = 0;
	glNudVars07.Value = 0;
	glNudVars07.Step = 1.5;
	glNudVars07.MinValue = 0;
	glNudVars07.MaxValue = 100;
	numeric_update(&glNudVars07);

	panel_add_child(&gL_Panel1, &glNudVars07); //add to the panel




	glNudVars06.Type = NUMERIC;
	strcpy(glNudVars06.Name, "glNudVars06");
	glNudVars06.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars06.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars06.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars06.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars06.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars06.FocusBorderColor = RGB16(2, 49, 72); 
	;
	glNudVars06.BorderWidth = 1;
	glNudVars06.CornerRadius = 1;
	glNudVars06.Font = &Font20;
	glNudVars06.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars06.TextAlign = MiddleRight;
	glNudVars06.Visible = 1;
	glNudVars06.RedrawMe = 1;
	glNudVars06.Location = (Point){ .x = 182, .y = 199 };
	glNudVars06.Size = (Size){ .width = 120, .height = 29 };
	glNudVars06.HasFocus = 0;
	glNudVars06.Value = 0;
	glNudVars06.Step = 1.5;
	glNudVars06.MinValue = 0;
	glNudVars06.MaxValue = 100;
	numeric_update(&glNudVars06);

	panel_add_child(&gL_Panel1, &glNudVars06); //add to the panel




	glNudVars05.Type = NUMERIC;
	strcpy(glNudVars05.Name, "glNudVars05");
	glNudVars05.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars05.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars05.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars05.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars05.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars05.FocusBorderColor = RGB16(2, 49, 72); 
	;
	glNudVars05.BorderWidth = 1;
	glNudVars05.CornerRadius = 1;
	glNudVars05.Font = &Font20;
	glNudVars05.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars05.TextAlign = MiddleRight;
	glNudVars05.Visible = 1;
	glNudVars05.RedrawMe = 1;
	glNudVars05.Location = (Point){ .x = 182, .y = 168 };
	glNudVars05.Size = (Size){ .width = 120, .height = 29 };
	glNudVars05.HasFocus = 0;
	glNudVars05.Value = 0;
	glNudVars05.Step = 1.5;
	glNudVars05.MinValue = 0;
	glNudVars05.MaxValue = 100;
	numeric_update(&glNudVars05);

	panel_add_child(&gL_Panel1, &glNudVars05); //add to the panel




	glNudVars04.Type = NUMERIC;
	strcpy(glNudVars04.Name, "glNudVars04");
	glNudVars04.BackColor = RGB16(0, 22, 34); 
	;
	glNudVars04.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars04.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars04.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars04.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars04.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars04.BorderWidth = 1;
	glNudVars04.CornerRadius = 1;
	glNudVars04.Font = &Font20;
	glNudVars04.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars04.TextAlign = MiddleRight;
	glNudVars04.Visible = 1;
	glNudVars04.RedrawMe = 1;
	glNudVars04.Location = (Point){ .x = 182, .y = 137 };
	glNudVars04.Size = (Size){ .width = 120, .height = 29 };
	glNudVars04.HasFocus = 0;
	glNudVars04.Value = 0;
	glNudVars04.Step = 1.5;
	glNudVars04.MinValue = 0;
	glNudVars04.MaxValue = 100;
	numeric_update(&glNudVars04);

	panel_add_child(&gL_Panel1, &glNudVars04); //add to the panel




	glNudVars03.Type = NUMERIC;
	strcpy(glNudVars03.Name, "glNudVars03");
	glNudVars03.BackColor = RGB16(0, 22, 34); 
	;
	glNudVars03.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars03.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars03.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars03.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars03.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars03.BorderWidth = 1;
	glNudVars03.CornerRadius = 1;
	glNudVars03.Font = &Font20;
	glNudVars03.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars03.TextAlign = MiddleRight;
	glNudVars03.Visible = 1;
	glNudVars03.RedrawMe = 1;
	glNudVars03.Location = (Point){ .x = 182, .y = 106 };
	glNudVars03.Size = (Size){ .width = 120, .height = 29 };
	glNudVars03.HasFocus = 0;
	glNudVars03.Value = 0;
	glNudVars03.Step = 1.5;
	glNudVars03.MinValue = 0;
	glNudVars03.MaxValue = 100;
	numeric_update(&glNudVars03);

	panel_add_child(&gL_Panel1, &glNudVars03); //add to the panel




	glNudVars02.Type = NUMERIC;
	strcpy(glNudVars02.Name, "glNudVars02");
	glNudVars02.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars02.ForeColor = RGB16(122, 225, 255);
	 ;
	glNudVars02.BorderColor = RGB16(1, 103, 137); 
	;
	glNudVars02.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars02.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNudVars02.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars02.BorderWidth = 1;
	glNudVars02.CornerRadius = 1;
	glNudVars02.Font = &Font20;
	glNudVars02.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars02.TextAlign = MiddleRight;
	glNudVars02.Visible = 1;
	glNudVars02.RedrawMe = 1;
	glNudVars02.Location = (Point){ .x = 182, .y = 75 };
	glNudVars02.Size = (Size){ .width = 120, .height = 29 };
	glNudVars02.HasFocus = 0;
	glNudVars02.Value = 0;
	glNudVars02.Step = 1.5;
	glNudVars02.MinValue = 0;
	glNudVars02.MaxValue = 100;
	numeric_update(&glNudVars02);

	panel_add_child(&gL_Panel1, &glNudVars02); //add to the panel




	glNudVars01.Type = NUMERIC;
	strcpy(glNudVars01.Name, "glNudVars01");
	glNudVars01.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars01.ForeColor = RGB16(122, 225, 255); 
	;
	glNudVars01.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars01.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars01.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars01.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	glNudVars01.BorderWidth = 1;
	glNudVars01.CornerRadius = 1;
	glNudVars01.Font = &Font20;
	glNudVars01.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars01.TextAlign = MiddleRight;
	glNudVars01.Visible = 1;
	glNudVars01.RedrawMe = 1;
	glNudVars01.Location = (Point){ .x = 182, .y = 44 };
	glNudVars01.Size = (Size){ .width = 120, .height = 29 };
	glNudVars01.HasFocus = 0;
	glNudVars01.Value = 0;
	glNudVars01.Step = 1.5;
	glNudVars01.MinValue = 0;
	glNudVars01.MaxValue = 100;
	numeric_update(&glNudVars01);

	panel_add_child(&gL_Panel1, &glNudVars01); //add to the panel




	glNudVars00.Type = NUMERIC;
	strcpy(glNudVars00.Name, "glNudVars00");
	glNudVars00.BackColor = RGB16(0, 22, 34);
	 ;
	glNudVars00.ForeColor = RGB16(122, 225, 255); 
	;
	glNudVars00.BorderColor = RGB16(1, 103, 137);
	 ;
	glNudVars00.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNudVars00.FocusForeColor = RGB16(0, 0, 0); 
	;
	glNudVars00.FocusBorderColor = RGB16(2, 49, 72); 
	;
	glNudVars00.BorderWidth = 1;
	glNudVars00.CornerRadius = 1;
	glNudVars00.Font = &Font20;
	glNudVars00.Padding = (PADDING) { 5, 5, 5, 5 };
	glNudVars00.TextAlign = MiddleRight;
	glNudVars00.Visible = 1;
	glNudVars00.RedrawMe = 1;
	glNudVars00.Location = (Point){ .x = 182, .y = 13 };
	glNudVars00.Size = (Size){ .width = 120, .height = 29 };
	glNudVars00.HasFocus = 0;
	glNudVars00.Value = 0;
	glNudVars00.Step = 1.5;
	glNudVars00.MinValue = 0;
	glNudVars00.MaxValue = 100;
	numeric_update(&glNudVars00);

	panel_add_child(&gL_Panel1, &glNudVars00); //add to the panel




	gL_Label1.Type = LABEL;
	strcpy(gL_Label1.Name, "gL_Label1");
	gL_Label1.BackColor = RGB16(0, 22, 34);
	gL_Label1.ForeColor = RGB16(122, 225, 255);
	gL_Label1.BorderColor = RGB16(0, 0, 0);
	gL_Label1.BorderWidth = 0;
	gL_Label1.CornerRadius = 0;
	gL_Label1.Font = &Font16;
	gL_Label1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label1.TextAlign = TopLeft;
	gL_Label1.Visible = 1;
	gL_Label1.RedrawMe = 1;
	gL_Label1.Location = (Point){ .x = 15, .y = 23 };
	gL_Label1.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label1.Text, "Amplifier Unit# ");
	//add click event callbacks
	gL_Label1.Event_Down = NULL;
	gL_Label1.Event_Hold = NULL;
	gL_Label1.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label1); //add to the panel




	gL_Label3.Type = LABEL;
	strcpy(gL_Label3.Name, "gL_Label3");
	gL_Label3.BackColor = RGB16(0, 22, 34);
	gL_Label3.ForeColor = RGB16(122, 225, 255);
	gL_Label3.BorderColor = RGB16(0, 0, 0);
	gL_Label3.BorderWidth = 0;
	gL_Label3.CornerRadius = 0;
	gL_Label3.Font = &Font16;
	gL_Label3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3.TextAlign = TopLeft;
	gL_Label3.Visible = 1;
	gL_Label3.RedrawMe = 1;
	gL_Label3.Location = (Point){ .x = 15, .y = 54 };
	gL_Label3.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label3.Text, "Channel number");
	//add click event callbacks
	gL_Label3.Event_Down = NULL;
	gL_Label3.Event_Hold = NULL;
	gL_Label3.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label3); //add to the panel




	gL_Label14.Type = LABEL;
	strcpy(gL_Label14.Name, "gL_Label14");
	gL_Label14.BackColor = RGB16(0, 22, 34);
	gL_Label14.ForeColor = RGB16(122, 225, 255);
	gL_Label14.BorderColor = RGB16(0, 0, 0);
	gL_Label14.BorderWidth = 0;
	gL_Label14.CornerRadius = 0;
	gL_Label14.Font = &Font16;
	gL_Label14.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label14.TextAlign = TopLeft;
	gL_Label14.Visible = 1;
	gL_Label14.RedrawMe = 1;
	gL_Label14.Location = (Point){ .x = 15, .y = 334 };
	gL_Label14.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label14.Text, "Status");
	//add click event callbacks
	gL_Label14.Event_Down = NULL;
	gL_Label14.Event_Hold = NULL;
	gL_Label14.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label14); //add to the panel




	gL_Label13.Type = LABEL;
	strcpy(gL_Label13.Name, "gL_Label13");
	gL_Label13.BackColor = RGB16(0, 22, 34);
	gL_Label13.ForeColor = RGB16(122, 225, 255);
	gL_Label13.BorderColor = RGB16(0, 0, 0);
	gL_Label13.BorderWidth = 0;
	gL_Label13.CornerRadius = 0;
	gL_Label13.Font = &Font16;
	gL_Label13.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label13.TextAlign = TopLeft;
	gL_Label13.Visible = 1;
	gL_Label13.RedrawMe = 1;
	gL_Label13.Location = (Point){ .x = 15, .y = 303 };
	gL_Label13.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label13.Text, "TC2");
	//add click event callbacks
	gL_Label13.Event_Down = NULL;
	gL_Label13.Event_Hold = NULL;
	gL_Label13.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label13); //add to the panel




	gL_Label12.Type = LABEL;
	strcpy(gL_Label12.Name, "gL_Label12");
	gL_Label12.BackColor = RGB16(0, 22, 34);
	gL_Label12.ForeColor = RGB16(122, 225, 255);
	gL_Label12.BorderColor = RGB16(0, 0, 0);
	gL_Label12.BorderWidth = 0;
	gL_Label12.CornerRadius = 0;
	gL_Label12.Font = &Font16;
	gL_Label12.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label12.TextAlign = TopLeft;
	gL_Label12.Visible = 1;
	gL_Label12.RedrawMe = 1;
	gL_Label12.Location = (Point){ .x = 15, .y = 272 };
	gL_Label12.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label12.Text, "TC1");
	//add click event callbacks
	gL_Label12.Event_Down = NULL;
	gL_Label12.Event_Hold = NULL;
	gL_Label12.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label12); //add to the panel




	gL_Label11.Type = LABEL;
	strcpy(gL_Label11.Name, "gL_Label11");
	gL_Label11.BackColor = RGB16(0, 22, 34);
	gL_Label11.ForeColor = RGB16(122, 225, 255);
	gL_Label11.BorderColor = RGB16(0, 0, 0);
	gL_Label11.BorderWidth = 0;
	gL_Label11.CornerRadius = 0;
	gL_Label11.Font = &Font16;
	gL_Label11.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label11.TextAlign = TopLeft;
	gL_Label11.Visible = 1;
	gL_Label11.RedrawMe = 1;
	gL_Label11.Location = (Point){ .x = 15, .y = 241 };
	gL_Label11.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label11.Text, "Bath Temp");
	//add click event callbacks
	gL_Label11.Event_Down = NULL;
	gL_Label11.Event_Hold = NULL;
	gL_Label11.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label11); //add to the panel




	gL_Label10.Type = LABEL;
	strcpy(gL_Label10.Name, "gL_Label10");
	gL_Label10.BackColor = RGB16(0, 22, 34);
	gL_Label10.ForeColor = RGB16(122, 225, 255);
	gL_Label10.BorderColor = RGB16(0, 0, 0);
	gL_Label10.BorderWidth = 0;
	gL_Label10.CornerRadius = 0;
	gL_Label10.Font = &Font16;
	gL_Label10.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label10.TextAlign = TopLeft;
	gL_Label10.Visible = 1;
	gL_Label10.RedrawMe = 1;
	gL_Label10.Location = (Point){ .x = 15, .y = 210 };
	gL_Label10.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label10.Text, "Power2");
	//add click event callbacks
	gL_Label10.Event_Down = NULL;
	gL_Label10.Event_Hold = NULL;
	gL_Label10.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label10); //add to the panel




	gL_Label9.Type = LABEL;
	strcpy(gL_Label9.Name, "gL_Label9");
	gL_Label9.BackColor = RGB16(0, 22, 34);
	gL_Label9.ForeColor = RGB16(122, 225, 255);
	gL_Label9.BorderColor = RGB16(0, 0, 0);
	gL_Label9.BorderWidth = 0;
	gL_Label9.CornerRadius = 0;
	gL_Label9.Font = &Font16;
	gL_Label9.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label9.TextAlign = TopLeft;
	gL_Label9.Visible = 1;
	gL_Label9.RedrawMe = 1;
	gL_Label9.Location = (Point){ .x = 15, .y = 179 };
	gL_Label9.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label9.Text, "Power1");
	//add click event callbacks
	gL_Label9.Event_Down = NULL;
	gL_Label9.Event_Hold = NULL;
	gL_Label9.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label9); //add to the panel




	gL_Label8.Type = LABEL;
	strcpy(gL_Label8.Name, "gL_Label8");
	gL_Label8.BackColor = RGB16(0, 22, 34);
	gL_Label8.ForeColor = RGB16(122, 225, 255);
	gL_Label8.BorderColor = RGB16(0, 0, 0);
	gL_Label8.BorderWidth = 0;
	gL_Label8.CornerRadius = 0;
	gL_Label8.Font = &Font16;
	gL_Label8.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label8.TextAlign = TopLeft;
	gL_Label8.Visible = 1;
	gL_Label8.RedrawMe = 1;
	gL_Label8.Location = (Point){ .x = 15, .y = 148 };
	gL_Label8.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label8.Text, "Frequency 2 ");
	//add click event callbacks
	gL_Label8.Event_Down = NULL;
	gL_Label8.Event_Hold = NULL;
	gL_Label8.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label8); //add to the panel




	gL_Label5.Type = LABEL;
	strcpy(gL_Label5.Name, "gL_Label5");
	gL_Label5.BackColor = RGB16(0, 22, 34);
	gL_Label5.ForeColor = RGB16(122, 225, 255);
	gL_Label5.BorderColor = RGB16(0, 0, 0);
	gL_Label5.BorderWidth = 0;
	gL_Label5.CornerRadius = 0;
	gL_Label5.Font = &Font16;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Visible = 1;
	gL_Label5.RedrawMe = 1;
	gL_Label5.Location = (Point){ .x = 15, .y = 117 };
	gL_Label5.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label5.Text, "TC6");
	//add click event callbacks
	gL_Label5.Event_Down = NULL;
	gL_Label5.Event_Hold = NULL;
	gL_Label5.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label5); //add to the panel




	gL_Label4.Type = LABEL;
	strcpy(gL_Label4.Name, "gL_Label4");
	gL_Label4.BackColor = RGB16(0, 22, 34);
	gL_Label4.ForeColor = RGB16(122, 225, 255);
	gL_Label4.BorderColor = RGB16(0, 0, 0);
	gL_Label4.BorderWidth = 0;
	gL_Label4.CornerRadius = 0;
	gL_Label4.Font = &Font16;
	gL_Label4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4.TextAlign = TopLeft;
	gL_Label4.Visible = 1;
	gL_Label4.RedrawMe = 1;
	gL_Label4.Location = (Point){ .x = 15, .y = 86 };
	gL_Label4.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label4.Text, "Frequency 1");
	//add click event callbacks
	gL_Label4.Event_Down = NULL;
	gL_Label4.Event_Hold = NULL;
	gL_Label4.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label4); //add to the panel




	panel_add_child(&glTabMainPanel_2, &gL_Panel1); //add to the panel





	glTabMainPanel_2.Type = PANEL;
	strcpy(glTabMainPanel_2.Name, "glTabMainPanel_2");
	glTabMainPanel_2.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_2.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_2.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_2.BorderWidth = 1;
	glTabMainPanel_2.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_2.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_2.StackIndex = -1;
	glTabMainPanel_2.CornerRadius = 0;
	glTabMainPanel_2.Font = &Font12;
	strcpy(glTabMainPanel_2.Text, "");
	glTabMainPanel_2.Visible = 1;
	glTabMainPanel_2.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_2.Event_Down = NULL;
	glTabMainPanel_2.Event_Hold = NULL;
	glTabMainPanel_2.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_2);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_2, &glTabMainPanel_2);
	tabcontrol_update(&glTabMain);
	tabcontrol_select_panel(&glTabMain, 0);

	panel_add_child(&Root_Panel, &glTabMain); //add to the panel




	PanelHandleList[0] = (uint32_t*)&Root_Panel; //set the root panel
	PanelHandleList[1] = (uint32_t*)&gL_Panel4;
	PanelHandleList[2] = (uint32_t*)&gL_Panel3;
	PanelHandleList[3] = (uint32_t*)&glTabMainPanel_0;
	PanelHandleList[4] = (uint32_t*)&gL_Panel7;
	PanelHandleList[5] = (uint32_t*)&gL_Panel5;
	PanelHandleList[6] = (uint32_t*)&glTabMainPanel_1;
	PanelHandleList[7] = (uint32_t*)&glTabMainPanel_2;
	PanelHandleList[8] = (uint32_t*)&gL_Panel1;
	sprintf(lblTitle.Text, " %s v%s", RevisionTitle, MajorStep);

}
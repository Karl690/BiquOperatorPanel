#include "global.h"
#include "display.h"
#include "displaylist.h"
#include "gui.h"

char strTempVal[80] = {0};
uint16_t idx = 0;
LcdVariableInfo *varInfo  = 0;
LcdVariableInfo CmdQuVars = {0};

char* tempstring2 = "karl is lucky";
#define FONTSIZE  32
#define PADDING_VALUE 5
void Format_Int32(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "%d ", (int)(*((uint32_t*)varInfo->VariablePointer)));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}
void Format_Int16(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "%d ", (int)(*((uint16_t*)varInfo->VariablePointer)));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_Hex8(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "0x%02x ", (uint8_t)(*((uint8_t*)varInfo->VariablePointer)));
	GUI_DrawString(LCD_WIDTH / 2, Y, strTempVal, FONTSIZE, varInfo->Color_2);

}
void Format_Hex16(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "0x%04x ", (uint16_t)(*((uint16_t*)varInfo->VariablePointer)));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}
void Format_Hex32(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "0x%08x ", (int)(*((uint32_t*)varInfo->VariablePointer)));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_Ascii(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1); //label?
	sprintf(strTempVal, "%s ", (uint8_t*)(uint32_t*)(varInfo->VariablePointer));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_Float3_3(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1); //label
	sprintf(strTempVal, "%.3f ", (float)(*((float*)varInfo->VariablePointer)));
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}


void Format_MemoryDumpAscii(uint8_t row, void* info)
{
	int index=0;
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	uint8_t* MemoryDumpPointer = 0;
	if(varInfo->Offset) MemoryDumpPointer = ((uint32_t**)(varInfo->VariablePointer));
	else MemoryDumpPointer = *((uint32_t**)(varInfo->VariablePointer));

	if(!MemoryDumpPointer)  return;
	strTempVal[0]=' ';
	strTempVal[1]=' ';
	for (index=2;index<22;index++)
	{
		strTempVal[index] = *MemoryDumpPointer;
		if(strTempVal[index]<0x1f)strTempVal[index]=' ';
		MemoryDumpPointer++;
	}
	strTempVal[index+1]=0;
	GUI_DrawString(LCD_WIDTH / 2, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}
void Format_MemoryDisplayAscii(uint8_t row, void* info)
{
	int index=0;
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	uint8_t* MemoryDumpPointer = varInfo->VariablePointer;
//	if(varInfo->Offset) MemoryDumpPointer = varInfo->VariablePointer;
//	else MemoryDumpPointer = *((uint32_t**)(varInfo->VariablePointer));

	if(!MemoryDumpPointer)  return;
	strTempVal[0]=' ';
	strTempVal[1]=' ';
	for (index=2;index<22;index++)
	{
		strTempVal[index] = *MemoryDumpPointer;
		if(strTempVal[index]<0x1f)strTempVal[index]=' ';
		MemoryDumpPointer++;
	}
	strTempVal[index+1]=0;
	
	GUI_DrawString(LCD_WIDTH / 2, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}
void Format_MemoryDumpHex(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	memset(strTempVal, 0, 40);
	char* temp = strTempVal;
	uint8_t* soapHex = (uint8_t*)(varInfo->VariablePointer + varInfo->Offset);
	for(idx = 0; idx < 8; idx ++) {
		sprintf(temp, "%02X ", soapHex[idx]);
		temp += 3;
	}
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_Boolean(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, Y, varInfo->Label, FONTSIZE, varInfo->Color_1);
	sprintf(strTempVal, "%s ", (*(uint8_t*)varInfo->VariablePointer) == 0?"False":"True");
	GUI_DrawString(VALUE_POS, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}
void Format_Bar_Dutty(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint16_t val = *(uint16_t*)varInfo->VariablePointer;
	uint32_t Divisor=(uint32_t*)varInfo->Offset;//get the scaler part
	if(Divisor)val/=Divisor;//use the Offset for a way to scale the value to 0-100
	if(val > 100) val = 100;
	float percentON = (float)(val * 0.01) ;//lets see how much ON time we have
	/*   |=====60%==|==40%==| */
	/*   X1========X2====X3*/

	GUI_DrawString(LEFT_PADDING, PADDING_VALUE, varInfo->Label, FONTSIZE, varInfo->Color_1);

	uint16_t X1 = VALUE_POS;
	uint16_t X2 = VALUE_POS + percentON * (LCD_WIDTH - VALUE_POS - RIGHT_PADDING); //Screen Width -Left padding - Right Padding
	uint16_t X3 = LCD_WIDTH - RIGHT_PADDING;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	if (X2 > X1)	GUI_FillRect(X1, Y, X2, Y + LCD_LINESIZE - PADDING_VALUE, varInfo->Color_2);
	
	//if(X3 > X2) GUI_FillRect(X2, PADDING, X3, LCD_LINESIZE-PADDING, COLOR_GRAY);
	sprintf(strTempVal, "%d%s", val, "%");
	GUI_DrawString((X1 + X3) / 2, Y, strTempVal, FONTSIZE, varInfo->Color_1);

}
void Format_Bar_Status(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint8_t val = *(uint8_t*)varInfo->VariablePointer;
	GUI_DrawString(LEFT_PADDING, PADDING_VALUE, varInfo->Label, FONTSIZE, varInfo->Color_1);
	uint16_t X1 = VALUE_POS;
	uint16_t X2 = LCD_WIDTH - RIGHT_PADDING;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	if(val) {
		GUI_FillRect(X1, Y, X2, Y + LCD_LINESIZE - PADDING_VALUE, varInfo->Color_2);
	}else {
		GUI_FillRect(X1, Y, X2, Y + LCD_LINESIZE - PADDING_VALUE, (uint16_t)COLOR_GRAY);
	}
	sprintf(strTempVal, "%d", val);
	GUI_DrawString((X1 + X2) / 2, PADDING_VALUE, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_Bar_Float(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	float val = *(float*)varInfo->VariablePointer;
	float max = *(float*)varInfo->Offset;
	if(val > max) val = max;
	float percentON = val / max ;//lets see how much ON time we have
	/*   |=====60%==|==40%==| */
	/*   X1========X2====X3*/
	uint16_t X1 = VALUE_POS;
	uint16_t X2 = VALUE_POS + percentON * (LCD_WIDTH - VALUE_POS - RIGHT_PADDING); //Screen Width -Left padding - Right Padding
	uint16_t X3 = LCD_WIDTH - RIGHT_PADDING;
	uint16_t Y = PADDING_VALUE + (LCD_LINESIZE * row);
	GUI_DrawString(LEFT_PADDING, PADDING_VALUE, varInfo->Label, FONTSIZE, varInfo->Color_1);

	if (X2 > X1)	GUI_FillRect(X1, Y, X2, Y + LCD_LINESIZE - PADDING_VALUE, varInfo->Color_2);
	if (X3 > X2)	GUI_FillRect(X2, Y, X3, Y + LCD_LINESIZE - PADDING_VALUE, COLOR_GRAY);

	sprintf(strTempVal, "%.3f", val);
	GUI_DrawString((X1 + X3) / 2 - 10, Y, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Format_SoapStringWithIndex(uint8_t row, void* info)
{
	varInfo = (LcdVariableInfo*)info;
	uint8_t* soap = (uint8_t*)varInfo->VariablePointer;
	uint16_t index = varInfo->Offset;
	uint16_t k = 0, p = 0;
	uint16_t delimeter_cnt = 0;
	memset(strTempVal, 0, 40);
	while(soap[k] != 0 && soap[k] != 0xff) //loop until end of string
	{
		if(delimeter_cnt == index && (soap[k] != ',' && soap[k] != '\n') )
		{
			strTempVal[p] = soap[k];
			p ++;
		}
		if(soap[k] == ',' || soap[k] == '\n') delimeter_cnt ++;
		if(delimeter_cnt > index) break;
		k ++;
	}
	varInfo = (LcdVariableInfo*)info;
	GUI_DrawString(LEFT_PADDING, PADDING_VALUE, varInfo->Label, FONTSIZE, varInfo->Color_1); //label?
	GUI_DrawString(VALUE_POS, PADDING_VALUE, strTempVal, FONTSIZE, varInfo->Color_2);
}

void Update_Page(LcdVariableInfo* InfoToDisplay)
{
	//GUI_Clear(COLOR_BLACK);
	uint16_t row = 0;
	while (InfoToDisplay->VariablePointer)
	{
		switch (InfoToDisplay->FuncType)
		{
		case FUNC_INT32: 		Format_Int32(row, &InfoToDisplay); break;
		case FUNC_INT16: 		Format_Int16(row, &InfoToDisplay); break;
		case FUNC_FLOAT: 		Format_Float3_3(row, InfoToDisplay); break;
		//case FUNC_FLOAT_QUEVAR: Format_Float_QueVar(row, InfoToDisplay); break;
		case FUNC_HEX8: 		Format_Hex8(row, InfoToDisplay); break;
		case FUNC_HEX16: 		Format_Hex16(row, InfoToDisplay); break;
		case FUNC_HEX32: 		Format_Hex32(row, InfoToDisplay); break;
		case FUNC_ASCII: 		Format_Ascii(row, InfoToDisplay); break;
		case FUNC_BOOLEAN: 		Format_Boolean(row, InfoToDisplay); break;
		case FUNC_BAR_STATUS: 	Format_Bar_Status(row, InfoToDisplay); break;
		case FUNC_BAR_DUTTY: 	Format_Bar_Dutty(row, InfoToDisplay); break;
		case FUNC_BAR_FLOAT: 	Format_Bar_Float(row, InfoToDisplay); break;
		case FUNC_MEMHEX_64:    Format_MemoryDumpHex(row, InfoToDisplay); break;
		case FUNC_MEMDUMPASCII: Format_MemoryDumpAscii(row, InfoToDisplay); break;
		case FUNC_MEMDUMPHEX:   Format_MemoryDumpHex(row, InfoToDisplay); break;
		case FUNC_MEMDISPASCII: Format_MemoryDisplayAscii(row, InfoToDisplay); break;
		case FUNC_ASCI_SOAP: 	Format_SoapStringWithIndex(row, InfoToDisplay); break;
		}
		InfoToDisplay++;    
		row++;
	}
}


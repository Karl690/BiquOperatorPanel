#include "configure.h"
#include "global.h"
#include "displaylist.h"

#define NUMBER_OF_DISPLAY_LISTS 7

void Format_Int(uint8_t row, void* info);
void Format_Int16(uint8_t row, void* info);
void Format_Hex8(uint8_t row, void* info);
void Format_Hex16(uint8_t row, void* info);
void Format_Hex32(uint8_t row, void* info);
void Format_Ascii(uint8_t row, void* info);
void Format_String(uint8_t row, void* info);
void Format_Float3_3(uint8_t row, void* info);
void Format_MemoryDumpAscii(uint8_t row, void* info);
void Format_MemoryDumpHex(uint8_t row, void* info);
void Format_Boolean(uint8_t row, void* info);
void Format_Bar(uint8_t row, void* info);
void Format_MemoryDumpAscii(uint8_t row, void* info);

void Update_Page(LcdVariableInfo* InfoToDisplay);
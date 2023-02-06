#include "configure.h"
#include "global.h"

extern uint8_t* MemoryDumpDisplayAddress;
void initializeSoapNudList();

void glBtnPlus_TouchEvent(void* sender, long unsigned int x, long unsigned int y);
void glBtnMinus_TouchEvent(void* sender, long unsigned int x, long unsigned int y);
void glBtnSave_TouchEvent(void* sender, long unsigned int x, long unsigned int y);
void glBtnApply_TouchEvent(void* sender, long unsigned int x, long unsigned int y);

void eraseFlashButonEvent(void* sender, long unsigned int x, long unsigned int y);
void displaySoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y);
void ShiftbitWritetestButtonEvent(void* sender, long unsigned int x, long unsigned int y);
void displayCalibrationButtonEvent(void* sender, long unsigned int x, long unsigned int y);
void LoadSoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y);
void SaveSoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y);

void ChangeDisplayModeListEvent(void* sender);

void PageUpListbox();
void PageDownListbox();



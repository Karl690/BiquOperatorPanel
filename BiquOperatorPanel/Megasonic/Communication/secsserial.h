#include "main.h"
void Init_SecsSerial(uint8_t UartIndex);
void CheckForSecsTxRx();
void SendUartSecsString(char* stringToSend);
void ParseIncommingLineToSecsString();

void SecsTimers(void);

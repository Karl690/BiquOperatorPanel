#pragma once
#include "main.h"
#define SECS_BUFFER_LENGTH 300

#define SECS_DEVICE_ID 1
typedef enum
{
	S1F1  = 101,
	S1F2  = 102,
	S1F3  = 103,
	S1F4  = 104,
	S1F5  = 105,
	S1F6  = 106,
	S2F19 = 219,
	S2F20 = 220,
	S2F21 = 221,
	S2F22 = 222,
	S7F1  = 701,
	S7F2  = 702,
	S7F3  = 703,
	S7F4  = 704,
	S7F5  = 705,
	S7F6  = 706,
	S9F1  = 901
}SECSCOMMAND;

typedef struct tagSecsMsgPacket
{
	uint8_t DataLength;
	uint8_t	Id;
	uint8_t Stream;
	uint8_t Function;
	uint8_t ReceiveWbit;
	uint8_t SystemByte1;
	uint8_t SystemByte2;
	uint8_t SystemByte3;
	uint8_t SystemByte4;
	uint16_t CheckSum;
	uint8_t RawData[SECS_BUFFER_LENGTH];
}SecsMsgPacket;


extern uint16_t secstimer1;
extern uint16_t secstimer2;
extern uint16_t secstimer3;
extern uint16_t secstimer5;
extern uint16_t secstimer6;
extern uint16_t secstimer7; //autoconnect in 3 seconds
extern uint16_t CHECKSUMCALCULATED;
extern uint16_t secsmessagelength;
extern uint16_t checksum_passed;
extern uint16_t numberofretriesleft;
extern uint16_t defaultnumberofretriesleft;
extern uint16_t secssendfail;
extern uint16_t secssendpass;
extern uint16_t systembytes;
extern uint16_t systembyte34;
extern uint16_t receiveid;

extern char ReceivedSecsCmd[10];
extern char SentSecsCmd[10];
void Init_SecsSerial(uint8_t UartIndex);
void CheckForSecsTxRx();
void SendUartSecsString(char* stringToSend);
void ParseIncommingLineToSecsString();

void SecsTimers(void);

void PrcessSecsReceivedMessage();
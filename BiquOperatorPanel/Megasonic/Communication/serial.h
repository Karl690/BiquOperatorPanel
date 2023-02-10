#pragma once
#include "configure.h"
#include "global.h"

#define NULL_CHAR                  '\0'    // 0
#define TERMINATE_WAIT_CHAR          1
#define PAUSE_AT_END_OF_MOVE_CHAR    2
#define PAUSE_AT_END_OF_LAYER_CHAR   3
#define AVAILABLE_4                  4  // can be harvested for Repetrel to Hydra comm
#define HELLO_WORLD_CHAR             4  // char to send to Repetrel to get repetrel to talk to Hydra over the master comm port with a PING
#define SEND_STATUS_CHAR             5
#define ASCII_ACK                    6
#define PING_CHAR                    7  // (bell)
#define ABORT_CHAR                   8  // abort all processes, and stop all motion (backspace)
#define URGENT_911_CMD_CHAR          9  //hot inject flag
#define CATASTROPHIC_ERROR_ALERT_CHAR 9
#define CMD_END_CHAR                 10 // '\n' -  used to terminate every gcode line (linefeet)
#define SENDSTRING_TERM_CHAR         10
#define LF_CHAR                      10 // '\n'
#define JOG_Z_TABLE_UP               11
#define JOG_Z_TABLE_DOWN             12
#define CR_CHAR                      13 // '\r' (carriage return)
#define REPETREL_COMM_WATCHDOG_CHAR  14
#define JOG_DISPLAYplus  			 15
#define JOG_DISPLAYminus             16
#define VARIABLE_RESET               17

#define LIGHTBURN_STOP               0x18
#define LARGEST_SPECIAL_CHAR         0x1f // anything below this will end a comment string %=

#define MAX_STRING_SIZE				260
#define MAX_CHARS_FOR_PARAMETER 	20
#define COMMENT_STRING_LENGTH   	(256+3)	//+3 for leading and trailing delim + NULL_CHAR
#define GCODE_STRING_ARG_LENGTH 	(256+3)	//+3 for leading and trailing delim + NULL_CHAR



#define SERIAL_BUFFER_SIZE 			(0x7ff)


typedef enum {
	COMTYPE_MAIN   = 0,
	COMTYPE_AUX    = 1,
	COMTYPE_EQUIP  = 2,
	COMTYPE_CUSTOM = 3,
	COMTYPE_SECS   = 4,
} ComPortType;

typedef enum {
	UNKNOWN_MASTER = 0,
	UART3_MASTER   = 1,
	UART4_MASTER   = 2,
	UART6_MASTER   = 3,
	USB_MASTER     = 4,
	BOOTUP         = 5
} masterPort_t;

typedef struct {
	char GCodeArgA[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgB[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgC[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgD[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgE[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgF[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgG[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgH[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgI[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgJ[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgK[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgL[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgM[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgN[MAX_CHARS_FOR_PARAMETER]; //line number
	char GCodeArgO[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgP[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgQ[MAX_CHARS_FOR_PARAMETER]; //checksum -- using 'Q'
	char GCodeArgR[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgS[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgT[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgU[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgV[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgW[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgX[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgY[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgZ[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgSplat[MAX_CHARS_FOR_PARAMETER];
	char GCodeArgComment[COMMENT_STRING_LENGTH]; //buffer mismatch, working buffer is only 1024 long
	char GcodeArgStringParam[GCODE_STRING_ARG_LENGTH];
}AsciArgs;

typedef struct {
	uint8_t*  	buffer; //receive buffer pointer
	uint8_t*  	BufferStart; //fixed memory address of beginning of buffer
	uint8_t*  	BufferEnd; //fixed memory address of END of BUffer
	uint8_t* 	Head; // index of where to store the next char
	uint8_t* 	Tail; // index of where to pull the next char
	uint16_t  	CharsInBuf; // total valid chars in buffer
	uint16_t  	RxLineCount; // if there is a valid command waiting
	uint16_t  	HeadRoom; // if more characters in the buffer than this number, do not allow more incoming commands
	uint16_t  	ReadyForAtof; //when we have encountered a full line "\n"  flip up the flag to convert to Float.
	uint16_t  	ArgumentLength; //how many charcters the incoming argument is so far
	char *GCodeArgPtr; //how many charcters the incoming argument is so far
	AsciArgs  AsciiArgs; //ascii buffers for each key character and their values in ascii, will convert to floats
} ComBuffer;

typedef struct {
	USART_TypeDef* UartHandler;
	ComBuffer       RxBuffer; //standard incoming receive buffer, circular
	ComBuffer RxUrgentBuffer; //Priority Gocode rx buffer, bypasses big input que to execute in front of qued commands
	ComBuffer       TxBuffer; //outgoing characters in que
	uint32_t      UrgentFlag; //set when 911 character is received, signifying the beginning of a priority gcode line
	uint32_t     AcksWaiting; //acknowledge waiting to implement Handshake
	ComPortType      ComType; // Main com, aux com, machine interface
} COMPORT;



#define SIZE_OF_DEFERRED_COMMAND_QUEUE   15
//
extern COMPORT COMUSB; //normal comport for com to pc
extern COMPORT COM2; //uart based rs232 for equipment com
extern COMPORT COM3; //ch340 usb to serial bridge for either equipment or pc, used for AUX command inject from Matlab...
//
extern COMPORT* MasterCommPort;
extern char SendString[MAX_STRING_SIZE];
extern uint32_t ExecuteImmediateFlag;
extern uint8_t Rx3Data[];
extern uint8_t Rx6Data[];
extern uint16_t USBPacketLength;
extern uint8_t* USBPacketAddress;
extern char ConnectionString[];
extern uint32_t gcodeCmdsReceived; //full count of packets recieved
extern uint8_t * LastMessageTail;

extern int JogMotorZFlag; // used to signal a offset adjust of the z axis , will jog up x pulses without changing pulse counter
extern uint32_t CmdQueDisplayOffset;

void Init_Serial(void);

extern void sendChar(uint8_t SerialIndex, uint8_t ch);
extern void sendString(char* text, uint8_t SerialIndex);
extern void sendStringCR(char* stringToSend, uint8_t SerialIndex);
extern void SendUsbVcpString(char* stringToSend);
void SendUart2String(char* stringToSend);
void SendUart3String(char* stringToSend);
extern void USBD_CDC_ReceivePacketCallback(uint8_t*Buf, uint32_t Len); //Callback function for recieving thru USB VCP


extern void parseIncomingCommand(ComBuffer * WorkRxBuffer);
extern void ResetGcodeParseBuffer();
extern void SplitCurrentGcodeLine2Arguments(ComBuffer * WorkingBuffer);
extern void addStringToBuffer(ComBuffer *targetBuffer, uint8_t* stringToAddToBuffer);
extern void USBTxProcessor(void);
extern void addCharToBuffer(ComBuffer *targetBuffer, uint8_t RawChar);
extern void GetCharFromBuffer(ComBuffer *SourceBuffer);
extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
extern void CheckForUart3Receive(void);
extern void CheckForUart6Receive(void);
void CheckForUart2TxRx(void);
void CheckForUart3TxRx(void);
extern void USART234_Init(void);
//extern void USART2_Init(void);
extern void USART3_Init(void);
extern void ResetAsciParsePointers(ComBuffer* BufferToReset);


void InitSerial(uint8_t UartIndex, COMPORT* ComPort, uint8_t* RxBuffer, uint8_t* RxUrgentBuffer, uint8_t* TxBuffer);
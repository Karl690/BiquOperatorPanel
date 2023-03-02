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
	uint8_t*  	buffer; //receive buffer pointer
	uint32_t    Buffer_Size;
	uint16_t 	Head; // index of where to store the next char
	uint16_t 	Tail; // index of where to pull the next char
	uint16_t  	RxLineCount; // if there is a valid command waiting
	uint16_t  	HeadRoom; // if more characters in the buffer than this number, do not allow more incoming commands
	uint16_t  	ReadyForAtof; //when we have encountered a full line "\n"  flip up the flag to convert to Float.
	uint16_t  	ArgumentLength; //how many charcters the incoming argument is so far
	char *GCodeArgPtr; //how many charcters the incoming argument is so far
} ComBuffer;
typedef struct {
	USART_TypeDef* UartHandler;
	ComBuffer       RxBuffer; //standard incoming receive buffer, circular
	ComBuffer       TxBuffer; //outgoing characters in que	
	uint32_t     AcksWaiting; //acknowledge waiting to implement Handshake
	uint32_t     CmdWaiting; //have received a magic end of line character
	ComPortType      ComType; // Main com, aux com, machine interface
} COMPORT;



#define SIZE_OF_DEFERRED_COMMAND_QUEUE   15
//
extern COMPORT COMUSB; //normal comport for com to pc
extern COMPORT COM2; //uart based rs232 for equipment com
extern COMPORT COM3; //ch340 usb to serial bridge for either equipment or pc, used for AUX command inject from Matlab...
extern COMPORT COM4; //ch340 usb to serial bridge for either equipment or pc, used for AUX command inject from Matlab...
//
extern COMPORT* MasterCommPort;
extern COMPORT* COMSECS;
extern COMPORT* COMSIMPLE;
extern char SendString[MAX_STRING_SIZE];


extern uint8_t Rx_BufferUSB[RX_BUFFER_SIZE];
extern uint8_t Tx_BufferUSB[TX_BUFFER_SIZE];
////serial port 3
extern uint8_t Rx_Buffer2[RX_BUFFER_SIZE];
extern uint8_t Tx_Buffer2[TX_BUFFER_SIZE];
extern uint8_t Rx_Buffer3[RX_BUFFER_SIZE];
extern uint8_t Tx_Buffer3[TX_BUFFER_SIZE];
extern uint8_t Rx_Buffer4[RX_BUFFER_SIZE];
extern uint8_t Tx_Buffer4[TX_BUFFER_SIZE];


extern uint32_t ExecuteImmediateFlag;
extern uint16_t USBPacketLength;
extern uint8_t* USBPacketAddress;
extern char ConnectionString[];
extern uint32_t gcodeCmdsReceived; //full count of packets recieved
extern uint8_t * LastMessageTail;

extern int JogMotorZFlag; // used to signal a offset adjust of the z axis , will jog up x pulses without changing pulse counter
extern uint32_t CmdQueDisplayOffset;

extern void SendUsbVcpString(char* stringToSend);

extern void USBD_CDC_ReceivePacketCallback(uint8_t*Buf, uint32_t Len); //Callback function for recieving thru USB VCP
extern void USBTxProcessor(void);
void InitSerialBuffers();
void AddSerialBufferToBuffer(ComBuffer *targetBuffer, uint8_t* buf, uint16_t size);
void AddSerialStringToBuffer(ComBuffer *targetBuffer, char*);
void AddSerialCharToBuffer(ComBuffer *targetBuffer, uint8_t RawChar);
extern void GetCharFromBuffer(ComBuffer *SourceBuffer);

void CheckForUart2TxRx(void);
void CheckForUart3TxRx(void);
void CheckForUart4TxRx(void);
extern void ResetAsciParsePointers(ComBuffer* BufferToReset);

#define SERIAL_UART_NUM 6
typedef enum
{
	SERIAL_UART1 = 0,
	SERIAL_UART2 = 1,
	SERIAL_UART3 = 2,
	SERIAL_UART4 = 3,
	SERIAL_UART5 = 4,
	SERIAL_UART6 = 5,
	SERIAL_USBVCP = 6,
}SERIAL_TYPE;

typedef struct
{
	USART_TypeDef* uart;
	uint32_t	DefaultBaudRate;
	__IO uint32_t* uart_aphb;
	uint32_t	uart_rcc;
	uint32_t	Pin_Tx; //pintype
	uint32_t	Pin_Rx;
	uint32_t	Port;
	uint32_t	Afunction;
	__IO uint32_t* gpio_aphb;
	uint32_t	gpio_rcc; //aphb;
	__IO uint32_t* dma_aphb;
	uint32_t	dma_rcc;
	uint8_t		dma_channel;
	DMA_Stream_TypeDef* dma_stream;	
	COMPORT* ComPort;

} Uart_configuration;

void Init_Uart(uint8_t port);
void InitCom_Buffers(COMPORT* CMPORT, uint8_t* Rxbff, uint8_t* Txbff);
void InitSerial_Buffers(uint8_t port);

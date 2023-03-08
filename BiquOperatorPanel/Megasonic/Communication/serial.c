#include "main.h"
#include "serial.h"
#include "global.h"
#include "RevisionHistory.h"
#include "taskmanager.h"
#include "configure.h"
#include "stm32f4xx_usart.h"
//USB SERIAL PORT
uint8_t Rx_BufferUSB[RX_BUFFER_SIZE] __attribute__((aligned(RX_BUFFER_SIZE))); //2k boundry
uint8_t Tx_BufferUSB[TX_BUFFER_SIZE] __attribute__((aligned(TX_BUFFER_SIZE))); //2k boundry
////serial port 2
uint8_t Rx_Buffer2[RX_BUFFER_SIZE] __attribute__((aligned(RX_BUFFER_SIZE))); //2k boundry
uint8_t Tx_Buffer2[TX_BUFFER_SIZE] __attribute__((aligned(TX_BUFFER_SIZE))); //2k boundry
//
////serial port 3
uint8_t Rx_Buffer3[RX_BUFFER_SIZE] __attribute__((aligned(RX_BUFFER_SIZE))); //2k boundry
uint8_t Tx_Buffer3[TX_BUFFER_SIZE] __attribute__((aligned(TX_BUFFER_SIZE))); //2k boundry
////serial port 4
uint8_t Rx_Buffer4[RX_BUFFER_SIZE] __attribute__((aligned(RX_BUFFER_SIZE))); //2k boundry
uint8_t Tx_Buffer4[TX_BUFFER_SIZE] __attribute__((aligned(TX_BUFFER_SIZE))); //2k boundry
//

COMPORT COMUSB; //normal comport for com to pc
COMPORT COM2; //uart based rs232 for equipment com  version
COMPORT COM3; 
COMPORT COM4;
COMPORT* MasterCommPort = &COMUSB; //used to specify which port is the master communications port to PC

ComBuffer* RawRxWorkBuff;

char ConnectionString[] = CONNECTIONSTRING;
uint32_t GcodeLineNumber = 0; // increments each command line, but also can be set with ARG_N; resets to 0 on M30 currentCommandString
char SendString[MAX_STRING_SIZE] = { 0 };
char* displayTestString = "this is a test \n";
char Headnumber = 0;
char HeadLetter = 0;
char WorkCharacter = '-'; //working character variable for getting characters from buffer
uint32_t  characterINCount = 0;
uint32_t asciiChecksum32   = 0;
uint32_t asciiCharsRcvd    = 0;
uint32_t gcodeCmdsReceived = 0; //full count of packets recieved
uint16_t USBPacketLength = 0;
uint8_t* USBPacketAddress = 0;
uint8_t* LastMessageTail;
int requestToAbortAtEndOfMove = 0;

int JogMotorZFlag = 0;

char *testData = CONNECTIONSTRING;
uint32_t CmdQueDisplayOffset = 0;

ComBuffer *WorkTxBuffUSB;
uint8_t USBXmitBuffer[1024];
uint32_t numberOfXmitCharactersToSend = 0;
//
uint8_t Uart3XmitBuffer[1024];
uint32_t Uart3numberOfXmitCharactersToSend = 0;
//
uint8_t Uart6XmitBuffer[1024];
uint32_t Uart6numberOfXmitCharactersToSend = 0;

uint32_t NumberOfCharactersSent = 0;
uint32_t NumberOfCharactersReceived = 0;

static const Uart_configuration Uart_Configurations[SERIAL_UART_NUM] = {
	{ NULL },
	{USART2, 9600, &RCC->APB1ENR, RCC_APB1Periph_USART2,
			PIN_NUM_02, PIN_NUM_03, PIN_PORT_A, PIN_AF_USART2, &RCC->AHB1ENR, RCC_AHB1Periph_GPIOA,
			&RCC->AHB1ENR, RCC_AHB1Periph_DMA1, 4, DMA1_Stream5, &COM2 },
	{ USART3, 9600, &RCC->APB1ENR, RCC_APB1Periph_USART3, //uart
			PIN_NUM_10, PIN_NUM_11, PIN_PORT_B, PIN_AF_USART3, &RCC->AHB1ENR, RCC_AHB1Periph_GPIOB, //pins
			&RCC->AHB1ENR, RCC_AHB1Periph_DMA1, 4, DMA1_Stream1, &COM3 },//dma
	{ UART4, 9600, &RCC->APB1ENR, RCC_APB1Periph_UART4, //uart
			PIN_NUM_10, PIN_NUM_11, PIN_PORT_C, PIN_AF_UART4, &RCC->AHB1ENR, RCC_AHB1Periph_GPIOC, //pins
			&RCC->AHB1ENR, RCC_AHB1Periph_DMA1, 4, DMA1_Stream2, &COM4 },//dma
	{ NULL },
	{ NULL },
};

void AddSerialBufferToBuffer(ComBuffer *targetBuffer, uint8_t* buf, uint16_t size)
{
	uint16_t index = 0;
	for (index = 0; index < size; index++)
	{
		targetBuffer->buffer[targetBuffer->Head] = buf[index];
		targetBuffer->Head++;
		targetBuffer->Head &= (targetBuffer->Buffer_Size - 1);
	}
}


void AddSerialStringToBuffer(ComBuffer *targetBuffer, char* SourceString)
{
	uint16_t size = strlen(SourceString);
	AddSerialBufferToBuffer(targetBuffer, (uint8_t*)SourceString, size);
}

void AddSerialCharToBuffer(ComBuffer *targetBuffer, uint8_t RawChar)
{
	targetBuffer->buffer[targetBuffer->Head] = RawChar;
	targetBuffer->Head++;
	targetBuffer->Head &= (targetBuffer->Buffer_Size - 1);
}

void SendUsbVcpString(char* stringToSend) {
	AddSerialStringToBuffer(&COMUSB.TxBuffer, stringToSend);
}

void ResetAsciParsePointers(ComBuffer* comport)
{
}
void InitSerialBuffers()
{
	COMUSB.ComType = COMTYPE_MAIN; //primary control port for PC and REPETREL comm
	//COM3.ComType = COMTYPE_AUX;
	//COM3.ComType = COMTYPE_EQUIP; //primary control port for PC and REPETREL comm
	//InitCom_Buffers(&COMUSB, Rx_BufferUSB, Tx_BufferUSB); //assign buffers and zero them out
	InitCom_Buffers(&COM2, Rx_Buffer2, Tx_Buffer2);
	InitCom_Buffers(&COM3, Rx_Buffer3, Tx_Buffer3);
	InitCom_Buffers(&COM4, Rx_Buffer4, Tx_Buffer4);
	
	// thess functions should be called in init_uart function
	RawRxWorkBuff = &COMUSB.RxBuffer;
	//karllvana look at the resetasciparsepointers() it is commented out now
	ResetAsciParsePointers(&COMUSB.RxBuffer);
	ResetAsciParsePointers(&COM2.RxBuffer);
	ResetAsciParsePointers(&COM3.RxBuffer);
	ResetAsciParsePointers(&COM4.RxBuffer);
}

void CheckForUart2TxRx()
{	
	if (COM2.UartHandler->SR & USART_SR_TXE)//if no room in tx register, skip
	{
		if (COM2.AcksWaiting)//acks have priority over all others
		{
			COM2.UartHandler->DR = (uint32_t) ASCII_ACK; //signal it is ok to send more commands
			COM2.AcksWaiting--;
		}
		else if(COM2.TxBuffer.Head != COM2.TxBuffer.Tail)
		{
			WorkCharacter = COM2.TxBuffer.buffer[COM2.TxBuffer.Tail];
			COM2.UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COM2.TxBuffer.Tail++;
			COM2.TxBuffer.Tail &= (COM2.TxBuffer.Buffer_Size - 1);
		}
	}
	//now check for receive
	//now check for receive
#ifndef USE_SERIAL_DMA
	while (Uart_Configurations[SERIAL_UART2].uart->SR & USART_SR_RXNE)
	{
		//this is polled mode
		COM2.RxBuffer.buffer[COM2.TxBuffer.Head] = (char)(uint8_t)(Uart_Configurations[SERIAL_UART2].uart->DR & 0xff); //rad the character
		COM2.RxBuffer.Head++;
		COM2.RxBuffer.Head &= (COM2.RxBuffer.Buffer_Size -1);
	}
#else
	//data from the uart triggers DMA transfer
	uint16_t oldHead = COM2.RxBuffer.Head;
	COM2.RxBuffer.Head = COM2.RxBuffer.Buffer_Size - Uart_Configurations[SERIAL_UART2].dma_stream->NDTR;	
	if (COM2.RxBuffer.Head - oldHead > 0)
	{
		NumberOfCharactersReceived += COM2.RxBuffer.Head - oldHead;
	}
	else if (COM2.RxBuffer.Head - oldHead < 0)
	{
		NumberOfCharactersReceived += COM2.RxBuffer.Head + (COM2.RxBuffer.Buffer_Size - oldHead);
	}
#endif
}

void CheckForUart3TxRx()
{	
	if (USART3->SR & USART_SR_TXE)//if no room in tx register, skip
	{
		if (COM3.AcksWaiting)//acks have priority over all others
		{
			USART3->DR = (uint32_t) ASCII_ACK; //signal it is ok to send more commands
			COM3.AcksWaiting--;
		}
		else if(COM3.TxBuffer.Head != COM3.TxBuffer.Tail)
		{
			WorkCharacter = COM3.TxBuffer.buffer[COM3.TxBuffer.Tail];
			USART3->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COM3.TxBuffer.Tail++;
			COM3.TxBuffer.Tail &= (COM3.TxBuffer.Buffer_Size - 1);
		}
	}
	//now check for receive
	//now check for receive
#ifndef USE_SERIAL_DMA
	while (Uart_Configurations[SERIAL_UART3].uart->SR & USART_SR_RXNE)
	{
		//this is polled mode
		COM3.RxBuffer.buffer[COM3.TxBuffer.Head] = (char)(uint8_t)(Uart_Configurations[SERIAL_UART3].uart->DR & 0xff); //rad the character
		COM3.RxBuffer.Head++;
		COM3.RxBuffer.Head &= (COM3.RxBuffer.Buffer_Size - 1);
	}
#else
	//data from the uart triggers DMA transfer
	uint32_t oldHead = COM3.RxBuffer.Head;
	COM3.RxBuffer.Head = COM3.RxBuffer.Buffer_Size - Uart_Configurations[SERIAL_UART3].dma_stream->NDTR;
	if (COM3.RxBuffer.Head - oldHead > 0)
	{
		NumberOfCharactersReceived += COM2.RxBuffer.Head - oldHead;
	}
	else if (COM3.RxBuffer.Head - oldHead < 0)
	{
		NumberOfCharactersReceived += COM3.RxBuffer.Head + (COM3.RxBuffer.Buffer_Size - oldHead);
	}
#endif
}


void CheckForUart4TxRx()
{	
	if (UART4->SR & USART_SR_TXE)//if no room in tx register, skip
	{
		if (COM4.AcksWaiting)//acks have priority over all others
		{
			UART4->DR = (uint32_t) ASCII_ACK; //signal it is ok to send more commands
			COM4.AcksWaiting--;
		}
		else if(COM4.TxBuffer.Head != COM4.TxBuffer.Tail)
		{
			WorkCharacter = COM4.TxBuffer.buffer[COM4.TxBuffer.Tail];
			UART4->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COM4.TxBuffer.Tail++;
			COM4.TxBuffer.Tail &= (COM4.TxBuffer.Buffer_Size - 1);
		}
	}
	//now check for receive
	//now check for receive
#ifndef USE_SERIAL_DMA
	while (Uart_Configurations[SERIAL_UART4].uart->SR & USART_SR_RXNE)
	{
		//this is polled mode
		COM4.RxBuffer.buffer[COM4.TxBuffer.Head] = (char)(uint8_t)(Uart_Configurations[SERIAL_UART4].uart->DR & 0xff); //rad the character
		COM4.RxBuffer.Head++;
		COM4.RxBuffer.Head &= (COM4.RxBuffer.Buffer_Size - 1);
	}
#else
	//data from the uart triggers DMA transfer
	uint32_t oldHead = COM4.RxBuffer.Head;
	COM4.RxBuffer.Head = COM4.RxBuffer.Buffer_Size - Uart_Configurations[SERIAL_UART4].dma_stream->NDTR;
	if (COM4.RxBuffer.Head - oldHead > 0)
	{
		NumberOfCharactersReceived += COM4.RxBuffer.Head - oldHead;
	}
	else if (COM4.RxBuffer.Head - oldHead < 0)
	{
		NumberOfCharactersReceived += COM4.RxBuffer.Head + (COM4.RxBuffer.Buffer_Size - oldHead);
	}
#endif
}


void InitCom_Buffers(COMPORT* CMPORT, uint8_t* Rxbff, uint8_t* Txbff)
{	
	//Initialize comport buffers and assign default values
	CMPORT->RxBuffer.buffer     			= Rxbff;
	CMPORT->RxBuffer.Buffer_Size			= RX_BUFFER_SIZE; //this number is used to keep in bounds
	CMPORT->RxBuffer.Head				= 0; //start of que
	CMPORT->RxBuffer.Tail				= 0; //end of the que
	CMPORT->RxBuffer.RxLineCount			= 0; // if there is a valid command waiting
	memset(CMPORT->RxBuffer.buffer, 0, CMPORT->RxBuffer.Buffer_Size);
	
	CMPORT->TxBuffer.buffer     			= Txbff;
	CMPORT->TxBuffer.Buffer_Size	= TX_BUFFER_SIZE; //this number is used to keep in bounds
	CMPORT->TxBuffer.Head				= 0; // index of where to put the next char
	CMPORT->TxBuffer.Tail				= 0; // index of where to pull the next char
	memset(CMPORT->TxBuffer.buffer, 0, CMPORT->TxBuffer.Buffer_Size);
}

void Init_Uart(uint8_t port)
{	
	Uart_configuration uartConfig = Uart_Configurations[port];
	if (uartConfig.uart == NULL) return;
	//Initialize serial buffers FIRST;
	uartConfig.ComPort->UartHandler	= uartConfig.uart; //assign the uart handle to the comport structure


	//GPIO pins next
	 //RCC for pin port enable
	*uartConfig.gpio_aphb |= uartConfig.gpio_rcc;
	//Initalize GPIO Pins (RX and TX)
	pinInit(uartConfig.Pin_Rx | uartConfig.Port | uartConfig.Afunction); // |INPUT_PULLDOWN);
	pinInit(uartConfig.Pin_Tx | uartConfig.Port | uartConfig.Afunction);
	
	//configure DMA NEXT
#ifdef USE_SERIAL_DMA
	*uartConfig.dma_aphb |= uartConfig.dma_rcc; //RCC for DMA enable	
	uartConfig.dma_stream->CR &= ~(1 << 0); // Disable DMA
	switch (port)
	{
	case 0: DMA2->LIFCR = (0x3F << 16); break;  // DMA2_Stream2 low  bits:16-21
	case 1: DMA1->HIFCR = (0xFC << 4); break;  // DMA1_Stream5 high bits: 6-11
	case 2: DMA1->LIFCR = (0xFC << 4); break;  // DMA1_Stream1 low  bits: 6-11
	case 3:  DMA1->LIFCR = (0x3F << 16); break;  // DMA1_Stream2 low  bits:16-21
	case 4:  DMA1->LIFCR = (0x3F << 0); break;  // DMA1_Stream0 low  bits: 0-5
	case 5: DMA2->LIFCR = (0xFC << 4); break;  // DMA2_Stream1 low  bits: 6-11
	}
	//	cfg->uart->CR3 |= 1 << 6; // DMA enable receiver

	uartConfig.dma_stream->PAR = (uint32_t)(&uartConfig.uart->DR); //data from the uart triggers DMA transfer
	uartConfig.dma_stream->M0AR = (uint32_t)(uartConfig.ComPort->RxBuffer.buffer); //memory address of beginning of buffer
	uartConfig.dma_stream->NDTR = uartConfig.ComPort->RxBuffer.Buffer_Size; //count of dma transfers remaining
	/* very important, we use circular dma buffer, so if you subtract the value in this register
	 * from the LENGHT of the buffer, you get the NEAD position, which we use for checking to see
	 * if there are any characters waiting to be processed
	  Rxbuffer.head=RxBuffer.Length-dma_stream->NDTR ;    */

	uartConfig.dma_stream->CR = uartConfig.dma_channel << 25;
	uartConfig.dma_stream->CR |= 3 << 16; // Priority level: Very high
	uartConfig.dma_stream->CR |= 0 << 13; // Memory data size: 8
	uartConfig.dma_stream->CR |= 0 << 11; // Peripheral data size: 8
	uartConfig.dma_stream->CR |= 1 << 10; // Memory increment mode
	uartConfig.dma_stream->CR |= 0 << 9; // Peripheral not increment mrrode
	uartConfig.dma_stream->CR |= 1 << 8; // Circular mode enabled
	uartConfig.dma_stream->CR |= 0 << 6; // Data transfer direction: Peripheral-to-memory
	uartConfig.dma_stream->CR |= 1 << 0; // Enable DMA
	
	uartConfig.uart->CR3 |= 1 << 6; // DMA enable receiver
#endif //
	*uartConfig.uart_aphb |= uartConfig.uart_rcc;
	//Initialize uart	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = uartConfig.DefaultBaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	
	USART_Init(uartConfig.uart, &USART_InitStructure);
	USART_Cmd(uartConfig.uart, ENABLE);
	ATOMIC_SET_BIT(uartConfig.uart->CR3, USART_CR3_DMAR); //enable dma flag for automatic transfers
}
#include "main.h"
#include "serial.h"
#include "global.h"
#include "RevisionHistory.h"
#include "taskmanager.h"
#include "configure.h"
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart6;

//declare a new buffer
uint8_t NewBuffer[10];
uint8_t Rx3Data[20];
uint8_t Rx6Data[20];

//USB SERIAL PORT
uint8_t  Rx_BufferUSB[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Rx_UrgentBufferUSB[SERIAL_BUFFER_SIZE] = { 0 };
uint8_t  Tx_BufferUSB[SERIAL_BUFFER_SIZE] = { 0 };
//serial port 6
uint8_t  RX_Buffer3[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Rx_UrgentBuffer3[SERIAL_BUFFER_SIZE] = { 0 };
uint8_t  Tx_Buffer3[0xfff] = { 0 };
 ;
//usb port
uint8_t  RX_Buffer6[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Rx_UrgentBuffer6[SERIAL_BUFFER_SIZE] = { 0 };
uint8_t  Tx_Buffer6[SERIAL_BUFFER_SIZE] = { 0 };
 ;
//

COMPORT COMUSB; //normal comport for com to pc
COMPORT COM2; //uart based rs232 for equipment com  version
COMPORT COM3; //ch340 usb to serial bridge for either equipment or pc, used for AUX command inject from Matlab...
COMPORT* MasterCommPort = &COMUSB; //used to specify which port is the master communications port to PC

ComBuffer* RawRxWorkBuff;

uint8_t RxBuffer[20] = { 0 };
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


////////////////////////////////////////////////////////////////////////////////
void AddSerialBufferToBuffer(ComBuffer *targetBuffer, uint8_t* buf, uint16_t size)
{
	uint16_t index = 0;
	for (index = 0; index < size; index++)
	{
		*targetBuffer->Head = buf[index];
		targetBuffer->Head++;
		if (targetBuffer->Head > targetBuffer->BufferEnd)
		  {targetBuffer->Head = targetBuffer->BufferStart; }
		targetBuffer->CharsInBuf++;
	}
}
void AddSerialStringToBuffer(ComBuffer *targetBuffer, char* SourceString)
{
	uint16_t size = strlen(SourceString);
	AddSerialBufferToBuffer(targetBuffer, (uint8_t*)SourceString, size);
}

void AddSerialCharToBuffer(ComBuffer *targetBuffer, uint8_t RawChar)
{
	*targetBuffer->Head = RawChar;
	targetBuffer->CharsInBuf++;
	targetBuffer->Head++;
	if (targetBuffer->Head > targetBuffer->BufferEnd)
	  {targetBuffer->Head = targetBuffer->BufferStart; }
	//if (RawChar == CMD_END_CHAR) targetBuffer->RxLineCount++; //tell them there is a cmd waiting to process.
	//add buffer full check and report overrun
}


void SendUsbVcpString(char* stringToSend) {
	AddSerialStringToBuffer(&COMUSB.TxBuffer, stringToSend);
}

void SendUart2String(char* stringToSend)
{
	AddSerialStringToBuffer(&COM2.TxBuffer, stringToSend);
}
void SendUart3String(char* stringToSend)
{
	AddSerialStringToBuffer(&COM3.TxBuffer, stringToSend);
}
void GetCharFromBuffer(ComBuffer *SourceBuffer)
{
	WorkCharacter = (uint8_t) *(SourceBuffer->Tail);
	SourceBuffer->CharsInBuf--;
	SourceBuffer->Tail++;
	if (SourceBuffer->Tail > SourceBuffer->BufferEnd)
	  {SourceBuffer->Tail = SourceBuffer->BufferStart; }
}

void InitSerialBuffers()
{
	COMUSB.ComType              = COMTYPE_MAIN; //primary control port for PC and REPETREL comm
	COMUSB.RxBuffer.buffer     	= Rx_BufferUSB;
	COMUSB.RxBuffer.BufferStart = &Rx_BufferUSB[0];
	COMUSB.RxBuffer.BufferEnd   = &Rx_BufferUSB[0] + sizeof(Rx_BufferUSB) - 1; //end of the que
	COMUSB.RxBuffer.Head        = &Rx_BufferUSB[0]; //start of que
	COMUSB.RxBuffer.Tail        = &Rx_BufferUSB[0]; //end of the que
	COMUSB.RxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	COMUSB.RxBuffer.RxLineCount = 0; // if there is a valid command waiting
	COMUSB.AcksWaiting          = 0;

	COMUSB.AcksWaiting          = 0;


	COMUSB.TxBuffer.buffer     	= Tx_BufferUSB;
	COMUSB.TxBuffer.BufferStart = &Tx_BufferUSB[0];
	COMUSB.TxBuffer.BufferEnd   = &Tx_BufferUSB[0] + sizeof(Tx_BufferUSB) - 1; //end of the que
	COMUSB.TxBuffer.Head		= COMUSB.TxBuffer.BufferStart; // index of where to put the next char
	COMUSB.TxBuffer.Tail	    = COMUSB.TxBuffer.BufferStart; // index of where to pull the next char
	COMUSB.TxBuffer.CharsInBuf	= 0; // total valid chars in buffer

	//
	COM2.ComType                = COMTYPE_AUX; //primary control port for PC and REPETREL comm
	COM2.RxBuffer.buffer     	= RX_Buffer3;
	COM2.RxBuffer.BufferStart   = &RX_Buffer3[0];
	COM2.RxBuffer.BufferEnd     = &RX_Buffer3[0] + sizeof(RX_Buffer3) - 1; //end of the que
	COM2.RxBuffer.Head          = &RX_Buffer3[0]; //start of que
	COM2.RxBuffer.Tail          = &RX_Buffer3[0]; //end of the que
	COM2.RxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	COM2.RxBuffer.RxLineCount = 0; // if there is a valid command waiting
	COM2.AcksWaiting            = 0;

	COM2.AcksWaiting               = 0;

	COM2.TxBuffer.buffer     	= Tx_Buffer3;
	COM2.TxBuffer.BufferStart   = &Tx_Buffer3[0];
	COM2.TxBuffer.BufferEnd     = &Tx_Buffer3[0] + sizeof(Tx_Buffer3) - 1; //end of the que
	COM2.TxBuffer.Head		    = COM2.TxBuffer.BufferStart; // index of where to put the next char
	COM2.TxBuffer.Tail	        = COM2.TxBuffer.BufferStart; // index of where to pull the next char
	COM2.TxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	//
	//RX_Buffer6
	COM3.ComType              = COMTYPE_EQUIP; //primary control port for PC and REPETREL comm
	COM3.RxBuffer.buffer     	= RX_Buffer6;
	COM3.RxBuffer.BufferStart   = &RX_Buffer6[0];
	COM3.RxBuffer.BufferEnd     = &RX_Buffer6[0] + sizeof(RX_Buffer6) - 1; //end of the que
	COM3.RxBuffer.Head          = &RX_Buffer6[0]; //start of que
	COM3.RxBuffer.Tail          = &RX_Buffer6[0]; //end of the que
	COM3.RxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	COM3.RxBuffer.RxLineCount = 0; // if there is a valid command waiting
	COM3.AcksWaiting            = 0;

	COM3.AcksWaiting               = 0;

	COM3.TxBuffer.buffer     	= Tx_Buffer6;
	COM3.TxBuffer.BufferStart   = &Tx_Buffer6[0];
	COM3.TxBuffer.BufferEnd     = &Tx_Buffer6[0] + sizeof(Tx_Buffer6) - 1; //end of the que
	COM3.TxBuffer.Head		    = COM3.TxBuffer.BufferStart; // index of where to put the next char
	COM3.TxBuffer.Tail	        = COM3.TxBuffer.BufferStart; // index of where to pull the next char
	COM3.TxBuffer.CharsInBuf	= 0; // total valid chars in buffer

	RawRxWorkBuff = &COMUSB.RxBuffer;
//
//	ResetGcodeParseBuffer(&COMUSB.RxBuffer);
//	ResetGcodeParseBuffer(&COMUSB.RxUrgentBuffer);
//	ResetGcodeParseBuffer(&COM6.RxBuffer);
//	ResetGcodeParseBuffer(&COM6.RxUrgentBuffer);
//	ResetGcodeParseBuffer(&COM3.RxBuffer);
//	ResetGcodeParseBuffer(&COM3.RxUrgentBuffer);
}

void Init_Serial(void)
{
	InitSerialBuffers(); //Initialized the buffers and configuration for All Serial(USB VCP, Uart3, Uart6)
	//ResetAsciParsePointers(&COMUSB.RxBuffer);
	//ResetAsciParsePointers(&COMUSB.RxUrgentBuffer);

	
	USART234_Init();
	//USART4_Init();
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(huart);

	if (huart == &huart2)
	{
		//karlchris
		HAL_UART_Receive_IT(huart, RxBuffer, 1);
	}
	else if (huart == &huart3)
	{
		HAL_UART_Receive_IT(huart, RxBuffer, 1);
	}
	/* NOTE : This function should not be modified, when the callback is needed,
	          the HAL_UART_RxCpltCallback can be implemented in the user file
	       */

}
////////////////////////////////////////////////////////////////////////////////

void USBTxProcessor(void)
{

	//	CDC_Transmit_FS((uint8_t *)testData,strlen (testData));
	//	return;
	WorkTxBuffUSB = &COMUSB.TxBuffer;
	uint8_t workcharacter = ' ';
	//todo, need to put a check in here to see if usb is busy or not.
	numberOfXmitCharactersToSend = 0;

	if (WorkTxBuffUSB->CharsInBuf > 0 || COMUSB.AcksWaiting)
	{
		while (COMUSB.AcksWaiting)
		{
			USBXmitBuffer[numberOfXmitCharactersToSend] = ASCII_ACK; //stuff the acks in the front of the serial stream
			COMUSB.AcksWaiting--;
			numberOfXmitCharactersToSend++;
		}
		while (WorkTxBuffUSB->CharsInBuf > 0)
		{
			workcharacter = *(WorkTxBuffUSB->Tail);
			USBXmitBuffer[numberOfXmitCharactersToSend] = workcharacter;
			WorkTxBuffUSB->CharsInBuf--;
			WorkTxBuffUSB->Tail++;
			if (WorkTxBuffUSB->Tail > WorkTxBuffUSB->BufferEnd)
			  {WorkTxBuffUSB->Tail = WorkTxBuffUSB->BufferStart; }
			numberOfXmitCharactersToSend++;
			if (workcharacter == CMD_END_CHAR)break;//one line at a time please
			if (numberOfXmitCharactersToSend > 150)break;//limit the transmission packet size
		}
		//VCP_write(USBXmitBuffer, numberOfXmitCharactersToSend);
		//CDC_Transmit_FS(USBXmitBuffer, numberOfXmitCharactersToSend); //send characater to USB port
		return;//only process 1 message per tick
	}
}
void USBD_CDC_ReceivePacketCallback(uint8_t*Buf, uint32_t Len)
{
	int Index = 0;
	USBPacketLength = Len;
	USBPacketAddress = Buf; //address of the usb string buffer
	if (Len > 2) LastMessageTail = COMUSB.RxBuffer.Head;
	RawRxWorkBuff = &COMUSB.RxBuffer; //point to the correct buffer
	while (Index < Len)
	{
		if (Buf[Index] > 0x19)
		{
			//normal ascii character processing, below 20 hex are special control characters
			*RawRxWorkBuff->Head = Buf[Index]; //read character from usb buff>>rxbuff
			RawRxWorkBuff->CharsInBuf++; //keep track of how many chars are ready for processing
			RawRxWorkBuff->Head++; //move pointer in rxbuffer to be ready for next char
			if (RawRxWorkBuff->Head > RawRxWorkBuff->BufferEnd)    //make sure we did not reach the end of the buffer
			{RawRxWorkBuff->Head = RawRxWorkBuff->BufferStart; }
			Index++; //increment to next INCOMING character position
			continue;//
		}
		//if you get here, you must process special characters

		switch (Buf[Index])
		{
		case   0:                                       break; //null end of the string
		case TERMINATE_WAIT_CHAR:   		//if (rawChar==1)
			//Process_TERMINATE_WAIT_CHAR(); 
			break;

		case PAUSE_AT_END_OF_MOVE_CHAR:     //if (rawChar==2)
			//requestToPauseAtEndOfMove = 1; 
			break;//set flag to stop at end of this move

		case PAUSE_AT_END_OF_LAYER_CHAR:     //if (rawChar==3)
			//requestToPauseAtEndOfLayer = 1; 
			break; //(when M790 is executed set flag to stop at end of this layer

		case AVAILABLE_4:	break; //if (rawChar==4)

		case SEND_STATUS_CHAR:    break; //if (rawChar==5)
			//M_Code_M775();break;// send live status on health of motion controller

		case ASCII_ACK: //if (rawChar==6)
			//ShowNextDisplay(); 
			break;

		case PING_CHAR:     //if (rawChar==7)
			AddSerialStringToBuffer(&COMUSB.TxBuffer, ConnectionString);
			AddSerialStringToBuffer(&COMUSB.TxBuffer, "COMUSB\n");
			break;

		case ABORT_CHAR:   requestToAbortAtEndOfMove = 1; break;  //if (rawChar==8)
			//this is a job abort, flush buffer NOW!!!!

		case URGENT_911_CMD_CHAR:     //if (rawChar==9)
			break;

		case CMD_END_CHAR:  //if (rawChar==10) 0xA or 0xD  can trigger the end of line
		case  13:
			gcodeCmdsReceived++;
			//addCharToBuffer(RawRxWorkBuff, CMD_END_CHAR);
			return;
		case JOG_Z_TABLE_UP:    JogMotorZFlag = 1; break;   //if (rawChar==11)

		case JOG_Z_TABLE_DOWN:  JogMotorZFlag = -1; break;   //if (rawChar==12)

		case REPETREL_COMM_WATCHDOG_CHAR:   // (rawChar==14)
			//_repetrelCommWatchCount = REPETREL_COMM_WATCHDOG_START_VALUE;
			break;

		case JOG_DISPLAYplus: 
			//ShowNextDisplay(); 
			break;											// (rawChar==15)

//		case JOG_DISPLAYminus:	ShowPreviousDisplay(); break;
//
//		case VARIABLE_RESET:   ClearSliceTimes(); ResetParseCounters(); break;				//if (rawChar==17)

		}
		Index++; //increment to next INCOMING character position
	}
}

void CheckForUart2TxRx()
{
	//todo, need to put a check in here to see if usb is busy or not.
	if (COM2.TxBuffer.CharsInBuf > 0 || COM2.AcksWaiting)
	{
		//transmit first
		while (USART2->SR & USART_SR_TXE)
		{
			if (COM2.AcksWaiting)
			{
				USART2->DR = (uint32_t) CMD_END_CHAR;
				COM2.AcksWaiting--;
				continue;
			}
			WorkCharacter = *COM2.TxBuffer.Tail;
			USART2->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COM2.TxBuffer.CharsInBuf--;			
			COM2.TxBuffer.Tail++;
			
			if (COM2.TxBuffer.Tail > COM2.TxBuffer.BufferEnd)
			{COM2.TxBuffer.Tail = COM2.TxBuffer.BufferStart; }
			if (WorkCharacter == CMD_END_CHAR)	break;//pause at a cr
			if (COM2.TxBuffer.CharsInBuf == 0) break;
		}
	}
	//now check for receive
	while (USART2->SR & USART_SR_RXNE)
	{
		*COM2.TxBuffer.Head = (uint8_t)(uint8_t)(USART2->DR & 0xff);
		COM2.TxBuffer.CharsInBuf++;
		COM2.TxBuffer.Head++;
		if (COM2.TxBuffer.Head > COM2.TxBuffer.BufferEnd)
		{COM2.TxBuffer.Head = COM2.TxBuffer.BufferStart; }
	}
}
void CheckForUart3TxRx()
{
	if (COM3.TxBuffer.CharsInBuf > 0 || COM3.AcksWaiting)
	{
		//transmit first
		while (USART3->SR & USART_SR_TXE)
		{
			if (COM3.AcksWaiting)
			{
				USART3->DR = (uint32_t) CMD_END_CHAR;
				COM3.AcksWaiting--;
				continue;
			}
			WorkCharacter = *COM3.TxBuffer.Tail;
			USART3->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COM3.TxBuffer.CharsInBuf--;
			COM3.TxBuffer.Tail++;
			if (COM3.TxBuffer.Tail > COM3.TxBuffer.BufferEnd)
			  {COM3.TxBuffer.Tail = COM3.TxBuffer.BufferStart; }
			if (WorkCharacter == CMD_END_CHAR)	break;//pause at a cr
			if (COM3.TxBuffer.CharsInBuf == 0) break;
		}
	}
	//now check for receive
	while (USART3->SR & USART_SR_RXNE)
	{
		*COM3.TxBuffer.Head = (char)(uint8_t)(USART3->DR & 0xff);
		COM3.TxBuffer.CharsInBuf++;
		COM3.TxBuffer.Head++;
		if (COM3.TxBuffer.Head > COM3.TxBuffer.BufferEnd)
		{COM3.TxBuffer.Head = COM3.TxBuffer.BufferStart; }
	}
}

//initialize the pointers so we put the parsed characters inthe right place
void ResetAsciParsePointers(ComBuffer* BufferToReset)
{
//	GCodeArgPtr = &BufferToReset->AsciiArgs.GCodeArgComment[0]; //use the gcode comment as the stunt double
//	currentArgLength = 0;
//	ResetGcodeParseBuffer(BufferToReset); //clean up the asc buffer pointers, so they can start at the beginning
//	GCodeArgsReadyToConvert = 0; //release the gcodeargs[char] so they can process the next one
}
void USART234_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 }; /* Init the low level hardware : GPIO, CLOCK */
	
	huart2.Instance = USART2;
	huart2.Init.BaudRate = USART2_BAUDRATE; //USART2_BAUDRATE;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (huart2.Init.BaudRate > 0)
	{
		__HAL_RCC_USART2_CLK_ENABLE(); /* Peripheral clock enable */
		huart2.Lock = HAL_UNLOCKED; /* Allocate lock resource and initialize it */
		HAL_UART_Init(&huart2);
		/**USART2 GPIO Configuration
		PA2     ------> USART3_TX
		PA3     ------> USART3_RX
		*/	
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		__HAL_UART_ENABLE(&huart2);
	}
	//now uart3
	huart3.Instance = USART3;
	huart3.Init.BaudRate = USART3_BAUDRATE; //USART2_BAUDRATE;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (huart3.Init.BaudRate > 0)
	{
		__HAL_RCC_USART3_CLK_ENABLE(); /* Peripheral clock enable must be done BEFORE tring to iInit*/
		huart3.Lock = HAL_UNLOCKED; /* Allocate lock resource and initialize it */
		HAL_UART_Init(&huart3);
		/**USART2 GPIO Configuration
		PB10     ------> USART4_TX
		PB11     ------> USART4_RX
		*/
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		__HAL_UART_ENABLE(&huart3);
	}
	//now uart4
	huart4.Instance = UART4;
	huart4.Init.BaudRate = USART4_BAUDRATE; //USART2_BAUDRATE;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (huart4.Init.BaudRate > 0)
	{
		__HAL_RCC_UART4_CLK_ENABLE(); /* Peripheral clock enable must be done BEFORE tring to i
		huart4.Lock = HAL_UNLOCKED; /* Allocate lock resource and initialize it */
		HAL_UART_Init(&huart4);
		/**USART2 GPIO Configuration
		PC10     ------> USART3_TX
		PC11     ------> USART3_RX
		*/
		__HAL_RCC_GPIOC_CLK_ENABLE(); /* Peripheral clock enable */
		GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		__HAL_UART_ENABLE(&huart4);
	}
	
}


void USART3_Init(void)
{
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	//huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	//huart6.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	//huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	__HAL_RCC_USART3_CLK_ENABLE(); /* Peripheral clock enable must be done BEFORE tring to init uart*/
	huart3.Lock = HAL_UNLOCKED; /* Allocate lock resource and initialize it */

	HAL_UART_Init(&huart3);
	GPIO_InitTypeDef GPIO_InitStruct = { 0 }; /* Init the low level hardware : GPIO, CLOCK */

	__HAL_RCC_GPIOC_CLK_ENABLE();
	/**USART6 GPIO Configuration
	PB10     ------> USART3_TX
	PB11     ------> USART3_RX
	//PC10     ------> USART3_TX
	//PC11     ------> USART3_RX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	huart3.gState = HAL_UART_STATE_BUSY;
	__HAL_UART_DISABLE(&huart3);

	//UART_SetConfig(&huart6);  /* Set the UART Communication parameters */

	//if (huart6.AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT) UART_AdvFeatureConfig(&huart6);

	/* In asynchronous mode, the following bits must be kept cleared:
	- LINEN and CLKEN bits in the USART_CR2 register,
	- SCEN, HDSEL and IREN  bits in the USART_CR3 register.*/
	CLEAR_BIT(huart3.Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
	CLEAR_BIT(huart3.Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

	//h750 gets this code to enable fifos
	//HAL_UARTEx_SetTxFifoThreshold(&huart6, UART_TXFIFO_THRESHOLD_1_8) ;
	//HAL_UARTEx_SetRxFifoThreshold(&huart6, UART_RXFIFO_THRESHOLD_1_8) ;
	__HAL_UART_ENABLE(&huart3);
}



////////////////////////////////////////////////////////////////
/*              write by lvana */

static volatile uint32_t* const rcc_uart_rst[] = {
	&RCC->APB2RSTR,
	&RCC->APB1RSTR,
	&RCC->APB1RSTR,
	&RCC->APB1RSTR,
	&RCC->APB1RSTR,
	&RCC->APB2RSTR,
};

static volatile uint32_t* const rcc_uart_en[] = {
	&RCC->APB2ENR,
	&RCC->APB1ENR,
	&RCC->APB1ENR,
	&RCC->APB1ENR,
	&RCC->APB1ENR,
	&RCC->APB2ENR,
};

static const uint32_t rcc_uart_bit[] = {
	0x00000010, // RCC_APB2  bit 4
	0x00020000, // RCC_APB1  bit 17
	0x00040000, // RCC_APB1  bit 18
	0x00080000, // RCC_APB1  bit 19
	0x00100000, // RCC_APB1  bit 20
	0x00000020, // RCC_APB2  bit 5
};
static USART_TypeDef* const uart[] = {
	USART1, // TX--PA9  RX--PA10
	USART2, // TX--PA2  RX--PA3
	USART3, // TX--PB10 RX--PB11
	UART4, // TX--PC10 RX--PC11
	UART5, // TX--PC12 RX--PD2
	USART6
 }; // TX--PG14 RX--PG9

static const uint16_t uart_tx[] = { USART1_TX_PIN, USART2_TX_PIN, USART3_TX_PIN, UART4_TX_PIN, UART5_TX_PIN, USART6_TX_PIN }; // TX
static const uint16_t uart_rx[] = { USART1_RX_PIN, USART2_RX_PIN, USART3_RX_PIN, UART4_RX_PIN, UART5_RX_PIN, USART6_RX_PIN }; // RX

void UART_GPIO_Init(uint8_t port)
{
	uint8_t UART_AF_NUM[] = { GPIO_AF_USART1, GPIO_AF_USART2, GPIO_AF_USART3, GPIO_AF_UART4, GPIO_AF_UART5, GPIO_AF_USART6 };

	GPIO_InitSet(uart_tx[port], MGPIO_MODE_AF_PP, UART_AF_NUM[port]);
	GPIO_InitSet(uart_rx[port], MGPIO_MODE_AF_PP, UART_AF_NUM[port]);
}

void InitSerial(uint8_t UartIndex, COMPORT* ComPort, uint8_t* RxBuffer, uint8_t* TxBuffer)
{
	UartIndex -= 1; //0: UART1, 1: UART2 ......
	//Initialize Secs serial's buffers
	ComPort->UartHandler = uart[UartIndex]; //USART2;
	ComPort->ComType                = COMTYPE_AUX; //primary control port for PC and REPETREL comm
	ComPort->RxBuffer.buffer     	= RxBuffer;
	ComPort->RxBuffer.BufferStart   = &RxBuffer[0];
	ComPort->RxBuffer.BufferEnd     = &RxBuffer[0] + SERIAL_BUFFER_SIZE - 1; //end of the que
	ComPort->RxBuffer.Head          = &RxBuffer[0]; //start of que
	ComPort->RxBuffer.Tail          = &RxBuffer[0]; //end of the que
	ComPort->RxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	ComPort->RxBuffer.RxLineCount = 0; // if there is a valid command waiting
	ComPort->AcksWaiting            = 0;

	ComPort->AcksWaiting               = 0;

	ComPort->TxBuffer.buffer     	= TxBuffer;
	ComPort->TxBuffer.BufferStart   = &TxBuffer[0];
	ComPort->TxBuffer.BufferEnd     = &TxBuffer[0] + sizeof(SERIAL_BUFFER_SIZE) - 1; //end of the que
	ComPort->TxBuffer.Head		    = &TxBuffer[0]; // index of where to put the next char
	ComPort->TxBuffer.Tail	        = &TxBuffer[0]; // index of where to pull the next char
	ComPort->TxBuffer.CharsInBuf	= 0; // total valid chars in buffer
	
	//Initalize Uart hardware.
	GPIO_InitTypeDef GPIO_InitStruct = { 0 }; /* Init the low level hardware : GPIO, CLOCK */
	UART_HandleTypeDef huart;
	huart.Instance = uart[UartIndex]; //USART2;
	huart.Init.BaudRate = USART2_BAUDRATE; //USART2_BAUDRATE;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (huart.Init.BaudRate > 0)
	{	
		*rcc_uart_en[UartIndex] |= rcc_uart_bit[UartIndex]; // Enable clock  //__HAL_RCC_USART2_CLK_ENABLE(); /* Peripheral clock enable */
		huart.Lock = HAL_UNLOCKED; /* Allocate lock resource and initialize it */
		HAL_UART_Init(&huart);
		UART_GPIO_Init(UartIndex);
		__HAL_UART_ENABLE(&huart);
	}
}

void addStringToBuffer(ComBuffer *targetBuffer, 
	uint8_t* buf, 
	uint16_t size)
{
}

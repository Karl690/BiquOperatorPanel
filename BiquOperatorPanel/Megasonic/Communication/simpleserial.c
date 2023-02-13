#include "serial.h"
#include "simpleserial.h"

COMPORT COMSIMPLE; //Simple Serial Class

uint8_t  RX_SimpleBufferSecs[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Tx_SimpleBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
void Init_SimpleSerial(uint8_t UartIndex)
{
	//Initialize Secs serial's buffers
	InitSerial(UartIndex, &COMSIMPLE, RX_SimpleBufferSecs, Tx_SimpleBufferSecs);
}

void CheckForSimplesTxRx()
{
	uint8_t WorkCharacter;
	//todo, need to put a check in here to see if usb is busy or not.
		//transmit first
	if (COMSIMPLE.UartHandler->SR & USART_SR_TXE)//is transmit buffer empty
	{
		//yes, then lets see if there is a character waiting to send
		if (COMSIMPLE.TxBuffer.CharsInBuf)
		{
			//yes, so send it
			WorkCharacter = *COMSIMPLE.TxBuffer.Tail; //get character
			COMSIMPLE.UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff); //cast for data register
			COMSIMPLE.TxBuffer.CharsInBuf--; //one less character to send			
			COMSIMPLE.TxBuffer.Tail++; //point to next character to send...
			if (COMSIMPLE.TxBuffer.Tail > COMSIMPLE.TxBuffer.BufferEnd)
			{COMSIMPLE.TxBuffer.Tail = COMSIMPLE.TxBuffer.BufferStart; }//reset set the pointer
		}
	}
	//now check for receive
	while (COMSIMPLE.UartHandler->SR & USART_SR_RXNE)
	{
		*COMSIMPLE.RxBuffer.Head = (uint8_t)(COMSIMPLE.UartHandler->DR & 0xff);
		COMSIMPLE.RxBuffer.CharsInBuf++;
		COMSIMPLE.RxBuffer.Head++;
		if (COMSIMPLE.RxBuffer.Head > COMSIMPLE.RxBuffer.BufferEnd)
		{COMSIMPLE.RxBuffer.Head = COMSIMPLE.RxBuffer.BufferStart; }
	}
}

void SendUartSimpleString(char* sendToString)
{
	AddSerialStringToBuffer(&COMSIMPLE.TxBuffer, sendToString);
}
void ParseIncommingLineToSimpleData()
{
}


#include "serial.h"
#include "simpleserial.h"

COMPORT* COMSIMPLE; //Simple Serial Class

void CheckForSimplesTxRx()
{
	uint8_t WorkCharacter;
	//todo, need to put a check in here to see if usb is busy or not.
		//transmit first
	if (COMSIMPLE->UartHandler->SR & USART_SR_TXE)//is transmit buffer empty
	{
		//yes, then lets see if there is a character waiting to send
		if (COMSIMPLE->TxBuffer.Head != COMSIMPLE->TxBuffer.Tail)
		{
			//yes, so send it
			WorkCharacter = COMSIMPLE->TxBuffer.buffer[COMSIMPLE->TxBuffer.Tail]; //get character
			COMSIMPLE->UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff); //cast for data register
			
			COMSIMPLE->TxBuffer.Tail++; //point to next character to send...
			COMSIMPLE->TxBuffer.Tail  &= COMSIMPLE->TxBuffer.Buffer_Size;
		}
	}
	//now check for receive
	while (COMSIMPLE->UartHandler->SR & USART_SR_RXNE)
	{
		COMSIMPLE->RxBuffer.buffer[COMSIMPLE->RxBuffer.Head] = (uint8_t)(COMSIMPLE->UartHandler->DR & 0xff);
		COMSIMPLE->RxBuffer.Head++;
		COMSIMPLE->RxBuffer.Head &= COMSIMPLE->RxBuffer.Buffer_Size;
	}
}

void SendUartSimpleString(char* sendToString)
{
	AddSerialStringToBuffer(&COMSIMPLE->TxBuffer, sendToString);
}
void ParseIncommingLineToSimpleData()
{
}


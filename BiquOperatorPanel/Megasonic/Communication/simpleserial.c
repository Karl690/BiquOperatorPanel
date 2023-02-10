#include "serial.h"
#include "simpleserial.h"

COMPORT COMSIMPLE; //Simple Serial Class

uint8_t  RX_SimpleBufferSecs[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Rx_SimpleUrgentBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
uint8_t  Tx_SimpleBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
void Init_SimpleSerial(uint8_t UartIndex)
{
	//Initialize Secs serial's buffers
	InitSerial(UartIndex, &COMSIMPLE, RX_SimpleBufferSecs, Rx_SimpleUrgentBufferSecs, Tx_SimpleBufferSecs);
}



void CheckForSimplesTxRx()
{
	uint8_t WorkCharacter;
	//todo, need to put a check in here to see if usb is busy or not.
	if (COMSIMPLE.TxBuffer.CharsInBuf > 0 || COMSIMPLE.AcksWaiting)
	{
		//transmit first
		while (COMSIMPLE.UartHandler->SR & USART_SR_TXE)
		{
			if (COMSIMPLE.AcksWaiting)
			{
				COMSIMPLE.UartHandler->DR = (uint32_t) CMD_END_CHAR;
				COM2.AcksWaiting--;
				continue;
			}
			WorkCharacter = *COMSIMPLE.TxBuffer.Tail;
			COMSIMPLE.UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COMSIMPLE.TxBuffer.CharsInBuf--;			
			COMSIMPLE.TxBuffer.Tail++;
			
			if (COMSIMPLE.TxBuffer.Tail > COM2.TxBuffer.BufferEnd)
			{COMSIMPLE.TxBuffer.Tail = COM2.TxBuffer.BufferStart; }
			if (WorkCharacter == CMD_END_CHAR)	break;//pause at a cr
			if (COMSIMPLE.TxBuffer.CharsInBuf == 0) break;
		}
	}
	//now check for receive
	while (COMSIMPLE.UartHandler->SR & USART_SR_RXNE)
	{
		*COMSIMPLE.TxBuffer.Head = (uint8_t)(uint8_t)(COMSIMPLE.UartHandler->DR & 0xff);
		COMSIMPLE.TxBuffer.CharsInBuf++;
		COMSIMPLE.TxBuffer.Head++;
		if (COMSIMPLE.TxBuffer.Head > COMSIMPLE.TxBuffer.BufferEnd)
		{COMSIMPLE.TxBuffer.Head = COMSIMPLE.TxBuffer.BufferStart; }
	}
}
void ParseIncommingLineToSimpleData()
{
}


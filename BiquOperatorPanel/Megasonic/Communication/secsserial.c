#include "serial.h"
#include "secsserial.h"

COMPORT COMSECS; //Secs Serial Class

uint8_t  RX_SecsBufferSecs[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Rx_SecsUrgentBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
uint8_t  Tx_SecsBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
void Init_SecsSerial(uint8_t UartIndex)
{
	//Initialize Secs serial's buffers
	InitSerial(UartIndex, &COMSECS, RX_SecsBufferSecs, Rx_SecsUrgentBufferSecs, Tx_SecsBufferSecs);
}
void ParseIncommingLineToSecsString()
{
}
void SendUartSecsString(char* stringToSend)
{
	addStringToBuffer(&COMSECS.TxBuffer, stringToSend);
}
void CheckForSecsTxRx()
{
	uint8_t WorkCharacter;
	//todo, need to put a check in here to see if usb is busy or not.
	if (COMSECS.TxBuffer.CharsInBuf > 0 || COMSECS.AcksWaiting)
	{
		//transmit first
		while (COMSECS.UartHandler->SR & USART_SR_TXE)
		{
			if (COMSECS.AcksWaiting)
			{
				COMSECS.UartHandler->DR = (uint32_t) CMD_END_CHAR;
				COM2.AcksWaiting--;
				continue;
			}
			WorkCharacter = *COMSECS.TxBuffer.Tail;
			COMSECS.UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff);
			COMSECS.TxBuffer.CharsInBuf--;			
			COMSECS.TxBuffer.Tail++;
			
			if (COMSECS.TxBuffer.Tail > COM2.TxBuffer.BufferEnd)
			{COMSECS.TxBuffer.Tail = COM2.TxBuffer.BufferStart; }
			if (WorkCharacter == CMD_END_CHAR)	break;//pause at a cr
			if (COMSECS.TxBuffer.CharsInBuf == 0) break;
		}
	}
	//now check for receive
	while (COMSECS.UartHandler->SR & USART_SR_RXNE)
	{
		*COMSECS.TxBuffer.Head = (uint8_t)(uint8_t)(COMSECS.UartHandler->DR & 0xff);
		COMSECS.TxBuffer.CharsInBuf++;
		COMSECS.TxBuffer.Head++;
		if (COMSECS.TxBuffer.Head > COMSECS.TxBuffer.BufferEnd)
		{COMSECS.TxBuffer.Head = COMSECS.TxBuffer.BufferStart; }
	}
}
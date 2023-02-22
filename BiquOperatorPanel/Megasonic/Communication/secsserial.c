#include "serial.h"
#include "secsserial.h"

COMPORT COMSECS; //Secs Serial Class

uint8_t  RX_SecsBufferSecs[SERIAL_BUFFER_SIZE] = { 0 }; //serial port receive buffer
uint8_t  Tx_SecsBufferSecs[SERIAL_BUFFER_SIZE] = { 0 };
void Init_SecsSerial(uint8_t UartIndex)
{
	//Initialize Secs serial's buffers
	InitSerial(UartIndex, &COMSECS, RX_SecsBufferSecs, Tx_SecsBufferSecs);
}

void SendUartSecsString(char* stringToSend)
{
	AddSerialStringToBuffer(&COMSECS.TxBuffer, stringToSend);
}
void CheckForSecsTxRx()
{
	uint8_t WorkCharacter;
	//todo, need to put a check in here to see if usb is busy or not.
		//transmit first
	if (COMSECS.UartHandler->SR & USART_SR_TXE)//is transmit buffer empty
	{//yes, then lets see if there is a character waiting to send
		if (COMSECS.TxBuffer.CharsInBuf)
		{//yes, so send it
			WorkCharacter = *COMSECS.TxBuffer.Tail;//get character
			COMSECS.UartHandler->DR = (uint32_t)(WorkCharacter & 0x00ff); //cast for data register
			COMSECS.TxBuffer.CharsInBuf--;//one less character to send			
			COMSECS.TxBuffer.Tail++;//point to next character to send...
			if (COMSECS.TxBuffer.Tail > COMSECS.TxBuffer.BufferEnd)
			{COMSECS.TxBuffer.Tail = COMSECS.TxBuffer.BufferStart; }//reset set the pointer
		}
	}
	//now check for receive
	while (COMSECS.UartHandler->SR & USART_SR_RXNE)
	{
		*COMSECS.RxBuffer.Head = (uint8_t)(COMSECS.UartHandler->DR & 0xff);
		COMSECS.RxBuffer.CharsInBuf++;
		COMSECS.RxBuffer.Head++;
		if (COMSECS.RxBuffer.Head > COMSECS.RxBuffer.BufferEnd)
		{COMSECS.RxBuffer.Head = COMSECS.RxBuffer.BufferStart; }
	}
}


/////////////////////////////////////////////////////////////////////
uint8_t SecsMessageWaiting = 0;
//secs variables

uint16_t secstimer1 = 15;
uint16_t secstimer2 = 15;
uint16_t secstimer3 = 15;
uint16_t secstimer5 = 10;
uint16_t secstimer6 = 20;
uint16_t secstimer7 = 20; //autoconnect in 3 seconds
uint16_t secstimer1default = 50;
uint16_t secstimer2default = 50;
uint16_t secs1bytesleft = 0;
uint16_t secsRecieveQuePointer1 = 0;
uint16_t secsRecieveQuePointer2 = 0;
uint8_t secs1_flag = 0;

uint16_t SecsSendQuePointer1 = 0;
uint16_t SecsSendQuePointer2 = 0;
uint8_t SecsSendQue[8][1000] = {0};
uint8_t secs1receivebuffer[300] = {0};
uint8_t secs_transmit_buffer[300] = {0};

uint16_t CHECKSUMCALCULATED = 0;
uint16_t secsmessagelength = 0;
uint16_t checksum_passed = 0;
uint16_t numberofretriesleft = 0;
uint16_t defaultnumberofretriesleft = 5;
uint16_t secssendfail = 0;
uint16_t secssendpass = 0;
uint16_t systembytes = 0;
uint16_t systembyte34 = 0;
uint16_t receiveid = 0;
uint16_t my_device_id = 1;
uint8_t SecsRetrys_ReloadValue = 3; //in c# project it is on 50ms timer
uint8_t Secs1Timer1_ReLoadValue = 3;
uint8_t Secs1Timer2_ReLoadValue = 3;

uint8_t ReceivedSecsMessageUpdateReadyFlag = 0;
uint16_t SentSecsMessageUpdateReadyFlag = 0;
uint16_t LastCharacterRecieved = 0;
uint16_t LastCharacterRead = 0;

uint8_t Receivebuffer[4096] = {0};

uint32_t SecsReceivedMessageTotalErrorNum = 0;
uint32_t SecsReceivedMessageTimeoutErrorNum = 0;
uint32_t SecsReceivedMessageCheckSumErrorNum = 0;
uint32_t SecsReceivedMessageParsingErrorNum = 0;
uint32_t secs1receivepointer = 0;
uint32_t secs1charactersreceived = 0;
uint32_t checksumfailed = 0;
uint32_t CheckedSumReceived = 0;
uint32_t SecsSendMessageTimeoutErrorNum = 0;
uint32_t SecsSendMessageTotalErrorNum = 0;
uint8_t ParseSecsMessage(uint8_t* secsbuffer)
{
	
}
void parse_send_message()
{
	if (ParseSecsMessage(secs_transmit_buffer))
	{
		SentSecsMessageUpdateReadyFlag = 1;
	}
}
void TestForSecsMessageReadyToSend()
{
	//this was modified to only work with secs1, secshsms is implemented by the secs4net library

	if (secs1_flag > 0) return;//cant start something new if we are not finished with the last one

	if (SecsSendQuePointer1 == SecsSendQuePointer2) return;//dont send anything if nothing is waiting to go
	uint16_t lengthOfMessage = SecsSendQue[SecsSendQuePointer2][0];
	uint16_t  messageType = SecsSendQue[SecsSendQuePointer2][1];
//	byte[] tempByteArray = new byte[lengthOfMessage];
//	if ((lengthOfMessage > 0) & (lengthOfMessage < 256))
//	{
//		for (int count = 0; count < lengthOfMessage; count++)
//		{
//			tempByteArray[count] = SecsSendQue[SecsSendQuePointer2, count + 2];
//		}
//	}
//	
//	//ok now we can send the data out
//	//this is the serial transmit message and it requires a different type of checking
//	//basically it is so slow that we could overwrite one of the messages
//
//	Array.Copy(tempByteArray, secs_transmit_buffer, tempByteArray.Length); //transfer the message
	memcpy(secs_transmit_buffer, &SecsSendQue[SecsSendQuePointer2][2], lengthOfMessage);
	
	SecsSendQuePointer2++; //move pointer to next que in the array for the next message
	SecsSendQuePointer2 &= 7; //only 8 entrys before spinning in the circular que
	
	parse_send_message(); //document the message that is being sent stream, funct, etc.          
	numberofretriesleft = SecsRetrys_ReloadValue; // defaultnumberofretriesleft;//set the number of retries
	secs1_flag = 10;

	secstimer1 = Secs1Timer1_ReLoadValue * 20; // secstimer1default;//set the character timeout timer
   // if (!checkBoxShowAllHsmsDataOut.Checked) return;
    //logBox1.addDataToListBox(tempByteArray, Color.White);// show in hex if desired
}

uint8_t GetLastChar()
{
	if (COMSECS.RxBuffer.CharsInBuf == 0) return 0;
	uint8_t RawRxChar = *COMSECS.RxBuffer.Tail;
	COMSECS.RxBuffer.Tail++;
	
	if (COMSECS.RxBuffer.Tail > COMSECS.RxBuffer.BufferEnd)
	{COMSECS.RxBuffer.Tail = COMSECS.RxBuffer.BufferStart; }
	COMSECS.RxBuffer.CharsInBuf--;
	
//	if (LastCharacterRecieved == LastCharacterRead) return character;
//	character = Receivebuffer[LastCharacterRead];
//	LastCharacterRead++;
//	LastCharacterRead &= 4095; // lastcharacter2 % 4095;
	return RawRxChar;
}

void secs1_idle()
{
	//check for any charcters waiting, if no then out of here
	//if (LastCharacterRecieved == LastCharacterRead) return;   //if (nextcharacter2 == lastcharacter2) return;
	if (COMSECS.RxBuffer.CharsInBuf == 0) return;
	//we do have a character
	uint8_t temp = GetLastChar();
	//is ita enq, a start secs1 request
	if (temp == ENQ)
	{
		AddSerialCharToBuffer(&COMSECS.TxBuffer, EOT); //sendToSecsSerialPort(EOT);
		secs1_flag = 1;
		secstimer2 = Secs1Timer2_ReLoadValue * 20; // secstimer2default;//set the reply timeout timer 
	}
}

/// <summary>
/// this state will check timer2 and if it goes to zero will cancel
/// this atemp at secs
/// otherwise it will try to read a character which should represent
/// the actual length of the message to be received.
/// </summary>
void waiting_for_length()
{
	if (secstimer2 == 0)
	{
		secs1_flag = 0; //reset the attemp flag if not good

		AddSerialCharToBuffer(&COMSECS.TxBuffer, NAK);//sendToSecsSerialPort(Nak);
		
		SecsReceivedMessageTotalErrorNum++;
		SecsReceivedMessageTimeoutErrorNum++;
		//reportError("Waiting for Length byte TimeOut");
		return;         //if you found timer2 is zero we have failed
	}
	if (COMSECS.RxBuffer.CharsInBuf == 0) return; //if (LastCharacterRecieved == LastCharacterRead) return;//check to see if any characers have been received
	uint8_t temp2 = GetLastChar();
	secs1receivebuffer[0] = temp2; //store the length for future use
	secs1bytesleft = temp2; //number of bytes in string
	secs1bytesleft += 2; //add 2 bytes for the checsum
	secs1receivepointer = 1; //set the pointer to second position because we already put the length byte i [0]
	secstimer1 = Secs1Timer1_ReLoadValue * 20; // secstimer1default;//set the character timeout timer
	secs1charactersreceived = 1; //set the number of characters recievd to 1
	secs1_flag = 2; //point to next state
}

uint8_t checksumreceivecheck()
{
	int messagelength = secs1receivebuffer[0];
	secsmessagelength = messagelength;

	uint16_t checksum = 0;
	for (int a = 1; a < messagelength + 1; a++)
	{
		checksum += secs1receivebuffer[a]; //add up the next character
	}
	int rcvdchecksum = (secs1receivebuffer[messagelength + 2]);
	rcvdchecksum += ((secs1receivebuffer[messagelength + 1]) * 256);
	CheckedSumReceived = rcvdchecksum;

	CHECKSUMCALCULATED = checksum; //update the global variables for diag
	
	//UpdateSecsData?.Invoke(); // Update CheckSUM, checkSum falied, passed data.
	ReceivedSecsMessageUpdateReadyFlag = 1;
	return checksum == rcvdchecksum;
}

void read_me_a_character()
{
	if (secstimer1 == 0)
	{
		secs1_flag = 0; //reset the attemp flag if not good
		AddSerialCharToBuffer(&COMSECS.TxBuffer, NAK);// sendToSecsSerialPort(Nak);
		//serialPort.Write(((char)NAK).ToString());//send the you failed sucker message 
		SecsReceivedMessageTotalErrorNum++;
		SecsReceivedMessageTimeoutErrorNum++;
		//reportError("TimeOut waiting for characters in message");
		return;         //if you found timer2 is zero we have failed
	}

	//read all available characters please,until we have recived them all, according to the length byte that was already received
	while (secs1bytesleft != 0)
	{
		//if (LastCharacterRecieved == LastCharacterRead) return;  // if (nextcharacter2 == lastcharacter2) 
		if(COMSECS.RxBuffer.CharsInBuf == 0) return; //if no character yet, bye
		uint8_t temp = GetLastChar(); //get me a character
		secs1receivebuffer[secs1receivepointer] = temp; //store the character
		secs1receivepointer++; // point to next character buffer location
		secs1charactersreceived++; //keep track of the total number of char rcvd
		secs1bytesleft--; // number of characters left to receive
		//need to add error checking for more than 255 characters
	}

	//if you get here then we have received the whole enchilada
	//including the checksum bytes so now we can do the checking
	if (!checksumreceivecheck())// not true we bombed out so cancel
	{
		checksumfailed++;
		secs1_flag = 0; //reset the attemp flag if not good
		//temp = nak;
		AddSerialCharToBuffer(&COMSECS.TxBuffer, NAK);
		//serialPort.Write(((char)NAK).ToString());//send the you failed sucker message  
		SecsReceivedMessageTotalErrorNum++;
		SecsReceivedMessageCheckSumErrorNum++;
		//reportError("Rcv Cksum Err");
		//textBox48.Text = checksumfailed.ToString();
		return;         //if you found timer2 is zero we have failed

	}//error make appropriate replys

	//if you get here we have succesfully received a fully checksum
	//validated mesage packet of the right length. yeaaah.
	//checksum_passed++;
            
	secs1_flag = 3; //set the flag to the next value
	checksum_passed++; //let the secs2 processor know  we have secs
	AddSerialCharToBuffer(&COMSECS.TxBuffer, ACK); //sendToSecsSerialPort(Ack);
	//serialPort.Write(((char)ACK).ToString());//send the you passed ok                           
	return;

}


void have_secs_message()
{
	secs1_flag = 0; //turn off the secs flag,go back to idle
	//parse_rcvd_message();
	if (secs1receivebuffer[0] < 10) return;//to short, not a real message
            
	if (ParseSecsMessage(secs1receivebuffer)) 
		SecsMessageWaiting = 1;
	else
	{
		SecsReceivedMessageTotalErrorNum++;
		SecsReceivedMessageParsingErrorNum++;
		//reportError("Secs message Parsing error.");
		return;
	}            
	//SecsRcvGuiDirty = 1; //update the gui
}

void initiate_block_transmit()
{
	AddSerialCharToBuffer(&COMSECS.TxBuffer, ENQ);//sendToSecsSerialPort(Enq);
	//serialPort.Write(((char)ENQ).ToString());//start the block xfer with "are you ready"  
	secstimer2 = Secs1Timer2_ReLoadValue * 20; //  secstimer2default;//set the reply timeout timer 
	secs1_flag = 11; //point to the next state for the secs1 processor
	return;         //
}

/// <summary>
        /// in this state we are waiting for the eot from the guy we are trying to 
        /// talk to, if the timer2 times out we retry again, but only so many times
        /// 
        /// </summary>
void waiting_for_eot()
{
	if (secstimer2 == 0)
	{
		if (numberofretriesleft < 1)
		{
			//add failure code hereurnn 
			secs1_flag = 0; //turn off the secs flag
			secssendfail++;
			//AppendLog ? .Invoke(LOGTYPE.ERROR, LOGSESSION.SECS1, DIRECTION.NONE, "SECSII Send TIMEOUT");
			//logBox1.scrollToBottom();
			return;
		}
		numberofretriesleft--; //count down and restart the process again

		secs1_flag = 10;
		return;
	}
	//if (LastCharacterRecieved == LastCharacterRead) return;   //if (nextcharacter2 == lastcharacter2) return;
	if (COMSECS.RxBuffer.CharsInBuf == 0) return; 
	uint8_t temp2 = GetLastChar();
	if (temp2 != EOT) return; //it must be a eot otherwise bye bye
	//ok now you are here it is time to send that actual stream and function
	int number_of_characters_to_send = secs_transmit_buffer[0];
	//now we have the message length; but do we have the overall length
	number_of_characters_to_send = number_of_characters_to_send + 3;
	//now we have included the length byte and the 2 checsum bytes

	//if (serialPort == null) return;//wait unil this com port is real
	//if (!serialPort.IsOpen) return;//add error reporting soon
	
	AddSerialBufferToBuffer(&COMSECS.TxBuffer, secs_transmit_buffer, number_of_characters_to_send);
	
	////string s = ""; //secs_transmit_buffer.ToString();
	//int length = secs_transmit_buffer[0];//get the number of characters to send
	//length += 3; //add length byte and checksum please

	////note must send data in byte format, if you convert to char
	////all values greater than 128 are converted to 3fhex
	////lvanankarl
	//string secsMessageToSend = System.Text.Encoding.UTF8.GetString(secs_transmit_buffer, 0, length);//convert to string for easy sending to serial port
	////serialPort.Write(secs_transmit_buffer, 0, length);
	//sendToSecsSerialPort(secsMessageToSend);
	secs1_flag = 12; // signal the wait for acknowledgement
}
void waiting_for_ack()
{
	if (secstimer2 == 0)
	{
		if (numberofretriesleft < 1)
		{
			//add failure code hereurnn 
			secs1_flag = 0; //turn off the secs flag
			secssendfail++;
			//SecsSendGuiDirty = true;
			return;
		}
		numberofretriesleft--; //count down and restart the process again
		secs1_flag = 10;
		return;
	}
	if (COMSECS.RxBuffer.CharsInBuf == 0) return; //if (LastCharacterRecieved == LastCharacterRead) return;   //if (nextcharacter2 == lastcharacter2) return;
	uint8_t temp2 = GetLastChar(); //            byte temp2 = getchar2();
	if (temp2 == ACK)
	{
		secssendpass++;
		secs1_flag = 0; //don't forget to turn off the secs flag please
		return; //it must be a eot otherwise bye bye
	}

	if (numberofretriesleft < 1)
	{
		//add failure code hereurnn 
		secs1_flag = 0; //turn off the secs flag
		secssendfail++;
		SecsSendMessageTimeoutErrorNum++;
		SecsSendMessageTotalErrorNum++;
		//reportError("SECSII Send TimeOut");
		return;
	}
	numberofretriesleft--; //count down and restart the process again
	secs1_flag = 10;
	return;
}
void ParseIncommingLineToSecsString()
{
	
	TestForSecsMessageReadyToSend(); //see if we should be sending any messages
	if (SecsMessageWaiting)
	{
		//ProcessReceivedMessage ? .Invoke(); //  PrcessSecsReceivedMessage();
		SecsMessageWaiting = 0;
	}
	if (secstimer1 > 0) secstimer1--;
	if (secstimer2 > 0) secstimer2--;

	switch (secs1_flag)
	{
	case 0: secs1_idle(); return;
	case 1: waiting_for_length(); return;
	case 2: read_me_a_character(); return;
	case 3: have_secs_message(); return;
	case 10: initiate_block_transmit(); return;
	case 11: waiting_for_eot(); return;
	case 12: waiting_for_ack(); return;
	default: secs1_flag = 0; return;
	}
}
uint16_t SecsTimerPrescaler = 5;
void SecsTimers(void)
{
	//decrements the secs timers every 50ms
	if (SecsTimerPrescaler)
	{
		SecsTimerPrescaler--;
		return;//not time to count down yet
	}
	SecsTimerPrescaler = 5;
	if (secstimer1) secstimer1--;
	if (secstimer2) secstimer2--;
	if (secstimer3) secstimer3--;
	if (secstimer5) secstimer5--;
	if (secstimer6) secstimer6--;
	if (secstimer7) secstimer7--;
}
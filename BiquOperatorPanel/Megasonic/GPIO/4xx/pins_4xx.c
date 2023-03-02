#include "configure.h"

#if defined(FK_407) || defined(BIQU_407) || defined(CORE_407I)
#include "pins_4xx.h"
uint16_t Home_X_Status=0;//setup the home status bits
uint16_t Home_Y_Status=0;//setup the home status bits
uint16_t Home_Z_Status=0;//setup the home status bits
uint16_t Home_A_Status=0;//setup the home status bits
uint16_t Home_B_Status=0;//setup the home status bits
uint16_t Home_C_Status=0;//setup the home status bits

uint16_t UserKey1_Status=1;
uint16_t UserKey2_Status=1;

GPIO_TypeDef *pinExtractPortPtr(pinType pin)
{   // return address pointer to this pin's port
	if (pin != PIN_UNDEFINED)
	{
		switch (pinExtractPortNum(pin))
		{
		case GPIO_PortSourceGPIOA : return(GPIOA);
		case GPIO_PortSourceGPIOB : return(GPIOB);
		case GPIO_PortSourceGPIOC : return(GPIOC);
		case GPIO_PortSourceGPIOD : return(GPIOD);
		case GPIO_PortSourceGPIOE : return(GPIOE);
		case GPIO_PortSourceGPIOF : return(GPIOF);
		case GPIO_PortSourceGPIOG : return(GPIOG);
		case GPIO_PortSourceGPIOH : return(GPIOH);
		case GPIO_PortSourceGPIOI : return(GPIOI);
		}
	}
	else
	{
		return(0);
	}
}


void GPIO_Config(GPIO_TypeDef* GPIOx, GPIOInitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  /* -------------------------Configure the port pins---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
	uint32_t temp = 0x00;
	uint32_t temp_2 = 0x00;

  /* Check the parameters */

	temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
	GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
	temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
	GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
}
void pinInit(pinType pin)
{   if (pin != PIN_UNDEFINED)
{   // skip if not a valid pin

	if (pinExtractMode(pin) == GPIO_Mode_AF)
	{   // if the pin is set for using an Alternate Function then complete
		// then complete the initialization for that pin by setting the requested
		// alternated function -- WARNING: this needs to be set BEFORE putting the I/O
		// pin in AF Mode, otherwise will have undetermined behavior

		// Warning: GPIO_PinAFConfig uses the BinNum and not BitPos like the other GPIO routines

		GPIO_PinAFConfig(pinExtractPortPtr(pin), pinExtractPinNum(pin), pinExtractAF(pin));
	}
	else
	{
		GPIO_PinAFConfig(pinExtractPortPtr(pin), pinExtractPinNum(pin), 0);
	}

	GPIOInitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = pinExtractPinMask(pin);
	GPIO_InitStructure.GPIO_Mode  = pinExtractMode(pin);
	GPIO_InitStructure.GPIO_Speed = pinExtractSpeed(pin);
	GPIO_InitStructure.GPIO_OType = pinExtractOType(pin);
	GPIO_InitStructure.GPIO_PuPd  = pinExtractPupd(pin);

	GPIO_Config(pinExtractPortPtr(pin), &GPIO_InitStructure);

	if (pinExtractInitEn(pin))
	{   // initialize pin
		pinWrite(pin, pinExtractInitVal(pin));
	}
}
}

////////////////////////////////////////////////////////////////////////////////

void pinClear(pinType pin)
{   // writing "1" to any bit in the UPPER 16 bits of the BSSR reg (BSSR[31:16]
	// will force the corresponding bit(s) on that port to be set to 0

	if (pin != PIN_UNDEFINED)
	{
		pinExtractPortPtr(pin)->BSRR = pinExtractPinMask(pin)<<16;


	}
}

////////////////////////////////////////////////////////////////////////////////

void pinSet(pinType pin)
{   // writing "1" to any bit in the LOWER 16 bits of the BSSR (ie, BSSR[15:0]
	// will force the corresponding bit(s) on that port to be set to 1

	if (pin != PIN_UNDEFINED)
	{
		pinExtractPortPtr(pin)->BSRR = pinExtractPinMask(pin);
	}
}

////////////////////////////////////////////////////////////////////////////////

void pinWrite(pinType pin, uint32_t value)
{   // use clear or set to force the output to the desired value
	// NO CHECKING is performed to make sure this is requested on an OUTPUT

	if (pin == PIN_UNDEFINED) return;

	if (value == 0)
		pinClear(pin);
	else
		pinSet(pin);
}

////////////////////////////////////////////////////////////////////////////////

uint32_t pinRead(pinType pin)
{   // grab the IDR for the port belong to the pin and shift results down to move
	// the desired bit position to the LBS and AND with 0x1 to make sure only
	// the value from the requested bit is return (returns a 0 or 1)

	if (pin == PIN_UNDEFINED) return(0);

	return((uint32_t)(pinExtractPortPtr(pin)->IDR >> pinExtractPinNum(pin)) & 0x1);

}

////////////////////////////////////////////////////////////////////////////////

uint32_t pinReadOutput(pinType pin)
{   // grab the IDR for the port belong to the pin and shift results down to move
	// the desired bit position to the LBS and AND with 0x1 to make sure only
	// the value from the requested bit is return (returns a 0 or 1)

	if (pin == PIN_UNDEFINED) return(0);

	return((uint32_t)(pinExtractPortPtr(pin)->ODR >> pinExtractPinNum(pin)) & 0x1);
}

////////////////////////////////////////////////////////////////////////////////

void pinToggleOutput(pinType pin)
{   // really used for driving the LA for debug....flip the output state of an output pin

	if (pin == PIN_UNDEFINED) return;

	pinWrite(pin, (~pinReadOutput(pin)) & 0x1);
}


////////////////////////////////////////////////////////////////////////////////
#endif

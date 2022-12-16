 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Mahmoud Elasmar
 *
 *******************************************************************************/
 
#include "twi.h"

#include "common_macros.h"
#include <avr/io.h>


void TWI_init(uint8 configurations)
{

#if(F_CPUU==8000000)
	if (configurations==BAUD_400Kb)
	{
		TWBR=0x02;
		TWSR=0x00;
	}
	else if(configurations==BAUD_100Kb)
	{
		TWBR=32;
		TWSR=0;
	}

#elif(F_CPUU==4000000)

	else if(configurations==BAUD_100Kb)
		{
			TWBR=12;
			TWSR=0;
		}


#endif
	
    TWAR = 0b00000010; // my address = 0x01 :)

    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
	 /*
		 * Clear the TWINT flag before sending the start bit TWINT=1
		 * send the start bit by TWSTA=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	    while(BIT_IS_CLEAR(TWCR,TWINT));

}

void TWI_stop(void)
{

	 TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

}

void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
    TWDR = data;
	    /*
		 * Clear the TWINT flag before sending the data TWINT=1
		 * Enable TWI Module TWEN=1
		 */
	    TWCR = (1 << TWINT) | (1 << TWEN);
	    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;

}

uint8 TWI_readByteWithNACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;

}

uint8 TWI_getStatus(void)
{

    uint8 status;
    status = TWSR & 0xF8;/*getting last 5 bits*/
    return status;
}

/*
 * UART.c
 *
 *  Created on: Apr 29, 2019
 *      Author: Kareem
 */
#include "UART.h"

void UART_init(const UART_ConfigType *Config_Ptr){

	/*
	 * U2X: Double Transmission Speed (baud rate divider from 16 to 8)
	 * RXEN: Receiver Enable
	 * TXEN: Transmitter Enable
	 * URSEL: Register Select bit - must be set to one to use "UCSRC"
	 */
	UCSRA = (1<<U2X);
	UCSRA = (1<<URSEL);
	UCSRB = (1<<RXEN) | (1<<TXEN);

	UCSRC = (UCSRC & 0xBF) | ((Config_Ptr -> modeSelect) << 6); //ASYNC or SYNC
	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr -> parityMode) << 4);
	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr -> stopBit) << 3);

	//Split on two registers
	UCSRC = (UCSRC & 0xF9) | (((Config_Ptr -> charSize) & 0x03) << 1); //Data size
	UCSRB = (UCSRB & 0xFB) | (((Config_Ptr -> charSize) & 0x04));

	//Only used for Synchronous mode, for Asynchronous mode write this bit to zero (choose RISING_XCK_EDGE)
	UCSRC = (UCSRC & 0xFE) | (Config_Ptr -> clockPolarity);

	//Register select bit - cleared to use UBRRH
	//UCSRA &= (~(1<<URSEL));

	//Baud Rate Registers - Split on two registers
	UBRRL = BAUD_RATE_REG;
	UBRRH = BAUD_RATE_REG>>8;

	//TDX Output (PD1)
	DDRD |= (1 << 1);

	//RXD Input (PD0)
	DDRD &= (~(1 << 0));

}
void UART_sendByte(uint8 byte){

	UDR = byte;

	while(BIT_IS_CLEAR(UCSRA, TXC));

	SET_BIT(UCSRA, TXC);
}
uint8 UART_receiveByte(void){

	while(BIT_IS_CLEAR(UCSRA, RXC));

	return UDR;
}
void UART_sendString(const uint8 *string){

	while(*string != '\0')
	{
		UART_sendByte(*string);
		string++;
	}
}
void UART_receiveString(uint8 *string){

	*string = UART_receiveByte();

	while(*string != '#')
	{
		string++;
		*string = UART_receiveByte();
	}
	*string = '\0';
}


/*
 * UART.h
 *
 *  Created on: Apr 29, 2019
 *      Author: Kareem
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define BAUD 9600
#define BAUD_RATE_REG ( ( (F_CPU) / ( (8UL) * (BAUD)) ) - 1)
#define NINE_BIT 9 // Used for UART_Char_Size because there were reserved bits

// Mode Select
typedef enum{
	ASYNC,SYNC
}UART_Mode_Select;

// Parity Mode
typedef enum{
	DISABLED,RESERVED,EN_EVEN,EN_ODD
}UART_Parity_Mode;

// Stop Bit Select
typedef enum{
	ONE_BIT,TWO_BIT
}UART_Stop_Bit;

// Character Size
typedef enum{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT
}UART_Char_Size;

/*
 * Clock Polarity for synchronous mode only
 * When asynchronous mode is used choose Rising XCK Edge
 */
typedef enum{
	RISING_XCK_EDGE,FALLING_XCK_EDGE
}Clock_Polarity;

typedef struct{

	UART_Mode_Select modeSelect;
	UART_Parity_Mode parityMode;
	UART_Stop_Bit stopBit;
	UART_Char_Size charSize;
	Clock_Polarity clockPolarity;

}UART_ConfigType;

/***********************
 * Function Prototypes *
 ***********************/

void UART_init(const UART_ConfigType *Config_Ptr);
void UART_sendByte(uint8 byte);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *string);
void UART_receiveString(uint8 *string);

#endif /* UART_H_ */

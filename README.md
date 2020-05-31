# USART-Serial-Communication-Software-Driver
AVR Atmega32 Microcontrollers

Example Initialization Code:-
________________________________

#include "UART.h"

int main(){

	/*
		 * USART Configurations { Mode_Select:  ASYNC or SYNC
		 *
		 * 			  Parity_Mode:  Disabled
		 * 				        EN_EVEN -> Enabled and Even Mode
		 * 				        EN_ODD  -> Enabled and Odd Mode
		 *
		 * 			    Stop_Bit:   ONE_BIT or TWO_BIT
		 *
		 * 			   Char_Size:   FIVE_BIT
		 * 			                SIX_BIT
		 * 				        SEVEN_BIT
		 *             			        EIGHT_BIT
		 * 	       			        NINE_BIT
		 *
		 * 		      Clock_Polarity:   RISING_XCK_EDGE
		 * 					FALLING_XCK_EDGE }
		 */

	// Example Initialization (Pointer to Configuration Structure) 
	UART_ConfigType Config_Ptr = {ASYNC, DISABLED, ONE_BIT, EIGHT_BIT, RISING_XCK_EDGE};
	
	// Initialization Function
	UART_init(&Config_Ptr);
  
}

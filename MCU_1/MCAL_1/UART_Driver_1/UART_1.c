/*
 * UART_1.c
 *
 * Created: 10/1/2022 4:50:02 PM
 *  Author: 3zz
 */ 

#include "UART_1.h"

void UART_init()
{
	// Set baud rate
	UART_set_BAUD(BAUD_rate);
	
	// Enable receiver and transmitter
	set_pin(UCSRB,RXEN);
	set_pin(UCSRB,TXEN);
	
	// Set frame format
	UART_set_frame(Data_bits,Stop_bits);
}
void UART_set_BAUD(uint16_t baud)
{
	UBRRH = (uint8_t)(baud >> 8); // Higher nibble 
	UBRRL = (uint8_t)baud; // lower nibble 
}
void UART_set_frame(uint8_t bitnum, uint8_t stopbits)
{
	switch(bitnum)
	{
		// 5 bits character size
		case 5:
			clr_pin(UCSRC,UCSZ0);
			clr_pin(UCSRC,UCSZ1);
			clr_pin(UCSRB,UCSZ2);
		break;
		// 6 bits character size
		case 6:
			set_pin(UCSRC,UCSZ0);
			clr_pin(UCSRC,UCSZ1);
			clr_pin(UCSRB,UCSZ2);
		break;
		// 7 bits character size
		case 7:
			clr_pin(UCSRC,UCSZ0);
			set_pin(UCSRC,UCSZ1);
			clr_pin(UCSRB,UCSZ2);
		break;
		// 8 bits character size
		case 8:
			set_pin(UCSRC,UCSZ0);
			set_pin(UCSRC,UCSZ1);
			clr_pin(UCSRB,UCSZ2);
		break;
		// 9 bits character size
		case 9:
			set_pin(UCSRC,UCSZ0);
			set_pin(UCSRC,UCSZ1);
			set_pin(UCSRB,UCSZ2);
		break;
		
		default:
		{
			// error handling
		}
	}
	switch(stopbits)
	{
		// 1 stop bit
		case 1:
			clr_pin(UCSRC,USBS);
		break;
		// 2 stop bit
		case 2:
			set_pin(UCSRC,USBS);
		break;
		
		default:
		{
			// error handling
		}
	}
}

void UART_transmit(uint8_t data)
{
	// Wait for empty transmit buffer
	while ( !( UCSRA & (1 << UDRE)) );
	
	// Put data into buffer, sends the data
	UDR = data;
}

void UART_transmitString(uint8_t *string_data)
{
	for(uint8_t cnt=0; *(string_data + cnt) != '\0'; cnt++)
		UART_transmit(*(string_data + cnt));
	UART_transmit('\0');
}

uint8_t UART_receive()
{
	// Wait for data to be received 
	while ( !( UCSRA & (1 << RXC)) );
	
	// Get and return received data from buffer 
	return UDR;
}
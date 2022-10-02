/*
 * MCU_2.c
 *
 * Created: 10/1/2022 8:30:37 AM
 * Author : mosta
 */ 

#include "MCAL_2/UART_2/UART_2.h"
#include "MCAL_2/DIO_2/DIO_2.h"
uint16_t data =0;


int main(void)
{
	DIO_init(PORT_A, 0, OUT);
	UART_init();
    
    while (1) 
    {
		UART_recieve();
		if(data == 0){
			DIO_write(PORT_A, 0, LOW);
		}else if(data ==1){
			DIO_write(PORT_A, 0, HIGH);
		}
		
    }
}


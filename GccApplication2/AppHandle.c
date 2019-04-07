/*
 * AppHandle.c
 *
 * Created: 3/25/2019 12:46:12 PM
 *  Author: msedl
 */ 

#include <avr/io.h>
#include <util/delay.h>



void GPIO_Setup(void)
{
	/*For button*/
	DDRD=0x00; 
	PORTD = 0xFF; 
	/*----*/
}
/*Checks if button is pressed - needs revision */
uint8_t Check_Pressed(void)
{
	uint8_t pom;
	
	pom=(1<<7)&(PIND);
	serial_poll_send(&pom, 1);
	if(pom==0x00)
	return 1;
	return 0;
}
/*DDRB = 0xFF;
	PORTB = 0x00;
	_delay_ms(1000);
	send[0]=255;
	serial_poll_send(send,1);
	send[0]=50;
	serial_poll_send(send,1);
	_delay_ms(10000);
	send[0]=255;
	serial_poll_send(send,1);
	send[0]=60;
	serial_poll_send(send,1);*/
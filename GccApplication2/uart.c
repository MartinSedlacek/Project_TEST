/*
 * uart.c
 *
 * Created: 2/26/2019 9:05:17 PM
 *  Author: msedl
 */ 



#include <avr/power.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <util/delay.h>
#include <main.h>

/*Serial config for ATMEGA328P refer to data sheet for more info*/
/*Interrupt enable included*/

 Buffer rx_buffer;

volatile uint8_t Pismeno[BUFFER_SIZE];
void serial_init() {

	power_usart0_enable();

	// configure ports double mode
	UCSR0A = 1<<U2X0;

	// configure the ports speed
	UBRR0 = (F_CPU / 4 / BAUD - 1) / 2;

	
	// asynchronous, 8N1 mode
	UCSR0C |= UCSZ01|UCSZ00;   

	// rx/tx enable
	
	UCSR0B |= 1<<(RXEN0);
	UCSR0B |= 1<<(TXEN0);
	
	UCSR0B |= 1<<(RXCIE0); //interrupt
}
/*polling uart receive data with wait for end of operation*/

unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size) {
	unsigned int cnt = a_size;

	while (a_size) {
		/* Wait for data to be received */
		while ( !(UCSR0A & (1<<RXC0)) );

		/* Get and return received data from buffer */
		*a_data = UDR0;
		a_data++;
		a_size--;
	}
	return cnt;
}

/*polling uart transfer data with wait for end of operation*/

unsigned int serial_poll_send(unsigned char *data, unsigned int a_size) {
	unsigned int i = 0x00;
	while (i < a_size) {
		// wait until usart buffer is empty
		while (!(UCSR0A & 1<<UDRE0));

		// send the data
		UDR0 = data[i++];
	}
	return i;
}
	
/*Debugging templates*/
	
unsigned int serial_poll_WaittingData() {
		unsigned int i = 0x00;
		unsigned char data[]={'W','a','i','t','i','n','g',' ','f','o','r',' ','d','a','t','a','\n'};
		int  a_size;
		a_size=strlen((char *)data)-1;
		while (i < a_size) {
			// wait until usart buffer is empty
			while (!(UCSR0A & 1<<UDRE0));

			// send the data
			UDR0 = data[i++];
		}

	return i;
}


void serial_poll_sendC(void){
	char c=0x01;
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
}

/*Simple buffer for 5 bytes + 1 extra for control*/

enum BufferStatus bufferWriteSimple( Buffer *buffer, uint8_t byte){
	uint8_t next_index=(buffer->newest_index)+1;
	buffer->data[buffer->newest_index] = byte;
	Pismeno[buffer->newest_index]=byte;
	if (next_index==BUFFER_SIZE){
		return BUFFER_FULL;
	}
	buffer->newest_index=next_index;
	return BUFFER_OK;
	}
enum BufferStatus bufferReadSimple( Buffer *buffer, uint8_t* data){
		if (buffer->newest_index == 0){
			return BUFFER_EMPTY;
		}
		*data=buffer->data[buffer->oldest_index];
		buffer->oldest_index=(buffer->oldest_index)+1;
		return BUFFER_OK;
	}

/*Solution for circular buffer*/ 
/*For our project simple buffer will be enough*/

enum BufferStatus bufferWrite( Buffer *buffer, uint8_t byte){
	uint8_t next_index = (((buffer->newest_index)+1) % BUFFER_SIZE);
	
	if (next_index == buffer->oldest_index){
		return BUFFER_FULL;
	}
	buffer->data[buffer->newest_index] = byte;
	buffer->newest_index = next_index;
	return (enum BufferStatus) BUFFER_OK;
}

enum BufferStatus bufferRead( Buffer *buffer, uint8_t *byte){
	
	if (buffer->newest_index == buffer->oldest_index){
		return BUFFER_EMPTY;
	}
	
	*byte = buffer->data[buffer->oldest_index];
	buffer->oldest_index = ((buffer->oldest_index+1) % BUFFER_SIZE);
	return (enum BufferStatus) BUFFER_OK;
}



ISR(USART_RX_vect){
	status = bufferWriteSimple(&rx_buffer, UDR0);
	if (status == BUFFER_FULL)
	{
		rx_buffer.newest_index=0;
		rx_buffer.oldest_index=0;
		Write_OLED_Char();
	}
}
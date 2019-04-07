/*
 * uart.h
 *
 * Created: 2/26/2019 9:17:08 PM
 *  Author: msedl
 */ 


#ifndef UART_H_
#define UART_H_



#include <Config.h>
/*Solution for circular buffer*/
/*For our project simple buffer will be enough*/

typedef  struct _Buffer{
	uint8_t data[BUFFER_SIZE];
	uint8_t newest_index;
	uint8_t oldest_index;
}Buffer;

extern Buffer rx_buffer;
volatile extern uint8_t Pismeno[BUFFER_SIZE];

enum BufferStatus{BUFFER_OK,BUFFER_EMPTY,BUFFER_FULL};

enum BufferStatus status;


void serial_init();
unsigned char serial_poll_recv(unsigned char *a_data, unsigned int a_size);
unsigned int serial_poll_send(unsigned char *data, unsigned int a_size);
void serial_poll_sendC(void);
unsigned int serial_poll_WaittingData(void);
enum BufferStatus bufferWriteSimple( Buffer *buffer, uint8_t byte);
enum BufferStatus bufferReadSimple( Buffer *buffer, uint8_t* data);

/*Solution for circular buffer*/
/*For our project simple buffer will be enough*/
enum BufferStatus bufferRead(Buffer *buffer, uint8_t *byte);
enum BufferStatus bufferWrite(Buffer  *buffer, uint8_t byte);



#endif /* UART_H_ */
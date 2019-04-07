/*
 * oled.c
 *
 * Created: 24. 9. 2018 16:48:25
 * Author : PAVOL ? Martin
 */ 

#include <main.h>
unsigned char send[1];
#define DELAY 10
enum AppStatus_
{
	APP_WAIT,
	APP_WRITESCREEN,
	APP_RUNNING,
	APP_REFRESHSCREEN, 
	APP_ERROR,
	};
enum AppStatus_ AppStatus=APP_WAIT;
 
 int main(void)
 {
	
	cli();
	sei();
	//GPIO_Setup();
	serial_init();
	SPI_MasterInit();
	Display_ON();
	clear() ;
	//text();
	while(1) {	
		switch(AppStatus)
		{
			case(APP_WAIT):
			{
				send[0]=255;
				serial_poll_send(send,1);
				send[0]=198;
				serial_poll_send(send,1);
				send[0]=255;
				_delay_ms(DELAY);
				serial_poll_send(send,1);
				send[0]=204;
				serial_poll_send(send,1);
				send[0]=255;
				_delay_ms(DELAY);
				serial_poll_send(send,1);
				send[0]=210;
				serial_poll_send(send,1);
				send[0]=255;
				_delay_ms(DELAY);
				serial_poll_send(send,1);
				send[0]=216;
				serial_poll_send(send,1);
				
				AppStatus=APP_WRITESCREEN;
				/*_delay_ms(100);
				Write_OLED_Char();
				
				send[0]=255;
				serial_poll_send(send,1);
				send[0]=204;
				serial_poll_send(send,1);
				_delay_ms(100);
				Write_OLED_Char();*/
				break;
			}
			case(APP_WRITESCREEN):
			{
				
				AppStatus=APP_RUNNING;
				break;
			}
		case(APP_RUNNING):
		{
			/*measure data to be implemented*/
			/*running time to be implemented*/
			/*clock mode to be implemented*/
			/*battery status to be implemented*/
			/*.....*/
			AppStatus=APP_REFRESHSCREEN;
			break;
		}
		case(APP_REFRESHSCREEN):
		{
			/*uint8_t pom[2];
			pom[0]=0xFF;
			serial_poll_send(pom, 1);
			serial_poll_send(0x00, 1);
			uint8_t i=0;
			while(i<6)
			{
				SPI_MasterTransmit_Data(rx_buffer.data[i+1]);
				i++;
			}*/
			AppStatus=APP_RUNNING;
			break;
		}
	}
 }
 }
 
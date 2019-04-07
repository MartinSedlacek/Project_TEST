/*
 * Config.h
 *
 * Created: 3/25/2019 12:53:19 PM
 *  Author: msedl
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_
/*GENERAL*/
#define F_CPU 16000000UL
/*SPI CONFIG*/
#define SCK DDB5
#define SDIN DDB3
#define CS DDB2
#define DC DDB0
#define RST DDB1
/*UART CONFIG*/

#define BAUD 57600
#define BUFFER_SIZE 6
#endif /* CONFIG_H_ */
/*
 * oled.h
 *
 * Created: 2/26/2019 12:44:26 PM
 *  Author: msedl
 */ 

#include <avr/io.h>
#include <uart.h>
#include <Config.h>
void SPI_MasterInit(void);
void SPI_MasterTransmit_Command(char cCommand);
void SPI_MasterTransmit_Data(char cData);
void Display_ON(void);
void setColumnAddress(uint8_t add);
void setPageAddress(uint8_t add) ;
void clear() ;
void filling();
void display(void); 
void MenuSetup(void);
void text(void);
void batteryStatus(void);
void Write_OLED_Char(void);



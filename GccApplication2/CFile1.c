/*
 * CFile1.c
 *
 * Created: 2/26/2019 10:46:56 PM
 *  Author: msedl
 */ 
/*
 * GccApplication3.c
 *
 * Created: 2/26/2019 10:42:33 PM
 * Author : msedl
 */ 

#include <avr/io.h>

/*******************************************************************
 *                                                                 *
 *     Project: UART_Echo                                          *
 *      Author: Mike McLaren, K8LH                                 *
 *        Date: 28-Apr-16                                          *
 *                                                                 *
 *   Arduino Nano USART Echo Test (9600 baud) tries to avoid       *
 *   using Arduino core function calls.                            *
 *                                                                 *
 *       Board: Arduino Nano                                       *
 *         IDE: Arduino 1.6.8                                      *
 *                                                                 *
 *******************************************************************/
 
 #include <avr/io.h>
 
#define F_CPU 16000000UL          // provided by boards.txt
 
/*******************************************************************
 *  constants & helper macros                                      *
 *******************************************************************/
 
 #define _BAUD    9600                 // baud rate
 #define _UBRR    (F_CPU/16)/_BAUD-1
 
 #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1<<bit))
 #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= 1<<bit)
 
/*******************************************************************
 *  variables                                                      *
 *******************************************************************/
/*******************************************************************
 *  functions                                                      *
 *******************************************************************/
 
 char usart_GetSer(void)            // GetSer (blocking)
 { while(!(UCSR0A & 1<<RXC0));      // wait char available
   return UDR0;                     //
 }                                  //
/*******************************************************************/
 void usart_PutSer(char data)       // PutSer (blocking)
 { while(!(UCSR0A & 1<<UDRE0));     //
     UDR0 = data;                   //
 }                                  //
/*******************************************************************/
 void usart_PutStr(char * data)     // PutStr
 { while(*data!=0)                  //
     usart_PutSer(*data++);         //
 }                                  //
/*******************************************************************/
 void usart_PutNib(char work)       // PutNib (hex nibble to ASCII)
 { work &= 0x0F;                    // lo nibble only
   if(work > 9) work += 7;          // 'A'..'F' values
   usart_PutSer(work + '0');        // put ascii nibble
 }                                  //
/*******************************************************************/
 void usart_PutHex(char value)      // PutHex
 { usart_PutNib(value >> 4);        //
   usart_PutNib(value);             //
 }                                  //
 
/*******************************************************************
 *  main setup                                                     *
 *******************************************************************/
 int trol (void)                    //
 { UBRR0H = (_UBRR) >> 8;           // setup USART port
   UBRR0L = (_UBRR);                //  "
 //UCSR0B |= _BV(TXEN0);            //  "
 //UCSR0B |= _BV(RXEN0);            //  "
 //sbi(UCSR0B, TXEN0);              //  "
 //sbi(UCSR0B, RXEN0);              //  "
   UCSR0B |= 1<<TXEN0 | 1<<RXEN0;   //  "
 
 //usart_PutStr("Hello world ");    // test
 //usart_PutHex(0x3C);              // test
 //usart_PutSer(' ');               // test
 
/*******************************************************************
 *  main loop                                                      *
 *******************************************************************/
   while(1)                         //
   { usart_PutSer(usart_GetSer());  // echo to terminal
   }                                //
 }                                  //
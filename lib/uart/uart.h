/*
 * uart.h
 *
 * Created: 2019-04-29 오후 7:27:16
 *  Author: yeong
 */ 

 #ifndef UART_H_
 #define UART_H_
 
 #include <avr/interrupt.h>
 #include <avr/io.h>
 #include <stdio.h>
 
 void uart0_init(void);
 void uart0_rx_int_init(void);
 int uart0_trasnmit(char data, FILE *stream);
 unsigned char uart0_receive(void);
 void uart0PrintString(char *str);
 void uart0Print1ByteNumber(unsigned char n);
 char uart0_receiveActuator(void);
 
 
 extern FILE OUTPUT;
 extern FILE INPUT;
 
 #endif /* UART_H_ */
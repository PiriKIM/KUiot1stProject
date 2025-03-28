/*
* uart.c
*
* Created: 2019-04-29 오후 7:27:25
*  Author: yeong
*/ 
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

int uart0_trasnmit(char data, FILE *stream);
unsigned char uart0_receive(void);

FILE OUTPUT = FDEV_SETUP_STREAM(uart0_trasnmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, uart0_receive, _FDEV_SETUP_READ);

volatile int flag;
volatile int rxdata;

ISR(USART0_RX_vect) {
	unsigned char tmp = UDR0;
	if(tmp >= '0' && tmp <= '9') {
		if(flag) {
			rxdata = rxdata * 10 + tmp - '0';
		}
		else {
			rxdata = tmp - '0';
			flag = 1;
		}
	}
	else if(tmp == '\r') {
		flag = 0;
	}
}

void uart0_init(void) {
    UCSR0A |= (1 << U2X0);  // 2배속 모드 ON (중요!)
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);  // 송수신 활성화
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8-bit, no parity, 1 stop bit

    UBRR0H = 0;
    UBRR0L = 15;  // ← 115200bps, 16MHz, 2배속 모드 정확한 값!!

    stdin = &INPUT;
    stdout = &OUTPUT;
}

int uart0_trasnmit(char data, FILE *stream) {
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	return 0;
}

unsigned char uart0_receive(void) {
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void uart0_rx_int_init(void) {
	UCSR0B |= (1 << RXCIE0);
	sei();
}

void uart0PrintString(char *str)
{
	for (int i = 0; str[i]; ++i)
    {
		uart0_trasnmit(str[i], NULL);
    }
}

void uart0Print1ByteNumber(unsigned char n)
{
	uint8_t numString[4] = "0";
    int i, index = 0;
    if (n > 0 && n < 1000)
    {
		for (i = 0; n != 0; i++)
        {
			numString[i] = n % 10 + '0';
            n = n / 10;
        }
        numString[i] = '\0';
        index = i - 1;
    }
    for (i = index; i >= 0; i--)
    uart0_trasnmit(numString[i], NULL);
}

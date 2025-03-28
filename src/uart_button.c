// #include "uart.h"
// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <stdio.h>

// // 버튼 누르면 이 값이 바뀜
// volatile uint8_t intData = '0';

// int main()
// {
//     uart0_init();  // UART 초기화
//     stdin = &INPUT;
//     stdout = &OUTPUT;

//     DDRE = 0x02; // RX 입력, TX 출력

//     // 외부 인터럽트 설정 (INT4~INT7 → 스위치 입력용)
//     EICRB = 0xFF;  // 상승 엣지
//     EIMSK = 0xF0;  // INT4~7 허용
//     EIFR = 0xF0;   // 인터럽트 플래그 클리어
//     sei();         // 전역 인터럽트 허용

//     printf(" Hi, I'm ATmega128!\r\n");

//     while (1)
//     {
//         if (intData != '0')
//         {
//             printf("Input Switch : %c\r\n", intData);
//             intData = '0';  // 초기화
//         }
//     }
//     return 0;
// }

// // -------------------- 인터럽트 핸들러 --------------------

// ISR(INT4_vect)
// {
//     cli();
//     intData = '1';
//     sei();
// }

// ISR(INT5_vect)
// {
//     cli();
//     intData = '2';
//     sei();
// }

// ISR(INT6_vect)
// {
//     cli();
//     intData = '3';
//     sei();
// }

// ISR(INT7_vect)
// {
//     cli();
//     intData = '4';
//     sei();
// }

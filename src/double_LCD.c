#include "clcd.h"
#include "dht11.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

int main(void)
{
    uart0_init();
    i2c_lcd_init();
    char str0[16] = "--Servo  Motor--";
    char str1[16] = "pulse:0000";

    i2c_lcd_string(0, 0, str0);
    i2c_lcd_string(1, 0, str1);
    _delay_ms(2000);

    while(1)
    {
        i2c_lcd_string(0, 0, str0);
        i2c_lcd_string(1, 0, str1);
        _delay_ms(2000);
    }

    return 0;
}
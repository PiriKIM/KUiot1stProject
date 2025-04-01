// #include "multiLCD.h"
// #include "dht11.h"
// #include "uart.h"
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdlib.h>

// uint8_t I2C_addr_0 = (0x27 << 1);
// uint8_t I2C_addr_1 = (0x26 << 1);
// uint8_t I2C_addr_2 = (0x23 << 1);

// int main(void)
// {
//     uart0_init();
//     int mod = 0;
//     char str0[16] = "----LED No.0----";
//     char str1[16] = "----LED No.1----";
//     char str2[16] = "----LED No.2----";
//     char str[16] = "I2C_addr_n: xxxx";

//     i2c_mlcd_init(I2C_addr_0);
//     i2c_mlcd_string(0, 0, str0, I2C_addr_0);
//     i2c_mlcd_string(1, 0, str, I2C_addr_0);

//     i2c_mlcd_init(I2C_addr_1);
//     i2c_mlcd_string(0, 0, str1, I2C_addr_1);
//     i2c_mlcd_string(1, 0, str, I2C_addr_1);

//     i2c_mlcd_init(I2C_addr_2);
//     i2c_mlcd_string(0, 0, str2, I2C_addr_2);
//     i2c_mlcd_string(1, 0, str, I2C_addr_2);

//     while(1)
//     {
//         for(int i = 1002; i < 9999; i++)
//         {
//             mod = i % 3;
//             if(mod == 0)
//             {
//                 sprintf(str, "I2C_addr_0: %d", i);
//                 i2c_mlcd_string(1, 0, str, I2C_addr_0);
//             }
//             else if(mod == 1)
//             {
//                 sprintf(str, "I2C_addr_1: %d", i);
//                 i2c_mlcd_string(1, 0, str, I2C_addr_1);
//             }
//             else if(mod == 2)
//             {
//                 sprintf(str, "I2C_addr_2: %d", i);
//                 i2c_mlcd_string(1, 0, str, I2C_addr_2);
//             }
//             _delay_ms(100);
//         }
//     }

//     return 0;
// }
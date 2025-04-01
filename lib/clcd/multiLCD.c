/*
 * clcd.c
 *
 * Created: 2019-07-06 오후 3:07:03
 *  Author: user
 */ 

 #include "multiLCD.h"
 #include "uart.h"
 
 #define F_SCL 100000UL // SCL frequency
 
 #define RS1_EN1   0x05
 #define RS1_EN0   0x01
 #define RS0_EN1   0x04
 #define RS0_EN0   0x00
 #define BackLight 0x08
 
//  uint8_t I2C_addr_PCF8574 = (0x27 << 1);
//  uint8_t I2C_addr_PCF8574 = (0x26 << 1);
//  uint8_t I2C_addr_PCF8574 = (0x23 << 1);
  
 void i2c_mlcd_init(uint8_t i2c_addr)
 {
     i2c_init();
     _delay_ms(500);
 
     printf("Before Initialize... \r\n");	
     i2c_mlcd_command_8(0x30, i2c_addr); _delay_ms(5);
     i2c_mlcd_command_8(0x30, i2c_addr); _delay_us(100);
     i2c_mlcd_command_8(0x30, i2c_addr); _delay_us(100);
     i2c_mlcd_command_8(0x20, i2c_addr); _delay_us(100);
     
     i2c_mlcd_command(0x28, i2c_addr); _delay_us(50);	
     i2c_mlcd_command(0x08, i2c_addr); _delay_us(50);	
     i2c_mlcd_command(0x01, i2c_addr); _delay_ms(3);	 
     i2c_mlcd_command(0x06, i2c_addr); _delay_us(50);
     i2c_mlcd_command(0x0C, i2c_addr); _delay_us(50);	
     
     printf("Connect Ok\r\n");	
 }
 
 void i2c_mlcd_command_8(uint8_t command, uint8_t i2c_addr)
 {
     uint8_t c_buf[2];
     
     c_buf[0] = (command&0xF0) | RS0_EN1 | BackLight; 
     c_buf[1] = (command&0xF0) | RS0_EN0 | BackLight; 
     
     while(i2c_transmit(i2c_addr, c_buf, 2));
 }
 
 void i2c_mlcd_command(uint8_t command, uint8_t i2c_addr)
 {
     uint8_t c_buf[4];
     
     c_buf[0] = (command &0xF0) | RS0_EN1 | BackLight; 
     c_buf[1] = (command &0xF0) | RS0_EN0 | BackLight; 
     
     c_buf[2] = ((command <<4)&0xF0) | RS0_EN1 | BackLight;
     c_buf[3] = ((command <<4)&0xF0) | RS0_EN0 | BackLight;
     
     while(i2c_transmit(i2c_addr, c_buf, 4));
 }
 
 void i2c_mlcd_data(uint8_t data, uint8_t i2c_addr)
 {
     uint8_t d_buf[4];
     
     d_buf[0] = (data &0xF0) | RS1_EN1 | BackLight;
     d_buf[1] = (data &0xF0) | RS1_EN0 | BackLight;
     
     d_buf[2] = ((data <<4)&0xF0) | RS1_EN1 | BackLight;
     d_buf[3] = ((data <<4)&0xF0) | RS1_EN0 | BackLight;
     
     while(i2c_transmit(i2c_addr, d_buf, 4));
 }
 
 void i2c_mlcd_goto_XY(uint8_t row, uint8_t col, uint8_t i2c_addr)
 {
     uint8_t address = (0x40 * row) + col;
     uint8_t command = 0x80 | address;
     
     i2c_mlcd_command(command, i2c_addr);
 }
 
 void i2c_mlcd_string(uint8_t row, uint8_t col, char *string, uint8_t i2c_addr)
 {
     i2c_mlcd_goto_XY(row, col, i2c_addr);
     while(*string) {
         i2c_mlcd_data(*string++, i2c_addr);
     }
 }
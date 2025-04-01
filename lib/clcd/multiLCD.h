 #ifndef CLCD_H_
 #define CLCD_H_
 
 #ifndef  F_CPU
 #define F_CPU 16000000UL
 #endif
 
 #include "i2c_master.h"
 #include <util/delay.h>
 
 #include <avr/io.h>
 #include <stdint.h>
 
 void twi_init(void);
 void i2c_mlcd_init(uint8_t i2c_addr);
 void i2c_mlcd_command(uint8_t command, uint8_t i2c_addr);
 void i2c_mlcd_command_8(uint8_t command, uint8_t i2c_addr);
 void i2c_mlcd_data(uint8_t data, uint8_t i2c_addr);
 void i2c_mlcd_goto_XY(uint8_t row, uint8_t col, uint8_t i2c_addr);
 void i2c_mlcd_string(uint8_t row, uint8_t col, char string[], uint8_t i2c_addr);
 
 #endif /* CLCD_H_ */
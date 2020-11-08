/*
 * adc1115.h
 *
 *  Created on: Nov 7, 2020
 *      Author: sguss
 */
#include "main.h"

#ifndef INC_ADS1115_H_
#define INC_ADS1115_H_

//#include <ads1115_LowLevel.h>

#define APR_CONV_REG 0x00
#define APR_CONF_REG 0x01
#define APR_LO_THR_REG 0x02
#define APR_HI_THR_REG 0x03

// ADDR to GND
#define ADDR_A0 0x48 << 1
// ADDR to VDD
#define ADDR_A1 0x49 << 1
// ADDR to SDA
#define ADDR_A2 0x4A << 1
// ADDR to SCL
#define ADDR_A3 0x4B << 1

#define START_CONVERSION 0x80
#define END_CONVERSION 	 0x80

#define AIN0_AIN1_DIFF	0x00
#define AIN0_AIN3_DIFF	0x10
#define AIN1_AIN3_DIFF	0x20
#define AIN2_AIN3_DIFF	0x30
#define AIN0_GND_NORM	0x40
#define AIN1_GND_NORM	0x50
#define AIN2_GND_NORM	0x60
#define AIN3_GND_NORM	0x70

#define UP_6V		0x00
#define UP_4V		0x02
#define UP_2V		0x04
#define UP_1V		0x06
#define UP_05V 		0x08
#define UP_0256V 	0x0A
#define UP_0256V2	0x0C
#define UP_0256V3	0x0E

#define MODE_ONCE   0x0100
#define MODE_ALWAYS 0x0000

#define DR_8HZ		0x00
#define DR_16HZ		0x10
#define	DR_32HZ		0x20
#define DR_64HZ		0x30
#define	DR_128HZ	0x40
#define	DR_250HZ	0x50
#define	DR_475HZ	0x60
#define	DR_860HZ	0x70

#define COMP_GIST	0x00
#define COMP_NOGIST 0x10

#define COMP_POL_0  0x00
#define COMP_POL_1  0x08

#define COMP_LATCH_ON 0x04
#define COMP_LATCH_OFF 0x00

#define COMP_CONV_1		0x00
#define COMP_CONV_2		0x01
#define COMP_CONV_4		0x02
#define COMP_OFF		0x03




/*I2C1
 * PB6 - SCL
 * PB7 - SDA
 * Speed- 200 000 Hz
 */

int8_t init_ads1115(I2C_HandleTypeDef hi, uint8_t DEV_ADDR);
int16_t read_value_ads1115(I2C_HandleTypeDef hi, uint8_t DEV_ADDR);


#endif /* INC_ADS1115_H_ */

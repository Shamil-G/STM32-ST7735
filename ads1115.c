#include "ads1115.h"
#define ads1115

#ifdef ads1115
#define GAIN_TWOTHIRDS
#endif

#include "ADS1115.h"
uint16_t ads_value;
float  precision;

uint8_t cmd_value[] = { APR_CONF_REG, // select config register
						START_CONVERSION | AIN0_GND_NORM |
					    //UP_6V, // start single conversion на A0 на 6v
						UP_4V, // start single conversion на A0 на 4.096v
						//UP_2V, // start single conversion на A0 на 2048v
						//UP_1V, // start single conversion на A0 на 2048v
						//UP_05V, // start single conversion на A0 на 2048v
						//UP_0256, // start single conversion на A0 на 2048v
						//DR_128HZ | COMP_POL_1 | COMP_OFF,
						DR_128HZ | COMP_OFF,
						//0x85,  // 128 SPS + Active=Hight + Assert after two conversions
						//0x83,  // 128 SPS + Active=Hight + disable comparator
				  };


int8_t init_ads1115(I2C_HandleTypeDef hi, uint8_t DEV_ADDR){
	// first byte  - DEV_ADDR, it is equal - ADDR_A0, ADDR_A1, ADDR_A2, ADDR_A3
	// second byte - select Config register - 0x01 = APR_CONF_REG
	// third byte  - mode conversion
	// fourth byte - SPS  and COMPARATOR mode
	precision = ((cmd_value[1] & 0x0f)==UP_6V)?187.5:
			    ((cmd_value[1] & 0x0f)==UP_4V)?125:
			    ((cmd_value[1] & 0x0f)==UP_2V)?62.5:
			    ((cmd_value[1] & 0x0f)==UP_1V)?31.25:
			    ((cmd_value[1] & 0x0f)==UP_05V)?15.625:
			    ((cmd_value[1] & 0x0f)==UP_0256V)?7.813:0;

	while(HAL_I2C_Master_Transmit( &hi, DEV_ADDR, &cmd_value[0], 3, 100)!= HAL_OK){
		return 0;
	}
	return 1;
}

int16_t read_value_ads1115(I2C_HandleTypeDef hi, uint8_t DEV_ADDR){
	// Select CHIP where DEV_ADDR select from ADDR_A0, ADDR_A1, ADDR_A2, ADDR_A3
	// and select Conversation register
	ads_value=0;
	unsigned char recieve_buffer[2];
	uint16_t new_addr = (uint16_t)DEV_ADDR | 0x01;

	recieve_buffer[0]=0x00;
	while(HAL_I2C_Master_Transmit( &hi, DEV_ADDR, (uint8_t *)recieve_buffer, 1, 100)!= HAL_OK){
		return 0;
	}

	while(HAL_I2C_Master_Receive(&hi, new_addr, recieve_buffer, 2, 1000)!= HAL_OK){
		   return 0;

	}
	ads_value = (float)((recieve_buffer[0]<<8) + recieve_buffer[1]) * precision/1000;
	return ads_value;
}


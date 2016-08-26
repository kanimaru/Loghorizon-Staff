#ifndef __PCA9685___
#define __PCA9685___

#include "Arduino.h"
#include <Wire.h>
#include "LED.h"

#define PCA9685_MODE1 0x00
#define PCA9685_MODE2 0x01
#define PCA9685_PRESCALE 0xFE
#define PCA9685_SUBADR3 0x04

class PCA9685
{
public:
	PCA9685(uint8_t address);
	void begin();
	void restart();
	void setInvertedLogicMode();
	void setNormalLogicMode();
	void wake();
	void sleep();
	void setFrequency(uint16_t frequency);
	uint16_t getFrequency();

	void setChannels(uint8_t start, uint8_t end, uint16_t value);
	void setChannel(uint8_t channel, uint16_t value);

	uint16_t getChannel(uint8_t channel);

	void update();
	LED leds[5];

private:
	uint8_t _address;
	void _setPreScale(uint8_t prescale);
	void _setChannels(uint8_t start, uint8_t end, uint16_t* values);
	uint8_t _read8bits(uint8_t addr);
	void _write8bits(uint8_t reg, uint8_t value);

};
#endif

// 
// 
// 

#include "PCA9685_LED.h"

PCA9685_LED::PCA9685_LED(uint8_t address) : PCA9685(address) {}

void PCA9685_LED::update()
{
	// start from channel 0 ON
	for (int i = 0; i < 5; i++)
	{
		if (leds[i].update == false) continue;

		Wire.beginTransmission(_address);
		byte startcmd = i * 3 * 4 + 6;
		Wire.write((uint8_t)startcmd);

		Wire.write((uint8_t)0x00); // set all ON time to 0
		Wire.write((uint8_t)0x00);
		Wire.write(lowByte(leds[i].r)); // set OFF according to value
		Wire.write(highByte(leds[i].r));

		Wire.write((uint8_t)0x00); // set all ON time to 0
		Wire.write((uint8_t)0x00);
		Wire.write(lowByte(leds[i].g)); // set OFF according to value
		Wire.write(highByte(leds[i].g));

		Wire.write((uint8_t)0x00); // set all ON time to 0
		Wire.write((uint8_t)0x00);
		Wire.write(lowByte(leds[i].b)); // set OFF according to value
		Wire.write(highByte(leds[i].b));

		Wire.endTransmission();
		leds[i].update = false;
	}
}
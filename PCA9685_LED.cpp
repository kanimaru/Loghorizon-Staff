// 
// 
// 

#include "PCA9685_LED.h"
#include "Hardware.h"

PCA9685_LED::PCA9685_LED(uint8_t address) : PCA9685(address) {
	stop();
}

boolean PCA9685_LED::isPlaying()
{
	return sound.duration > 0;
}

void PCA9685_LED::stop()
{
	sound.duration = 0;
	sound.enabled = false;
	sound.update = true;
	updateFreq(PCA_FREQ);
}

void PCA9685_LED::play(uint16_t note, uint16_t duration)
{
	updateFreq(note);
	sound.duration = duration;
	sound.enabled = true;
	sound.update = true;
	sound.endless = duration == -1;
}

void PCA9685_LED::updateFreq(uint16_t freq)
{
	sound.updateFreq = true;
	sound.freq = freq;
}

void PCA9685_LED::update()
{

	if (sound.enabled && sound.duration > 0 && !sound.endless)
	{
		sound.duration -= hardware.diff;
		if (sound.duration < 0)
			stop();
	}

	if (sound.updateFreq)
	{
		setFrequency(sound.freq);
		sound.updateFreq = false;
	}

	if(sound.update) {
		sound.update = 0;
		if (sound.enabled) setChannel(15, 0x7FF);
		else setChannel(15, 0);
	}

	// start from channel 0 ON
	for (int i = 0; i < 5; i++)
	{
		if (leds[i].update == false) continue;

		Wire.beginTransmission(_address);
		byte startcmd = i * 12 + 6;
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
// PCA9685_LED.h

#ifndef _PCA9685_LED_h
#define _PCA9685_LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PCA9685.h"

class PCA9685_LED : public PCA9685
{
public:
	PCA9685_LED(uint8_t address);
	void update();
	LED leds[5];
	

	void play(uint16_t note, uint16_t duration);
	void stop();
	void updateFreq(uint16_t freq);
	boolean isPlaying();
private:
	struct Sound
	{
		uint8_t enabled : 1,
			update : 1,
			updateFreq : 1,
			endless : 1;
		int16_t duration;
		uint16_t freq;
	} sound;

};


#endif


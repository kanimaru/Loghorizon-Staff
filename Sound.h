// Sound.h

#ifndef _SOUND_h
#define _SOUND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Defines.h"


#include "PCA9685_LED.h"

class Sound
{
public:
	void boot();
	void tap();
	void doubleTap();
	void wake();
	void sleep();

	void doSound();
	

private:
	uint16_t curBufLoadPos;
	uint16_t delayBuffer[SOUND_BUFFER];
	uint16_t melodyBuffer[SOUND_BUFFER];

	void playSong(const uint16_t* song, const uint16_t* delay, uint16_t songLength, int8_t speed);
	const uint16_t* melody;
	const uint16_t* delay;
	uint16_t songLength;
	int8_t speed;
	uint16_t step;
	int16_t nextDelay;

	void playTone(uint16_t step);
	void buffer();
};

extern Sound sound;
#endif
// 
// 
// 

#include "Sound.h"
#include "Timer.h"
#include <avr/pgmspace.h>

#define melodyPin 3
#define START 0

const PROGMEM uint16_t melody[] = {
	// Messure 1
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, 
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,

	// Messure 2
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,

	// Messure 3
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,

	// Messure 4
	NOTE_CS5, 
	
	// Messure 5
	NOTE_D2, NOTE_D4,
	
	// Messure 6
	NOTE_D3, NOTE_F4, NOTE_E4, NOTE_C4,

	// Messure 7
	NOTE_A2, NOTE_A4, 
	
	// Messure 8
	NOTE_A2, NOTE_A4, NOTE_C5,
	
	// Messure 9
	NOTE_G2, NOTE_G4,

	// Messure 10
	NOTE_G2, NOTE_G4, NOTE_F4, NOTE_E4,

	// Messure 11
	NOTE_A2, NOTE_G4,

	// Messure 12
	NOTE_E3, NOTE_A3, NOTE_CS4,

	// Messure 13
	NOTE_D2, NOTE_D4,

	// Messure 14
	NOTE_D2, NOTE_F4, NOTE_E4, NOTE_D4,

	// Messure 15
	NOTE_A2, NOTE_A4,

	// Messure 16
	NOTE_A2, NOTE_A4, NOTE_E4, NOTE_A4, NOTE_C5,

	// Messure 17
	NOTE_G4, NOTE_A4, NOTE_G2, NOTE_G4,

	// Messure 18
	NOTE_G2, NOTE_G4, NOTE_F4, NOTE_E4,

	// Messure 19
	NOTE_AS2, NOTE_G4,

	// Messure 20
	NOTE_C2, NOTE_G2, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_G3, NOTE_E4,

	// Messure 21
	NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_G4,

	// Messure 22
	NOTE_F4, NOTE_A4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_D4, NOTE_G4,

	// Messure 23
	NOTE_A4, NOTE_CS4,

	// Messure 24
	NOTE_D5, NOTE_A5, NOTE_D6
};

const PROGMEM uint16_t tempo[] = {
	// Messure 1
	125, 125, 125, 125, 250, 
	125, 125, 125, 125, 1200,

	// Messure 2
	125, 125, 125, 125, 250,
	125, 125, 125, 125, 1200,

	// Messure 3
	125, 125, 125, 125, 250,
	125, 125, 125, 125, 1500,

	// Messure 4
	2000, 

	// Messure 5
	1500, 2000, 
	
	// Messure 6
	750, 750, 750, 750,

	// Messure 7
	1500, 2250, 
	
	// Messure 8
	1250, 500, 1250,
	
	// Messure 9
	1500, 2500,

	// Messure 10
	1000, 1000, 1000, 1000,

	// Messure 11
	1500, 2500,

	// Messure 12 (50)
	75, 75, 3750,

	// Messure 13
	1500, 2500,

	// Messure 14
	1000, 1000, 1000, 1000,

	// Messure 15
	1500, 2500,

	// Messure 16
	1500, 500, 75, 75, 1500,

	// Messure 17
	125, 125, 500, 2000,

	// Messure 18 (70)
	1500, 1000, 1000, 1000,

	// Messure 19
	1500, 2000,

	// Messure 20
	200,200, 200,200, 200,200, 500,

	// Messure 21
	200,200,200,200,200,200,200,200,

	// Messure 22
	200,200,200,200,200,200,200,200,

	// Messure 23
	1500, 2000,

	// Messure 24
	125,125,2000
};

void setupSound()
{
	pinMode(3, OUTPUT);//buzzer
	pinMode(13, OUTPUT);//led indicator when singing a note
	int mel;
	int temp;
	int size = 104;

	// iterate over the notes of the melody:
	for (int thisNote = START; thisNote < size; thisNote++)
	{
		mel = pgm_read_word_near(melody + thisNote);
		temp = pgm_read_word_near(tempo + thisNote);
		tone(3, mel, temp);
		delay(temp + 50);
		// stop the tone playing:
		noTone(3);
	}
}


//int notes[] = { 10, 50, 10, 100, 10, 50, 10, 100 };
int cur = 0;
int sec = 0;
void doSound()
{
	cur += diff;
	sec = cur / 1000;
//	analogWrite(11, notes[sec]);
//	if (sec == 7)
//	{
//		sec = 0;
//	}
}

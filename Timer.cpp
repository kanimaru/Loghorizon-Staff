// 
// 
// 

#include "Timer.h"

unsigned long ms;
unsigned long last;
unsigned long diff;

void handleTime() {
	ms = millis();
	diff = ms - last;
	last = ms;
}
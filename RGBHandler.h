// RGBHandler.h

#ifndef _RGBHANDLER_h
#define _RGBHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// LED Pins ---------- TEMP|
#define LED_STATUS 0
#define LED_WORKER 1    
const int PIN_R1 = 3;   // |
const int PIN_G1 = 6;   // |
const int PIN_B1 = 5;   // |

const int PIN_R2 = 9;   // |
const int PIN_G2 = 10;  // |
const int PIN_B2 = 11;  // |
//-------------------------/

void RGB_clr(int which);
void RGB_set(int which, int rVal, int gVal, int bVal);
void RGB_add(int which, int rVal, int gVal, int bVal);

#endif


// 
// 
// 

#include "RGBHandler.h"

int rgb[2][3];

void RGB_clr(int which) {
	RGB_set(which, 0, 0, 0);
}

void RGB_set(int which, int rVal, int gVal, int bVal) {
	rgb[which][0] = constrain(rVal, 0, 255);
	rgb[which][1] = constrain(gVal, 0, 255);
	rgb[which][2] = constrain(bVal, 0, 255);
	if (which == LED_STATUS) {
		analogWrite(PIN_R1, rgb[which][0]);
		analogWrite(PIN_G1, rgb[which][1]);
		analogWrite(PIN_B1, rgb[which][2]);
	}
	else {
		analogWrite(PIN_R2, rgb[which][0]);
		analogWrite(PIN_G2, rgb[which][1]);
		analogWrite(PIN_B2, rgb[which][2]);
	}
}

void RGB_add(int which, int rVal, int gVal, int bVal) {
	rgb[which][0] = constrain(rgb[which][0] + rVal, 0, 255);
	rgb[which][1] = constrain(rgb[which][1] + gVal, 0, 255);
	rgb[which][2] = constrain(rgb[which][2] + bVal, 0, 255);
}
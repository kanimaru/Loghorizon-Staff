// 
// 
// 

#include "Hardware.h"

/*
My min and max values for my chip.
Min-x:243 y:261 z:268
Max-x:421 y:420 z:422
*/
#ifndef ACCEL_SIMMULATE
int minAccel[3] = { 262,261,275 };
int maxAccel[3] = { 403,403,413 };
#else
const int minAccel[3] = { 0,0,0 };
const int maxAccel[3] = { 255,255,255 };
#endif // !ACCEL_SIMMULATE

// accerlated Values
int x;
int y;
int z;

// angle Values
double angX;
double angY;
double angZ;

//
//   Calculates the x,y,z values to the angeles.
//
void transform(int xRead, int yRead, int zRead) {
	//convert read values to degrees -90 to 90 - Needed for atan2
	x = map(xRead, minAccel[0], maxAccel[0], -90, 90);
	y = map(yRead, minAccel[1], maxAccel[1], -90, 90);
	z = map(zRead, minAccel[2], maxAccel[2], -90, 90);

	int constX = constrain(x, -90, 90);
	int constY = constrain(y, -90, 90);
	int constZ = constrain(z, -90, 90);

	//Caculate 360deg values like so: atan2(-yAng, -zAng)
	//atan2 outputs the value of -π to π (radians)
	//We are then converting the radians to degrees
	angX = RAD_TO_DEG * (atan2(-constY, -constZ) + PI);
	angY = RAD_TO_DEG * (atan2(-constX, -constZ) + PI);
	angZ = RAD_TO_DEG * (atan2(-constY, -constX) + PI);
}

//
// Simulates ACEL Sensor 
//
#ifdef ACCEL_SIMMULATE
int tempX = 0;
int tempY = 0;
int tempZ = 0;
int incomingByte = 0;
int counter = 0;

void serialIn() {
	while (Serial.available()) {
		incomingByte = Serial.read();

		if (counter == 0) tempX = incomingByte;
		else if (counter == 1) tempY = incomingByte;
		else if (counter == 2) tempZ = incomingByte;

		counter++;
		if (incomingByte == 255) {
			counter = 0;
			transform(tempX, tempY, tempZ);
		}
	}
}
#endif // ACCEL_SIMMULATE

#ifdef ACCEL_MESSURE
void messureAccel(int xRead, int yRead, int zRead)
{
	minAccel[0] = min(xRead, minAccel[0]);
	minAccel[1] = min(yRead, minAccel[1]);
	minAccel[2] = min(zRead, minAccel[2]);

	maxAccel[0] = max(xRead, maxAccel[0]);
	maxAccel[1] = max(yRead, maxAccel[1]);
	maxAccel[2] = max(zRead, maxAccel[2]);

	Serial.print("Cur-");
	Serial.print("x:");
	Serial.print(xRead);
	Serial.print("\ty:");
	Serial.print(yRead);
	Serial.print("\tz:");
	Serial.print(zRead);

	Serial.print("\tMin-");
	Serial.print("x:");
	Serial.print(minAccel[0]);
	Serial.print("\ty:");
	Serial.print(minAccel[1]);
	Serial.print("\tz:");
	Serial.print(minAccel[2]);

	Serial.print("\tMax-");
	Serial.print("x:");
	Serial.print(maxAccel[0]);
	Serial.print("\ty:");
	Serial.print(maxAccel[1]);
	Serial.print("\tz:");
	Serial.println(maxAccel[2]);
}

#endif // ACCEL_MESSURE

void readAccel() {
	int xRead = analogRead(PIN_ACCEL_X);
	int yRead = analogRead(PIN_ACCEL_Y);
	int zRead = analogRead(PIN_ACCEL_Z);

#ifdef ACCEL_MESSURE
	messureAccel(xRead, yRead, zRead);
#endif // ACCEL_MESSURE

	transform(xRead, yRead, zRead);
	
#ifdef ACCEL_DEBUG
	Serial.print("X:");
	Serial.print(x);
	Serial.print("\tY:");
	Serial.print(y);
	Serial.print("\tZ:");
	Serial.print(z);
	Serial.print("\t\taX:");
	Serial.print(angX);
	Serial.print("\taY:");
	Serial.print(angY);
	Serial.print("\taZ:");
	Serial.println(angZ);
#endif // ACCEL_DEBUG

}

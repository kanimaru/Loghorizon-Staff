// 
// 
// 

#include "Hardware.h"

Hardware hardware = Hardware();

void Hardware::selfCheck()
{
	for (uint8_t i = 0; i < PCA_AMOUNT; i++)
	{
		chips[i].setChannel(PCA_ALL, 0xFFF);
		delay(SELF_CHECK_DUR);
		chips[i].setChannel(PCA_ALL, 0);
	}
}

void Hardware::setup()
{
	pinMode(PIN_ACCEL_X, INPUT);
	pinMode(PIN_ACCEL_Y, INPUT);
	pinMode(PIN_ACCEL_Z, INPUT);

	// Chips
	for (uint8_t i = 0; i < PCA_AMOUNT; i++)
	{
		chips[i].begin();
		chips[i].setFrequency(PCA_FREQ);
		chips[i].setChannel(PCA_ALL, 0x000);

		for (uint8_t l = 0; l < 5; l++)
		{
			leds[i * 5 + l] = &chips[i].leds[l];
		}
	}
	selfCheck();
}

void Hardware::doAccel()
{
	int8_t xRead = analogRead(PIN_ACCEL_X);
	int8_t yRead = analogRead(PIN_ACCEL_Y);
	int8_t zRead = analogRead(PIN_ACCEL_Z);

#ifdef ACCEL_MESSURE
	messureAccel(xRead, yRead, zRead);
#endif // ACCEL_MESSURE

	this->transform(xRead, yRead, zRead);

#ifdef ACCEL_DEBUG
	Serial.print("X:");
	Serial.print(_x);
	Serial.print("\tY:");
	Serial.print(_y);
	Serial.print("\tZ:");
	Serial.print(_z);
	Serial.print("\t\taX:");
	Serial.print(angX);
	Serial.print("\taY:");
	Serial.print(angY);
	Serial.print("\taZ:");
	Serial.println(angZ);
#endif // ACCEL_DEBUG
}

/* Calculates the x,y,z values to the angeles. */
void Hardware::transform(uint8_t xRead, uint8_t yRead, uint8_t zRead)
{
	//convert read values to degrees -90 to 90 - Needed for atan2
	_x = map(xRead, minAccel[0], maxAccel[0], -90, 90) - offsetX;
	_y = map(yRead, minAccel[1], maxAccel[1], -90, 90) - offsetY;
	_z = map(zRead, minAccel[2], maxAccel[2], -90, 90) - offsetZ;

	int8_t constX = constrain(_x, -90, 90);
	int8_t constY = constrain(_y, -90, 90);
	int8_t constZ = constrain(_z, -90, 90);

	//Caculate 360deg values like so: atan2(-yAng, -zAng)
	//atan2 outputs the value of -π to π (radians)
	//We are then converting the radians to degrees
	angX = RAD_TO_DEG * (atan2(-constY, -constZ) + PI);
	angY = RAD_TO_DEG * (atan2(-constX, -constZ) + PI);
	angZ = RAD_TO_DEG * (atan2(-constY, -constX) + PI);
}

/* Refreshes LEDs */
void Hardware::doLEDs()
{
	for (uint8_t pca_choose = 0; pca_choose < PCA_AMOUNT; pca_choose++)
		chips[pca_choose].update();
}

/* Turn of every LED */
void Hardware::turnOffLEDs()
{
	for (uint8_t pca_choose = 0; pca_choose < PCA_AMOUNT; pca_choose++)
		chips[pca_choose].setChannel(PCA_ALL, 0);
}

/* Simulates Accel Sensor via Serial */
#ifdef ACCEL_SIMMULATE
int tempX = 0;
int tempY = 0;
int tempZ = 0;
int incomingByte = 0;
int counter = 0;

void Hardware::simmulateAccel()
{
	while (Serial.available())
	{
		incomingByte = Serial.read();

		if (counter == 0) tempX = incomingByte;
		else if (counter == 1) tempY = incomingByte;
		else if (counter == 2) tempZ = incomingByte;

		counter++;
		if (incomingByte == 255)
		{
			counter = 0;
			transform(tempX, tempY, tempZ);
		}
	}
}
#endif // ACCEL_SIMMULATE

/*Messure the hardware values and sends over serial*/
#ifdef ACCEL_MESSURE
void Hardware::messureAccel(uint8_t xRead, uint8_t yRead, uint8_t zRead)
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

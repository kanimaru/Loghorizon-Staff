// 
// 
// 

#include "Hardware.h"
#include "Modes.h"
#include "Sound.h"

Hardware hardware = Hardware();

void Hardware::init()
{

	adxl.powerOn();
	adxl.setRangeSetting(8);
	adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
	adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
	adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

	adxl.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
	adxl.setActivityThreshold(30);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
	
	adxl.setTapDetectionOnXYZ(0, 0, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
										// Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
	adxl.setTapThreshold(50);           // 62.5 mg per increment
	adxl.setTapDuration(15);            // 625 μs per increment
	adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
	adxl.setDoubleTapWindow(200);       // 1.25 ms per increment

	adxl.doubleTapINT(1);
	adxl.singleTapINT(1);
	adxl.InactivityINT(1);
	adxl.ActivityINT(1);

	adxl.setAxisOffset(-10, 0, 0);

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

void Hardware::selfCheck()
{
	for (uint8_t i = 0; i < PCA_AMOUNT; i++)
	{
		chips[i].setChannel(PCA_ALL, 0xFFF);
		delay(SELF_CHECK_DUR);
		chips[i].setChannel(PCA_ALL, 0);
	}
}


void Hardware::doAccel()
{
	int x, y, z;
	adxl.readAccel(&x, &y, &z);
	_flatX[_pos] = x + _xOffset;
	_flatY[_pos] = y + _yOffset;
	_flatZ[_pos] = z + _zOffset;
	_pos = _pos++ % SMOOTHNESS;

	_x = 0;
	_y = 0;
	_z = 0;

	for (uint8_t i = 0; i < SMOOTHNESS; i++)
	{
		_x += _flatX[i] / SMOOTHNESS;
		_y += _flatY[i] / SMOOTHNESS;
		_z += _flatZ[i] / SMOOTHNESS;
	}
	
#ifdef ACCEL_DEBUG
	Serial.print("X:");
	Serial.print(_x);
	Serial.print("\tY:");
	Serial.print(_y);
	Serial.print("\tZ:");
	Serial.print(_z);
	Serial.println(inactivity ? "Inactive" : "Active");
#endif // ACCEL_DEBUG

	byte interrupts = adxl.getInterruptSource();
	if (adxl.triggered(interrupts, ADXL345_INACTIVITY))
	{
		_inactivity = true;
		_inactiveCounter = 0;
	}
	if (adxl.triggered(interrupts, ADXL345_ACTIVITY))
	{
		if (inactive)
		{
			turnOn();
		}
		_inactivity = false;
		inactive = false;
		
	}
	if (adxl.triggered(interrupts, ADXL345_DOUBLE_TAP))
	{
		modes.doubleTap();
	} else if (adxl.triggered(interrupts, ADXL345_SINGLE_TAP))
	{
		modes.singleTap();
	}
	
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
	for (uint8_t i = 0; i < LED_AMOUNT; i++)
		leds[i]->setRGB(0, 0, 0);

	//for (uint8_t pca_choose = 0; pca_choose < PCA_AMOUNT; pca_choose++)
	//	chips[pca_choose].setChannel(PCA_ALL, 0);
}

void Hardware::doCheckInactivity()
{
	if (_inactivity && !inactive && _inactivityEnabled)
	{
		_inactiveCounter += diff;
		if (_inactiveCounter > 10000)
		{
			inactive = true;
			turnOff();
		}
	}
}

void Hardware::doTime()
{
	ms = millis();
	diff = (uint8_t)(ms - last);
	last = ms;
}

void Hardware::turnOff()
{
	sound.sleep();
	for (uint8_t pca_choose = 0; pca_choose < PCA_AMOUNT; pca_choose++)
		chips[pca_choose].sleep();

}

void Hardware::turnOn()
{
	for (uint8_t pca_choose = 0; pca_choose < PCA_AMOUNT; pca_choose++)
		chips[pca_choose].wake();

	sound.wake();
}

void Hardware::disableInactive()
{
	_inactivityEnabled = false;
}

void Hardware::enableInactive()
{
	_inactivityEnabled = true;
}
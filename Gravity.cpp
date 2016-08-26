// 
// 
// 

#include "Gravity.h"
#include "Ball.h"
#include "Hardware.h"

Ball ball(0, 0, 0, 30);
Ball ball2(0, 0, 0, 30);

void doGravity()
{
	int16_t accelX = constrain(x, -60, 60) / 10;
	if (x < 10 && x > -10)
	{
		accelX = 0;
	}

	int16_t accelY = constrain(y, -60, 60) / 10;
	if (y < 10 && y > -10)
	{
		accelY = 0;
	}

	ball.x -= accelX;
	ball.x = constrain(ball.x, -30, 30);
	ball.y += accelY;
	ball.y = constrain(ball.y, -20, 20);

	ball2.x += accelX;
	ball2.x = constrain(ball2.x, -30, 30);
	ball2.y -= accelY;
	ball2.y = constrain(ball2.y, -20, 20);

	for (uint8_t i = 0; i < LED_AMOUNT; i++)
	{
		int32_t dist = -0xFF * ball.dist(leds[i]->x, leds[i]->y, leds[i]->z);
		int32_t dist2 = -0xFF * ball2.dist(leds[i]->x, leds[i]->y, leds[i]->z);

		dist = constrain(dist, 0, 0xFFF);
		dist2 = constrain(dist2, 0, 0xFFF);

		leds[i]->setRGB(dist2, dist, 0);
	}
}
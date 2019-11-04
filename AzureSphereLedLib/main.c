#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include "PwmControl.h"
#include "Apa102Control.h"


int main(void)
{

	SetupApa102(1, -1);
	struct ColorWithBrightness apaColor = { 31, 150, 150, 150 };
	SetSolid(apaColor, 2);
	TeardownApa102();
	
	
	SetupPwm(2, 0, 1, 2);
	struct timespec sleeper = { 0,5000000 };

	struct Color color = { 255, 0, 0 };

	while(1)
	{
		if (color.Red)
		{
			if (color.Blue)
			{
				color.Blue--;
				color.Red++;
			}
			else
			{
				color.Red--;
				color.Green++;
			}
		}
		else if (color.Green)
		{
			color.Green--;
			color.Blue++;
		}
		else
		{
			color.Blue--;
			color.Red++;
		}
		SetColor(color);
		nanosleep(&sleeper, NULL);
	}
	
	TeardownPwm();
}
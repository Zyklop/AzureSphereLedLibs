#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <applibs/log.h>
#include "PwmControl.h"


int main(void)
{

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
#include "Samples.h"

#include "PwmControl.h"
#include "Apa102Control.h"
#include <stddef.h>
#include <threads.h>

void AdvanceRainbow(struct Color* color)
{
	if (color->Red)
	{
		if (color->Blue)
		{
			color->Blue--;
			color->Red++;
		}
		else
		{
			color->Red--;
			color->Green++;
		}
	}
	else if (color->Green)
	{
		color->Green--;
		color->Blue++;
	}
	else
	{
		color->Blue--;
		color->Red++;
	}
}

void PwmRainbow(unsigned int controllerId, uint32_t redPin, uint32_t greenPin, uint32_t bluePin, int msDelay)
{
	SetupPwm(controllerId, redPin, greenPin, bluePin);
	struct timespec sleeper = { 0, msDelay * 1000000 };

	struct Color color = { 255, 0, 0 };

	while (1)
	{
		SetColor(color);
		AdvanceRainbow(&color);
		nanosleep(&sleeper, NULL);
	}

	TeardownPwm();
}

void ApaSolidRainbow(int interfaceId, int chipSelectId, int length, int msDelay)
{
	SetupApa102(interfaceId, chipSelectId);
	struct timespec sleeper = { 0, msDelay * 1000000 };

	struct Color color = { 255, 0, 0 };

	while (1)
	{
		struct ColorWithBrightness apaColor = { 31, color.Red, color.Green, color.Blue };
		SetSolid(apaColor, length);
		AdvanceRainbow(&color);
		nanosleep(&sleeper, NULL);
	}

	TeardownApa102();
}

void ApaMovingRainbow(int interfaceId, int chipSelectId, int length, int msDelay)
{
	SetupApa102(interfaceId, chipSelectId);
	struct timespec sleeper = { 0, msDelay * 1000000 / length };

	struct Color color = { 255, 0, 0 };
	struct Color startColor = { 255, 0, 0 };
	int index = 0;
	PrepareForStreaming();

	while (1)
	{
		struct ColorWithBrightness apaColor = { 31, color.Red, color.Green, color.Blue };
		AppendColor(apaColor);
		index++;
		AdvanceRainbow(&color);
		if (index >= length)
		{
			FinishStreaming();
			PrepareForStreaming();
			AdvanceRainbow(&startColor);
			color.Red = startColor.Red;
			color.Green = startColor.Green;
			color.Blue = startColor.Blue;
			index = 0;
		}
		nanosleep(&sleeper, NULL);
	}

	TeardownApa102();
}

void ApaMovingLight(int interfaceId, int chipSelectId, int length, int msDelay)
{
	SetupApa102(interfaceId, chipSelectId);
	struct timespec sleeper = { msDelay/1000, (msDelay * 1000000)%1000000000 };

	struct ColorWithBrightness on = { 31, 255, 255, 255 };
	struct ColorWithBrightness off = { 31, 0, 0, 0 };
	int index = 0;

	while (1)
	{
		PrepareForStreaming();
		for (int i = 0; i < length; ++i)
		{
			if (i == index)
			{
				AppendColor(on);
			}
			else
			{
				AppendColor(off);
			}
		}
		FinishStreaming();
		index++;
		if (index >= length)
		{
			index = 0;
		}
		nanosleep(&sleeper, NULL);
	}

	TeardownApa102();
}
#pragma once
#include <applibs/pwm.h>

struct Color;

typedef struct Color {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};

int SetupPwm(unsigned int controller_id, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

int TeardownPwm();

int SetColor(struct Color color);
int SetColorFromInt(int red, int green, int blue);
int SetColorFromBytes(uint8_t red, uint8_t green, uint8_t blue);

int TurnOff();

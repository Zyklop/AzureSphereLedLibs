#pragma once
#include <applibs/pwm.h>

struct Color;

typedef struct Color {
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
};

int SetupPwm(unsigned int controller_id, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

int TeardownPwm();

int SetColor(struct Color color);
int SetColorFromInt(int red, int green, int blue);
int SetColorFromChar(unsigned char red, unsigned char green, unsigned char blue);

int TurnOff();

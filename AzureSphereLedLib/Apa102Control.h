#pragma once
#include <stdint.h>

struct ColorWithBrightness;

typedef struct ColorWithBrightness {
	uint8_t Brightness;
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};


int SetupApa102(int interfaceId, int chipSelectId);

int TeardownApa102();

int AppendColorFromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

int AppendColor(struct ColorWithBrightness color);

int PrepareForStreaming();

int FinishStreaming();

int SetSolid(struct ColorWithBrightness color, int length);

int SetCustom(struct ColorWithBrightness *color, int length);
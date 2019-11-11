#pragma once
#include <applibs/pwm.h>

struct Color;

typedef struct Color {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};

/**
 * \brief enables the pwm controller to control the leds
 * \param controller_id id of the pwm controller to use. 2 for the dev-boards onboard led
 * \param redPin id of the pin which is connected to the red channel. 0 for the onboard led
 * \param greenPin id of the pin which is connected to the green channel. 1 for the onboard led
 * \param bluePin id of the pin which is connected to the blue channel. 2 for the onboard led
 * \return 0 if successful
 */
int SetupPwm(unsigned int controller_id, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);

/**
 * \brief turns off the channels and turns the controller off
 * \return 0 if successful
 */
int TeardownPwm();

/**
 * \brief sets the output to a color
 * \param color color to set
 * \return 0 if successful
 */
int SetColor(struct Color color);

/**
 * \brief sets the outputs to the selected color
 * \param red red brightness  value, 0-255
 * \param green green brightness value to set, 0-255
 * \param blue blue brightness value, 0-255
 * \return 0 if successful
 */
int SetColorFromInt(int red, int green, int blue);

/**
 * \brief sets the outputs to the selected color
 * \param red red brightness  value, 0-255
 * \param green green brightness value to set, 0-255
 * \param blue blue brightness value, 0-255
 * \return 0 if successful
 */
int SetColorFromBytes(uint8_t red, uint8_t green, uint8_t blue);

/**
 * \brief turns the strip off, eg. setting it to black
 * \return 0 if successful
 */
int TurnOff();

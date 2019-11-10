#pragma once
#include <stdint.h>

/**
 * \brief Shows a Rainbow pattern on simple 3-channel leds
 * \param controllerId Id of the pwm controller, 2 for the onboard led
 * \param redPin Id of the pin for the red channel, 0- for the dev board
 * \param greenPin Id of the pin for the green channel, 1 for the dev board
 * \param bluePin Id of the pin for the blue channel, 2 for the dev board
 * \param msDelay Time in ms before changing to the next color
 */
void PwmRainbow(unsigned int controllerId, uint32_t redPin, uint32_t greenPin, uint32_t bluePin, int msDelay);

/**
 * \brief Shows a solid rainbow on APA 102 Leds
 * \param interfaceId Id of the interface for the SPI channel. 1 for the dev/boards headers
 * \param chipSelectId chip select id for SPI. -1 for the dev board
 * \param length Amount of Leds in the strip to drive
 * \param msDelay Time in ms between changing the colors
 */
void ApaSolidRainbow(int interfaceId, int chipSelectId, int length, int msDelay);

/**
 * \brief Shows a moving rainbow pattern on APA 102 Leds
 * \param interfaceId Id of the interface for the SPI channel. 1 for the dev/boards headers
 * \param chipSelectId chip select id for SPI. -1 for the dev board
 * \param length Amount of Leds in the strip to drive
 * \param msDelay Time in ms between changing the colors
 */
void ApaMovingRainbow(int interfaceId, int chipSelectId, int length, int msDelay);

/**
 * \brief Shows a moving light on APA 102 Leds
 * \param interfaceId Id of the interface for the SPI channel. 1 for the dev/boards headers
 * \param chipSelectId chip select id for SPI. -1 for the dev board
 * \param length Amount of Leds in the strip to drive
 * \param msDelay Time in ms between changing the colors
 */
void ApaMovingLight(int interfaceId, int chipSelectId, int length, int msDelay);
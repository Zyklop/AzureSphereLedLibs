#pragma once
#include <stdint.h>

struct ColorWithBrightness;

/**
 * \brief A basic color struct also holding a brightness value.
 */
typedef struct ColorWithBrightness {
	/**
	 * \brief Brigthness value between 0 and 31
	 */
	uint8_t Brightness;
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};


/**
 * \brief setup the selected SPI interface to communicate to the Apa102 leds
 * \param interfaceId id of the SPI-Interface to use. 1 for the mikrobus-connectors on the dev board
 * \param chipSelectId Chip select id to select the SPI/Chip. -1 on the dev board
 * \return 0 if successful
 */
int SetupApa102(int interfaceId, int chipSelectId);

/**
 * \brief Closes spi channels for communication. Does not reset or turn off any connected leds
 * \return 0 if successful
 * \attention to turn the strip off, use SetSolid() to black before.
 */
int TeardownApa102();

/**
 * \brief set a single led in the strip and advances to the next
 * \param red red brightness value, 0-255
 * \param green green brightness value, 0-255
 * \param blue blue brightness value, 0-255
 * \param brightness global brightness value, 0-31
 * \return 0 if successful
 */
int AppendColorFromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);

/**
 * \brief set a single led in the strip and advances to the next
 * \param color Color value to  send
 * \return 0 if successful
 */
int AppendColor(struct ColorWithBrightness color);

/**
 * \brief Ste the strip up to begin receiving values as a stream, beginning from the first led
 * \return 0 if successful
 */
int PrepareForStreaming();

/**
 * \brief ends the streaming activaates the colors (depending on the model) and enables to start a new stream or other commands
 * \return 0 if successful
 */
int FinishStreaming();

/**
 * \brief sets all the leds in the strip to a solid color
 * \param color target color to set the strip
 * \param length number of led in the strip
 * \return 0 if successful
 */
int SetSolid(struct ColorWithBrightness color, int length);

/**
 * \brief Sets the whole strip to a custom pattern using an array
 * \param color array of colors to set
 * \param length length of the array and the strip
 * \return 0 if successful
 */
int SetCustom(struct ColorWithBrightness *color, int length);
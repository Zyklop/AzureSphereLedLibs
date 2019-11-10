#include "Apa102Control.h"
#include "libsVersions.h"

#include <errno.h>

#include <applibs/log.h>
#include <applibs/spi.h>
#include <string.h>
#include <unistd.h>

static int spiFd = 0;
static int lengthCounter = 0;

int SetupApa102(int interfaceId, int chipSelectId)
{
	SPIMaster_Config config;
	int ret = SPIMaster_InitConfig(&config);
	if (ret != 0) {
		Log_Debug("ERROR: SPIMaster_InitConfig = %d errno = %s (%d)\n", ret, strerror(errno),
			errno);
		return -1;
	}

	config.csPolarity = SPI_ChipSelectPolarity_ActiveHigh;
	spiFd = SPIMaster_Open((SPI_InterfaceId)interfaceId, (SPI_ChipSelectId) chipSelectId, &config);
	if (spiFd < 0) {
		Log_Debug("ERROR: SPIMaster_Open: errno=%d (%s)\n", errno, strerror(errno));
		return -1;
	}

	int result = SPIMaster_SetBusSpeed(spiFd, 12000000);
	if (result != 0) {
		Log_Debug("ERROR: SPIMaster_SetBusSpeed: errno=%d (%s)\n", errno, strerror(errno));
		return -1;
	}

	result = SPIMaster_SetMode(spiFd, SPI_Mode_3);
	if (result != 0) {
		Log_Debug("ERROR: SPIMaster_SetMode: errno=%d (%s)\n", errno, strerror(errno));
		return -1;
	}
	
	result = SPIMaster_SetBitOrder(spiFd, SPI_BitOrder_MsbFirst);
	if (result != 0) {
		Log_Debug("ERROR: SPIMaster_SetBitOrder: errno=%d (%s)\n", errno, strerror(errno));
		return -1;
	}
}

int TeardownApa102()
{
	Log_Debug("Closing file descriptors.\n");
	if (spiFd >= 0) {
		int result = close(spiFd);
		if (result != 0) {
			Log_Debug("ERROR: Could not close fd %s: %s (%d).\n", "Spi", strerror(errno), errno);
			return -1;
		}
	}
	Log_Debug("File descriptors closed.\n");

	return 0;
}

int Send(uint8_t* data, size_t size)
{
	SPIMaster_Transfer transfer;
	int result = SPIMaster_InitTransfers(&transfer, 1);
	if (result != 0) {
		return -1;
	}
	
	transfer.flags = SPI_TransferFlags_Write;
	transfer.length = size;
	transfer.writeData = data;

	ssize_t transferredBytes = SPIMaster_TransferSequential(spiFd, &transfer, 1);
	if (transferredBytes != (ssize_t)size) {
		return -1;
	}

	return 0;
}

int AppendColorFromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
{
	lengthCounter++;
	uint8_t data[4] = { 0b11100000 | brightness, blue, green, red };
	return Send(data, sizeof data);
}

int AppendColor(struct ColorWithBrightness color)
{
	lengthCounter++;
	uint8_t data[4] = { 0b11100000 | color.Brightness, color.Blue, color.Green, color.Red };
	return Send(data, sizeof data);
}

int PrepareForStreaming()
{
	lengthCounter = 0;
	uint8_t data[4] = { 0,0,0,0 };
	return Send(data, sizeof data);
}

int FinishStreaming()
{
	int endFrameLength = 5 + lengthCounter/16;
	uint8_t data[endFrameLength];
	
	for (int i = 0; i < endFrameLength; ++i)
	{
		data[i] = 0b11111111;
	}
	return Send(data, sizeof data);
}

int SetSolid(struct ColorWithBrightness color, int length)
{
	size_t dataLength = 8 + length * 4 + length / 16;
	uint8_t data[dataLength];
	uint8_t strippedBrightness = 0b11100000 | color.Brightness;
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
	for (int i = 0; i < length; i++)
	{
		data[4 + i * 4] = strippedBrightness;
		data[5 + i * 4] = color.Blue;
		data[6 + i * 4] = color.Green;
		data[7 + i * 4] = color.Red;
	}
	for (unsigned int i = 4 + length * 4; i < dataLength; i++)
	{
		data[i] = 0;
	}
	return Send(data, sizeof data);
}

int SetCustom(struct ColorWithBrightness *color, int length)
{
	size_t dataLength = 8 + length * 4 + length / 16;
	uint8_t data[dataLength];
	uint8_t stripped_brightness; 
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
	for (int i = 0; i < length; i++)
	{
		stripped_brightness = 0b11100000 | color[i].Brightness;
		data[4 + i * 4] = stripped_brightness;
		data[5 + i * 4] = color[i].Blue;
		data[6 + i * 4] = color[i].Green;
		data[7 + i * 4] = color[i].Red;
	}
	for (unsigned int i = 4 + length * 4; i < dataLength; i++)
	{
		data[i] = 0;
	}
	return Send(data, sizeof data);
}
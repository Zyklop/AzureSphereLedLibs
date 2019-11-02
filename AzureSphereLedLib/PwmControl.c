#include "PwmControl.h"

#include <applibs/log.h>
#include <applibs/pwm.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

static const unsigned int cycleLength = 10240;
static const unsigned int stepLength = 40;

static int controllerFd = -1;

static PWM_ChannelId redChannel;
static PWM_ChannelId greenChannel;
static PWM_ChannelId blueChannel;

static PwmState redState = { .period_nsec = cycleLength,
							   .polarity = PWM_Polarity_Inversed,
							   .dutyCycle_nsec = 0,
							   .enabled = true };
static PwmState greenState = { .period_nsec = cycleLength,
							   .polarity = PWM_Polarity_Inversed,
							   .dutyCycle_nsec = 0,
							   .enabled = true };
static PwmState blueState = { .period_nsec = cycleLength,
							   .polarity = PWM_Polarity_Inversed,
							   .dutyCycle_nsec = 0,
							   .enabled = true };


int SetupPwm(unsigned int controller_id, uint32_t redPin, uint32_t greenPin, uint32_t bluePin)
{
	redChannel = redPin;
	greenChannel = greenPin;
	blueChannel = bluePin;

	controllerFd = PWM_Open(controller_id);
	if (controllerFd == -1) {
		Log_Debug(
			"Error opening SAMPLE_LED_PWM_CONTROLLER: %s (%d). Check that app_manifest.json "
			"includes the PWM used.\n",
			strerror(errno), errno);
		return -1;
	}

	return TurnOff();
}

void CloseFdAndPrintError(int fd, const char* fdName)
{
	if (fd >= 0) {
		int result = close(fd);
		if (result != 0) {
			Log_Debug("ERROR: Could not close fd %s: %s (%d).\n", fdName, strerror(errno), errno);
		}
	}
}

int TeardownPwm()
{
	if (TurnOff())
	{
		return -1;
	}
	Log_Debug("Closing file descriptors.\n");
	CloseFdAndPrintError(controllerFd, "ControllerFd");
	Log_Debug("File descriptors closed.\n");
	return 0;
}

int SetColor(struct Color color)
{
	return SetColorFromChar(color.Red, color.Green, color.Blue);
}

int SetColorFromInt(int red, int green, int blue)
{
	return SetColorFromChar((unsigned char)red, (unsigned char)green, (unsigned char)blue);
}

int SetColorFromChar(unsigned char red, unsigned char green, unsigned char blue)
{
	redState.dutyCycle_nsec = red * stepLength;
	greenState.dutyCycle_nsec = green * stepLength;
	blueState.dutyCycle_nsec = blue * stepLength;
	int result = PWM_Apply(controllerFd, redChannel, &redState);
	result += PWM_Apply(controllerFd, greenChannel, &greenState);
	result += PWM_Apply(controllerFd, blueChannel, &blueState);
	if (result != 0) {
		Log_Debug("PWM_Apply failed: result = %d, errno: %s (%d)\n", result, strerror(errno),
			errno);
	}
}

int TurnOff()
{
	return SetColorFromChar(0, 0, 0);
}
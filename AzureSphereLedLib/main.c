#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "Samples.h"

int main(void)
{
	//PwmRainbow(2, 0, 1, 2, 10);
	//ApaSolidRainbow(1, -1, 2, 10);
	//ApaMovingLight(1, -1, 3, 500);
	ApaMovingRainbow(1, -1, 2, 10);
}
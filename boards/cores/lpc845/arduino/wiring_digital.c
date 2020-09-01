#include "../Arduino.h"

#ifdef __cplusplus
 extern "C" {
#endif

const uint8_t pin_map[] = {0, 17, 4, 13, 18, 23, 14, 21, 0, 7, 25, 1, 24, 16, 11, 10, 12};

void pinMode( uint32_t dwPin, uint32_t dwMode )
{
	gpio_pin_config_t config =
	{
		kGPIO_DigitalInput,
		0,
	};

	if (dwMode == OUTPUT)
		config.pinDirection = kGPIO_DigitalOutput;

	GPIO_PinInit(GPIO, 0, pin_map[dwPin], &config);
}

void digitalWrite( uint32_t dwPin, uint32_t dwVal )
{
	GPIO_PinWrite(GPIO, 0, pin_map[dwPin], dwVal);
}

int digitalRead( uint32_t ulPin )
{
	return GPIO_PinRead(GPIO, 0, pin_map[ulPin]);
}

void digitalToggle( uint32_t dwPin )
{
	digitalWrite(dwPin, !digitalRead(dwPin));
}

#ifdef __cplusplus
 }
#endif
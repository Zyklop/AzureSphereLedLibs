# AzureSphereLedLibs
Led driver libraries for Azure Sphere

## Supported Features
- Driving Rgb-Leds and and simple rgb-led strips with PWM
- Driving Apa102 and similar leds using SPI

# Wiring
## Single rgb led
1. Connect the color channels to 3 pwm-enabled gpio pins
1. Connect the leds ground to a ground pin 

## Rgb led strip
1. Connect 3 pwm enabled gpio-pins to your booster circuit
1. Connect the boosters output to your led-strip
1. Connect the boosters positive input to a power-supply
1. Connect the the boosters ground to the power supply and to the Sphere's ground

## Apa 102 leds
1. Connect the SPI-CLK pin to the led's CI connection
1. Connect the SPI-MOSI pin to the led's DI connection
1. Connect the led's 5v to a power supply
1. Connect the led's GND to the power supply and to Sphere's GND pin

# Usage
Use the provided samples or start from scratch

## Pwm
1. Find the controller_id and the ids of the pins you connected to
1. Add "Pwm": `[ "PWM-CONTROLLER-{yourControllerId}" ]` to the applications manifest capabilities
1. Add the setup and teardow methods: 
```c
SetupPwm(unsigned int controller_id, uint32_t redPin, uint32_t greenPin, uint32_t bluePin);
Teardown();
```
4. Set the desired color by using the color-srtruct or by setting the values directly
```c
SetColor(struct Color color);
SetColorFromInt(int red, int green, int blue);
SetColorFromBytes(uint8_t red, uint8_t green, uint8_t blue);
```
## Apa 102
1. Find the interface_id and the chipselct_id of the interface you used
1. Add `"SpiMaster": [ "ISU{interface_id}" ]` to the applications manifest capabilities
1. Add the setup and teardow methods:
```c
SetupApa102(int interfaceId, int chipSelectId);
Teardown();
```
4.1. Set the whole strip to a solid color: `SetSolid(struct ColorWithBrightness color, int length);`

4.2. Set the whole strip to custom colors: `SetCustom(struct ColorWithBrightness *color, int length);`

4.3. Stream colors to the leds, from the first to the last:
```c
PrepareForStreaming();
while(?)
{
  AppendColor(struct ColorWithBrightness color);
}
FinishStreaming();
```

# Buttons Library for Arduino boards

This library provides an easy way to use buttons on Arduino Boards.

## Add it to your Arduino IDE

- clone the repo somewhere (but not in your sketch's parent folder);
- add the library in the Arduino IDE

Once it is there, it will be copied in your Arduino lib folder, and you can use it in your sketches.

## How to use it

### Button.h (On / off switch)

Button.h provides a simple on off switch. It works with the buttons provided in the Arduino Starter kit.

The button will start as "off", then each press will toggle its state on and off. You can then pass a callback which will be invoked when the button is pressed.

```cpp
#include "Button.h"

const uint8_t switchPin = 2;
const uint8_t letPin = 3;
const bool debug = true;

// create the button by passing the digital pin number you want to use for the button. Debug flag is optional

Button switch(switchPin, debug);

void setup()
{
  if (debug)
  {
    // if you set the debug flag to true, remember to start a serial session
    Serial.begin(9600);
  }

  // no need to initialize the button pin here

  pinMode(ledPin, OUTPUT);
}

void switchPressed(uint8_t pin, bool on)
{
  // this callback will be triggered when the switch is pressed
  // with the pin number and whether it's on or off
  digitalWrite(ledPin, on ? HIGH : LOW);
}

void loop()
{
  // simply use the button and pass the callback to invoke
  // when the switch is pressed
  switch.use(switchPressed);
}

```

### SerialButtons.h

SerialButtons.h provides a way to have multiple buttons connected to a single analog pin. Typically, the buttons will be connected in series, and each wired through a resistance with increasing value, so that each button pressed will yield a different analog value.

```cpp
#include "SerialButtons.h"

const uint8_t buttonsPin = A0;
const ledPins[4] = {2, 3, 4, 5};
const bool debug = true;

// create the buttons by passing the analog pin number you want to use for the button. debug flag is optional

SerialButtons buttons(buttonsPin, debug);

void setup()
{
  if (debug)
  {
    // if you set the debug flag to true, remember to start a serial session
    Serial.begin(9600);
  }

  // no need to initialize the buttons pin here

  for (int i = 0; i <= 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void buttonPressed(uint16_t value)
{
  // typically here we'd keep an array of values matching the resistance
  // of each button in the setup, and compare with the value received
  // to know which button was pressed. Here we have typically no
  // resistance on the first button, then 4.7 kΩ, 10 kΩ and 10 MΩ;


  uint16_t buttonValues[] = { 1000, 600, 400, 4};

  if (value >= buttonValues[0])
  {
    digitalWrite(ledPin[0], HIGH);
  }
  else if (value >= buttonValues[1])
  {
    digitalWrite(ledPin[1], HIGH);
  }

  // etc...

}

void loop()
{
  // simply use the button. it will invoke the callback with the value received on the analog pin
  buttons.use(buttonPressed);
}

```

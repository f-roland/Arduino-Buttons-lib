/*
  SerialButtons.h - Handler for Serial buttons on Arduino boards.
  Created by F. Roland, July 2020
*/

#include "Arduino.h"
#include "SerialButtons.h"

/**
 * Creates the buttons
 * 
 * @param uint8_t arduino analog pin to use for the buttons
 */
SerialButtons::SerialButtons(uint8_t pin)
{
  _debug = false;
  _init(pin);
}

/**
 * Creates the buttons
 * 
 * @param uint8_t arduino analog pin to use for the buttons
 * 
 * @param bool debug flag to toggle messages to the arduino Serial Monitor
 * when one of the buttons is pressed
 */
SerialButtons::SerialButtons(uint8_t pin, bool debug)
{
  _debug = debug;
  _init(pin);
}

/**
 * private initializer - sets initial time, debounce value and registers the pin
 * 
 * @param uint8_t analog pin to use for the button
 */
void SerialButtons::_init(uint8_t pin)
{
  _pin = pin;
  _previousButtonValue = 0;
  _debounce = 200;
  pinMode(_pin, INPUT);
  _time = millis();

  if (_debug)
  {
    Serial.print("Setting up serial buttons on pin ");
    Serial.println(_pin);
  }
}

/**
 * public method to call in your sketch's loop method. will read the value
 * on the analog pin, and invoke the provided callback if it is different
 * than the previous value and doesn't happen within the debounce time.
 * 
 * @param buttonPressedCallback callback invoked when a button is pressed, invoked
 * with the value read from the analog pin
 */
void SerialButtons::use(buttonPressedCallback serialButtonPressed)
{
  const int val = analogRead(_pin);

  if (val != _previousButtonValue && millis() - _time >= _debounce)
  {
    if (_debug)
    {
      Serial.print("Serial button pressed with value ");
      Serial.println(val);
    }

    serialButtonPressed(val);
    _previousButtonValue = val;
    _time = millis();
  }
}
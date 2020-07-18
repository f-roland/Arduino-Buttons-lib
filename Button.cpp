/*
  Button.cpp - On / Off switch button for Arduino boards.
  Created by F. Roland, July 2020
*/

#include "Arduino.h"
#include "Button.h"

/**
 * Creates a button
 * 
 * @param uint8_t arduino digital pin to use for the button
 */
Button::Button(uint8_t pin)
{
  _debug = false;
  _init(pin);
}

/**
 * Creates a button
 * 
 * @param uint8_t arduino digital pin to use for the button
 * 
 * @param bool debug flag to toggle messages to the arduino Serial Monitor
 * when the button is pressed
 * 
 * @overload
 */
Button::Button(uint8_t pin, bool debug)
{
  _debug = debug;
  _init(pin);
}

/**
 * private initializer - sets initial time, debounce value and registers the pin
 * 
 * @param uint8_t digital pin to use for the button
 */
void Button::_init(uint8_t pin)
{
  _time = millis();
  _debounce = 200;
  _on = false;
  _prevState = LOW;

  _pin = pin;
  pinMode(_pin, INPUT);

  if (_debug)
  {
    Serial.print("Setting up button on pin: ");
    Serial.println(_pin);
  }
}

/**
 * tells whether the button has changed state. this function is debounce to avoid
 * having consecutive triggers
 * 
 * @param uint8_t state of the button read from the input pin
 * 
 * @returns true if state has changed, false otherwise
 */
bool Button::_stateHasChanged(uint8_t state)
{
  return state == HIGH && _prevState == LOW && millis() - _time > _debounce;
}

/**
 * public method to call in your sketch's loop method. will read the value on the digital pin
 * of the button and invoke a callback with its on / off status if it has changed
 * 
 * @param switchPressedCallback callback invoked when the switch has changed state,
 * invoked with the pin called, and the on / off state
 */
void Button::use(switchPressedCallback switchPressed)
{
  uint8_t state = digitalRead(_pin);

  if (_stateHasChanged(state))
  {
    _on = !_on;
    _time = millis();

    if (_debug)
    {
      Serial.print("button ");
      Serial.print(_pin);
      Serial.println(" was pressed and its state has changed");
      Serial.print("Invoking callback with state: ");
      Serial.println(_on);
    }

    switchPressed(_pin, _on);
  }

  _prevState = state;
}

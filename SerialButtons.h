/*
  SerialButtons.h - Handler for Serial buttons on Arduino boards.
  Created by F. Roland, July 2020
*/

#ifndef SerialButtons_h
#define SerialButtons_h

#include "Arduino.h"

typedef void (*buttonPressedCallback)(uint16_t button);

/**
 * Powers a series of buttons wired in parallel with a resistance
 * scale to trigger each individual button
 */
class SerialButtons
{
public:
  SerialButtons(uint8_t pin);
  SerialButtons(uint8_t pin, bool debug);
  void use(buttonPressedCallback serialButtonPressed);

private:
  void _init(uint8_t pin);
  bool _debug;
  uint8_t _pin;
  uint16_t _previousButtonValue;
  long _time;
  uint8_t _debounce;
};

#endif

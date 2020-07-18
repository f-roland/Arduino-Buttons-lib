/*
  Button.h - On / Off switch button for Arduino boards.
  Created by F. Roland, July 2020
*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"

typedef void (*switchPressedCallback)(uint8_t pin, bool on);

/**
 * On / Off switch button
 */
class Button
{
public:
  Button(uint8_t pin);
  Button(uint8_t pin, bool debug);
  bool isOn() { return _on; };
  void use(switchPressedCallback switchPressed);

private:
  void _init(uint8_t pin);
  bool _stateHasChanged(uint8_t state);
  bool _debug;
  uint8_t _pin;
  uint8_t _debounce;
  long _time;
  bool _on;
  uint8_t _prevState;
};

#endif
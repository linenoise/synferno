#include "Button.h"

void Button::begin(byte pin, boolean pressedValue) {

  this->pin = pin;
  this->pressedValue = pressedValue;

  pinMode(pin, INPUT_PULLUP);

  this->update();
}

boolean Button::update() {
 
  // there's no good reason to sample more than 1/ms.  Nyquist frequency, etc.
  static Metro updateInterval(1UL);
  if( ! updateInterval.check() ) return( false );
  updateInterval.reset();

  boolean newState = ( digitalRead(pin) == this->pressedValue );

  if( newState != this->currentState ) {
    this->currentState = newState;
    return( true );
  } else {
    return( false );
  }
}

byte Button::getState() {
  return( this->currentState );
}


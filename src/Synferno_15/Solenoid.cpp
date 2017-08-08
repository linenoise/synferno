#include "Solenoid.h"

void Solenoid::begin(byte pin, boolean fireValue) {
  this->pin = pin;
  this->fireValue = fireValue;

  // order is important here.
  this->off();
  pinMode(pin, OUTPUT);
}

boolean Solenoid::update() {
  if( this->state != this->lastState ) {
    this->lastState = this->state;
    return( true );
  }
  return( false );
}

boolean Solenoid::getState() {
  return( this->state );
}

void Solenoid::on() {
  // we cannot actuate the solenoid until the lockout is done.
  if( millis() < lockoutTime ) return;

  // only impose the lockout if we're changing solenoid states.
  if( this->state != true ) {
    // we've asked for the solenoid to change states, so lockout any actuation request until that happens.
    lockoutTime = millis() + MIN_ON_TIME;
  }
  
  // pro-tip; code that triggers a 1M BTU flamethrower should appear once and be shrouded in all manner of care and caution.
  this->state = true;
  digitalWrite(this->pin, this->fireValue);
}

void Solenoid::off() {
  // we cannot actuate the solenoid until the lockout is done.
  if( millis() < lockoutTime ) return;

  // only impose the lockout if we're changing solenoid states.
  if( this->state != false ) {
    // we've asked for the solenoid to change states, so lockout any actuation request until that happens.
    lockoutTime = millis() + MIN_OFF_TIME;
  }
  
  this->state = false;
  digitalWrite(this->pin, ! this->fireValue);  
}


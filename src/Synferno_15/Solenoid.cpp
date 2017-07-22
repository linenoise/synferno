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
  this->state = true;
  digitalWrite(this->pin, this->fireValue);
}
void Solenoid::off() {
  this->state = false;
  digitalWrite(this->pin, ! this->fireValue);
}


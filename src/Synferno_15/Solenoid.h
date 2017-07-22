#ifndef Solenoid_h
#define Solenoid_h

#include <Arduino.h>

#define SOLENOID_PIN1 4
#define SOLENOID_PIN2 5

class Solenoid{
  public:
    void begin(byte pin, boolean fireValue=HIGH);

    boolean update();
    
    boolean getState();
    
    void on();
    void off();

  private:
    byte pin;
    boolean fireValue, state, lastState;
};

#endif

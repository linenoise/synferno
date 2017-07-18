#ifndef Solenoid_h
#define Solenoid_h

#include <Arduino.h>

#define SOLENOID_PIN1 2
#define SOLENOID_PIN2 3
#define SOLENOID_PIN3 4
#define SOLENOID_PIN4 5

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

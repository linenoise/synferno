#ifndef Solenoid_h
#define Solenoid_h

#include <Arduino.h>

#define SOLENOID_PIN1 4
#define SOLENOID_PIN2 5

/* 
 * When the solenoid (an inductor) is powered up, it pulls significantly more (3x?) amperage than the
 * steady-state amperage.  Likewise, when turned off, the inductor will generate power from the magnetic
 * field collapse event.  Thus, if you turn off the solenoid mid-powerup, you'll end up with a weird
 * electrical and physical state.  A partially open solenoid will yield abberant firing.  
 * 
 * Thus, we impose a cap on the duty cycle keeping with the hardware limit.  
 */
// hardware limits; software calls to Solenoid class outside these bounds will be ignored, silently.
#define MIN_ON_TIME 50UL
#define MIN_OFF_TIME 150UL

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

    unsigned long lockoutTime;
};

#endif

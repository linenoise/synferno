#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>

#include <Metro.h>

#define POT_PIN1 A0 // A0, specifically
#define POT_PIN2 A1
#define POT_PIN3 A2
#define POT_PIN4 A3

// ~2230 updates per second with FASTADC 0
// ~6220 updates per second with FASTADC 1
// See: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1208715493/11
#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

class Potentiometer{
  public:
    void begin(byte pin, byte sectors=0, word minimum=0, word maximum=1023, byte smoothing=10);

    boolean update();

    word getValue();
    byte getSector();

  private:
    byte pin, smoothing, sectors;
    word maximum, minimum;

    unsigned long currentValue;
    byte currentSector;
};

#endif

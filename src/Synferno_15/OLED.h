#ifndef OLED_h
#define OLED_h

#include <Arduino.h>

#include <U8x8lib.h>

class OLED{
  public:
    void begin();

    String buffer;
    void write(byte row, byte col=0, boolean pad=false);

  private:
  
};

#endif

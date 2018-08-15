#ifndef MIDI_h
#define MIDI_h

#include <Arduino.h>

#include <SoftwareSerial.h>
#include <Metro.h>

// pins
#define MIDI_RX_PIN 10
#define MIDI_TX_PIN 11

// Relevant MIDI messages
#define MIDI_CLOCK 248
#define MIDI_START 250
#define MIDI_CONTINUE 251
#define MIDI_STOP 252

#define MIDI_CLOCKS_PER_BEAT 24

#define FREQUENCY_SECTORS 5   // number of frequency options (keep odd so knob at 12:00 means default)
#define FREQUENCY_DEVIATION 4 // multiplier (for max) and divisor (for min) of beats per poof (must be 1 through 10)

#define SIMULATE_MIDI 0
#define SIMULATE_BPM 120.0

class MIDI{
  public:
    void begin();

    boolean update(); // process MIDI messages.

    byte getCounter(); // 0-23 ticks

    void resetCounter(); // set counter back to 0

    unsigned long tickLength(); // length of ticks, uS
    unsigned long beatLength();  // length of 24 ticks (one beat), ms
    
  private:
    byte clockCounter;

    unsigned long tickDuration, beatDuration;
    
    void processTick();
};

#endif

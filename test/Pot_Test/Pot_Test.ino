// Compile for Arduino Nano

#include <Streaming.h>
#include <Metro.h>

// Potentiometers
#include "Potentiometer.h"
Potentiometer duration, offset, frequency, options;

#define FREQUENCY_SECTORS 5   // number of frequency options (keep odd so knob at 12:00 means default)
#define FREQUENCY_DEVIATION 4 // multiplier (for max) and divisor (for min) of beats per poof (must be 1 through 10)

#define MIDI_CLOCKS_PER_BEAT 24 // from

#define NUM_OPTIONS 6

void setup() {
  Serial.begin(115200);

  // knobs
  duration.begin(POT_PIN1, MIDI_CLOCKS_PER_BEAT, 20000);
  frequency.begin(POT_PIN3, FREQUENCY_SECTORS, 50000);
  offset.begin(POT_PIN4, MIDI_CLOCKS_PER_BEAT, 50000);
  options.begin(POT_PIN2, NUM_OPTIONS, 10000);

}

void loop() {

  duration.update();
  frequency.update();
  offset.update();
  options.update();

  static Metro printEvery(50UL);
  const byte showMe = 0;
  if ( printEvery.check() ) {
    switch( showMe ) {
      case 0:
        Serial << F("Duration.") << F(" val: ") << duration.getValue() << F(" sec: ") << duration.getSector() << F(" val: ") << analogRead(POT_PIN1) << endl;
        break;
      case 1:
        Serial << F("Frequency.") << F(" val: ") << frequency.getValue() << F(" sec: ") << frequency.getSector() << F(" val: ") << analogRead(POT_PIN3) << endl;
        break;
      case 2:
        Serial << F("Offset.") << F(" val: ") << offset.getValue() << F(" sec: ") << offset.getSector() << F(" val: ") << analogRead(POT_PIN4) << endl;
        break;
      case 3:
        Serial << F("Unused.") << F(" val: ") << options.getValue() << F(" sec: ") << options.getSector() << F(" val: ") << analogRead(POT_PIN2) << endl;
        break;    
    }

    printEvery.reset();
  }

}


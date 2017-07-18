#include "MIDI.h"
#include <Streaming.h>

// MIDI buffer and counter
SoftwareSerial MIDISerial(MIDI_RX_PIN, MIDI_TX_PIN);

void MIDI::begin() {
  // give MIDI-device a short time to "digest" MIDI messages
  MIDISerial.begin(31250);
  delay(100);

  clockCounter = 255; // no MIDI signal; we're "off the clock".
}

boolean MIDI::update() {
  // in case the midi drops out
  static Metro timeoutMIDI(1000UL);
  
  if (MIDISerial.available() > 0) {

    byte midiByte = MIDISerial.read();
    byte midiChannel = midiByte & B00001111;
    byte midiCommand = midiByte & B11110000;

    // We get 24 clock ticks per beat.
    if (midiByte == MIDI_CLOCK) {
      clockCounter = (clockCounter+1) % MIDI_CLOCKS_PER_BEAT;
      timeoutMIDI.reset();

      return ( true );
    }
  }
  
  if( SIMULATE_MIDI ) {
    const float beatEvery = 60.0*1000.0/MIDI_CLOCKS_PER_BEAT/SIMULATE_BPM; // ms/tick
    static Metro clockEvery(beatEvery);
    if( clockEvery.check() ) {
      clockEvery.reset();

      clockCounter = (clockCounter+1) % MIDI_CLOCKS_PER_BEAT;
      timeoutMIDI.reset();
      
      return( true );
    }
  } 

  if( timeoutMIDI.check() ) clockCounter = 255; // loss of signal

  return ( false );
}

byte MIDI::getCounter() { 
  return( clockCounter );
}



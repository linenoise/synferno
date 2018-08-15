#include "MIDI.h"
#include <Streaming.h>

// MIDI buffer and counter
SoftwareSerial MIDISerial(MIDI_RX_PIN, MIDI_TX_PIN);

void MIDI::begin() {
  // give MIDI-device a short time to "digest" MIDI messages
  MIDISerial.begin(31250);
  delay(100);

  clockCounter = 255; // no MIDI signal; we're "off the clock".
  tickDuration = 20833; // us, 120 bpm
  beatDuration = 500; // ms, 120 bpm
}

boolean MIDI::update() {
  // in case the midi drops out
  static Metro timeoutMIDI(1000UL);

  if (MIDISerial.available() > 0) {

    byte midiByte = MIDISerial.read();
//    byte midiChannel = midiByte & B00001111;
//    byte midiCommand = midiByte & B11110000;

    // We get 24 clock ticks per beat.
    if (midiByte == MIDI_CLOCK) {
      timeoutMIDI.reset();
      processTick();
      return ( true );
    }
  }

  if ( SIMULATE_MIDI ) {
    const float beatEvery = 60.0 * 1000.0 / MIDI_CLOCKS_PER_BEAT / SIMULATE_BPM; // ms/tick
    static Metro clockEvery(beatEvery);
    if ( clockEvery.check() ) {
      clockEvery.reset();

      timeoutMIDI.reset();
      processTick();

      return ( true );
    }
  }

  if ( timeoutMIDI.check() ) clockCounter = 255; // loss of signal

  return ( false );
}

byte MIDI::getCounter() {
  return ( clockCounter );
}

void MIDI::resetCounter() {
  clockCounter = 0;
}

void MIDI::processTick() {
  // increment the clock
  clockCounter = (clockCounter + 1) % MIDI_CLOCKS_PER_BEAT;

  // time the ticks
  static unsigned long lastTick = micros();
  unsigned long thisTick = micros();
  unsigned long deltaTick = thisTick - lastTick;
  lastTick = thisTick;

  // apply exponential smoothing, in case we miss a tick
  const word smoothTick = 100;
  tickDuration = (tickDuration*(smoothTick-1) + deltaTick)/smoothTick;

  // time the beats
  if( clockCounter==0 ) {
    // time the beats
    static unsigned long lastBeat = millis();
    unsigned long thisBeat = millis();
    unsigned long deltaBeat = thisBeat - lastBeat;
    lastBeat = thisBeat;
    
    // apply exponential smoothing, in case we miss a tick
    const word smoothBeat = 20;
    beatDuration = (beatDuration*(smoothBeat-1) + deltaBeat)/smoothBeat;

  }
}

unsigned long MIDI::tickLength() {
  // length of ticks, uS
  return( this->tickDuration );
}
unsigned long MIDI::beatLength() {
  // length of 24 ticks (one beat), ms
  return( this->beatDuration );
}



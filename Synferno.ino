// -----------------------------------------------------------------------------
// Synferno.ino
//
// Controls flame effects through MIDI
//
// Danne Stayskal <danne@stayskal.com>
// -----------------------------------------------------------------------------

#include "Synferno.h"

// MIDI buffer and counter
SoftwareSerial mySerial(MIDI_RX_PIN, MIDI_TX_PIN);
unsigned clockCounter = 0;
byte midiByte;
byte midiChannel;
byte midiCommand;

// Input buffers
bool armed = false;            // Arming Switch
bool fire = false;             // Whether we're currently triggering fire
int calibration_delay = 0;     // Calibration (knob) pot
int fire_duration = 0;         // Duration (slider) pot
unsigned int fire_on_at = 0;   // Which of the 24 pulses per beat we turn on at
unsigned int fire_off_at = 0;  // Which of the 24 pulses per beat we turn off at


// -----------------------------------------------------------------------------
// syncInterfaces() runs once per loop to pull interface values into buffers
//   so we're not calling read functions every time we need to know a thing
// -----------------------------------------------------------------------------

void syncInterfaces() {
  
  // Check to see whether the arming switch is engaged (HIGH or LOW)
  if (digitalRead(ARMING_SWITCH_PIN) == HIGH) {
    armed = true;
    digitalWrite(ARM_LED_PIN, HIGH);
  } else {
    armed = false;
    digitalWrite(ARM_LED_PIN, LOW);   
  }

  // Are we currently making fire?
  if (fire) {
    digitalWrite(FIRE_LED_PIN, HIGH);
    digitalWrite(FIRE_RELAY_PIN, HIGH);
  } else {
    digitalWrite(FIRE_LED_PIN, LOW);
    digitalWrite(FIRE_RELAY_PIN, LOW);
  }

  // Get our current calibration value (0..24)
  calibration_delay = (int) (analogRead(CALIBRATION_POT_PIN) / 45);

  // Get our current flame duration (0..24)
  fire_duration = (int) (analogRead(DURATION_POT_PIN) / 45);

  // Figure out when during a 24-count beat cycle we turn the flame on and off
  fire_on_at = 24 - calibration_delay;
  if (fire_on_at == 24){
    fire_on_at = 0;
  }
  fire_off_at = fire_on_at + fire_duration;
  if (fire_off_at > 24){
    fire_off_at = fire_off_at - 24;  
  }
}


// -----------------------------------------------------------------------------
// processMidi() takes MIDI input, syncs, and calibrates the system
// -----------------------------------------------------------------------------

void processMidi() {
  if (mySerial.available() > 0) {

    midiByte = mySerial.read();
    midiChannel = midiByte & B00001111;
    midiCommand = midiByte & B11110000;
    
    // We get 24 clock ticks per beat. 
    if (midiByte == MIDI_CLOCK) {
      if (clockCounter <= 22) {
        clockCounter = clockCounter + 1;
      } else {
        clockCounter = 0;
      }
    }

    // When we're on a beat. Blink.
    if (clockCounter == 0) {
      digitalWrite(SYNC_LED_PIN, HIGH);
    }
    if (clockCounter == 1) {
      digitalWrite(SYNC_LED_PIN, LOW);
    }

    // If we're making fire, do that thing.
    if (armed) {
      if (clockCounter == fire_on_at) {
        fire = true;
      }
      if (clockCounter == fire_off_at) {
        fire = false;
      }
    } else {
      fire = false;
    }
  }
}


// -----------------------------------------------------------------------------
// setup() prepares the console for operation
// -----------------------------------------------------------------------------

void setup() {

    // Initialize the Sync LED
    pinMode(SYNC_LED_PIN, OUTPUT);
    digitalWrite(SYNC_LED_PIN, LOW);
    digitalWrite(SYNC_LED_PIN, HIGH);
    delay(50);
    digitalWrite(SYNC_LED_PIN, LOW);
    delay(50);
    
    // Initialize the Arm LED
    pinMode(ARM_LED_PIN, OUTPUT);
    digitalWrite(ARM_LED_PIN, LOW);
    digitalWrite(ARM_LED_PIN, HIGH);
    delay(50);
    digitalWrite(ARM_LED_PIN, LOW);
    delay(50);

    // Initialize the Fire LED
    pinMode(FIRE_LED_PIN, OUTPUT);
    digitalWrite(FIRE_LED_PIN, LOW);
    digitalWrite(FIRE_LED_PIN, HIGH);
    delay(50);
    digitalWrite(FIRE_LED_PIN, LOW);
    delay(50);

    // Initialize the arming switch and fire channels
    pinMode(ARMING_SWITCH_PIN, INPUT);
    pinMode(FIRE_RELAY_PIN, OUTPUT);

    // give MIDI-device a short time to "digest" MIDI messages
    mySerial.begin(31250);
    delay(100);
    
    Serial.begin(115200);
}


// -----------------------------------------------------------------------------
// loop() runs indefinitely until power is removed from the Arduino
// -----------------------------------------------------------------------------

void loop() {
  syncInterfaces();
  processMidi();
}

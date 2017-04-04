// -----------------------------------------------------------------------------
// Synferno.ino
//
// Controls flame effects through MIDI
//
// Danne Stayskal <danne@stayskal.com>
// -----------------------------------------------------------------------------

#include <MIDI.h>
#include "TimerOne.h"

// Digital output pin mappings
#define SYNC_LED_PIN 2
#define ARM_LED_PIN 3
#define FIRE_LED_PIN 4
#define FIRE_LEFT_CHANNEL_PIN 5
#define FIRE_RIGHT_CHANNEL_PIN 5

// Digital input pin mappings
#define ARMING_SWITCH_PIN 7
#define MANUAL_FIRE_SWITCH_PIN 8
#define KEY_LOCK_PIN 9

// Analog pin mappings
#define CALIBRATION_POT_PIN 0
#define DURATION_POT_PIN 1

// MIDI buffer and counter
unsigned clockCounter = 0;
byte inputByte = 0;
bool inputSynced = false;

// Input buffers
bool enabled = false;          // Key Lock
bool armed = false;            // Arming Switch
bool manually_firing = false;  // Big Red Button
int calibration_delay = 0;    // Calibration (knob) pot
int fire_duration = 0;        // Duration (slider) pot

// Time synchronization
unsigned long this_beat_millis = 0;
unsigned long last_beat_millis = 0;
unsigned int inter_beat_period = 0;
unsigned int total_delay = 0;

MIDI_CREATE_DEFAULT_INSTANCE(HardwareSerial, Serial1, MIDI);


// -----------------------------------------------------------------------------
// syncInterfaces() runs once per loop to pull interface values into buffers
//   so we're not calling read functions every time we need to know a thing
// -----------------------------------------------------------------------------

void syncInterfaces() {
	
	// Check to see whether the key lock is engaged (HIGH or LOW)
	if (digitalRead(KEY_LOCK_PIN) == HIGH) {
		enabled = true;
	} else {
		enabled = false;
	}

	// Check to see whether the arming switch is engaged (HIGH or LOW)
	if (digitalRead(ARMING_SWITCH_PIN) == HIGH) {
		armed = true;
	} else {
		armed = false;
	}

	// Check to see whether we're manually firing (HIGH or LOW)
	if (digitalRead(MANUAL_FIRE_SWITCH_PIN) == HIGH) {
		manually_firing = true;
	} else {
		manually_firing = false;
	}

	// Get our current calibration value (0..1023)
	calibration_delay = analogRead(CALIBRATION_POT_PIN);

	// Get our current flame duration (0..1023)
	fire_duration = analogRead(DURATION_POT_PIN) / 2;
	
}


// -----------------------------------------------------------------------------
// processMidi() takes MIDI input, syncs, and calibrates the system
// -----------------------------------------------------------------------------

void processMidi() {
    if (MIDI.read()) {
		inputByte = MIDI.getType();

		// Sync to the downbeat when the DJ starts or continues
        if ((inputByte == midi::Start) || (inputByte == midi::Continue)) {
			clockCounter = 0;
			Timer1.resume();
			inputSynced = true;
			digitalWrite(SYNC_LED_PIN, HIGH);
		}

		// Stop when the DJ stops
        if (inputByte == midi::Stop) {
			Timer1.stop();
			inputSynced = false;
			digitalWrite(SYNC_LED_PIN, LOW);
		}
		
		// We get 24 clock ticks per beat. Wait for it...
        if (inputByte == midi::Clock) {
			if (clockCounter < 24) {
				clockCounter = clockCounter + 1;
			} else {
				clockCounter = 0;
			}
        }

		// When we're on a beat, calculate our period based on millis since the last beat
		if (inputSynced == true && clockCounter == 0) {
			this_beat_millis = millis();
			if(last_beat_millis > 0){
				inter_beat_period = this_beat_millis - last_beat_millis;
				total_delay = inter_beat_period - calibration_delay;
				Timer1.setPeriod(inter_beat_period);
				Timer1.restart();
			}
			last_beat_millis = this_beat_millis;
		}
    }
}


// -----------------------------------------------------------------------------
// fireControl() runs once per beat through Timer1
// -----------------------------------------------------------------------------

void fireControl() {
	if ((enabled == true) && (armed == true)) {
		digitalWrite(FIRE_LED_PIN, HIGH);
		digitalWrite(FIRE_LEFT_CHANNEL_PIN, HIGH);
		digitalWrite(FIRE_RIGHT_CHANNEL_PIN, HIGH);
		delay(fire_duration); // DIRTY DIRTY BLOCKING HACK FIXME
		digitalWrite(FIRE_LED_PIN, LOW);
		digitalWrite(FIRE_LEFT_CHANNEL_PIN, LOW);
		digitalWrite(FIRE_RIGHT_CHANNEL_PIN, LOW);
	}
}


// -----------------------------------------------------------------------------
// processManualFire() will run the poofers if the system is NOT armed but 
//   the manual fire button is pressed. Either or, not both.
// -----------------------------------------------------------------------------

void processManualFire() {
	if ((enabled == true) && (armed == false)){
		if(manually_firing == true) {
			digitalWrite(FIRE_LED_PIN, HIGH);
			digitalWrite(FIRE_LEFT_CHANNEL_PIN, HIGH);
			digitalWrite(FIRE_RIGHT_CHANNEL_PIN, HIGH);
		} else {
			digitalWrite(FIRE_LED_PIN, LOW);
			digitalWrite(FIRE_LEFT_CHANNEL_PIN, LOW);
			digitalWrite(FIRE_RIGHT_CHANNEL_PIN, LOW);
		}
	}
}


// -----------------------------------------------------------------------------
// setup() prepares the console for operation
// -----------------------------------------------------------------------------

void setup() {
    pinMode(SYNC_LED_PIN, OUTPUT);
    pinMode(ARM_LED_PIN, OUTPUT);
    pinMode(FIRE_LED_PIN, OUTPUT);
    pinMode(FIRE_LEFT_CHANNEL_PIN, OUTPUT);
    pinMode(FIRE_RIGHT_CHANNEL_PIN, OUTPUT);

    pinMode(ARMING_SWITCH_PIN, INPUT);
    pinMode(MANUAL_FIRE_SWITCH_PIN, INPUT);
	pinMode(KEY_LOCK_PIN, INPUT);

	Timer1.initialize();
	Timer1.attachInterrupt(fireControl);
    MIDI.begin();
}


// -----------------------------------------------------------------------------
// loop() runs indefinitely until power is removed from the Arduino
// -----------------------------------------------------------------------------

void loop() {
	syncInterfaces();
	processMidi();
	processManualFire();
}



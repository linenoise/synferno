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
bool inputSynced = false;
const int midiSendDelay = 100; // give MIDI-device a short time to "digest" MIDI messages
byte midiByte;
byte midiChannel;
byte midiCommand;

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
		digitalWrite(ARM_LED_PIN, HIGH);		
	} else {
		armed = false;
		digitalWrite(ARM_LED_PIN, LOW);		
	}

	// Check to see whether we're manually firing (HIGH or LOW)
	if (digitalRead(MANUAL_FIRE_SWITCH_PIN) == HIGH) {
		manually_firing = true;
		digitalWrite(FIRE_LED_PIN, HIGH);		
	} else {
		manually_firing = false;
		digitalWrite(FIRE_LED_PIN, LOW);		
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
    if (mySerial.available() > 0) {

    midiByte = mySerial.read();
    midiChannel = midiByte & B00001111;
    midiCommand = midiByte & B11110000;

		// Sync to the downbeat when the DJ starts or continues
    if ((midiByte == MIDI_START) || (midiByte == MIDI_CONTINUE)) {
			clockCounter = 0;
			Timer1.resume();
			inputSynced = true;
			digitalWrite(SYNC_LED_PIN, HIGH);
		}

		// Stop when the DJ stops
    if (midiByte == MIDI_STOP) {
			Timer1.stop();
			inputSynced = false;
			digitalWrite(SYNC_LED_PIN, LOW);
		}
		
		// We get 24 clock ticks per beat. Wait for it...
        if (midiByte == MIDI_CLOCK) {
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

    mySerial.begin(31250);
    delay(midiSendDelay);
}


// -----------------------------------------------------------------------------
// loop() runs indefinitely until power is removed from the Arduino
// -----------------------------------------------------------------------------

void loop() {
	syncInterfaces();
	processMidi();
	processManualFire();
}



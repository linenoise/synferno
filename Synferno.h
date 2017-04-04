// -----------------------------------------------------------------------------
// Synferno.h
//
// Header for Synferno MIDI-to-Flame-Effect bridge
//
// Danne Stayskal <danne@stayskal.com>
// -----------------------------------------------------------------------------

#ifndef Synferno_h
#define Synferno_h

#include <SoftwareSerial.h>
#include "TimerOne.h"

// Relevant MIDI messages
#define MIDI_CLOCK 248
#define MIDI_START 250
#define MIDI_CONTINUE 251
#define MIDI_STOP 252

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
#define MIDI_RX_PIN 10
#define MIDI_TX_PIN 11

// Analog pin mappings
#define CALIBRATION_POT_PIN 0
#define DURATION_POT_PIN 1


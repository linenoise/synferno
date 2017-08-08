# Synferno

This codebase contains the software and hardware designs that allow Tautology's flame effects to be controlled by MIDI devices. Synferno is an group of flame effects that are sequenced, synchronized, and controlled by DJs and other electronic musicians. Beats and heats.

A synferno system consists of a console and one or more flame effects. The default configuration has one flame effect each on the right and left channels. Each flame effect has a pass-through SpeakOn port, which allows for multiple flame effects to be connected in series on stage left and stage right.

# Console

The synferno console is the device that sits in the DJ booth and allows the performer to synchronize her hardware to the flame effects.

## Console Physical Layout

The back of the console has six interface components:

* One DIN-5 MIDI input port
* One knob potentiometer for calibration
* One rocker-style power switch
* One IEC power socket
* Two SpeakOn connectors to drive the flame effects

The top of the console has ten interface components:

* One blue LED indicating power supply status
* One green LED indicating microcontroller status
* One yellow LED indicating MIDI synchronization status
* One orange LED indicating controller arming status
* One red LED indicating fire control signal status
* One rotary potentiometer to set poof frequency
* One slide potentiometer to set flame duration
* One key-lock switch to ensure user is permitted to run console
* One arming switch to ensure user wants to run console
* One big red button to initiate manual fire control signalling

![Synferno Console Interface Layout](https://raw.githubusercontent.com/linenoise/synferno/master/docs/diagrams/Synferno%20Console%20Interface%20Layout.png)

## Console Block Diagram

![Synferno Block Diagram](https://github.com/linenoise/synferno/blob/master/docs/diagrams/Synferno%20Block%20Diagram.png)

## Console Bill of Materials

The following parts are required to build the Synferno console.

| Subsystem | Quantity | Item | Part |
|-----------|----------|------|------|
| Interface | 1x       | Console Enclosure | [Sloped Console Enclosure](http://www.mouser.com/ProductDetail/Hammond-Manufacturing/1456PH1WHBU/?qs=sGAEpiMZZMsrGrAVj6eTve6SRaySZpuD%2fmsbes6t2eY%3d) |
| Interface | 1x       | Arming Toggle Switch | [Toggle Switch 631H-2](http://www.mouser.com/Search/ProductDetail.aspx?qs=%2fs1LKTamv0xq52nnIMvCmA%3d%3d) |
| Interface | 1x       | Arming Toggle Switch Cover | [Toggle Switch Cover GT-4R](http://www.mouser.com/ProductDetail/CW-Industries/GT-4R/?qs=sGAEpiMZZMtQ1ytNl72Bk4W6RQFxQU1iz3A6OXxfbKA%3d) |
| Interface | 1x       | Manual Fire Switch | [Sparkfun Big Red Button](https://www.sparkfun.com/products/9181) |
| Interface | 1x       | Duration Slider | [Slide Potentiometer PTF01-151A-203B2](http://www.mouser.com/search/ProductDetail.aspx?R=0virtualkey0virtualkeyPTF01-151A-203B2) |
| Interface | 1x       | Duration Slider Cap | [Slide Control B/W](http://www.mouser.com/ProductDetail/Eagle-Plastic-Devices/450-SL2612/) |
| Interface | 1x       | Calibration Knob | [Knob Potentiometer](http://www.mouser.com/ProductDetail/Bourns/3310Y-001-103L/?qs=sGAEpiMZZMtC25l1F4XBUzucK%2fsLA9imt%2fQ5wgh8OPI%3d) |
| Interface | 1x       | Frequency Knob | [Rotary Potentiometer](https://www.adafruit.com/product/562) |
| Interface | 1x       | Frequency Knob Cover | [Rotary Potentiometer Cover](https://www.adafruit.com/product/2046) |
| Interface | 1x       | Key Lock | [Key Lock KO128F2007](http://www.mouser.com/ProductDetail/E-Switch/KO128F2007/?qs=sGAEpiMZZMsw5ceDr7HJSDhm1FNsn9uc) |
| Power     | 1x       | Locking Power Cable | [NEMA5-15 IL13-US1-SVT-3100-183](http://www.mouser.com/ProductDetail/Schaffner/IL13-US1-SVT-3100-183/?qs=sGAEpiMZZMvXcJVS4l7FPzCKqis1WRpbesAGrSNHj1w%3d) |
| Power     | 1x       | Power Socket | [IEC Socket](http://www.mouser.com/ProductDetail/Schurter/62002300/?qs=sGAEpiMZZMvh4ezHM5rsUjbMf3rMlzcg3muYRtLA8Pw%3d) |
| Power     | 1x       | Power Switch | [Rocker Switch](http://www.mouser.com/ProductDetail/ZF/SRB22A2FBBNN/?qs=sGAEpiMZZMt%252bZbscA2DaEkUexJYfg5jP) |
| Power     | 1x       | 5v Power Supply | [5V/2A power supply](https://www.amazon.com/iMBAPrice-Adapter-Listed-Supply-5-Feet/dp/B00GUO5WUI/) |
| Power     | 1x       | 12v Power Supply | [Intocircuit LCD 60W 12V 5A Adapter](https://www.amazon.com/gp/product/B0023Y9EQC/) |
| MIDI      | 1x       | MIDI Cable | [Hosa MID-305BK 5-Pin DIN to 5-Pin DIN MIDI Cable](https://smile.amazon.com/Hosa-MID-305BK-5-Pin-MIDI-Cable/dp/B000068NTU/ref=sr_1_2?ie=UTF8&qid=1491257019&sr=8-2&keywords=MIDI+cable) |
| MIDI      | 1x       | MIDI DIN Socket | [57PC5F DIN connector](http://www.mouser.com/ProductDetail/Switchcraft/57PC5F/?qs=sGAEpiMZZMtAYTMy7wxAr0y4uKaR6FokQ9OyYICcpew%3d) |
| MIDI      | 2x       | 220 Ohm Resistor | [220 Ohm Resistor](http://www.mouser.com/ProductDetail/Ohmite/OY221KE/?qs=sGAEpiMZZMtlubZbdhIBIMnBmbYwsLxH0milUae1tMQ%3d) |
| MIDI      | 1x       | 4.7 Ohm Resistor | [4.7k Ohm Resistor](http://www.mouser.com/ProductDetail/Ohmite/OX472KE/?qs=sGAEpiMZZMsPqMdJzcrNwk%2fg3DPSHRNzqdU6hd7M%2fPE%3d) |
| MIDI      | 1x       | 1N914 Diode | [1N914 Diode](http://www.mouser.com/ProductDetail/Fairchild-Semiconductor/1N914/?qs=NSEUUqpg2uCfNuQFcxVZsA%3d%3d) |
| MIDI      | 2x       | 1N4001 Diode | [1N914 Diode](http://www.mouser.com/ProductDetail/Taiwan-Semiconductor/1N4001/?qs=sGAEpiMZZMuMAfj%252bWfX4nAIxm%252bOcj%252b2l) |
| MIDI      | 1x       | 6N138 Optocoupler | [6N138 Optocoupler](http://www.mouser.com/ProductDetail/Vishay-Semiconductors/6N138/?qs=sGAEpiMZZMtd3yBnp8bAgBFyizqDgEBJrkPNUPogu6s%3d) |
| Status    | 5x       | 1k Ohm Resistor | [1k Ohm Resistor](http://www.mouser.com/ProductDetail/Ohmite/OX102KE/?qs=sGAEpiMZZMsPqMdJzcrNwrKLa5kaGLxISs%2fpJlieb%252bA%3d) |
| Status    | 1x       | Blue Power LED | [Blue LED](https://www.radioshack.com/products/10mm-blue-led-lamp) |
| Status    | 1x       | Green Online LED | [Green LED](https://www.radioshack.com/products/radioshack-5mm-green-led) |
| Status    | 1x       | Yellow Sync LED | [Yellow LED](https://www.radioshack.com/products/5mm-yellow-led) |
| Status    | 1x       | Orange Armed LED | [Orange LED](https://www.radioshack.com/products/5mm-orance-led-1) |
| Status    | 1x       | Red Fire LED | [Red LED](https://www.radioshack.com/products/5mm-red-led-1) |
| Logic     | 1x       | Arduino Uno | [Arduino Uno](https://smile.amazon.com/Arduino-Uno-R3-Microcontroller-A000066/dp/B008GRTSV6/) |
| Logic     | 1x       | 4 Channel Relay Module | [SainSmart 20-018-901](https://www.sainsmart.com/sainsmart-4-channel-5v-solid-state-relay-module-board-omron-ssr-avr-dsp-arduino.html) |
| Logic     | 1x       | 5V Power Rail Connector Wire | [Spool Red Connector Wire](https://smile.amazon.com/GS-Powers-Power-Primary-Remote/dp/B01NCSJZWM/) |
| Logic     | 1x       | 12V Power Rail Connector Wire | [Spool Yellow Connector Wire](https://smile.amazon.com/GS-Powers-Power-Primary-Remote/dp/B01NCSJZWM/) |
| Logic     | 1x       | Ground Plane Connector Wire | [Spool Black Connector Wire](https://smile.amazon.com/GS-Powers-Power-Primary-Remote/dp/B01NCSJZWM/) |
| Logic     | 1x       | Signaling Connector Wire | [Spool Blue Connector Wire](https://smile.amazon.com/GS-Powers-Power-Primary-Remote/dp/B01NCSJZWM/) |
| Fire      | 4x       | SpeakOn Port | [NL2MP SpeakOn Port](https://www.amazon.com/Neutrik-Chassis-Speakon-Connector-NL2MP/dp/B00067JS3M/)
| Fire      | 2x       | SpeakOn Cable | [SpeakOn Cable](https://www.amazon.com/Ignite-Pro-Speakon-Gauge-Speaker/dp/B01CBC5ZE0/)

# Flame Effects

The design of the flame effects closely parallels the design of [Mike Dodds' *Amplifire* design](https://github.com/the-magister/amplifire). Please reference his codebase for hardware designs of the flame effects.

When the flame effects are being used as *Synferno* accumulators, they are connected as with any other sound system component: with locking, interference-resistant SpeakOn cables. When the flame effects are being used as *Amplifire* accumulators, they are controlled via WiFi and infrared sensors.

## Flame Effect Physical Layout

![Flame Effect Physical Layout](https://raw.githubusercontent.com/linenoise/synferno/master/docs/diagrams/accumulator_physical.png)

## Flame Effect Block Diagram

![Flame Effect Block Diagram](https://github.com/linenoise/synferno/blob/master/docs/diagrams/accumulator_diagram.png)

## Flame Effect Bill of Materials

* 55 gallon drum
* Milled steel, welding consumables
* 5 gallon propane tank
* Solenoid
* Pilot
* Regulator
* Misc plumbing
* 50’ propane line
* 2x SpeakOn NL2MP ports

# References

* [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library/)
* [Arduino MIDI Library Reference](http://arduinomidilib.fortyseveneffects.com/index.html)
* [Arduino SoftwareSerial Library](https://www.arduino.cc/en/Reference/SoftwareSerial)
* [Software Integration Example](http://libremusicproduction.com/tutorials/arduino-and-midi-in)


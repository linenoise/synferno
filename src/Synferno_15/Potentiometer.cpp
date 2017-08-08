#include "Potentiometer.h"

void Potentiometer::begin(byte pin, byte sectors, word Rpot, word Rpullup, byte smoothing) {

#if FASTADC
  // set ADC prescale to 16
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
#endif

  this->pin = pin;
  this->sectors = sectors;
  this->Rpot = Rpot;
  this->smoothing = smoothing;

  // use internal pullup resistor.
  pinMode(this->pin, INPUT_PULLUP);
  this->Rpullup = Rpullup;

  this->currentValue = 0;
  this->currentSector = 0;
}

boolean Potentiometer::update() {
  // there's no good reason to sample more than 1/ms.  Nyquist frequency, etc.
  static Metro updateInterval(1UL);
  if( ! updateInterval.check() ) return( false );
  updateInterval.reset();

  // take a reading
  word newValue = analogRead(pin);

  // update with exponential smoothing
  if ( smoothing > 0 ) {
    newValue = (currentValue * (smoothing - 1) + newValue) / smoothing;
  }
  
  // store current value
  this->currentValue = newValue;
    
  // calculate sectors
  // Vout/Vin = fr*Rpot/(Rpullup+fr*Rpot)
  // fr = Vout*Rpullup/(Rpot*(Vin-Vout))
  // sector = (sectors-1)*fr
  unsigned long num = (sectors-1) * newValue * Rpullup;
  unsigned long den = Rpot * (1024L - newValue);
  byte newSector = num/den;
  
  // is there a change in sector?
  if ( newSector != this->currentSector ) {
    this->currentSector = newSector;
    return ( true );
  } else {
    return ( false );
  }
}

word Potentiometer::getValue() {
  return ( this->currentValue );
}
byte Potentiometer::getSector() {
  return ( this->currentSector );
}


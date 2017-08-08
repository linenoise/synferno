### libraries
require(tidyverse)
require(ggthemes)
require(minpack.lm)

### voltage
Vcc = 5 # Volts

### pullup resistor value
Rknown = 50000 # Ohm, frequency and offset
Vknown = 553/1023*Vcc
Rpullup = (Vcc/Vknown)*(1-Vknown/Vcc)*Rknown # Ohm; spec is 20-50 kOhm
print(Rpullup)

Rknown = 20000 # Ohm, duration
Vknown = 360/1023*Vcc
Rpullup = (Vcc/Vknown)*(1-Vknown/Vcc)*Rknown # Ohm; spec is 20-50 kOhm
print(Rpullup)

Rknown = 10000 # Ohm, options
Vknown = 235/1023*Vcc
Rpullup = (Vcc/Vknown)*(1-Vknown/Vcc)*Rknown # Ohm; spec is 20-50 kOhm
print(Rpullup)

Rpullup = 37500 # Ohms

### voltage divider formula
Vout = function(Rpot, Rup=Rpullup, Vin=Vcc) { Vin*Rpot/(Rpullup+Rpot) }

### Rpot value by position
Rpot = function(positionFraction, Rmax) { Rmax*positionFraction }

### analogRead by voltage
Aread = function(Vout, Vin=Vcc) { as.integer(Vout/Vin*1023) }

### calculate the pot fraction
Fraction = function(Aread, Rpot, Rp=Rpullup) {
	Aread*Rp/(Rpot*(1024-Aread))
}

### Simulation
sim = data_frame(
	fr = seq(from=0, to=1, len=100),
	Rmax = 50000,
	Rpot = Rpot(fr, Rmax),
	Vout = Vout(Rpot),
	Aread = Aread(Vout),
	fc = Fraction(Aread, Rmax)
)
tail(sim)

qplot(fr,fc,data=sim) + geom_abline(slope=1,intercept=0)
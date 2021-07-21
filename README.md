# automated-spray-from-3Dprinter
 The code used for converting a 3D printer into an automated small area spraying device

A *Creality3D Ender-3 Pro* 3D printer has been converted in order to spray small area surfaces.

This repository contains some code and some hardware description for easing the modification.

## Hardware modifications

### Extruder nozzle

The whole nozzle block has been removed and its connections unplugged from the motherboard.

In order to convince the printer that is ok to move the extruder motor (needed for enabling/disabling the pump, see below), it has to be tricked to think that the nozzle is hot.
This can be achieved connecting a 1 kΩ resistor in place of the nozzle thermocouple, which results in the system read a false temperature aroud 173 °C.

### Extruder stepper motor

The extruder motor has also been removed.
An external circuit, described below, has been connected to the connector of the cable going from the motherboard to the removed extruder motor.

### Pump

An XXX pump has been attached to the frame of the printer. The pump is controlled by a small motherboard, which allows us to control the flow using a 0-5 V input which we can provide using an Arduino.

### Spray nozzle

A XXX nozzle has been selected for outputting a fine mist spray and connected to the pump. It has been installed in place of the extruder nozzle.

### Circuit interface for Arduino output

The Arduino can output 5 V. Can provide variations in form of a pulse modulated width (PWM) that seems not reliable with our pump. So, in order to output voltages in the 0-5 V we connected a potentiometer to an Arduino output and to one of its ground connections.

### Circuit interface for Arduino input

For convenience, we'll have the extruder motor connection cable communicating to the Arduino when the pump should be activated.

The extruder stepper motor receives pulses of +24 V, 0 V and -24 V. Arduino analog input can read 0-5 V. For converting the voltages into the acceptable range we used the following electrical scheme:


the result is a clean signal pulsing at 0 V for 0.45 s and at approx 1 V for 0.15 s.

## Software

In order to get a constant ON state and a quick switch to the OFF state for the pump, the pulsed extruder stepper motor signal can be processed using an Arduino rather than an analogic circuit.

The code can be found in the `arduino-pulse_detector.ino` file.

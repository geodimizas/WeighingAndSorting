# WeighingAndSorting
This project requires a mechanical equipment with an elliptican turning axis in order to move each item from one position to the other (from 0 to 5, position zero is the weighting station and the other 5 are the outputs), a solenoid valve in order to read the position in the begining of each cycle and five solenoid valves to "pull" the items in the appropriate position.

In order to calibrate the sensor connect the sensor to HX711 (wiring.jpg), put an item with known weight to the load cell and make the corrections from the arduino's serial port.

Connect the solenoid valves in pins 9 to 13 and the input signal (for syncronization) in pin 6 and load the program to your microcontroller.

-HOW IT WORKS?
Each time an input signal comes arduino weights the item on the load cell, in the next input signal weights the next item and opening the appropriate positions.
For example in the first cycle weights an item from the 3d category (0.1 < weight < 0.8) and in the next cycles counts 0 then in the cycles 2 and 3 won't open an output but it will open the position 3 in cycle 4.


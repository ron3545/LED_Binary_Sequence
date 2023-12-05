#include <Arduino.h>
#include "../include/Sequencer.hpp"

const uint8_t led_arr[] = {3, 5, 6, 9, 10};
int analog_values[] = {51, 102, 153, 204, 255};
Sequencer led_sequence = Sequencer(32, led_arr, analog_values); //object

void setup() 
{
  Serial.begin(9600);
  led_sequence.Begin();
}
void loop() 
{
    led_sequence.Run();
}
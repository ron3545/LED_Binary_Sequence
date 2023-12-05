#pragma once
#include "Arduino.h"
#include "Queue.hpp"

constexpr int MAX_BIT = 5;
//only for 5 bits
class Sequencer
{
private:
    char *buffer;
    int n_comb;
    uint8_t led_arr[MAX_BIT];
    int analog_values[MAX_BIT];

    Queue<char*> queue = Queue<char*>(n_comb);

public:
    Sequencer(int n_combination, const uint8_t led_arr[MAX_BIT],int analog_values[MAX_BIT]);
    Sequencer(const uint8_t led_arr[MAX_BIT],int analog_values[MAX_BIT]);
    ~Sequencer() { delete [] buffer; } 

    void Run();
    void Begin();
private:
    void Generate_Binary_Map(); 
    void LED(int index);
};
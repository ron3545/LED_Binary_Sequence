#include "../include/Sequencer.hpp"
#include <string>
//also a constructor
Sequencer::Sequencer(int n_combination, const uint8_t led_arr[MAX_BIT],int analog_values[MAX_BIT]) 
        :  buffer( new char[MAX_BIT] ), n_comb( n_combination )
{
    for(int i = 0; i < MAX_BIT; i++)
    {
        this->led_arr[i] = led_arr[i];
        this->analog_values[i] = analog_values[i];
    }
    if(n_comb > 32){
        n_comb = 32;
        Serial.println("\n Too much combination");
    }
}
//constructor
Sequencer::Sequencer(const uint8_t led_arr[MAX_BIT],int analog_values[MAX_BIT]) 
        :  buffer( new char[MAX_BIT] ), n_comb( 32 )
{
    for(int i = 0; i < MAX_BIT; i++)
    {
        this->led_arr[i] = led_arr[i];
        this->analog_values[i] = analog_values[i];
    }
}

void Sequencer::Generate_Binary_Map()
{
    for(int decimal = 0; decimal < n_comb; decimal++)
    {
        std::string binary = "";
        for(int i = 4; i >= 0; i--)
        {
            int mask = 1 << i;
            binary += (decimal & mask)? "1" : "0"; 
        }
        char *cstr = new char[binary.length() + 1];
        strcpy(cstr,binary.c_str());
        queue.enqueue(cstr);
    }
}

void Sequencer::Begin()
{
    for(int i = 0; i < MAX_BIT; i++)
        pinMode(led_arr[i], OUTPUT);
    Generate_Binary_Map();
}

void Sequencer::Run()
{
    while(!queue.isEmpty())
    {
        buffer = queue.dequeue();
        Serial.println(buffer);
        for(int i = 0; i < MAX_BIT; i++)
            LED(i);
       
    }
}

void Sequencer::LED(int index)
{
    
    if(buffer[index] == '1')
    {
        for(int i = 0; i < MAX_BIT; i++){
            analogWrite(led_arr[index], analog_values[i]);
            delay(80);
        }
    }
    else 
        analogWrite(led_arr[index], 0);
}
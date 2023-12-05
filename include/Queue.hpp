#pragma once
#include <ArduinoSTL.h>
//First in First out Data Structure
//implemented using circular buffer para sa speed and space
template<typename T> class Queue
{
private:
    T* buffer;
    int head, tail;
    int size, capacity;

public:
    Queue(unsigned int capacity) 
        : buffer(new T[capacity]), head(0), 
        tail(0), size(0), capacity(capacity)
    {}
    ~Queue() { delete[] buffer; } 

    void enqueue(T data) 
    { 
        if(isFull()){
            Serial.println("Queue is full");
            return;
        }
        buffer[head] = data;
        head = (head + 1) % capacity;
        size++;
    }
    T dequeue() 
    { 
        if(isEmpty()){
            Serial.println("Queue is empty");
            return T();
        }
        T data = buffer[tail]; 
        tail = (tail + 1) % capacity;
        size--;
        return data;
    }
    unsigned int Size() const { return size; }
    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }
};
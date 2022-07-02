#pragma once
#include <Arduino.h>
#include <Wire.h>

class BMA220
{

public:
    BMA220(TwoWire *pWire);

    int8_t getX();

    void printTest();

private:
    TwoWire *wire;

    int8_t x_data;
};
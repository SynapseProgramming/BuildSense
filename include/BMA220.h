#pragma once
#include <Arduino.h>
#include <Wire.h>

class BMA220
{

public:
    BMA220(TwoWire *pWire);

    int8_t getX();
    int8_t getY();


private:
    TwoWire *wire;

};
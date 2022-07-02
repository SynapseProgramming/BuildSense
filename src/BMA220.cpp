#include "BMA220.h"

BMA220::BMA220(TwoWire *pWire)
{
    wire = pWire;
    wire->beginTransmission(0x0A); // address of the accelerometer
    // low pass filter, range settings
    wire->write(0x20);
    wire->write(0x05);
    wire->endTransmission();
}

int8_t BMA220::getX()
{
    byte xinp;
    wire->beginTransmission(0x0A); // address of the accelerometer
    // reset the accelerometer
    wire->write(0x04); // X data
    wire->endTransmission();
    wire->requestFrom(0x0A, 1); // request 6 bytes from slave device #2
    while (wire->available())   // slave may send less than requested
    {
        xinp = wire->read(); // receive a byte as characte
    }
    return (int8_t)xinp >> 2;
}

int8_t BMA220::getY()
{
    byte yinp;
    wire->beginTransmission(0x0A); // address of the accelerometer
    // reset the accelerometer
    wire->write(0x06); // Y data
    wire->endTransmission();
    wire->requestFrom(0x0A, 1); // request 6 bytes from slave device #2
    while (wire->available())   // slave may send less than requested
    {
        yinp = wire->read(); // receive a byte as characte
    }
    return (int8_t)yinp >> 2;
}
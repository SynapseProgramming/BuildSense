#include <Arduino.h>
#include <DFRobot_BME280.h>
#include <BMA220.h> 
#include <Wire.h>
byte Version[3];
int8_t x_data;
int8_t y_data;
int8_t z_data;

#define I2C_SDA 27
#define I2C_SCL 26
#define MICPIN 32

#define SEA_LEVEL_PRESSURE 1015.0f

typedef DFRobot_BME280_IIC BME; // ******** use abbreviations instead of full names ********

BME *test;
TwoWire I2C = TwoWire(0);
BMA220 wow; 

// show last sensor operate status
void printLastOperateStatus(BME::eStatus_t eStatus)
{
  switch (eStatus)
  {
  case BME::eStatusOK:
    Serial.println("everything ok");
    break;
  case BME::eStatusErr:
    Serial.println("unknow error");
    break;
  case BME::eStatusErrDeviceNotDetected:
    Serial.println("device not detected");
    break;
  case BME::eStatusErrParameter:
    Serial.println("parameter error");
    break;
  default:
    Serial.println("unknow status");
    break;
  }
}

void setup()
{
  Serial.begin(115200); 
  I2C.begin(I2C_SDA, I2C_SCL);

  test = new BME(&I2C, 0x77);
  test->reset();
  Serial.println("bme read data test");
  while (test->begin() != BME::eStatusOK)
  {
    Serial.println("bme begin failed");
    delay(2000);
  }
  Serial.println("bme begin success");
}

void loop()
{

  float temp = test->getTemperature();
  uint32_t press = test->getPressure();
  float alti = test->calAltitude(SEA_LEVEL_PRESSURE, press);
  float humi = test->getHumidity();
  Serial.println();
  Serial.println("======== start print ========");
  Serial.print("temperature (unit Celsius): ");
  Serial.println(temp);
  Serial.print("pressure (unit pa):         ");
  Serial.println(press);
  Serial.print("altitude (unit meter):      ");
  Serial.println(alti);
  Serial.print("humidity (unit percent):    ");
  Serial.println(humi);
  Serial.println("========  end print  ========");

  wow.printTest();

  delay(1000);
}
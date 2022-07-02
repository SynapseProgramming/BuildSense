#include <Arduino.h>
#include <DFRobot_BME280.h>
#include <BMA220.h>
#include <Wire.h>

#define I2C_SDA 27
#define I2C_SCL 26
#define MICPIN 32

#define SEA_LEVEL_PRESSURE 1015.0f

typedef DFRobot_BME280_IIC BME; // ******** use abbreviations instead of full names ********

BME *evnSensor;
TwoWire I2C = TwoWire(0);
BMA220 *accSensor;

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

  evnSensor = new BME(&I2C, 0x77);
  accSensor = new BMA220(&I2C);

  evnSensor->reset();
  Serial.println("bme read data test");
  while (evnSensor->begin() != BME::eStatusOK)
  {
    Serial.println("bme begin failed");
    delay(2000);
  }
  Serial.println("bme begin success");
}

void loop()
{

  float temp = evnSensor->getTemperature();
  uint32_t press = evnSensor->getPressure();
  float alti = evnSensor->calAltitude(SEA_LEVEL_PRESSURE, press);
  float humi = evnSensor->getHumidity();
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

  Serial.print("acc X: ");
  Serial.println(accSensor->getX());

  Serial.print("acc Y: ");
  Serial.println(accSensor->getY());

  Serial.print("acc Z: ");
  Serial.println(accSensor->getZ());

  double micVoltage;
  micVoltage = analogReadMilliVolts(MICPIN) * 1.0e-3;
  Serial.print("Sound sensor Voltage: ");
  Serial.println(micVoltage);

  delay(1000);
}
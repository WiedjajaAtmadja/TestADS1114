// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1114
// This code is designed to work with the ADS1114_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1114_I2CADC#tabs-0-product_tabset-2
#include <Arduino.h>
#include <Wire.h>

#define ADC_CONFIG_FSR_2048 0x84
#define ADC_CONFIG_FSR_4096 0x82
#define ADC_CONFIG_FSR_6144 0x80

#define ADC_CONFIG_FSR ADC_CONFIG_FSR_4096
#define ADC_FULLSCALE_VOLTAGE 4096.0

// ADS1114 I2C address is 0x48(72)
#define Addr 0x4B

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(115200);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  Wire.write(ADC_CONFIG_FSR);

  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);

  // 8 SPS
  // Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    int raw_adc = (Wire.read()&0xFF) << 8;
    raw_adc |= Wire.read();
    // Convert the data
    float voltage = (raw_adc/1000.0) * (ADC_FULLSCALE_VOLTAGE/32767.0);
    // Output data to serial monitor
    Serial.printf("Digital Value of Analog Input : %d, voltage: %.3f\n", raw_adc, voltage);
  }
  else
  {
      Serial.println("Read ADC error");
  }
  
  delay(1000);
} 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

const int BAUD_RATE = 9600; //Bits que s'envien cada segon
const int TEMPS_TRANSMISSIO = 1000; //temps entre una dada i una altra en ms

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C


void setup() {
  Serial.begin(9600);

  
  while ( !Serial ) delay(100);   // wait for native usb
  unsigned status;
  status = bmp.begin();
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);

  while(!status){
    Serial.println("Error");
    while (1) delay(10);
  }

}

void loop() {
  float pressio = bmp.readPressure();
  Serial.println(pressio);

  delay(TEMPS_TRANSMISSIO);
}

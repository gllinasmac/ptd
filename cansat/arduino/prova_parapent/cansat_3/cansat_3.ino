#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <TinyGPSPlus.h>
#include <DHT11.h>

const int BAUDS_PER_SEGON = 9600;    //Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000;  //Delay entre el final en ms

const int PIN_TERMISTOR = A2;

Adafruit_BMP280 bmp;              // I2C
float PRESSIO_ALTURA_0 = 1032.0;  //Ajustar el dia de la mesura

int num_paquet = 0;

void setup() {
  Serial.begin(BAUDS_PER_SEGON);

  //TEST FUNCIONAMENT BMP280
  while (!Serial) delay(100);
  unsigned status;
  status = bmp.begin();
  /*
  if (!status) {
    Serial.println("Error de connexió BMP280");
    while (1) delay(10);
  }
  */

}

void loop() {

  int lectura_termistor = analogRead(PIN_TERMISTOR);
  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();

  //  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

  float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

  Serial.print(num_paquet);
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print("Ajuntament");
  Serial.print(",");
  Serial.print(lectura_termistor);
  Serial.print(",");
  Serial.print(pressio);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(altura_bmp280);
  Serial.println();

  num_paquet++;

  delay(TEMPS_ENTRE_DADES);
  }

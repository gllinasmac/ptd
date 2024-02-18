#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <DHT.h>

const int BAUDS_PER_SEGON = 9600;    //Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000;  //Delay entre el final en ms

const int PIN_MQ135 = 3;
const int PIN_UV = 0;

const int PIN_TERMISTOR = 2;         //Analògic
const int PIN_DHT = 7
DHT11 dht11(PIN_DHT);

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

Adafruit_BMP280 bmp;              // I2C
float PRESSIO_ALTURA_0 = 1032.0;  //Ajustar el dia de la mesura

int num_paquet = 0;

void setup() {
  Serial.begin(BAUDS_PER_SEGON);
  ss.begin(GPSBaud);

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

  int lectura_uv = analogRead(PIN_UV);
  int lectura_mq135 = analogRead(PIN_MQ135);
  int lectura_termistor = analogRead(PIN_TERMISTOR);
  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();

  int temperatura_dht = 0;
  int humitat = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperatura_dht, humitat);
  //  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

  float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

  Serial.print(num_paquet);
  Serial.print(",");
  Serial.print("Alicia Sintes");
  Serial.print(",");
  Serial.print(lectura_termistor);
  Serial.print(",");
  Serial.print(pressio);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(altura_bmp280);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(humitat);

  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        Serial.print(",")
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        Serial.print(",");
        Serial.print(gps.altitude.meters());
        Serial.print(",");
        Serial.print(gps.speed.kmph());
      } else {
        Serial.print(F("-,-,-,-"));
      }
    }
  }
  
  Serial.println();

  num_paquet++;

  if(lectura_ir == LOW){
    digitalWrite(PIN_RGB_VERMELL, 0);
    digitalWrite(PIN_RGB_VERD, 255);
    digitalWrite(PIN_RGB_BLAU, 0);
  }else {
    digitalWrite(PIN_RGB_VERMELL, 0);
    digitalWrite(PIN_RGB_VERD, 0);
    digitalWrite(PIN_RGB_BLAU, 255);
  }

  smartDelay(TEMPS_ENTRE_DADES);
  //delay(TEMPS_ENTRE_DADES);
  }

  // This custom version of delay() ensures that the gps object
  // is being "fed".
  static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
      while (ss.available())
        gps.encode(ss.read());
    } while (millis() - start < ms);
  }
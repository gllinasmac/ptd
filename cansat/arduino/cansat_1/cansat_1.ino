#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const int BAUDS_PER_SEGON = 9600;    //Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000;  //Delay entre el final en ms

const int PIN_IR = 6;                ////Digital

const int PIN_RGB_VERMELL = 5;       //Digital
const int PIN_RGB_BLAU = 8;          //Digital
const int PIN_RGB_VERD = 2;          //Digital

const int PIN_BRUNZIDOR = 11;         //Digital
const int FREQ_BRUNZIDOR = 400;
const int TEMPS_BRUNZIDOR = 1000;

const int PIN_TERMISTOR = 2;         //Analògic

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

Adafruit_BMP280 bmp;              // I2C
float PRESSIO_ALTURA_0 = 1032.0;  //Ajustar el dia de la mesura
float ALTURA_0 = 16;

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
  pinMode(PIN_IR, INPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_RGB_VERMELL, OUTPUT);
  pinMode(PIN_RGB_VERD, OUTPUT);
  pinMode(PIN_RGB_BLAU, OUTPUT);

  //digitalWrite(PIN_RGB_VERMELL,HIGH);
  
}

void loop() {

  tone(PIN_BRUNZIDOR,FREQ_BRUNZIDOR);
  delay(250);
  noTone(PIN_BRUNZIDOR);
  
  int lectura_ir = digitalRead(PIN_IR);
  int lectura_termistor = analogRead(PIN_TERMISTOR);
  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();
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
  Serial.print(altura_bmp280 + ALTURA_0);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(lectura_ir);
  

  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        Serial.print(",");
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.print(gps.date.year());

        Serial.print(",");
        Serial.print(gps.time.hour()+1);
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.print(gps.time.second());

        Serial.print(",");

        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        Serial.print(",");
        Serial.print(gps.altitude.meters());
        Serial.print(",");
        Serial.print(gps.speed.kmph());
      }
    }
  }
  Serial.println();

  num_paquet++;
  
  if(lectura_ir == HIGH){
    digitalWrite(PIN_RGB_VERMELL, LOW);
    digitalWrite(PIN_RGB_VERD, LOW);
    digitalWrite(PIN_RGB_BLAU, LOW);
  }else {
    digitalWrite(PIN_RGB_VERMELL, LOW);
    digitalWrite(PIN_RGB_VERD, HIGH);
    digitalWrite(PIN_RGB_BLAU, LOW);
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
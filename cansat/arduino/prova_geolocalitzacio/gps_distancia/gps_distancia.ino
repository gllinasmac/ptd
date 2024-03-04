#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const int BAUDS_PER_SEGON = 9600;
const int TEMPS_ENTRE_DADES = 1000;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = BAUDS_PER_SEGON;
TinyGPSPlus gps;

static const double LATITUD_ORIGEN = 51.508131, LONGITUD_ORIGEN = -0.128002;

SoftwareSerial ss(RXPin, TXPin);

int num_paquet = 0;

void setup() {
  Serial.begin(BAUDS_PER_SEGON);
  ss.begin(GPSBaud);
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      Serial.print(num_paquet);
      Serial.print(F(","));

      if (gps.date.isValid()) {
        Serial.print(gps.date.month());
        Serial.print(F("/"));
        Serial.print(gps.date.day());
        Serial.print(F("/"));
        Serial.print(gps.date.year());
      } else {
        Serial.print(F("INVALID DATE"));
      }

      Serial.print(F(","));
      if (gps.time.isValid()) {
        if (gps.time.hour() < 10) Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        if (gps.time.second() < 10) Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(F("."));
        if (gps.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(gps.time.centisecond());
      } else {
        Serial.print(F("INVALID TIME"));
      }

      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        Serial.print(F(","));
        Serial.print(gps.altitude.meters(), 2);
        Serial.print(F(","));
        Serial.print(gps.speed.kmph(),2);
        Serial.print(F(","));
        
        unsigned long distancia_origen =
          (unsigned long)TinyGPSPlus::distanceBetween(
            gps.location.lat(),
            gps.location.lng(),
            LATITUD_ORIGEN,
            LONGITUD_ORIGEN)
          / 1000;

        Serial.print(distancia_origen);
      } else {
        Serial.print(F("INVALID LOCATION"));
      }

      Serial.println();
      num_paquet++;
    }
  }
  smartDelay(TEMPS_ENTRE_DADES);
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

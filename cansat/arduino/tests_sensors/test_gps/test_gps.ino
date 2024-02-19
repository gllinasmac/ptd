#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const int BAUDS_PER_SEGON = 9600;
const int TEMPS_ENTRE_DADES = 1000;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = BAUDS_PER_SEGON;
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

int num_paquet = 0;

void setup() {
  Serial.begin(BAUDS_PER_SEGON);
  ss.begin(GPSBaud);
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
      } else {
        Serial.print(F("INVALID LOCATION"));
      }
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

      Serial.println();
    }
  }

  num_paquet++;
}

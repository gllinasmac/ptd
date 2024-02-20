#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

const int BAUDS_PER_SEGON = 9600;    //Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000;  //Delay entre el final en ms

const int PIN_IR = 6;  ////Digital

const int PIN_RGB_VERMELL = 5;  //Digital
const int PIN_RGB_BLAU = 8;     //Digital
const int PIN_RGB_VERD = 2;     //Digital

const int PIN_BRUNZIDOR = 11;  //Digital
const int FREQ_BRUNZIDOR = 400;
const int TEMPS_BRUNZIDOR = 1000;

const int PIN_TERMISTOR = A2;  //Analògic

Adafruit_BMP280 bmp;              // I2C
float PRESSIO_ALTURA_0 = 1032.0;  //Ajustar el dia de la mesura
float ALTURA_0 = 16;

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
  pinMode(PIN_IR, INPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_RGB_VERMELL, OUTPUT);
  pinMode(PIN_RGB_VERD, OUTPUT);
  pinMode(PIN_RGB_BLAU, OUTPUT);

  //digitalWrite(PIN_RGB_VERMELL,HIGH);
}

void loop() {



  int lectura_ir = digitalRead(PIN_IR);
  int lectura_termistor = analogRead(PIN_TERMISTOR);
  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();
  //  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

  float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

  Serial.print(num_paquet);
  Serial.print(",");
  Serial.print(millis());  //Milisegons
  Serial.print(",");
  Serial.print("Alicia Sintes");
  Serial.print(",");
  Serial.print(lectura_termistor);
  Serial.print(",");
  Serial.print(pressio);
  Serial.print(",");
  Serial.print(altura_bmp280);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(lectura_ir);
  Serial.println();

  num_paquet++;

  if (lectura_ir == HIGH) {
    digitalWrite(PIN_RGB_VERMELL, LOW);
    digitalWrite(PIN_RGB_VERD, LOW);
    digitalWrite(PIN_RGB_BLAU, HIGH);
  } else {
    digitalWrite(PIN_RGB_VERMELL, LOW);
    digitalWrite(PIN_RGB_VERD, HIGH);
    digitalWrite(PIN_RGB_BLAU, LOW);
  }

  tone(PIN_BRUNZIDOR,FREQ_BRUNZIDOR);
  delay(TEMPS_ENTRE_DADES/2);
  noTone(PIN_BRUNZIDOR);
  delay(TEMPS_ENTRE_DADES/2);
}
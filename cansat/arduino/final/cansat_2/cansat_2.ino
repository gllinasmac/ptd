#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <TinyGPSPlus.h>
#include <DHT11.h>

const int BAUDS_PER_SEGON = 9600;    //Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000;  //Delay entre el final en ms

const int PIN_MQ135 = A3;
const int PIN_UV = A0;

const int PIN_TERMISTOR = A2;
const int PIN_DHT = 12;

DHT11 dht11(PIN_DHT);

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

  int lectura_uv = analogRead(A0); // 20 = estàndard
  int lectura_mq135 = analogRead(PIN_MQ135);
  int lectura_termistor = analogRead(PIN_TERMISTOR);
  
  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();


  int temperatura_dht = 0;
  int humitat = 0;
  int result = dht11.readTemperatureHumidity(temperatura_dht, humitat);

  //  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

  float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

  Serial.print(num_paquet);
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print("Sara Garcia");
  Serial.print(",");
  Serial.print(lectura_termistor);
  Serial.print(",");
  Serial.print(pressio);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(altura_bmp280);
  Serial.print(",");
  Serial.print(temperatura_dht);
  Serial.print(",");
  Serial.print(humitat);
  Serial.print(",");
  Serial.print(lectura_mq135);

  float mq135_voltaje = lectura_mq135 * (5.0 / 1023.0);
  float mq135_resistencia = 1000*((5-mq135_voltaje)/mq135_voltaje);
  double dioxidoDeCarbono = 245*pow(mq135_resistencia/5463, -2.26);
  double oxidosDeNitrogeno = 132.6*pow(mq135_resistencia/5463, -2.74);
  double amoniaco = 161.7*pow(mq135_resistencia/5463, -2.26);
  
  Serial.print(",");
  Serial.print(dioxidoDeCarbono);
  Serial.print(",");
  Serial.print(oxidosDeNitrogeno);
  Serial.print(",");
  Serial.print(amoniaco);
  Serial.print(",");
  Serial.print(lectura_uv);
  Serial.println();

  num_paquet++;

  delay(TEMPS_ENTRE_DADES);
  }

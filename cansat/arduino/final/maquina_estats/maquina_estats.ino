#include <Wire.h>             //bmp280
#include <SPI.h>              //bmp280
#include <Adafruit_BMP280.h>  //bmp280

#include <TinyGPSPlus.h>     //gps
#include <SoftwareSerial.h>  //gps

#include <stdio.h>

//BMP280
Adafruit_BMP280 bmp;              // I2C
float PRESSIO_ALTURA_0 = 1032.0;  // Ajustar el dia de la mesura
float ALTURA_0 = 16;
#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

//CONNEXIÓ SÈRIE
const int BAUDS_PER_SEGON = 9600;  // Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)

//GPS
TinyGPSPlus gps;
static const uint32_t GPSBaud = BAUDS_PER_SEGON;
static const int RXPin = 4, TXPin = 3;
SoftwareSerial ss(RXPin, TXPin);

void enviar_geolocalitzacio();

//INICIALITZACIÓ SENSORS

void inicialitzar_gps();
void inicialitzar_serial();
void inicialitzar_pins();
void inicialitzar_bmp280();

//MÀQUINA ESTATS
int estat_actual = 0;
const int NUM_ESTATS_POSSIBLES = 10;
char ESTATS_POSSIBLES[NUM_ESTATS_POSSIBLES] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

void actualitzar_estat(char lectura);
bool es_estat(char caracter);

//LLEGIR DADES
char llegir_dada_serial();

//Enviar dades
const int DELAY_REPOS = 3000;  // Delay quan estam en repòs
const int DELAY_DADES = 1000;  // Delay entre dada i dada quan enviam els sensors
const int DELAY_TEST_CONNEXIO = 2000;
int num_paquet = 0;
void enviar_dades_sensors();

//TERMISTOR
const int PIN_TERMISTOR = A2;  // Analògic
int llegir_termistor();

//Brunzidor
const int PIN_BRUNZIDOR = 11;  // Digital
const int FREQ_BRUNZIDOR = 400;
const int TEMPS_BRUNZIDOR = 1000;

void pitar(int pin, int freq, int temps);

//LED RGB
const int PIN_LED_VERD = 2;     // Verd
const int PIN_LED_BLAU = 8;     // Blau
const int PIN_LED_VERMELL = 5;  // Vermell

void encendre_led();
void apagar_led();

void encendre_led_verd();
void encendre_led_vermell();
void encendre_led_blau();
void apagar_led_verd();
void apagar_led_blau();
void apagar_led_vermell();

void encendre_led_integrat();
void apagar_led_integrat();

//SENSOR IR
const int PIN_IR = 6;  ////Digital

//Codi localització
int NUM_SENYALS_CODI = 2;
int TEMPS_MIN_SENYAL = 500;
int TEMPS_MAX_SENYAL = 5000;

int llegir_ir();
void mirar_si_localitzat();
bool localitzat = false;



//MORSE
const int MAX_NUM_RETXES_PUNTS = 5;  //Màxim de punts i retxes que pot tenir un símbol

struct simbol_morse {
  char simbol;
  int morse[MAX_NUM_RETXES_PUNTS];
};


// 1 = punt
// 2 = retxa

simbol_morse alfabet[] = {
  { 'a', { 1, 2, 0, 0, 0 } },
  { 'b', { 2, 1, 1, 1, 0 } },
  { 'c', { 2, 1, 2, 1, 0 } },
  { 'd', { 2, 1, 1, 0, 0 } },
  { 'e', { 1, 0, 0, 0, 0 } },
  { 'f', { 1, 1, 2, 1, 0 } },
  { 'g', { 2, 2, 1, 0, 0 } },
  { 'h', { 1, 1, 1, 1, 0 } },
  { 'i', { 1, 1, 0, 0, 0 } },
  { 'j', { 1, 2, 2, 2, 0 } },
  { 'k', { 2, 1, 2, 0, 0 } },
  { 'l', { 1, 2, 1, 1, 0 } },
  { 'm', { 2, 2, 0, 0, 0 } },
  { 'n', { 2, 1, 0, 0, 0 } },
  { 'o', { 2, 2, 2, 0, 0 } },
  { 'p', { 1, 2, 2, 1, 0 } },
  { 'q', { 2, 2, 1, 2, 0 } },
  { 'r', { 1, 2, 1, 0, 0 } },
  { 's', { 1, 1, 1, 0, 0 } },
  { 't', { 2, 0, 0, 0, 0 } },
  { 'u', { 1, 1, 2, 0, 0 } },
  { 'v', { 1, 1, 1, 2, 0 } },
  { 'w', { 1, 2, 2, 0, 0 } },
  { 'x', { 2, 1, 1, 2, 0 } },
  { 'y', { 2, 1, 2, 2, 0 } },
  { 'z', { 2, 2, 1, 1, 0 } },
  { '1', { 1, 2, 2, 2, 2 } },
  { '2', { 1, 1, 2, 2, 2 } },
  { '3', { 1, 1, 1, 2, 2 } },
  { '4', { 1, 1, 1, 1, 2 } },
  { '5', { 1, 1, 1, 1, 1 } },
  { '6', { 2, 1, 1, 1, 1 } },
  { '7', { 2, 2, 1, 1, 1 } },
  { '8', { 2, 2, 2, 1, 1 } },
  { '9', { 2, 2, 2, 2, 1 } },
  { '0', { 2, 2, 2, 2, 2 } }
};
const int NUM_CARACTERS_ALFABET = sizeof(alfabet);

const int TEMPS_PUNT = 1000;
const int TEMPS_RETXA = 3000;
const int TEMPS_ESPERA_SENYAL = 500;   //Temps entre punt i retxa
const int TEMPS_ESPERA_SIMBOL = 3000;  //Temps entre simbol i simbol

void mostrar_punt();
void mostrar_retxa();
void esperar(int temps);
void mostrar_morse(char caracter);


//const int PIN_LDR = A8;
int llegir_ldr(int pin);

void setup() {

  inicialitzar_serial();
  inicialitzar_gps();
  inicialitzar_bmp280();
  inicialitzar_pins();
}

void loop() {

  char lectura = llegir_dada_serial();
  actualitzar_estat(lectura);

  switch (estat_actual) {

    case 0:  //Repòs. Sense connexió a estació de terra
      Serial.print("0/");
      Serial.println("Cansat Alicia Sintes. En repos. Esperant ordres.");
      //encendre_led_vermell();
      delay(DELAY_REPOS);
      break;

    case 1:  //Repòs amb connexió a estació de terra
      Serial.print("1/");
      Serial.println("Cansat Alicia Sintes. Missatge rebut. Esperam ordres");
      encendre_led_verd();
      pitar(PIN_BRUNZIDOR, FREQ_BRUNZIDOR, DELAY_TEST_CONNEXIO);
      //delay(DELAY_REPOS);
      apagar_led_verd();
      estat_actual = 0;
      break;

    case 2:  //Localitzar

      if (localitzat) {
        Serial.print("2/");
        Serial.println("CanSat localitzat. Enviar ajuda.");
        noTone(PIN_BRUNZIDOR);
        apagar_led_vermell();
        encendre_led_verd();
        //delay(DELAY_REPOS);
      } else {
        Serial.print("2/");
        Serial.println("CanSat Alicia Sintes pitant a la espera de ser localitzat.");
        //encendre_led_vermell();
        //tone(PIN_BRUNZIDOR, FREQ_BRUNZIDOR);
        //pitar(PIN_BRUNZIDOR, FREQ_BRUNZIDOR, TEMPS_BRUNZIDOR);
        //delay(TEMPS_BRUNZIDOR);
        //apagar_led_vermell();

        mirar_si_localitzat();
        //localitzat = !llegir_ir();
      }
      delay(DELAY_DADES);
      break;

    case 3:  //Enviar dades
      Serial.print("3/");
      enviar_dades_sensors();
      //enviar_geolocalitzacio();
      delay(DELAY_DADES);
      break;

    case 4:  //Enviar morse (IR)
      Serial.print("4/");
      Serial.println(llegir_ir());
      delay(DELAY_DADES);
      break;

    case 5:  //Rebre morse

      if (!Serial.available()) {
        Serial.print("5/");
        Serial.println("Esperant missatge per a transmetre en Morse.");
        delay(DELAY_REPOS);
      } else {

        while (Serial.available()) {
          Serial.print("5/");
          Serial.print("Codificant la lletra: ");
          char caracter_rebut = llegir_dada_serial();
          Serial.println(caracter_rebut);
          if (caracter_rebut != '\0') {
            if (es_estat(caracter_rebut)) {
              actualitzar_estat(caracter_rebut);
            } else {
              mostrar_morse(caracter_rebut);
              Serial.print("5/");
              Serial.print("Lletra ");
              Serial.print(caracter_rebut);
              Serial.println(" codificada amb exit");
            }
          }
        }
      }

      break;

    case 6:  //Geolocalització
      enviar_geolocalitzacio();
      break;
  }
}

bool es_estat(char caracter) {
  bool estat = false;
  for (int i = 0; i < NUM_ESTATS_POSSIBLES; i++) {
    if (ESTATS_POSSIBLES[i] == caracter) {
      estat = true;
    }
  }
  return estat;
}

void actualitzar_estat(char lectura) {

  switch (lectura) {
    case '\0': //No he rebut res
      break;
    case '0':  //Repòs
      estat_actual = 0;
      break;
    case '1':
      //Serial.println("Connexio establerta");
      estat_actual = 1;
      break;
    case '2':  //Mode localitzar
      tone(PIN_BRUNZIDOR, FREQ_BRUNZIDOR);
      encendre_led_vermell();
      localitzat = false;
      estat_actual = 2;
      break;
    case '3':
      estat_actual = 3;  // Enviam dades
      break;
    case '4':  //Enviar IR
      estat_actual = 4;
      break;
    case '5':  //Rebem missatges morse
      estat_actual = 5;
      break;
    case '6':  //Geolocalització
      estat_actual = 6;
      break;
  }
}

void inicialitzar_bmp280() {
  unsigned status = bmp.begin();
  if (!status) {
    Serial.println("Error de connexio BMP280");
    while (1)
      delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void inicialitzar_pins() {
  pinMode(PIN_LED_BLAU, OUTPUT);
  pinMode(PIN_LED_VERD, OUTPUT);
  pinMode(PIN_LED_VERMELL, OUTPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_IR, INPUT);

  apagar_led_blau();
  apagar_led_verd();
  apagar_led_vermell();
}

void inicialitzar_serial() {
  Serial.begin(BAUDS_PER_SEGON);
  while (!Serial)
    delay(100);
}

void inicialitzar_gps() {
  ss.begin(GPSBaud);
}

char llegir_dada_serial() {

  char caracter = '\0';

  if (Serial.available() != 0) {
    char lectura = Serial.read();

    if (lectura != '\n') {  //Per eliminar es salt de línia
      caracter = lectura;
    }
  }
  return caracter;
}


//PAS PER REFERÈNCIA
void comprobarNAN(float &nombre) {
  if (isnan(nombre)) {
    nombre = -1;
  }
}

void enviar_dades_sensors() {

  float pressio = bmp.readPressure();
  float temperatura_bmp280 = bmp.readTemperature();
  float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

  //Si no llegeix bé, pot ser un nan (not a number), en aquest cas enviam un -1
  //comprobarNAN(pressio);
  //comprobarNAN(temperatura_bmp280);
  //comprobarNAN(altura_bmp280);

  Serial.print(num_paquet);
  Serial.print(",");
  Serial.print("Alicia Sintes");
  Serial.print(",");
  Serial.print(llegir_termistor());
  Serial.print(",");
  Serial.print(pressio);
  Serial.print(",");
  Serial.print(temperatura_bmp280);
  Serial.print(",");
  Serial.print(altura_bmp280);
  //Serial.print(",");
  //Serial.println(llegir_ir());
  Serial.println();

  num_paquet++;
}

void pitar(int pin, int freq, int temps) {
  tone(pin, freq);
  delay(temps);
  noTone(pin);
}

void encendre_led(int pin) {
  digitalWrite(pin, HIGH);
}

void apagar_led(int pin) {
  digitalWrite(pin, LOW);
}

void encendre_led_blau() {
  encendre_led(PIN_LED_BLAU);
  apagar_led(PIN_LED_VERD);
  apagar_led(PIN_LED_VERMELL);
}

void apagar_led_vermell() {
  apagar_led(PIN_LED_VERMELL);
}

void apagar_led_verd() {
  apagar_led(PIN_LED_VERD);
}
void apagar_led_blau() {
  apagar_led(PIN_LED_BLAU);
}

void encendre_led_vermell() {
  encendre_led(PIN_LED_VERMELL);
  apagar_led(PIN_LED_BLAU);
  apagar_led(PIN_LED_VERD);
}

void encendre_led_verd() {
  encendre_led(PIN_LED_VERD);
  apagar_led(PIN_LED_VERMELL);
  apagar_led(PIN_LED_BLAU);
}

int llegir_ir() {
  return digitalRead(PIN_IR);
}

int llegir_termistor() {
  return analogRead(PIN_TERMISTOR);
}


//Variables temporals
unsigned long temps_inici_tapat = 0;
unsigned long temps_tapat = 0;
const int TAPAT = 0;
bool estaba_tapat = false;
int num_senyals = 0;

bool mirar_si_esta_tapat() {

  bool esta_tapat = false;
  int lectura = llegir_ir();
  //int lectura = llegir_ldr(PIN_LDR);

  return lectura == TAPAT;
}

void mirar_si_localitzat() {

  bool ara_tapat = mirar_si_esta_tapat();

  if (ara_tapat && !estaba_tapat) {  //No estaba tapat i ara sí (començam a contar)
    estaba_tapat = true;             //A la següent iteració estarà tapat
    temps_inici_tapat = millis();
  }

  if (!ara_tapat && estaba_tapat) {  //Estaba tapat i ara no
    estaba_tapat = false;            //A la següent iteració estarà destapat
    temps_tapat = millis() - temps_inici_tapat;
    //Si el temps està entre el mínim i el màxim de la longitud de la senyal
    if ((temps_tapat > TEMPS_MIN_SENYAL) && (temps_tapat < TEMPS_MAX_SENYAL)) {
      localitzat = true;
    }
  }
  /*
  if (num_senyals >= NUM_SENYALS_CODI) {
    localitzat = true;
    num_senyals = 0;
  }
  */


}

void esperar(int temps) {
  delay(temps);
}

void mostrar_punt() {
  encendre_led_blau();
  //Serial.println("5/.");
  esperar(TEMPS_PUNT);

  apagar_led_blau();
}

void mostrar_retxa() {
  encendre_led_blau();

  //Serial.println("5/-");
  esperar(TEMPS_RETXA);

  apagar_led_blau();
}

int cercar_caracter_alfabet(char caracter) {
  bool trobat = false;
  int i = 0;

  while (!trobat && (i < NUM_CARACTERS_ALFABET)) {
    if (alfabet[i].simbol == caracter) {
      trobat = true;
    }
    i++;
  }

  if (trobat) {
    return i - 1;
  } else {
    return -1;
  }
}

void mostrar_morse(char caracter) {
  int posicio = cercar_caracter_alfabet(caracter);

  if (posicio != -1) {

    for (int i = 0; i < MAX_NUM_RETXES_PUNTS; i++) {
      int simbol_morse = alfabet[posicio].morse[i];
      switch (simbol_morse) {
        case 1:
          mostrar_punt();

          esperar(TEMPS_ESPERA_SENYAL);
          break;
        case 2:
          mostrar_retxa();
          esperar(TEMPS_ESPERA_SENYAL);
          break;
      }
    }

  } else {
    Serial.println("5/No s'ha trobat a l'alfabet");
  }
}


void enviar_coordenades_gps() {

  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F(","));
    Serial.print(gps.altitude.meters());
    Serial.print(F(","));
    Serial.print(gps.speed.kmph());
  }
}

void enviar_dia_gps() {
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
}

void enviar_hora_gps() {
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
  }
}

void enviar_geolocalitzacio() {
  if (ss.available() > 0) {
    while (ss.available() > 0) {
      if (gps.encode(ss.read())) {
        Serial.print("6/");
        enviar_dia_gps();
        Serial.print(F(","));
        enviar_hora_gps();
        Serial.print(F(","));
        enviar_coordenades_gps();
        Serial.println();
      }
    }
  }
  {
    Serial.println("6/No hi ha senyal GPS");
  }
}


int llegir_ldr(int pin) {
  int lectura = analogRead(pin);

  return (lectura < 600 ? 1 : 0);
}

void encendre_led_integrat() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void apagar_led_integrat() {
  digitalWrite(LED_BUILTIN, LOW);
}
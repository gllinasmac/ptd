#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
/*
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
*/

const int BAUDS_PER_SEGON = 9600;   // Baud = nombre de símbols (9600 = 9600 símbols enviats cada segon)
const int TEMPS_ENTRE_DADES = 1000; // Delay entre el final en ms

const int PIN_IR = 6; ////Digital

const int PIN_LED_VERD = 2;    // Verd
const int PIN_LED_BLAU = 8;    // Blau
const int PIN_LED_VERMELL = 5; // Vermell

const int PIN_BRUNZIDOR = 11; // Digital
const int FREQ_BRUNZIDOR = 400;
const int TEMPS_BRUNZIDOR = 1000;

const int PIN_TERMISTOR = A2; // Analògic

const char CARACTER_INICI_CONNEXIO = 'x';
bool connexio_terra = false;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = BAUDS_PER_SEGON;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

Adafruit_BMP280 bmp;             // I2C
float PRESSIO_ALTURA_0 = 1032.0; // Ajustar el dia de la mesura
float ALTURA_0 = 16;

int num_paquet = 0;

int LLETRES = 5;
int MAX_SENYALS_MORSE = 5;

struct lletra_morse
{
    char lletra;
    int morse[MAX_SENYALS_MORSE];
}

struct lletra_morse alfabet = {
    {'a', {1, 2, 0, 0, 0}},
    {'b', {2, 1, 1, 1, 0}},
    {'c', {2, 1, 2, 1, 0}},
    {'d', {2, 1, 1, 0, 0}},
    {'e', {1, 0, 0, 0, 0}}
    };

void setup()
{
    Serial.begin(BAUDS_PER_SEGON);

    ss.begin(GPSBaud);

    // TEST FUNCIONAMENT BMP280
    while (!Serial)
        delay(100);
    unsigned status;
    status = bmp.begin();

    if (!status)
    {
        Serial.println("Error de connexió BMP280");
        while (1)
            delay(10);
    }

    pinMode(PIN_LED_BLAU, OUTPUT);
    pinMode(PIN_LED_VERD, OUTPUT);
    pinMode(PIN_LED_VERMELL, OUTPUT);
    pinMode(PIN_BRUNZIDOR, OUTPUT);
    pinMode(PIN_IR, INPUT);

    digitalWrite(PIN_LED_VERMELL, LOW);
    digitalWrite(PIN_LED_BLAU, LOW);
    digitalWrite(PIN_LED_VERD, LOW);

    // digitalWrite(PIN_RGB_VERMELL,HIGH);
}

void loop()
{

    int lectura_ir = digitalRead(PIN_IR);

    if (lectura_ir == 0)
    {
        digitalWrite(PIN_LED_VERMELL, HIGH);
        tone(PIN_BRUNZIDOR, 400);
    }
    else
    {
        digitalWrite(PIN_LED_VERMELL, LOW);
        noTone(PIN_BRUNZIDOR);
    }

    int lectura_termistor = analogRead(PIN_TERMISTOR);
    float pressio = bmp.readPressure();
    float temperatura_bmp280 = bmp.readTemperature();
    //  altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

    float altura_bmp280 = bmp.readAltitude(PRESSIO_ALTURA_0);

    Serial.print(num_paquet);
    Serial.print(",");
    Serial.print(millis()); // Milisegons
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

    while (ss.available() > 0)
    {
        if (gps.encode(ss.read()))
        {
            if (gps.location.isValid())
            {
                Serial.print(",");
                Serial.print(gps.date.day());
                Serial.print("/");
                Serial.print(gps.date.month());
                Serial.print("/");
                Serial.print(gps.date.year());

                Serial.print(",");
                Serial.print(gps.time.hour() + 1);
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

    if (connexio_terra == false)
    {
        tone(PIN_BRUNZIDOR, FREQ_BRUNZIDOR);
        delay(250);
        noTone(PIN_BRUNZIDOR);
    }

    if (Serial.available() != 0)
    {

        char caracter = Serial.read();

        if (connexio_terra == false)
        {
            if (caracter == CARACTER_INICI_CONNEXIO)
            { // Tenim connexió i ho indicam encenent el led verd
                digitalWrite(PIN_LED_VERD, HIGH);
                connexio_terra = true;
                Serial.println("Cansat Alicia Sintes, missatge rebut. Esperam comunicacio.");
            }
        }
        else
        {
            for (int i = 0; i < LLETRES; i++)
            {
                if (alfabet[i].lletra == caracter)
                {
                    for (int j = 0; j < MAX_SENYALS_MORSE; j++)
                    {
                        if (alfabet[i].morse[j] == 1)
                        {
                            tone(PIN_BRUNZIDOR, 300);
                            digitalWrite(PIN_LED_VERMELL, HIGH);
                            delay(TEMPS_PUNT);
                            noTone(PIN_BRUNZIDOR);
                            digitalWrite(PIN_LED_VERMELL, LOW);
                            delay(TEMPS_ENTRE_SENYAL);
                        }
                        if ((alfabet[i].morse[j] == 2))
                        {
                            tone(PIN_BRUNZIDOR, 300);
                            digitalWrite(PIN_LED_VERMELL, HIGH);
                            delay(TEMPS_RETXA);
                            noTone(PIN_BRUNZIDOR);
                            digitalWrite(PIN_LED_VERMELL, LOW);
                            delay(TEMPS_ENTRE_SENYAL);
                        }
                    }
                }
            }
            /*

            if (caracter == 's')
            {


                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_PUNT);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);

                delay(TEMPS_ENTRE_SENYAL);

                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_PUNT);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);

                delay(TEMPS_ENTRE_SENYAL);

                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_PUNT);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);
            }

            if (caracter == 'o')
            {

                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_RETXA);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);

                delay(TEMPS_ENTRE_SENYAL);

                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_RETXA);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);

                delay(TEMPS_ENTRE_SENYAL);

                tone(PIN_BRUNZIDOR, 300);
                digitalWrite(PIN_LED_VERMELL, HIGH);
                delay(TEMPS_RETXA);
                noTone(PIN_BRUNZIDOR);
                digitalWrite(PIN_LED_VERMELL, LOW);
            }
            */
        }
    }
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
    unsigned long start = millis();
    do
    {
        while (ss.available())
            gps.encode(ss.read());
    } while (millis() - start < ms);
}
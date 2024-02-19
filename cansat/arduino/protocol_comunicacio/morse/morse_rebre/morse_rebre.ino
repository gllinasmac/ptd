const int PIN_LED_ESPERA = 2;  //Verd
const int PIN_LED_ENVIAR = 8;  //Blau
const int PIN_LED_REBRE = 5;   //Vermell

const int PIN_BRUNZIDOR = 11;  //Millor si és analògic o
const int PIN_IR = 6;          ////Digital

const char CARACTER_INICI_CONNEXIO = '1';

bool connexio_terra = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_ESPERA, OUTPUT);
  pinMode(PIN_LED_REBRE, OUTPUT);
  pinMode(PIN_LED_ENVIAR, OUTPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_IR, INPUT);

  digitalWrite(PIN_LED_ESPERA, LOW);
  digitalWrite(PIN_LED_ENVIAR, LOW);
  digitalWrite(PIN_LED_REBRE, LOW);
}

void loop() {

  //Si rebem dades
  if (Serial.available() != 0) {
    char caracter = Serial.read();
    if (connexio_terra == false) {
      if (caracter == CARACTER_INICI_CONNEXIO) {

        digitalWrite(PIN_LED_ESPERA, HIGH);
        connexio_terra = true;
        Serial.println("Cansat Alicia Payne, missatge rebut. Esperam comunicació.");
      }
    } else {
      
      //Si rebem una a feim sonar el brunzidor.
      if (caracter == 's') {
        
        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms

        delay(1000);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(1000);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(1000);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor

        Serial.println("Rebut: S");
        //Tornam la dada a través del port sèrie i encemnem el LED blau
        digitalWrite(PIN_LED_ENVIAR, HIGH);
        Serial.println(caracter);
        delay(1000);
        digitalWrite(PIN_LED_ENVIAR, LOW);
      }
    }
  }

  delay(1000);
  digitalWrite(PIN_LED_REBRE, LOW);
}

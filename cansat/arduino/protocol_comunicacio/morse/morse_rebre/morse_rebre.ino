const int PIN_LED_VERD = 2;  //Verd
const int PIN_LED_BLAU = 8;  //Blau
const int PIN_LED_VERMELL = 5;   //Vermell

const int PIN_BRUNZIDOR = 11;  //Millor si és analògic o
const int PIN_IR = 6;          ////Digital

const char CARACTER_INICI_CONNEXIO = 'x';
const int TEMPS_PUNT = 1000;
const int TEMPS_RETXA = 3000;

bool connexio_terra = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_VERD, OUTPUT);
  pinMode(PIN_LED_VERMELL, OUTPUT);
  pinMode(PIN_LED_BLAU, OUTPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_IR, INPUT);

  digitalWrite(PIN_LED_VERD, LOW);
  digitalWrite(PIN_LED_BLAU, LOW);
  digitalWrite(PIN_LED_VERMELL, LOW);
}

void loop() {

  //Si rebem dades
  if (Serial.available() != 0) {
    char caracter = Serial.read();
    if (connexio_terra == false) {
      if (caracter == CARACTER_INICI_CONNEXIO) { //Tenim connexió i ho indicam encenent el led verd
        digitalWrite(PIN_LED_VERD, HIGH);
        connexio_terra = true;
        Serial.println("Cansat Alicia Payne, missatge rebut. Esperam comunicació.");
      }
    } else { 
      
      if (caracter == 's') {
        
        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        digitalWrite(PIN_LED_VERMELL, HIGH);
        delay(TEMPS_PUNT);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(TEMPS_PUNT);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(TEMPS_PUNT);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        Serial.println("Rebut: s");
      }

      if (caracter == 'o') {
        
        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        digitalWrite(PIN_LED_VERMELL, HIGH);
        delay(TEMPS_RETXA);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(TEMPS_RETXA);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        tone(PIN_BRUNZIDOR, 300);  //Encén el brunzidor a 100 Hz durant 1000 ms
        delay(TEMPS_RETXA);
        noTone(PIN_BRUNZIDOR); //Atura el brunzidor
        digitalWrite(PIN_LED_VERMELL, LOW);

        Serial.println("Rebut: o");
      }
    }
  }

  delay(1000);
}

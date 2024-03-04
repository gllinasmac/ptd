const int PIN_LED_VERD = 2; 
const int PIN_LED_BLAU = 8; 
const int PIN_LED_VERMELL = 5;

const int PIN_BRUNZIDOR = 11; 
const int PIN_IR = 6;         

const char CARACTER_INICI_CONNEXIO = 'x';
const int TEMPS_PUNT = 1000;
const int TEMPS_RETXA = 2000;
const int TEMPS_ENTRE_SENYAL = 1000;

bool connexio_terra = false;
bool esperant_dades = true;

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
    
    if (caracter == 's') {
      
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

    if (caracter == 'o') {
      
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
  }
  }

  delay(TEMPS_ENTRE_SENYAL);
}

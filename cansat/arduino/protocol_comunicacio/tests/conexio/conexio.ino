const int PIN_LED_VERD = 2;  //Verd
const int PIN_LED_BLAU = 8;  //Blau
const int PIN_LED_VERMELL = 5;   //Vermell

const char CARACTER_INICI_CONNEXIO = 'x';
bool connexio_terra = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_VERD, OUTPUT);
  pinMode(PIN_LED_VERMELL, OUTPUT);
  pinMode(PIN_LED_BLAU, OUTPUT);

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
        Serial.println("Cansat Alicia Payne, missatge rebut. Esperam comunicacio.");
      }
    } 
  }

  delay(1000);
}

const int PIN_LED_VERD = 2;  //Verd
const int PIN_LED_BLAU = 8;  //Blau
const int PIN_LED_VERMELL = 5;   //Vermell

bool connexio_terra = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_VERD, OUTPUT);
  pinMode(PIN_LED_BLAU, OUTPUT);
  pinMode(PIN_LED_VERMELL, OUTPUT);

  digitalWrite(PIN_LED_VERD, LOW);
  digitalWrite(PIN_LED_BLAU, LOW);
  digitalWrite(PIN_LED_VERMELL, LOW);
}

void loop() {

  //Si rebem dades
  if (Serial.available() != 0) {
    char caracter = Serial.read();
    if(caracter == "r"){
      digitalWrite(PIN_LED_VERD, LOW);
      digitalWrite(PIN_LED_BLAU, LOW);
      digitalWrite(PIN_LED_VERMELL, HIGH);
    }else if(caracter == "g"){
      digitalWrite(PIN_LED_VERD, HIGH);
      digitalWrite(PIN_LED_BLAU, LOW);
      digitalWrite(PIN_LED_VERMELL, LOW);
    }else if(caracter == "v"){
      digitalWrite(PIN_LED_VERD, LOW);
      digitalWrite(PIN_LED_BLAU, HIGH);
      digitalWrite(PIN_LED_VERMELL, LOW);
    }
  }

  delay(1000);
}

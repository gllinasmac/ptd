const int PIN_LED_ENVIAR = 4;  //Blau
const int PIN_LED_REBRE = 3;   //Verd
const int PIN_LED_ESPERA = 2;  //Vermell
const int PIN_BRUNZIDOR = 9;   //Millor si és analògic o PWM

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_ESPERA, OUTPUT);
  pinMode(PIN_LED_REBRE, OUTPUT);
  pinMode(PIN_LED_ENVIAR, OUTPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
}

void loop() {

  //Mentre esperam dades encenem el LED vermell
  if (Serial.available() == 0) {
    digitalWrite(PIN_LED_ESPERA, HIGH);
  }

  // Apagam el LED vermell i encenem el verd per indicar que hem rebut
  digitalWrite(PIN_LED_ESPERA, LOW);
  digitalWrite(PIN_LED_REBRE, HIGH);
  //Llegim un byte
  char caracter = Serial.read();
  delay(1000);
  digitalWrite(PIN_LED_REBRE, LOW);
  //Apagam el LED verd

  //Si rebem una a feim sonar el brunzidor.
  if (caracter == 's') {
    tone(PIN_BRUNZIDOR, 100, 1000);  //Encén el brunzidor a 100 Hz durant 1000 ms
    //delay(100);
    //noTone(PIN_BRUNZIDOR); //Atura el brunzidor


    //Tornam la dada a través del port sèrie i encemnem el LED blau
    digitalWrite(PIN_LED_ENVIAR, HIGH);
    Serial.println(caracter);
    delay(1000);
    digitalWrite(PIN_LED_ENVIAR, LOW);
  }
}

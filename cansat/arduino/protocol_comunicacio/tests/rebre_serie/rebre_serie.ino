int TEMPS_PUNT = 500;
int TEMPS_RETXA = 1000;
int DESCANS_PULSACIO = 500;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char dato = Serial.read();
    if (dato == 's') {
      //Serial.println(dato);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_PUNT);
      digitalWrite(LED_BUILTIN, LOW);
      delay(DESCANS_PULSACIO);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_PUNT);
      digitalWrite(LED_BUILTIN, LOW);
      delay(DESCANS_PULSACIO);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_PUNT);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (dato == 'o') {
      //Serial.println(dato);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_RETXA);
      digitalWrite(LED_BUILTIN, LOW);
      delay(DESCANS_PULSACIO);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_RETXA);
      digitalWrite(LED_BUILTIN, LOW);
      delay(DESCANS_PULSACIO);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(TEMPS_RETXA);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(1000);
}
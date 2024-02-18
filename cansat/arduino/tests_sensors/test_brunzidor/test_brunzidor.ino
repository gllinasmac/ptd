const int PIN_BRUNZIDOR = 11;
const int FREQUENCIA = 400;
const int DURACIO = 1000;
const int SILENCI = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BRUNZIDOR,OUTPUT);
}

void loop() {
  tone(PIN_BRUNZIDOR,FREQUENCIA);
  delay(DURACIO);
  noTone(PIN_BRUNZIDOR);
  delay(SILENCI);
}

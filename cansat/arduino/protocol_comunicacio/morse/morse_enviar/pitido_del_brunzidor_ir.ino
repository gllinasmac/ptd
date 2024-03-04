const int PIN_LED_VERD = 2;
const int PIN_LED_BLAU = 8;
const int PIN_LED_VERMELL = 5;

const int PIN_BRUNZIDOR = 11;
const int PIN_IR = 6;        

const int TEMPS_ESPERA = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_BLAU, OUTPUT);
  pinMode(PIN_LED_VERD, OUTPUT);
  pinMode(PIN_LED_VERMELL, OUTPUT);
  pinMode(PIN_BRUNZIDOR, OUTPUT);
  pinMode(PIN_IR, INPUT);

  digitalWrite(PIN_LED_VERMELL, LOW);
  digitalWrite(PIN_LED_BLAU, LOW);
  digitalWrite(PIN_LED_VERD, LOW);
}

void loop() {

  
  int lectura_ir = digitalRead(PIN_IR);
  Serial.println(lectura_ir);
  if(lectura_ir == 0){
    digitalWrite(PIN_LED_VERMELL, HIGH);
    tone(PIN_BRUNZIDOR, 400);
  }else{
    digitalWrite(PIN_LED_VERMELL, LOW);
    noTone(PIN_BRUNZIDOR);
  }

  delay(TEMPS_ESPERA);
}

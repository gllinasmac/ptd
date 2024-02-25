const int PIN_LED_ESPERA = 2;  //Verd
const int PIN_LED_ENVIAR = 8;  //Blau
const int PIN_LED_REBRE = 5;   //Vermell

const int PIN_BRUNZIDOR = 11;  //Millor si és analògic o
const int PIN_IR = 6;          ////Digital

const char CARACTER_INICI_CONNEXIO = 'x';
const int TEMPS_PUNT = 1000;
const int TEMPS_RETXA = 3000;

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

  
  int lectura_ir = digitalRead(PIN_IR);
  Serial.println(lectura_ir);

  delay(1000);
}

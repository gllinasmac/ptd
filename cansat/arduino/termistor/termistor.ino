const int PIN_TERMISTOR = 3;
const float R_AUX = 10000;
const float VCC = 5.0;
const float BETA = 3950.0; 
const float T0 = 298.15;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TERMISTOR,INPUT);

}

void loop() {
  int lectura = analogRead(PIN_TERMISTOR);
  Serial.print("Lectura analògica: ");
  Serial.println(lectura);
  Serial.print("Voltatge: ");
  float Vm = VCC * lectura / 1023.0;
  Serial.println(Vm);
  float R = R_AUX / ((VCC / Vm) - 1);
  Serial.print("Temperatura: ");
  float temp = BETA / (log(R / R_AUX) + (BETA / T0)) - 273.15;
  Serial.println(temp);
  delay(1000);
}

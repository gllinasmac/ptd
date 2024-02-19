//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {
  //mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {

  int lectura = analogRead(1);
   //mySerial.println("test");
   //mySerial.print("\n");
  Serial.print("Cototo,");
  Serial.print(lectura);
  Serial.print(",");
  Serial.println("test");
  delay(1000);

}

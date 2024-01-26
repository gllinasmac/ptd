int num_paquet = 0;
float pressio = 500;
float voltatge = 4.5;

void setup() {
  Serial.begin(9600);

}

void loop() {

  //1,Biel,440000,800,3.5
  //2,Biel,440000,820,3.3
  //3,Biel,440000,830,3.3

  Serial.print(num_paquet);
  Serial.print(",Biel,450000,");
  Serial.print(pressio);
  Serial.print(",");
  Serial.println(voltatge);
  delay(1000);
  
  if(pressio > 1100){
    pressio = 500;
    voltatge = 4.5;
    num_paquet = 0;
  }else{
    pressio -= 2;
    voltatge -= 0.01;
    num_paquet += 1;
  }

}

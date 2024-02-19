const int STOP_LED = 2;   //Vermell
const int START_LED = 3;  //Verd
const int SEND_LED = 4; //Blau
const int WAIT_LED = 5;   //Groc
const int PIN_BRUNZIDOR = 9;   //Millor si és analògic o PWM
bool start = false;       //Indica si començam el programa
int dada1 = 1024;
int dada2 = 10;

void setup() {
  Serial.begin(9600);
  pinMode(STOP_LED, OUTPUT);
  pinMode(WAIT_LED, OUTPUT);
  pinMode(START_LED, OUTPUT);
  pinMode(SEND_LED, OUTPUT);
  digitalWrite(STOP_LED, HIGH);
  digitalWrite(START_LED, LOW);
  digitalWrite(WAIT_LED, LOW);
  digitalWrite(SEND_LED, LOW);
}

void loop() {

  //Esperam que arribi una dada
  if (Serial.available() == 0) {
    digitalWrite(WAIT_LED, HIGH);
  } else {
    digitalWrite(WAIT_LED, LOW);
    
    

    char caracter_rebut = Serial.read();

    //Si rebem una s és la senyal per a començar a enviar les dades
    if (caracter_rebut == 's') {
      start = true;
      digitalWrite(START_LED, HIGH);
      digitalWrite(STOP_LED, LOW);
      Serial.println("Comensam transmissio");
    } else if (caracter_rebut == 't') {
      start = false;
      tone(PIN_BRUNZIDOR, 100, 1000); //Fem sonar per indicar que ha anat bé.
      Serial.println("test");
    } else if (caracter_rebut == 'a') { // Si rebem una 'a' vol dir que aturam la trasmissió
      start = false;
      digitalWrite(START_LED, LOW);
      digitalWrite(STOP_LED, HIGH);
      Serial.println("a");
    } else if (caracter_rebut == 'c' && start == true){
      // Si rebem una 'c' és la confirmació que s'ha rebut bé el missatge
      // Enviam les dades del cansat.
      digitalWrite(SEND_LED,HIGH);

      Serial.print(dada1);
      Serial.print(",");
      Serial.println(dada2);

      dada2 += 1;
      
      digitalWrite(SEND_LED,LOW);
      
    }else{
      //Marcam un error en la recepció de dades.
    }
  }
}

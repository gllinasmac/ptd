#include <FastLED.h>

//VARIABLES GLOBALS DE LA PLACA (NO TOCAR)

#define LED_TYPE WS2811 //Tipus de placa
#define COLOR_ORDER GRB //Model de color (RGB)

//VARIABLES GLOBALS DEL NOSTRE DIBUIX

#define LED_PIN 3 //Pin on connectam de l'Arduino
#define NUM_LEDS 64 //Quantitat de LEDs de la matriu (8x8 = 64)
#define BRIGHTNESS 100 //Brillantor dels LEDs (0 a 100)

//CRGB leds[NUM_LEDS]; //Cream un array de 64 leds

//DEFINIM ELS COLORS QUE VOLEM EMPRAR

CRGB n = CRGB(0,0,0); //Negre
CRGB v = CRGB(34,139,34); //Verd
CRGB g = CRGB(255,255,0); //Groc
CRGB t = CRGB(255,140,0); //Taronja
CRGB r = CRGB(255,10,147); //Rosa

//FEM ELS DIBUIXOS

CRGB leds[NUM_LEDS] = {
  n, r, n, n, n, n, n, n, 
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
  n, r, n, n, n, n, n, n,
};

CRGB leds_corregit[NUM_LEDS];

void setup() {

  //INICIALITZAM LA MATRIU, NO TOCAR

  delay(3000);  // power-up safety delay
  

  for(int dot = 0; dot < NUM_LEDS; dot++) {
    int fila = dot / 8;
    int columna = dot % 8;

    if (fila % 2 == 1){
      leds_corregit[dot] = leds[fila*8 + 7 - columna];
    }else{
      leds_corregit[dot] = leds[dot];
    }
  }

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds_corregit, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  //Passam el dibuix a la matriu
  /*
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = dibuix[i];
  }
  */
  FastLED.show(); //Mostram els colors

}

void loop() {

}

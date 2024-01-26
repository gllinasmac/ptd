#include <FastLED.h>

//VARIABLES GLOBALS DE LA PLACA (NO TOCAR)

#define LED_TYPE WS2811 //Tipus de placa
#define COLOR_ORDER GRB //Model de color (RGB)

//VARIABLES GLOBALS DEL NOSTRE DIBUIX

#define LED_PIN 3 //Pin on connectam de l'Arduino
#define NUM_LEDS 64 //Quantitat de LEDs de la matriu (8x8 = 64)
#define BRIGHTNESS 100 //Brillantor dels LEDs (0 a 100)

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);  // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
}

void loop() {

  //Al revés
  
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    int fila = dot / 8;
    int columna = dot % 8;
    if (fila % 2 == 1){
      leds[fila*8 + 7 - columna] = CRGB::Blue;
      FastLED.show();
      leds[fila*8 + 7 - columna] = CRGB::Black;
    }else{
      leds[dot] = CRGB::Blue;
      FastLED.show();
      // clear this led for the next time around the loop
      leds[dot] = CRGB::Black;
    }
    delay(100);
  }
  
  /*
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Blue;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);
    }
  */
}

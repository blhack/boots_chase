#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 200

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define CLOCK_PIN 8

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  leds[0] = CRGB::Black;
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void blackout() {
  for (int i = 0; i < NUM_LEDS - 1; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void shift() {
 for (int i = NUM_LEDS-1; i>=1; i--) {
  leds[i] = leds[i-1];
 }
  FastLED.show(); 
}

void random_color(int index, int maxi) {
   leds[index].r = random(0,analogRead(0)/4);
   leds[index].g = random(0,analogRead(1)/4);
   leds[index].b = random(0,analogRead(1)/4);
}

void fill_random(int count) {
  for (int i = 1; i < count; i++) {
    random_color(i, 255.0/i);
  }
}
  

void loop() {
  //blackout();
  fill_random(random(0,20));
  for (int i = 0; i < NUM_LEDS; i++) {
    shift();
    if (random(0,10) == 1) {
      fill_random(random(0,10)); 
    }
    delay(30);
  }
  Serial.println(analogRead(0)/4);
  delay(100);
}

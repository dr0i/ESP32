#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 20

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.
#define DATA_PIN 4

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  clearAllLeds();
}

void loop() {
  clearAllLeds();
  smileyLaugh();
  clearAllLeds();
  smileySad();
  clearAllLeds();
  smileyNeutral();
}

void smileyLaugh()
{
  leds[0] = CRGB::Green;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Green;
  leds[3] = CRGB::Green;
  leds[4] = CRGB::Green;
  leds[5] = CRGB::Green;
  leds[8] = CRGB::Green;
  leds[9] = CRGB::Green;
  leds[13] = CRGB::Green;
  leds[14] = CRGB::Green;
  leds[17] = CRGB::Green;
  leds[18] = CRGB::Green;
  leds[19] = CRGB::Green;
  FastLED.show();
  delay(2500);
}

void smileySad()
{
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  leds[6] = CRGB::Red;
  leds[7] = CRGB::Red;
  leds[9] = CRGB::Red;
  leds[10] = CRGB::Red;
  leds[11] = CRGB::Red;
  leds[12] = CRGB::Red;
  leds[14] = CRGB::Red;
  leds[15] = CRGB::Red;
  leds[16] = CRGB::Red;
  FastLED.show();
  delay(2500);
}

void smileyNeutral()
{
  leds[1] = CRGB::Yellow;
  leds[2] = CRGB::Yellow;
  leds[3] = CRGB::Yellow;
  leds[4] = CRGB::Yellow;
  leds[9] = CRGB::Yellow;
  leds[12] = CRGB::Yellow;
  leds[14] = CRGB::Yellow;
  leds[10] = CRGB::Yellow;
  leds[11] = CRGB::Yellow;
  leds[19] = CRGB::Yellow;
  leds[17] = CRGB::Yellow;
  leds[18] = CRGB::Yellow;
  FastLED.show();
  delay(2500);
}

// turn the LED off, then pause
void clearAllLeds()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

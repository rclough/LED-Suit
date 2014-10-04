#include "Animation.h"

Sparkle::Sparkle () {
  reset();
}

void Sparkle::draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step) {
  for (int i=0;i<NUM_STRIP;i++) {
    for (int j=0; j<STRIP_LEN;j++) {
      leds[i][j] -= CRGB(10,10,10);
      if (leds[i][j]) {
        continue;
      }
      if (random16(PROB) == 2) {
        leds[i][j] = CHSV(0,0,255);
      }
    }
    FastLED.delay(1000/FPS);
  }
}

void Sparkle::reset() {
}

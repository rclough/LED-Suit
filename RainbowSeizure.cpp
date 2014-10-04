#include "Animation.h"

RainbowSeizure::RainbowSeizure () {
  reset();
}

void RainbowSeizure::draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step) {
  int shift = (step/4) % STRIP_LEN;
  int flash_rate = FPS/15;
  if (step%(flash_rate) < flash_rate/2) {
    // Black out strip
    for (int strip=0; strip < NUM_STRIP; strip++) {
      for (int i=0;i<STRIP_LEN;i++) {
        leds[strip][i] = CRGB::Black;
      }
    }
  } else {
    // Flash some rainbows!
    for (int i=0;i<STRIP_LEN;i++) {
      int index = (i+shift) % STRIP_LEN;
      if (i % RS_BAR_SIZE < (RS_BAR_SIZE/4)) {
        // Draw Color bar
        int prehue = index-shift;
        if (prehue < 0) {
          prehue += STRIP_LEN;
        }
        int hue = map(prehue,0,STRIP_LEN,0,255);
        for (int strip=0; strip < NUM_STRIP; strip++) {
          leds[strip][index] = CHSV(hue,255,255);
        }
      } else {
        // Draw black bar
        for (int strip=0; strip < NUM_STRIP; strip++) {
          leds[strip][index] = CRGB::Black;
        }
      }
    }
  }
  FastLED.delay(1000/FPS);
}

void RainbowSeizure::reset() {
}

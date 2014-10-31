#include "Animation.h"

RainbowWaves::RainbowWaves () {
  Serial.println("RWAVE");
  reset();
}

void RainbowWaves::draw(CRGB leds[NUM_STRIP][STRIP_LEN],uint32_t step) {
  for (int i=0;i<NUM_STRIP;i++) {
    for (int j=0; j<STRIP_LEN;j++) {
      int shifter = (i*STRIP_LEN)+j;
      int fast_wave = quadwave8( shifter*20+step*4 );
      leds[i][j] = CHSV(quadwave8( shifter*6-step ),255,fast_wave);
    }
  }
  FastLED.delay(1000/FPS);
}

void RainbowWaves::reset() {
}

#include "Animation.h"

Pulse::Pulse () {
  reset();
}

void Pulse::draw(CRGB leds[NUM_STRIP][STRIP_LEN], uint32_t step) {
  for (int i=0;i<NUM_STRIP;i++) {
    for (int j=0; j<STRIP_LEN;j++) {
      int shifter = (i*STRIP_LEN)+j;
      int slow_wave = quadwave8( shifter/2+step );
      int fast_wave = quadwave8( shifter*20+step*4 );
      leds[i][j] = CHSV(quadwave8( step/15 ),255,map(fast_wave,0,255,0, slow_wave));
    }
  }
  FastLED.delay(1000/FPS);
}

void Pulse::reset() {
}

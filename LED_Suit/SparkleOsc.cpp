#include "Animation.h"

SparkleOsc::SparkleOsc () {
  del = 1000/FPS;
  reset();
}

SparkleOsc::SparkleOsc(int fps) {
  this->del = 1000/fps; 
  reset();
}

void SparkleOsc::draw(CRGB leds[NUM_STRIP][STRIP_LEN],uint32_t step) {
  int tick = step*3;
  for (int i=0;i<LEVEL;i++) {
    int pixel = (OSC_SIZE*i)+map(triwave8(tick),0,255,0,30);
    leds[0][pixel] = CHSV(tick/OSC_SIZE,255,255);
    
    if (pixel+1 < OSC_SIZE*(i+1)) {
      leds[0][pixel+1] = CHSV(tick/OSC_SIZE,255,100);
    }
    if (pixel-1 >= OSC_SIZE*i) {
      leds[0][pixel-1] = CHSV(tick/OSC_SIZE,255,100);
    }
  }
  
  int i = random16(10);
  // only write sparkle once every 4 frames
  if (step%8 == 0) {
    while(i<NUM_PANT) {
      leds[0][i] = CHSV(0,0,random8(150));
      i+=random8(1,10);
    }
  } else {
    // Fade
    for (int i=0; i<STRIP_LEN;i++) {
      leds[0][i] /= 2;
    }
  }
  
  // Duplicate to other strands
  for (int i=1;i<NUM_STRIP;i++) {
    for (int j=0;j<STRIP_LEN;j++) {
      leds[i][j] = leds[0][j];
    }
  }
  FastLED.delay(del);
}

void SparkleOsc::reset() {
}

#include "Animation.h"

Splash::Splash () {
  reset();
}

void Splash::draw(CRGB leds[NUM_STRIP][STRIP_LEN], unsigned int step) {
  reset_check(leds);
  for (int i=0; i<NUM_SPLASH;i++) {
    // Activate a splatter  1/SPLASH_CHANCE probability
    if (!active[i] && random16(SPLASH_CHANCE) == 23) {
      active[i] = true;
      cs[i] = random16(STRIP_LEN);
      strip[i]=random16(NUM_STRIP);
    }
    if (active[i]) {
      // Draw current tick
      if (tick[i] < SPLASH_FADE) {
        // Increasing brightness
        drawTail(cs[i],0,tick[i],leds[strip[i]]);
      } 
      else if (tick[i] >= SPLASH_FADE) {
        // Decreasing brightness
        drawTail(cs[i],0,(SPLASH_FADE*2)-tick[i],leds[strip[i]]);
      }
      tick[i]++;

      // Terminate splash if enough ticks passed
      if (tick[i] > SPLASH_FADE*2) {
        active[i] = false;
        tick[i]=0;
        strip[i]=0;
        cs[i]=0;
      }  
    }
  }
  FastLED.delay(1000/FPS);
}

void Splash::reset() {
  for (int i=0; i<NUM_SPLASH;i++) {
    active[i] = false;
    tick[i]=0;
    cs[i]=0;
  }
  has_reset=true;
}

/**
 * drawTail() - draw a pixel with a tail on either side (splatter)
 * 
 * venter: center LED of the splatter
 * part: part of the tail we're on (0 to SPLASH_TAIL inclusive)
 * scale: how much to scale brightness by
 * array: array of LEDs to operate on
 */
void Splash::drawTail(int center, int part, int scale, CRGB array[]) {
  // First LED, recurse down to the next
  if (part == 0) {
    array[center] = CHSV(0,0,(255*scale)/SPLASH_FADE);
    return drawTail(center, part+1, scale, array);
  }
  // Check if we're done drawing
  if (part > SPLASH_TAIL) {
    return;
  }
  // non negative modulus operator is poo
  int l_tail = (((center-part) % STRIP_LEN) + STRIP_LEN) % STRIP_LEN;
  int r_tail = (center+part) % STRIP_LEN;
  // Generate the raw brightness  for this position, then scale
  int raw_bright = map(part,0,SPLASH_TAIL,100,0);
  int scaled_bright = (raw_bright*scale)/SPLASH_FADE;
  // Clip low light LEDs to black
  if (scaled_bright <8) {
    scaled_bright = 0;
  }
  array[l_tail] = CHSV(0,0,scaled_bright);
  array[r_tail] = CHSV(0,0,scaled_bright);
  return drawTail(center,part+1, scale, array);
}

void Splash::reset_check(CRGB leds[NUM_STRIP][STRIP_LEN]) {
  if (has_reset) {
    has_reset = false;
    // Black out
    for (int i=0; i<NUM_STRIP;i++) {
      for (int j=0; j<STRIP_LEN; j++) {
        leds[i][j] = CRGB::Black;
      }
    }
  }
}


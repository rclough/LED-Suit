#include "Animation.h"

RainbowTails::RainbowTails () {
  #if DEBUG
  Serial.println("RTAILS");
  #endif
  currentPalette = RainbowColors_p;
  currentBlending = BLEND;
  reset();
}

void RainbowTails::draw(CRGB leds[NUM_STRIP][STRIP_LEN],uint32_t step) {
  // Shift is used to move the "starting" pixel. each step, it moves over 1
  // until it hits the end of the loop and starts over
  uint8_t shift = (step/2) % STRIP_LEN;

  // Pallette shift
  if ((step % 300) == 0){
    ChangePalettePeriodically();
  }
  for (int16_t i=0;i<NUM_STRIP;i++) {
    fill_solid(leds[i], STRIP_LEN, CRGB::Black);
    for (int16_t j=0; j<STRIP_LEN;j += TAIL_LEN) {
      // Calculate what part of the loop the pixel starts w/ shift
      uint16_t shifted_pixel = j + shift;
      if (shifted_pixel >= STRIP_LEN) {
          
        shifted_pixel -= STRIP_LEN;
      }
      uint8_t color = (j/TAIL_LEN)*(255/(STRIP_LEN/TAIL_LEN));
      drawTail(leds[i], shifted_pixel, 0, color);
    }
  }
  FastLED.delay(1000/FPS);
}

void RainbowTails::drawTail(CRGB leds[STRIP_LEN],int16_t start_led, uint8_t tail_level, uint8_t color) {
  if (tail_level > TAIL_LEN-4 ) {
    return;
  }
  // Determine which LED we're coloring
  int16_t target = start_led-tail_level;
  if (target < 0) {
    target += STRIP_LEN;
  }
  uint8_t brightness = map(tail_level, 0, TAIL_LEN-4, 255, 0);
  leds[target] = ColorFromPalette( currentPalette, color, brightness, currentBlending);

  drawTail(leds,start_led,tail_level+1,color);
}

void RainbowTails::reset() {
}

void RainbowTails::ChangePalettePeriodically()
{
  uint8_t choice = (millis() / 1000) % 7;
  if( choice == 0)  { currentPalette = RainbowColors_p;   currentBlending = BLEND; }  if( choice == 1)  { currentPalette = CloudColors_p;     currentBlending = BLEND; }
  if( choice == 2)  { currentPalette = LavaColors_p;      currentBlending = BLEND; }
  if( choice == 3)  { currentPalette = OceanColors_p;     currentBlending = BLEND; }
  if( choice == 4)  { currentPalette = ForestColors_p;    currentBlending = BLEND; }
  if( choice == 5)  { SetupPurpleAndGreenPalette();       currentBlending = BLEND; }
  if( choice == 6)  { SetupCoolPalette();       currentBlending = BLEND; }
}

void RainbowTails::SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;
  
  currentPalette = CRGBPalette16( 
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}
void RainbowTails::SetupCoolPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB blue  = CHSV( HUE_BLUE, 255, 255);
  CRGB pink  = CHSV( HUE_PINK, 255, 255);
  
  currentPalette = CRGBPalette16( 
    purple,  purple,  blue,  blue,
    pink, pink, blue,  blue,
    purple,  purple,  blue,  blue,
    pink, pink, blue,  blue  );
}

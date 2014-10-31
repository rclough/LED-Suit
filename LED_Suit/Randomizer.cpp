#include "Animation.h"

uint8_t shift;
boolean direction;
uint8_t fps;
uint8_t elapse;
uint32_t then;
boolean blink;

Randomizer::Randomizer () {
  #if DEBUG
  Serial.println("Randomizer");
  #endif
  currentPalette = RainbowColors_p;
  currentBlending = BLEND;
  shift = 0;
  direction = 0;
  fps = FPS;
  elapse = 4;
  then = millis()/1000;
  blink = 0;
  reset();
}

void Randomizer::draw(CRGB leds[NUM_STRIP][STRIP_LEN],uint32_t step) {

  // should we randomize?
  uint32_t now = millis()/1000; // time in seconds
  if (now-then > elapse) {
    then = now;
    elapse = random8(1,5); // seconds to next randomize
    fps = random8(15,150); // FPS/Speed
    if (random8(5) == 0) {
      ChangePalettePeriodically();
    }
    direction++;
    if (random8(2) == 0) {
      direction++;
    }
    direction = direction % 4;
    blink = random8(2);
  }

  for (int16_t i=0;i<NUM_STRIP;i++) {
    fill_solid(leds[i], STRIP_LEN, CRGB::Black);
    if (!blink || step % 4 < 2) {
      for (int16_t j=0; j<STRIP_LEN;j++) {
        // Blocks of 4, only color even blocks
        uint8_t target = j+shift;
        if ((j) % 8 < 4) {
          if (target >= STRIP_LEN) {
            target -= STRIP_LEN;
          }
          uint8_t color= map(j,0,STRIP_LEN,0,255);
          leds[i][target] = ColorFromPalette( currentPalette, color, 255, currentBlending);
        }
      }
    }
  }
  if (direction < 2) {
    if (shift >= STRIP_LEN) {
      shift = 0;
    } else {
      shift++;
    }
  } else {
    if (shift == 0) {
      shift = STRIP_LEN-1;
    } else {
      shift--;
    }
  }
  FastLED.delay(4000/fps);
}

void Randomizer::reset() {
}

void Randomizer::ChangePalettePeriodically()
{
  uint8_t choice = (millis() / 1000) % 7;
  if( choice == 0)  { currentPalette = RainbowColors_p;   currentBlending = BLEND; }  if( choice == 1)  { currentPalette = CloudColors_p;     currentBlending = BLEND; }
  if( choice == 2)  { currentPalette = LavaColors_p;      currentBlending = BLEND; }
  if( choice == 3)  { currentPalette = OceanColors_p;     currentBlending = BLEND; }
  if( choice == 4)  { currentPalette = ForestColors_p;    currentBlending = BLEND; }
  if( choice == 5)  { SetupPurpleAndGreenPalette();       currentBlending = BLEND; }
  if( choice == 6)  { SetupCoolPalette();       currentBlending = BLEND; }
}

void Randomizer::SetupPurpleAndGreenPalette()
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
void Randomizer::SetupCoolPalette()
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

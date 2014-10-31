#include <FastLED.h>
#include "includes.h"
#include "Animation.h"

CRGB leds[NUM_STRIP][STRIP_LEN];

// Animations
Animation* animation[NUM_ANIMATIONS] =
{
  new Randomizer(),
  new RainbowTails(),
  new RainbowWaves(),
  new Pulse(),
  new Sparkle(),
  new SparkleOsc(30),
  new SparkleOsc(),
  new Splash(),
  new RainbowSeizure()
};

// Other initializations
uint8_t buttonState;
boolean held;
uint32_t last_p;
uint32_t step;
uint8_t current_animation;
uint32_t last_change;

void setup() {
  #if DEBUG
  Serial.begin(9600);
  #endif

  // Used to give a master "step" to animations
  step = 0;
  
  // Button related variables
  pinMode(B_PIN, INPUT);
  buttonState = 0;
  held = false;
  last_p = millis();

  // Set up LEDs
  #if V == PANTS
  FastLED.addLeds<WS2812B,R_PANT_PIN,GRB>(leds[R_PANT_STRIP],NUM_PANT);
  FastLED.addLeds<WS2812B,L_PANT_PIN,GRB>(leds[L_PANT_STRIP],NUM_PANT);
  #elif V == JACKET
  FastLED.addLeds<WS2812B,R_CHEST_PIN,GRB>(leds[R_CHEST_STRIP],NUM_CHEST);
  FastLED.addLeds<WS2812B,L_CHEST_PIN,GRB>(leds[L_CHEST_STRIP],NUM_CHEST);
  FastLED.addLeds<WS2812B,R_ARM_PIN,GRB>(leds[R_ARM_STRIP],NUM_ARM);
  FastLED.addLeds<WS2812B,L_ARM_PIN,GRB>(leds[L_ARM_STRIP],NUM_ARM);
  #endif
  
  // Set up animations
  FastLED.setBrightness(BRIGHTNESS);
  current_animation = 0;
  last_change = millis();
}

uint16_t seconds = 0;
void loop() {
  if (millis()-last_change > 1000) {
    seconds++;
    last_change=millis();
  }
  if (change_animation() || seconds >= 5*60) {
    animation[current_animation]->reset();
    current_animation = (current_animation + 1) % NUM_ANIMATIONS;
    seconds = 0;
  }
  // Execute frame
  animation[current_animation]->draw(leds,step++);
}


/**
 * Handle detection of button presses and debouncing
 */
boolean change_animation() {
  buttonState = digitalRead(B_PIN);
  uint32_t elapsed = millis()-last_p;

  if (elapsed > DEBOUNCE) {
    // Check for button release
    if (buttonState == LOW && held) {     
      held = false;

      // Don't allow to go if its "pressed" too fast
      if (elapsed > PRESS_LIMIT) {
        return true;
      }

      // Prevents rapid retrigger glitch
      last_p = millis();
    } 
    else if (buttonState == HIGH && !held && elapsed > DEBOUNCE) {
      held = true;
    }
  }
  return false;
}


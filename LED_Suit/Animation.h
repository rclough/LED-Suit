#include "includes.h"
#include <FastLED.h>

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
  public:
    virtual void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step) = 0;
    virtual void reset() = 0;
  private:
};

class RainbowSeizure : public Animation
{
  public:
    RainbowSeizure();
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
};

class Splash : public Animation
{
  public:
    Splash();
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
    boolean active[NUM_SPLASH];
    int tick[NUM_SPLASH];
    int cs[NUM_SPLASH];
    int strip[NUM_SPLASH];
    boolean has_reset;
    void drawTail(int center, int part, int scale, CRGB array[]);
    void reset_check(CRGB leds[NUM_STRIP][STRIP_LEN]);
};

class SparkleOsc : public Animation
{
  public:
    SparkleOsc();
    SparkleOsc(int brightness);
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
    int del;
};

class Sparkle : public Animation
{
  public:
    Sparkle();
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
};

class Pulse : public Animation
{
  public:
    Pulse();
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
};

class RainbowWaves : public Animation
{
  public:
    RainbowWaves();
    void draw(CRGB leds[NUM_STRIP][STRIP_LEN],unsigned int step);
    void reset();
   private:
};

#endif /* ANIMATION_H */

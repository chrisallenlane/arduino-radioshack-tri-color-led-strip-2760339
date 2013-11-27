/**
 * @todo:
 * - More sequences
 * - Write to PROGMEM where appropriate
 * - Segment methods: alpha(), rgb(), fadeBy(), fadeTo()?
 * - Comments (autodocs?) and README
 * - Pass arguments via structs?
 * - expose strip.animation_delay
 */

#define STRIP_PINOUT (DDRC=0xFF)  // for UNO

#include <avr/pgmspace.h>

#include "../lib/segment.cpp"
#include "../lib/strip.cpp"

Strip strip(10, 25);
  
void setup() {
  // set the pinout
  STRIP_PINOUT;

  // clear the strip
  strip.clear();
  delay(10);
}

void loop() {

  // @todo: write some example sequences here
  /*
  uint32_t red    = 0xFF0000FF;
  uint32_t orange = 0xFFA500FF;
  uint32_t yellow = 0xFFFF00FF;
  uint32_t green  = 0x00FF00FF;
  uint32_t blue   = 0x0000FFFF;
  uint32_t indigo = 0x4B0082FF;
  uint32_t violet = 0x82EE82FF;
  uint32_t white  = 0xFFFFFFFF;
  */
  
  delay(500);

  strip.sequence_solid(0xFF00FFFF);
  strip.sequence_fade(0x00);
  strip.sequence_fade(0xFF);
}

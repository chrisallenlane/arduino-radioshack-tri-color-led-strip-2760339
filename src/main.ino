/**
 * @todo:
 * - More sequences
 * - Write to PROGMEM where appropriate
 * - Segment methods: alpha(), rgb(), fadeBy(), fadeTo()?
 * - Comments (autodocs?) and README
 */

#define STRIP_PINOUT (DDRC=0xFF)  // for UNO

#include <avr/pgmspace.h>

#include "../lib/segment.h"
#include "../lib/strip.h"

#include "../lib/segment.cpp"
#include "../lib/strip.cpp"

Strip strip(10, 50);
  
void setup() {
  // set the pinout
  STRIP_PINOUT;

  // clear the strip
  strip.clear();
  delay(1000);
}

void loop() {
  uint32_t red    = 0xFF0000FF;
  uint32_t orange = 0xFFA500FF;
  uint32_t yellow = 0xFFFF00FF;
  uint32_t green  = 0x00FF00FF;
  uint32_t blue   = 0x0000FFFF;
  uint32_t indigo = 0x4B0082FF;
  uint32_t violet = 0x82EE82FF;
  uint32_t white  = 0xFFFFFFFF;

  strip.sequence_scroll(orange);
  strip.sequence_scroll(red);
}

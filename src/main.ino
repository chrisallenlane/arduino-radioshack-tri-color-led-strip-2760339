/**
 * @todo:
 * - move #defines into constants?
 * - interactive sensors
 * - buy AVR book
 * - read C books
 * - fix color specification byte order (want RGB)
 */

#define STRIP_PINOUT (DDRC=0xFF)  // for UNO

//            0xGGBBRR
//#define COLOR 0x00FF33
#define OFF   0x000000
#define COLOR 0xFF0000
#define RED   0x0000FF
#define BLUE  0x00FF00
#define GREEN 0xFF0000

#include <avr/pgmspace.h>

#include "../lib/strip.h"
#include "../lib/segment.h"

#include "../lib/segment.cpp"
#include "../lib/strip.cpp"


// initialize our strip
Strip strip(10);


void setup() {
  // set the pinout
  STRIP_PINOUT;

  // blank out the strip
  strip.clear();

  // I seem to need this, though I don't know why
  delay(250);
}


void loop() {
  delay(250);

  //strip.push_solid(COLOR);
  //strip.sequence_radiate(COLOR);
  strip.sequence_scroll(COLOR);
}

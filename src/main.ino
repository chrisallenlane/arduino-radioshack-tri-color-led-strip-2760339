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
#define COLOR 0x00FF33
#define OFF   0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF

#include <avr/pgmspace.h>

#include "../lib/strip.h"
#include "../lib/segment.h"

#include "../lib/segment.cpp"
#include "../lib/strip.cpp"


// initialize our strip
Strip strip(10, 250);


void setup() {
  Serial.begin(9600);

  // set the pinout
  STRIP_PINOUT;

  // blank out the strip
  strip.clear();

  // I seem to need this, though I don't know why
  delay(250);
}


void loop() {
  uint32_t red    = 0xFF0000;
  uint32_t orange = 0xFFA500;
  uint32_t yellow = 0xFFFF00;
  uint32_t green  = 0x00FF00;
  uint32_t blue   = 0x0000FF;
  uint32_t indigo = 0x4B0082;
  uint32_t violet = 0x82EE82;
  uint32_t white  = 0xFFFFFF;

  strip.clear();
  delay(2000);

  strip.sequence_solid(red);
  delay(1000);
  strip.sequence_solid(orange);
  delay(1000);
  strip.sequence_solid(yellow);
  delay(1000);
  strip.sequence_solid(green);
  delay(1000);
  strip.sequence_solid(blue);
  delay(1000);
  strip.sequence_solid(indigo);
  delay(1000);
  strip.sequence_solid(violet);
  delay(1000);
  strip.sequence_solid(white);
  delay(1000);
}

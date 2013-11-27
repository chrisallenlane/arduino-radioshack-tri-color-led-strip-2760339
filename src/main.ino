/**
 * @todo:
 * - RGBA support
 * - Sequence class
 * - Segment::write() -> Segment::buffer()
 * - Make segements individually addressible with overloaded color() method
 * - More sequences
 */
#define STRIP_PINOUT (DDRC=0xFF)  // for UNO

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
  uint32_t red    = 0xFF0000FF;
  uint32_t orange = 0xFFA500FF;
  uint32_t yellow = 0xFFFF00FF;
  uint32_t green  = 0x00FF00FF;
  uint32_t blue   = 0x0000FFFF;
  uint32_t indigo = 0x4B0082FF;
  uint32_t violet = 0x82EE82FF;
  uint32_t white  = 0xFFFFFFFF;

  /*
  uint32_t red    = 0xFF000066;
  uint32_t orange = 0xFFA50066;
  uint32_t yellow = 0xFFFF0066;
  uint32_t green  = 0x00FF0066;
  uint32_t blue   = 0x0000FF66;
  uint32_t indigo = 0x4B008266;
  uint32_t violet = 0x82EE8266;
  uint32_t white  = 0xFFFFFF66;
  */

  strip.clear();
  delay(2000);

  strip.sequence_solid(red);
  delay(1000);
  strip.sequence_solid(0xFF000055);
  delay(1000);
  strip.sequence_solid(0xFF000022);
  delay(1000);
  strip.sequence_solid(0xFF000002);
  delay(1000);
  strip.sequence_solid(0xFF000000);
  delay(1000);
  /*
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
  */
}

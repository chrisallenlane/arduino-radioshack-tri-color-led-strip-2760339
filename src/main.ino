/**
 * @todo:
 * - More sequences (strobe)
 * - Write to PROGMEM where appropriate
 * - README
 * - Convert into "proper" library?
 * - name and publish
 * - sample sequences
 * - move sequences into optional file? (Keep library small)
 * - ability to play "generic" sequences?
 * - safety delay on Strip::write()?
 */

#define STRIP_PINOUT (DDRC=0xFF)  // for UNO

#include <avr/pgmspace.h>

#include "../lib/segment.cpp"
#include "../lib/strip.cpp"


// initialize our global strip object
Strip strip(10, 25);
  

// set the output pins and clear the strip
void setup() {
  STRIP_PINOUT;
  strip.clear();
  delay(10);
}


// Go!
void loop() {

  // @todo: write some example sequences here
  uint32_t red    = 0xFF0000FF;
  uint32_t orange = 0xFFA500FF;
  uint32_t yellow = 0xFFFF00FF;
  uint32_t green  = 0x00FF00FF;
  uint32_t blue   = 0x0000FFFF;
  uint32_t indigo = 0x4B0082FF;
  uint32_t violet = 0x82EE82FF;
  uint32_t white  = 0xFFFFFFFF;
  


  // Fade in/out
  //strip.sequence_solid(0xFF00FFFF);
  strip.sequence_solid(0x0033FFFF);
  strip.sequence_fade(0x00);
  strip.sequence_fade(0xFF);
  delay(500);


  // Alarm
  /*
  strip.animation_delay = 50;
  strip.sequence_scroll(red);
  strip.sequence_scroll(orange);
  */


  // Cylon
  /*
  strip.animation_delay = 50;
  strip.sequence_cylon(red);
  */
  
  // Radiate
  /*
  strip.animation_delay = 70;
  strip.sequence_radiate(yellow);
  */
}

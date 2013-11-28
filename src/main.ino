/**
 * @todo:
 * - README
 * - Convert into "proper" library?
 * - name and publish
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
  // @todo: put these somewhere?
  uint32_t red    = 0xFF0000FF;
  uint32_t orange = 0xFFA500FF;
  uint32_t yellow = 0xFFFF00FF;
  uint32_t green  = 0x00FF00FF;
  uint32_t blue   = 0x0000FFFF;
  uint32_t indigo = 0x4B0082FF;
  uint32_t violet = 0x82EE82FF;
  uint32_t white  = 0xFFFFFFFF;


  // Fade in/out
  /*
  strip.sequence_solid(0x0033FFFF);
  strip.sequence_fade(0x00);
  strip.sequence_fade(0xFF);
  delay(500);
  */

  // Random fade in/out
  strip.sequence_fade(0x00);

  uint32_t random_color = (random(1, 16777215) << 8);

  for (byte i = 0; i < 10; i++) {
    strip.segments[i].color(random_color);
  }

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

  // Strobe
  /*
  strip.animation_delay = 150;
  strip.sequence_strobe(0xFFFFFFFF);
  */
}

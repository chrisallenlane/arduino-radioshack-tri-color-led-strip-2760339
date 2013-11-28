#define OFF   0x000000

#include "Arduino.h"
#include "strip.h"


/**
 * Default constructor
 *
 * @return void
 */
Strip::Strip(byte number_of_segments, unsigned short animation_delay) {
  this->_number_of_segments = number_of_segments;
  this->animation_delay     = animation_delay;
}

/**
 * Sets the alpha of every segment on the strip to the supplied alpha value
 *
 * @param uint32_t alpha
 * @return void
 */
void Strip::alpha(uint32_t alpha) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].alpha(alpha);
  }
  this->write();
}


/**
 * Blanks out the strip
 *
 * @return void
 */
void Strip::clear() {
  this->sequence_solid(0x0);
}


/**
 * Reads an array of bytes
 */
void Strip::read(uint32_t sequence[]) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].color(sequence[i]);
  }
}


/**
 * Pushes bytes out to the physical strip. It does this by flushing the color
 * buffers of each segment iteratively.
 *
 * @return void
 */
void Strip::write() {
  noInterrupts();
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].write();
  }
  interrupts();
}


/*****************************************************************************
 * Sequences
 ****************************************************************************/

/**
 * Turns the strip a solid color
 *
 * @param uint32_t color
 * @return void
 */
void Strip::sequence_solid(uint32_t color) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].color(color);
  }
  this->write();
}


/**
 * Makes the strip radiate light out from the center
 *
 * @param uint32_t color
 * @return void
 */
void Strip::sequence_radiate(uint32_t color) {
  this->clear();

  uint32_t sequence[6][10] = {
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , color , color , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , color , color , color , color , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , color , color , color , color , color , color , OFF   , OFF}   ,
    {OFF   , color , color , color , color , color , color , color , color , OFF}   ,
    {color , color , color , color , color , color , color , color , color , color} ,
  };

  for (byte i = 0; i < 6; i++) {
    this->read(sequence[i]);
    this->write();
    delay(this->animation_delay);
  }
} 


/**
 * Scrolls light in one direction across the strip
 *
 * @param uint32_t color
 * @return void
 */
void Strip::sequence_scroll(uint32_t color) {
  this->clear();

  uint32_t sequence[10][10] = {
    {color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color} ,
  };

  for (byte i = 0; i < 10; i++) {
    this->read(sequence[i]);
    this->write();
    delay(this->animation_delay);
  }
} 


/**
 * Boundes a light back and forth from end-to-end.
 *
 * @param uint32_t color
 * @return void
 */
void Strip::sequence_cylon(uint32_t color) {
  this->clear();

  uint32_t sequence[18][10] = {
    {color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color} ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , color , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
  };

  for (byte i = 0; i < 18; i++) {
    this->read(sequence[i]);
    this->write();
    delay(this->animation_delay);
  }
} 


/**
 * Fades the entire strip to the specified opacity
 *
 * @param uint32_t color
 * @return void
 */
void Strip::sequence_fade(uint32_t alpha) {
  // fade out
  if (this->segments[0].alpha() > alpha) {
    while(this->segments[0].alpha() > alpha) {
      this->alpha(this->segments[0].alpha() - 1);
      this->write();
      delay(this->animation_delay);
    }
  }

  // fade in
  else {
    while(this->segments[0].alpha() < alpha) {
      this->alpha(this->segments[0].alpha() + 1);
      this->write();
      delay(this->animation_delay);
    }
  }
}

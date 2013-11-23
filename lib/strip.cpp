#define OFF   0x000000

#include "Arduino.h"
#include "strip.h"

Strip::Strip(byte number_of_segments) {
  this->_number_of_segments = number_of_segments;
}

void Strip::clear() {
  for(byte i = 0; i < this->_number_of_segments; i++) {
    Segment::write(0x000000);
  }
}

void Strip::write(uint32_t colors[]) {
  noInterrupts();
  for (byte i = 0; i < this->_number_of_segments; i++) {
    Segment::write(colors[i]);
  }
  interrupts();
}

void Strip::sequence_radiate(uint32_t color) {
  this->clear();

  // @todo: make number of lights in strip configurable
  uint32_t sequence[6][10] = {
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , color , color , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , color , color , color , color , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , color , color , color , color , color , color , OFF   , OFF}   ,
    {OFF   , color , color , color , color , color , color , color , color , OFF}   ,
    {color , color , color , color , color , color , color , color , color , color} ,
  };

  for (byte i = 0; i < 6; i++) {
    Strip::write(sequence[i]);
    delay(500);
  }
} 

void Strip::sequence_scroll(uint32_t color) {
  this->clear();

  // @todo: make number of lights in strip configurable
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
    Strip::write(sequence[i]);
    delay(500);
  }
} 

void Strip::sequence_solid(uint32_t color) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    Segment::write(color);
  }
}


// @todo: play_sequence() and abstraction

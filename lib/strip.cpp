#define OFF   0x000000

#include "Arduino.h"
#include "strip.h"


Strip::Strip(byte number_of_segments, unsigned short animation_delay) {
  this->_number_of_segments = number_of_segments;
  this->_animation_delay    = animation_delay;
}


void Strip::clear() {
  this->sequence_solid(0x00000000);
}


void Strip::read(uint32_t sequence[]) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].color(sequence[i]);
  }
}


void Strip::write() {
  noInterrupts();
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].write();
  }
  interrupts();
}


void Strip::sequence_solid(uint32_t color) {
  for (byte i = 0; i < this->_number_of_segments; i++) {
    this->segments[i].color(color);
  }
  this->write();
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
    this->read(sequence[i]);
    this->write();
    delay(this->_animation_delay);
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
    this->read(sequence[i]);
    this->write();
    delay(this->_animation_delay);
  }
} 


void Strip::sequence_cylon(uint32_t color) {
  this->clear();

  // @todo: make number of lights in strip configurable
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
    delay(this->_animation_delay);
  }
} 

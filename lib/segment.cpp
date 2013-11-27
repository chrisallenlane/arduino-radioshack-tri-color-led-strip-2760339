#include "Arduino.h"
#include "segment.h"

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define NOP "nop\n\t"

void Segment::color(uint32_t color) {
  // Despite what the TM1803 documentation says, the chip seems to want the
  // bytes fed to it in GBR order. Thus, chop up the RGB values, and construct
  // a GBR sequence.
  
  // parse the RGBA color into its constituent bytes
  this->_color     = color;
  this->_red       = (uint32_t) (color >> 24);
  this->_green     = (uint32_t) ((color << 8) >> 24);
  this->_blue      = (uint32_t) ((color << 16) >> 24);
  this->_alpha     = (uint32_t) (color << 24) >> 24;

  // modify the RGB values per alpha
  float mod        = (float)    this->_alpha / (float) 255;
  uint32_t red     = (uint32_t) this->_red   * mod;
  uint32_t green   = (uint32_t) this->_green * mod;
  uint32_t blue    = (uint32_t) this->_blue  * mod;

  // create the composite color
  this->_composite = (green << 16) | (blue << 8) | red;
}

uint32_t Segment::color() {
  return this->_color;
}

void Segment::write() {
  uint32_t mask = 0x800000;
  for (byte i = 0; i < 24; i++) {
    (this->_composite & mask) ? Segment::high() : Segment::low();
    mask >>= 1;
  }  
}

void Segment::alpha(uint32_t alpha) {
  // prevent alpha from overflowing on bad values
  alpha = (alpha > 255) ? 0 : alpha ;

  // set the new color
  this->color(
    (this->_red << 24)   |
    (this->_green << 16) |
    (this->_blue << 8)   |
    alpha
  );
}

uint32_t Segment::alpha() {
  return this->_alpha;
}

void Segment::high() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
}

void Segment::low() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
  __asm__(NOP NOP NOP);  
}


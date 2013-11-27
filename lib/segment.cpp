#include "Arduino.h"
#include "segment.h"

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define NOP "nop\n\t"


/**
 * The TM1803 documentation claims that the chip expects to receive color
 * information in RGB format, but from experimentation (unless I'm doing
 * something wrong that I'm not aware of, it seems to /really/ expect GBR. 
 *
 * This method takes an RGB hex code, converts it to GBR, and then adjusts for
 * alpha.
 *
 * @param uint32_t color
 * @return void
 */
void Segment::color(uint32_t color) {
  // parse the RGBA color into its constituent bytes
  this->_color     = color;
  this->_red       = (uint32_t) (color >> 24);
  this->_green     = (uint32_t) ((color << 8) >> 24);
  this->_blue      = (uint32_t) ((color << 16) >> 24);
  this->_alpha     = (uint32_t) (color << 24) >> 24;

  // adjust the RGB values per the alpha modifier
  float mod        = (float)    this->_alpha / (float) 255;
  uint32_t red     = (uint32_t) this->_red   * mod;
  uint32_t green   = (uint32_t) this->_green * mod;
  uint32_t blue    = (uint32_t) this->_blue  * mod;

  // assemble a GBR byte
  this->_gbr = (green << 16) | (blue << 8) | red;
}


/**
 * Returns the color of the segment
 *
 * @return uint32_t color
 */
uint32_t Segment::color() {
  return this->_color;
}


/**
 * Pushes a 24-bit stream to the TM1803 bus. This will change the state of a
 * single segment.
 *
 * @return void
 */
void Segment::write() {
  uint32_t mask = 0x800000;
  for (byte i = 0; i < 24; i++) {
    (this->_gbr & mask) ? Segment::high() : Segment::low();
    mask >>= 1;
  }  
}


/**
 * Changes the alpha (opacity) of this segment. Note that only the buffered
 * color is changed: this operation does not actually output to the strip.
 *
 * @return void
 */
void Segment::alpha(uint32_t alpha) {
  // prevent alpha from overflowing
  alpha = (alpha > 255) ? 0 : alpha ;

  // set the new color
  this->color(
    (this->_red << 24)   |
    (this->_green << 16) |
    (this->_blue << 8)   |
    alpha
  );
}


/**
 * Returns the alpha (opacity) of the segment.
 *
 * @return uint32_t alpha
 */
uint32_t Segment::alpha() {
  return this->_alpha;
}


/**
 * Writes to UART such as to represent a high bit to the TM1803.
 *
 * @return void
 */
void Segment::high() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
}


/**
 * Writes to UART such as to represent a high bit to the TM1803.
 *
 * @return void
 */
void Segment::low() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
  __asm__(NOP NOP NOP);  
}


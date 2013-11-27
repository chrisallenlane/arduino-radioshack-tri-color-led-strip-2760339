#include "Arduino.h"
#include "segment.h"

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define NOP "nop\n\t"

void Segment::write(uint32_t color) {
  // Despite what the TM1803 documentation says, the chip seems to want the
  // bytes fed to it in GBR order. Thus, chop up the RGB values, and construct
  // a GBR sequence.
  float alpha    = ((float) ((color << 24) >> 24)) / (float) 255;
  uint32_t red   = (uint32_t) (color >> 24)         * alpha;
  uint32_t green = (uint32_t) ((color << 8) >> 24)  * alpha;
  uint32_t blue  = (uint32_t) ((color << 16) >> 24) * alpha;
  uint32_t gbr   = (green << 16) | (blue << 8) | red;

  // step through the bits of the byte
  uint32_t mask = 0x800000;
  for (byte i = 0; i < 24; i++) {
    (gbr & mask) ? high() : low();
    mask >>= 1;
  }  
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

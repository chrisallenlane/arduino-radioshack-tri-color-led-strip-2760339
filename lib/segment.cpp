#include "Arduino.h"
#include "segment.h"

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define NOP "nop\n\t"

void Segment::write(uint32_t color) {
  unsigned long j = 0x800000;
  
  // step through the bits of the byte
  for (byte i = 0; i < 24; i++) {
    (color & j) ? high() : low();
    j>>=1;
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

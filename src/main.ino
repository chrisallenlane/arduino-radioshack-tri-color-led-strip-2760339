#include <avr/pgmspace.h>

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)  // for UNO
#define NOP "nop\n\t"

//            0xGGBBRR
//#define COLOR 0x00FF33
#define COLOR 0xFF0000
#define RED   0x0000FF
#define BLUE  0x00FF00
#define GREEN 0xFF0000

#define SEGMENT_COUNT 10

/**
 * @todo:
 * - encapsulate into proper library
 * - move #defines into constants?
 * - write new cool methods (effects and such)
 * - interactive sensors
 * - figure out vim workflow
 * - buy AVR book
 * - read C books
 * - fix color specification byte order (want RGB)
 */

/**********************************
 * Main
 *********************************/
 void setup() {
  // set the pinout
  STRIP_PINOUT;
  
  // horrible sync issues occur without this
  noInterrupts();
  
  // blank out the strip
  strip_clear();
  
  // I seem to need this, though I don't know why
  delay(250);
}

void loop() {
  // write solid colors to the strip
  strip_push_solid(COLOR);
  
  // there's really no need to do a lot of writing to the LEDs right now
  delay(1000 * 60 * 60 * 24);
}

/* @todo: move these to a library */
/**********************************
 * Strip
 *********************************/
void strip_clear() {
  for(byte i = 0; i < SEGMENT_COUNT; i++) {
    segment_push(0x000000);
  }
}

void strip_push(uint32_t colors[]) {
  for (byte i = 0; i < SEGMENT_COUNT; i++) {
    segment_push(colors[i]);
  }
}

void strip_push_solid(uint32_t color) {
  for (byte i = 0; i < SEGMENT_COUNT; i++) {
    segment_push(color);
  }
}


/**********************************
 * Segment
 *********************************/
void segment_push(uint32_t data) {
  unsigned long j = 0x800000;
  
  // step through the bits of the byte
  for (byte i = 0; i < 24; i++) {
    (data & j) ? high() : low();
    j>>=1;
  }  
} 


/**********************************
 * Bit
 *********************************/
void high() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
}

void low() {
  DATA_1;
  __asm__(NOP NOP NOP NOP NOP NOP NOP NOP NOP);
  DATA_0;
  __asm__(NOP NOP NOP);  
}

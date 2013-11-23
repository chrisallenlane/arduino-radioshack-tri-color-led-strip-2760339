#include <avr/pgmspace.h>

#define DATA_1 (PORTC |=  0X01)   // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)   // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)  // for UNO
#define NOP "nop\n\t"

//            0xGGBBRR
//#define COLOR 0x00FF33
#define OFF   0x000000
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
 * - buy AVR book
 * - read C books
 * - fix color specification byte order (want RGB)
 */

/**********************************
 * Main
 *********************************/
 void setup() {

  //Serial.begin(9600);

  // set the pinout
  STRIP_PINOUT;

  // blank out the strip
  strip_clear();

  // I seem to need this, though I don't know why
  delay(250);
}

void loop() {
  //delay(250);
  sequence_radiate(COLOR);
  //sequence_scroll(COLOR);
  // write solid colors to the strip
  //strip_push_solid(COLOR);
  
  // there's really no need to do a lot of writing to the LEDs right now
  //delay(1000 * 60 * 60 * 24);
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
void segment_push(uint32_t color) {
  unsigned long j = 0x800000;
  
  // step through the bits of the byte
  for (byte i = 0; i < 24; i++) {
    (color & j) ? high() : low();
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


/**********************************
 * Sequences
 *********************************/
void sequence_radiate(uint32_t color) {
  strip_clear();

  uint32_t sequence[6][10] = {
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , COLOR , COLOR , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , COLOR , COLOR , COLOR , COLOR , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , OFF   , OFF}   ,
    {OFF   , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , OFF}   ,
    {COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR , COLOR} ,
  };

  for (byte i = 0; i < 6; i++) {
    noInterrupts();
    for (byte j = 0; j < 10; j++) {
      segment_push(sequence[i][j]);
    }
    interrupts();
    delay(500);
  }
} 

void sequence_scroll(uint32_t color) {
  strip_clear();

  uint32_t sequence[10][10] = {
    {COLOR , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , COLOR , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , COLOR , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , COLOR , OFF   , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , COLOR , OFF   , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , COLOR , OFF   , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , COLOR , OFF   , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , COLOR , OFF   , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , COLOR , OFF}   ,
    {OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , OFF   , COLOR} ,
  };

  for (byte i = 0; i < 10; i++) {
    noInterrupts();
    for (byte j = 0; j < 10; j++) {
      segment_push(sequence[i][j]);
    }
    interrupts();
    delay(500);
  }
} 

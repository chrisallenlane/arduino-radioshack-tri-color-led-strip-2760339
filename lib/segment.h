#ifndef Segment_h
#define Segment_h

#include "Arduino.h"

class Segment {
  public:
    static void write(uint32_t color);
    static void high();
    static void low();
};

#endif

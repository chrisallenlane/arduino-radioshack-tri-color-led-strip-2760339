#ifndef Segment_h
#define Segment_h

#include "Arduino.h"

class Segment {
  public:
    static void high();
    static void low();
    uint32_t color();
    void color(uint32_t color);
    void write();

  private:
    uint32_t _color = 0x00000000;
};

#endif

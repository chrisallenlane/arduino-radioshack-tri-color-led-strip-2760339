#ifndef Segment_h
#define Segment_h

#include "Arduino.h"

class Segment {
  public:
    uint32_t alpha();
    void alpha(uint32_t alpha);

    uint32_t color();
    void color(uint32_t color);

    void write();
    
    static void high();
    static void low();

  private:
    uint32_t _color;
    uint32_t _red;
    uint32_t _green;
    uint32_t _blue;
    uint32_t _alpha;
    uint32_t _gbr;
};

#endif

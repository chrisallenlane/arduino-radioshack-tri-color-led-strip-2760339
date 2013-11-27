#ifndef Segment_h
#define Segment_h

#include "Arduino.h"

class Segment {
  public:
    static void high();
    static void low();
    uint32_t alpha();
    uint32_t color();
    //uint32_t rgb();
    void alpha(uint32_t alpha);
    void color(uint32_t color);
    //void rgb(uint32_t rgb);
    void write();

  private:
    uint32_t _alpha;
    uint32_t _blue;
    uint32_t _color;
    uint32_t _composite;
    uint32_t _green;
    uint32_t _red;
};

#endif

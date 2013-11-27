#ifndef Strip_h
#define Strip_h

#include "Arduino.h"

class Strip {
  public:
    Strip(byte number_of_segments, unsigned short animation_delay);
    void alpha(uint32_t alpha);
    void clear();
    void read(uint32_t sequence[]);
    void sequence_cylon(uint32_t color);
    void sequence_fadein();
    void sequence_fadeout();
    void sequence_radiate(uint32_t color);
    void sequence_scroll(uint32_t color);
    void sequence_solid(uint32_t color);
    void write();
    Segment segments[10];

  private:
    byte _number_of_segments;
    unsigned short _animation_delay;
};

#endif

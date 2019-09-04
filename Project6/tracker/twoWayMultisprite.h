#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "multisprite.h"

class TwoWayMultisprite : public MultiSprite {
public:
  TwoWayMultisprite(const std::string&);
  TwoWayMultisprite(const TwoWayMultisprite&);
  virtual ~TwoWayMultisprite() { }

protected:
  virtual void advanceFrame(Uint32 ticks);
};
#endif

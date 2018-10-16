#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include<string>
#include<vector>
#include "multisprite.h"

class twoWayMultisprite : public MultiSprite {
public:
   twoWayMultisprite(const std::string&);
   twoWayMultisprite(const twoWayMultisprite&);
   virtual ~twoWayMultisprite() {}

protected:
  virtual void advanceFrame(Uint32 ticks);
};
#endif

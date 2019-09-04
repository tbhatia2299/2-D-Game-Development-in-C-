#ifndef SMARTSPRITE_H
#define SMARTSPRITE_H
#include <string>
#include "multisprite.h"
#include "explodingSprite.h"

class SmartSprite : public MultiSprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite();

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  void explode();
  virtual void draw() const;
  void reset();

private:
  enum MODE {NORMAL, EVADE};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;
  ExplodingSprite* explosion;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  SmartSprite& operator = (const SmartSprite&);

};
#endif

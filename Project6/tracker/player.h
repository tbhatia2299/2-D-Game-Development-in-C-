#ifndef PLAYER__H
#define PLAYER__H
#include "twoWayMultisprite.h"
#include "gamedata.h"

class Player : public TwoWayMultisprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }

  void right();
  void left();
  void up();
  void down();
  void stop();
  void reset();

private:

  bool collision;
  Vector2f initialVelocity;
  Player& operator = (const Player&);
};
#endif

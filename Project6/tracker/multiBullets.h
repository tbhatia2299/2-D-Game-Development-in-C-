#include <list>
#include "bullet.h"
#include "collisionStrategy.h"
#include "hud.h"

class CollisionStrategy;

class MultiBullets {

  MultiBullets& operator=(const MultiBullets&) = delete;

public:
  MultiBullets(const std::string&);
  MultiBullets(const MultiBullets&);
  ~MultiBullets();
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel);

  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount()  const { return freeList.size(); }

  bool shooting() const { return bulletList.empty(); }
  bool collided(const Drawable* obj) const;

private:
  std::string name;
  CollisionStrategy* strategy;
  float frameInterval;
  float timeSinceLastFrame;
  mutable std::list<Bullet> bulletList;
  mutable std::list<Bullet> freeList;

};

#ifndef SHOOTINGSPRITE__H
#define SHOOTINGSPRITE__H
#include <string>
#include <iostream>
#include <list>
#include "subjectSprite.h"
#include "multiBullets.h"
#include "explodingSprite.h"

class ExplodingSprite;

class ShootingSprite : public SubjectSprite {
public:
  ShootingSprite(const std::string& n);
  ShootingSprite(const ShootingSprite& s);
  ~ShootingSprite(){if (explosion) delete explosion;}
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  void explode();
  virtual bool collidedWith(const Drawable*) const;
  void godMode() {godmode = !godmode;}

private:
  std::string bulletName;
  float minSpeed;
  MultiBullets bullets;
  ExplodingSprite* explosion;
  bool godmode;
  ShootingSprite& operator=(const ShootingSprite&);

};
#endif

#include <sstream>
#include <cmath>
#include "ioMod.h"
#include "gamedata.h"
#include "multiBullets.h"

MultiBullets::~MultiBullets() {
  delete strategy;
}

MultiBullets::MultiBullets(const std::string& n) :
  name(n),
  strategy( NULL ),
  frameInterval(Gamedata::getInstance().getXmlInt(name+"/interval")),
  timeSinceLastFrame( 0 ),
  bulletList(),
  freeList()
{
  std::string thisStrategy = Gamedata::getInstance().getXmlStr(name+"/strategy");
    if ( thisStrategy == "Per-pixel" )
    {strategy = new PerPixelCollisionStrategy;}
    else if ( thisStrategy == "Rectangular" )
    {strategy = new RectangularCollisionStrategy;}
    else if ( thisStrategy == "Midpoint" )
    {strategy = new MidPointCollisionStrategy;}
}

MultiBullets::MultiBullets(const MultiBullets& b) :
  name(b.name),
  strategy(b.strategy),
  frameInterval(b.frameInterval),
  timeSinceLastFrame( b.timeSinceLastFrame ),
  bulletList(b.bulletList),
  freeList(b.freeList)
{ }

bool MultiBullets::collided(const Drawable* obj) const {
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    if ( strategy->execute(*ptr, *obj) ) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
      return true;
    }
    ++ptr;
  }
  return false;
}

void MultiBullets::shoot(const Vector2f& position, const Vector2f& velocity) {
	if (timeSinceLastFrame > frameInterval) {
    if ( freeList.empty() ) {
      Bullet b(name);
      b.setPosition( position );
      b.setVelocity( velocity );
      bulletList.push_back( b );
    }
    else {
      Bullet b = freeList.front();
      freeList.pop_front();
      b.reset();
      b.setVelocity(velocity);
      b.setPosition(position);
      bulletList.push_back( b );
    }
		timeSinceLastFrame = 0;
	}
}

void MultiBullets::draw() const {
  std::stringstream stream;
  Hud::getInstance().setActiveBulletList(bulletList.size());
  Hud::getInstance().setFreeBulletList(freeList.size());
  for ( Bullet bullet : bulletList ) {
    bullet.draw();
  }
}

void MultiBullets::update(Uint32 ticks) {
	timeSinceLastFrame += ticks;
  std::list<Bullet>::iterator ptr = bulletList.begin();
  while (ptr != bulletList.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
      freeList.push_back(*ptr);
      ptr = bulletList.erase(ptr);
    }
    else ++ptr;
  }
}

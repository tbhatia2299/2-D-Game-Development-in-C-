#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::goLeft()  { setVelocityX( abs(getVelocityX()) );  }
void SmartSprite::goRight() { setVelocityX( -fabs(getVelocityX()) );  }
void SmartSprite::goUp()    { setVelocityY( fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( -fabs(getVelocityY()) );  }

SmartSprite::~SmartSprite() {
  if(explosion) {
  delete explosion;
  }
}

SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos,
  int w, int h) :
  MultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  explosion(nullptr)
{}


SmartSprite::SmartSprite(const SmartSprite& s) :
  MultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  explosion(s.explosion)
{}

void SmartSprite::draw() const {
  if(explosion){
  		explosion->draw();
  }
	else
    MultiSprite::draw();
}

void SmartSprite::explode() {
  if(!explosion) {
   Sprite
   sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
   explosion = new ExplodingSprite(sprite);
   setPosition(Vector2f(getPosition()[0] + 500, getPosition()[1] + 0));
  }
}

void SmartSprite::reset(){
  MultiSprite::reset();
}

void SmartSprite::update(Uint32 ticks) {
  if(explosion){
    explosion->update(ticks);
    if(explosion->chunkCount() == 0) {
      delete explosion;
       explosion = NULL;
    }
    return;
}

  MultiSprite::update(ticks);
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
}

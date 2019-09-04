#include "shootingSprite.h"
#include "gamedata.h"

ShootingSprite::ShootingSprite(const std::string& name) :
  SubjectSprite(name),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bullets(bulletName),
  explosion(NULL)
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  SubjectSprite(s),
  bulletName(s.bulletName),
  minSpeed(s.minSpeed),
  bullets(s.bullets),
  explosion(s.explosion)
{ }

void ShootingSprite::shoot() {
  Vector2f vel = getVelocity();
    float x;
    float y = getY()+ getScaledHeight()/2;
    if(currentFrame < numberOfFrames/2) {
      x = getX() + getScaledWidth() + 5;
      vel[0] += minSpeed;
    }
    else {
      x = getX() - 50;
      vel[0] -= minSpeed;
    }
    vel[1] *=0;

    bullets.shoot(Vector2f(x,y), vel);
  }

bool ShootingSprite::collidedWith(const Drawable* obj) const {
  return bullets.collided(obj);
}

void ShootingSprite::draw() const {
  if(explosion){
  		explosion->draw();
  }
	else
    SubjectSprite::draw();
    bullets.draw();
  }

void ShootingSprite::explode() {
  if(!explosion)
 {
   Sprite
   sprite(getName(), getPosition(), getVelocity(), images[currentFrame]);
   explosion = new ExplodingSprite(sprite);
  }
}

void ShootingSprite::update(Uint32 ticks) {
  if(explosion){

    explosion->update(ticks);
    if(explosion->chunkCount() == 0)
    {
      delete explosion;
       explosion = NULL;

    }
    return;
}
  SubjectSprite::update(ticks);
  bullets.update(ticks);
}

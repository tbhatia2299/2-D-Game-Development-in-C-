#include "multisprite.h"
#include "gamedata.h"
#include "renderContext.h"

Vector2f MultiSprite::makeVelocity(int vx, int vy, std::string name) const {
	if(name == "bat"){
		float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);
	  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);
		newvx *= [](){ if(rand()%2) return -1; else return 1; }();
	  newvy *= [](){ if(rand()%2) return -1; else return 1; }();
		return Vector2f(newvx,newvy);
	}
  return Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
	Gamedata::getInstance().getXmlInt(name+"/speedY"));
}

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"),name)
           ),
  images( RenderContext::getInstance()->getImages(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s),
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void MultiSprite::draw() const {
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void MultiSprite::reset()
{
   setX(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));
   setY(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y"));
   setVelocity(makeVelocity(Gamedata::getInstance().getXmlInt(getName()+"/speedX"),
                    Gamedata::getInstance().getXmlInt(getName()+"/speedY"),"bat"));
}

void MultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > 0.87 * (worldHeight-getScaledHeight())) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }

}

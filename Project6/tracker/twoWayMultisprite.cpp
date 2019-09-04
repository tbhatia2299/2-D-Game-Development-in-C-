#include "twoWayMultisprite.h"
#include "gamedata.h"

void TwoWayMultisprite::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
if (timeSinceLastFrame > frameInterval) {
  if (getVelocityX() >= 0) {
    currentFrame = (currentFrame + 1) % (numberOfFrames/2);
  }
  else {
    if (currentFrame > numberOfFrames / 2) {
      currentFrame = (currentFrame + 1) % numberOfFrames;
      if(currentFrame < numberOfFrames / 2){
        currentFrame = (numberOfFrames /2)  +1;
      }
    }
    else{
      currentFrame = (currentFrame + (numberOfFrames / 2) + 1) % numberOfFrames;
      if(currentFrame < numberOfFrames / 2){
        currentFrame = (numberOfFrames /2) + 1;
      }
    }
  }
  timeSinceLastFrame = 0;
}
}

TwoWayMultisprite::TwoWayMultisprite(const std:: string& name) : MultiSprite(name) {}
TwoWayMultisprite::TwoWayMultisprite(const TwoWayMultisprite& two) : MultiSprite(two) {}

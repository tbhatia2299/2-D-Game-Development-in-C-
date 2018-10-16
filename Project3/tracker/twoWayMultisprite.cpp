#include "twoWayMultisprite.h"
#include "gameData.h"

void twoWayMultisprite::advanceFrame(Uint32 ticks) {
   timeSinceLastFrame += ticks;
if (timeSinceLastFrame> frameInterval){
   if(getVelocityX() <= 0){
         if(currentFrame<=numberOfFrames /2){
              currentFrame=(currentFrame+(numberOfFrames /2) +1) %numberOfFrames;
              while(currentFrame<= numberOfFrames /2) {
                  currentFrame=(currentFrame+(numberOfFrames/2)+1)%numberOfFrames;
                }
          }
          else{
             currentFrame=(currentFrame +1)% numberOfFrames;
            
             while (currentFrame <= numberOfFrames/2){
                currentFrame=(currentFrame+(numberOfFrames /2) +1) % numberOfFrames;
                }
           }
    }
          else if (getVelocityX() > 0) {
              currentFrame=(currentFrame+1)%( numberOfFrames/2);
            }
            timeSinceLastFrame=0;
       }
   }

   twoWayMultisprite::twoWayMultisprite(const std:: string& name) : MultiSprite(name) {}
   twoWayMultisprite::twoWayMultisprite(const twoWayMultisprite& two) : MultiSprite(two) {}

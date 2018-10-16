#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "twoWayMultisprite.h"
Engine::~Engine() { 
  for (auto& s : sprites){
  delete s;
}
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  purplesky("purplesky", Gamedata::getInstance().getXmlInt("purplesky/factor") ),
  road("road", Gamedata::getInstance().getXmlInt("road/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  makeVideo( false )

{
 
  sprites.push_back(new twoWayMultisprite("wolfyiron")),
  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),

  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),
  sprites.push_back(new Sprite("wolf")),  





  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  purplesky.draw();
  road.draw();

  for(auto* sprite : sprites){
    sprite->draw();
}

 SDL_Color color ={255,255,255,0};

   std::stringstream stre;
   stre<<"fps: "<<clock.getFps();
   io.writeText(stre.str(), 29,80,color);
   io.writeText("Tanmay Bhatia", 25, 525, color);

  

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* sprite : sprites){
   sprite->update(ticks);
     }
  purplesky.update();
  road.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
    Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
  
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}

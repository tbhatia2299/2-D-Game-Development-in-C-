#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "twoWayMultisprite.h"
#include "collisionStrategy.h"
#include "smartSprite.h"
#include "subjectSprite.h"


Engine::~Engine() {
  delete player;
  for(auto& s : sprites) {
    delete s;
  }

  for(auto& s : smart) {
    delete s;
  }

  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  purplesky("purplesky", Gamedata::getInstance().getXmlInt("purplesky/factor") ),
  road("road", Gamedata::getInstance().getXmlInt("road/factor") ),
  viewport( Viewport::getInstance() ),
  player(new SubjectSprite("wolf")),
  sprites(),
  smart(),
  strategies(),
  currentStrategy(0),
  collision(false),
  hudTime( Gamedata::getInstance().getXmlInt("hud/time") ),
  drawHud( false ),
  hud( Hud::getInstance() ),
  currentSprite(0),
  makeVideo( false )
{

  int n = Gamedata::getInstance().getXmlInt("numberOfBats");
  smart.reserve(n);
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  for (int i = 0; i < n; ++i) {
    smart.push_back( new SmartSprite("bat", pos, w, h) );
    player->attach( smart[i] );
  }

  

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {

  SDL_Color color = {255, 255, 255, 255};

  purplesky.draw();
  road.draw();

  for(auto* sprite : sprites){
    sprite->draw();
  }

  for(auto* s : smart){
    s->draw();
  }

  std::stringstream strm;
  strm << smart.size() << " Stupid Bats Remaining";
  IOmod::getInstance().writeText(strm.str(), 500, 50,color);
  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Collision", 500, 70,color);
}
  io.writeText("Tanmay Bhatia", 30, 490, color);
  player->draw();

  if(clock.getSeconds() < hudTime || drawHud){
    hud.makeHud();
  }
  //viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for ( const Drawable* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }
  auto it = smart.begin();
  while ( it != smart.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      collision = true;
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it = smart.erase(it);
    }
    else ++it;
  }
}
void Engine::update(Uint32 ticks) {

  checkForCollisions();

  player->update(ticks);
  for(auto* sprite : sprites){
    sprite->update(ticks);
  }

  for(auto* s : smart){
    s->update(ticks);
  }

  purplesky.update();
  road.update();
  viewport.update(); // always update viewport last
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

        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
        if(keystate[SDL_SCANCODE_F1]){
          drawHud = !drawHud;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if(keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D]){
        player->stop();
      }
      else if (keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_W]) {
        player->stop();
      }
      else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_W]) {
        player->left();
        player->up();
      }
      else if (keystate[SDL_SCANCODE_D] && keystate[SDL_SCANCODE_W]) {
        player->right();
        player->up();
      }
       else if (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_S]) {
        player->left();
        player->down();
      }
       else if (keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_D]) {
        player->right();
        player->down();
      }
      else if (keystate[SDL_SCANCODE_A]) {
        player->left();
      }
      else if (keystate[SDL_SCANCODE_D]) {
        player->right();
      }
      else if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      else if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      

      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}

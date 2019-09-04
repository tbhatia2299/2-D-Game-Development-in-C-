#ifndef HEALTH_H
#define HEALTH_H
#include <SDL.h>
#include <SDL_image.h>
#include "renderContext.h"
#include "gamedata.h"

class Health {
public:
  static Health& getInstance();

  void draw() ;
  void update();
  void reset() { barLength = 100; }
  int getHealthBar() { return barLength; }

private:
  int x;
  int y;
  int w;
  int h;
  int barLength = 100;
  void drawBar(int x, int y, int w, int h, float decrement);
  SDL_Renderer * renderer;

  Health();
  Health(const Health&);
  Health& operator=(const Health&);
};

#endif

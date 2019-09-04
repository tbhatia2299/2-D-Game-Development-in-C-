#ifndef HUD_H
#define HUD_H
#include <string>
#include <SDL.h>
#include <stdint.h>
#include "clock.h"
#include "collisionStrategy.h"

class Hud {
public:
  static Hud& getInstance();
  ~Hud();
  void makeHud() const;
  void setActiveBulletList(int activeBullets) {activeBulletList = activeBullets;}
  void setFreeBulletList(int freeBullets) {freeBulletList = freeBullets;}

private:
  const int w;
  const int h;
  int x;
  int y;
  Clock& c;
  SDL_Rect rect;
  SDL_Color color;
  SDL_Renderer* renderer;
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  int activeBulletList;
  int freeBulletList;

};
#endif

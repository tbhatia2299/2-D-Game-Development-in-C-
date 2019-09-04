#include <string>
#include <SDL.h>
#include <stdint.h>
#include "clock.h"

class Hud {
public:
  static Hud& getInstance();
  ~Hud();
  void makeHud() const;

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

};

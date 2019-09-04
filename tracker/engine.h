#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"

class CollisionStrategy;
class SmartSprite;
class SubjectSprite;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World purplesky;
  World road;
  Viewport& viewport;

  SubjectSprite* player;
  std::vector<Drawable*> sprites;
  std::vector<SmartSprite*> smart;

  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  unsigned int hudTime;
  bool drawHud;
  Hud& hud;

  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();

};

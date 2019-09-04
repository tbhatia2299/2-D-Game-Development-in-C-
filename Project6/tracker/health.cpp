#include "health.h"

Health& Health::getInstance(){
    static Health instance;
    return instance;
}

Health::Health() :
  x(Gamedata::getInstance().getXmlFloat("health/x")),
  y(Gamedata::getInstance().getXmlFloat("health/y")),
  w(Gamedata::getInstance().getXmlFloat("health/w")),
  h(Gamedata::getInstance().getXmlFloat("health/h")),
  renderer(RenderContext::getInstance()->getRenderer())
{}

  void Health::drawBar(int x, int y, int w, int h, float decrement) {

     SDL_Rect rect1 = { x, y, w, h };
     SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
     SDL_RenderFillRect(renderer, &rect1);
     SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
     int s =  (int)((float)w * (decrement/100));
     SDL_Rect rect2 = { x, y, s, h };
     SDL_RenderFillRect(renderer, &rect2);
  }

  void Health::draw()  {
    drawBar(x, y , w , h , (float) barLength );
  }

void Health::update() {
  if ( barLength > 0) {
    barLength = barLength - 10;
  }
  draw();
}

#include "hud.h"
#include "renderContext.h"
#include "ioMod.h"
#include "gamedata.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

Hud& Hud::getInstance(){
    static Hud instance;
    return instance;
}

Hud::Hud():
    w(Gamedata::getInstance().getXmlInt("hud/w")),
    h(Gamedata::getInstance().getXmlInt("hud/h")),
    x(Gamedata::getInstance().getXmlInt("hud/startLoc/x")),
    y(Gamedata::getInstance().getXmlInt("hud/startLoc/y")),
    c(Clock::getInstance()),
    rect({x,y,w,h}),
    color({0, 0, 0, 255}),
    renderer( RenderContext::getInstance()->getRenderer()),
    activeBulletList(0),
    freeBulletList(0)
{}


Hud::~Hud(){}

void Hud::makeHud() const{

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/4 );

    std::stringstream fps, ac, fr;
    fps << "fps: " << c.getFps();
    ac << "Bullet List: " << activeBulletList;
    fr << "Free List: " << freeBulletList;

    SDL_RenderFillRect( renderer, &rect );
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect( renderer, &rect );
    IOmod::getInstance().writeText("Controls: ", x+25, y+20, color);
    IOmod::getInstance().writeText("a: Left", x+25, y+40, color);
    IOmod::getInstance().writeText("d: Right", x+25, y+60, color);
    IOmod::getInstance().writeText("w: Up", x+25, y+80, color);
    IOmod::getInstance().writeText("s: Down", x+25, y+100, color);
    IOmod::getInstance().writeText("Space: Shoot", x+25, y+120, color);
    IOmod::getInstance().writeText("p: Pause", x+25, y+140, color);
    IOmod::getInstance().writeText("F1: Display Hud", x+25, y+160, color);
    IOmod::getInstance().writeText("F4: Generate Frames", x+25, y+180, color);
    IOmod::getInstance().writeText("F4: Generate Frames", x+25, y+200, color);
    IOmod::getInstance().writeText("Strategy: Per-Pixel", x+25, y+220, color);
    IOmod::getInstance().writeText(fps.str(), x+25, y+240, color);
    IOmod::getInstance().writeText(ac.str(), x+25, y+260, color);
    IOmod::getInstance().writeText(fr.str(), x+25, y+280, color);
}

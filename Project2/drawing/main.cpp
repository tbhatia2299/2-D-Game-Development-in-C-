#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"
#include "skier.h"

const std::string TITLE = "Tanmay's Scenery";
const std::string NAME = "tbhatia";

const int WIDTH = 640;
const int HEIGHT = 480;

void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}
void writeName(SDL_Renderer* renderer){
	TTF_Init();
	TTF_Font*font=TTF_OpenFont("fonts/arial.ttf",24);
	if(font==NULL){
		throw std::string("error: font not found");
	}
	SDL_Color textColor={0xff,0,0,0};
	SDL_Surface* surface=TTF_RenderText_Solid(font,TITLE.c_str(),textColor);
	SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);

	int textWidth=surface->w;
	int textHeight=surface->h;
	SDL_FreeSurface(surface);
	SDL_Rect dst={20,HEIGHT-40,textWidth,textHeight};

	SDL_RenderCopy(renderer,texture,NULL,&dst);
	SDL_DestroyTexture(texture);
}


void drawRect1(SDL_Renderer* renderer,int x,int y, int w, int h){
	SDL_Rect fillRect={x,y,w,h};
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	SDL_RenderFillRect(renderer,&fillRect);
}

void drawWave(SDL_Renderer* renderer,int x, int y){
	SDL_SetRenderDrawColor(renderer,50,50,255,255);
	SDL_Point points[4]= {{x,y},{x+10,y-10},{x+15,y-5},{x+20,y-10}};
	SDL_RenderDrawLines(renderer,points,4);
}

void drawRect2(SDL_Renderer* renderer,int x,int y, int w,int h){
	SDL_Rect fillRect={x,y,w,h};
	SDL_SetRenderDrawColor(renderer,100,175,255,255);
	SDL_RenderFillRect(renderer,&fillRect);
}

int main(void) {

	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&window,&renderer);

	SDL_SetRenderDrawColor(renderer,0,225,255,255);
	SDL_RenderClear(renderer);

	// I will draw the Clouds
	skier k1(renderer,45,25,55);
	skier k2(renderer,45,25,55);
	skier k3(renderer,95,25,55);
	skier k4(renderer,95,25,55);
	k1+k2;//Using the overloaded operator
	k3+k4;
	skier k5(renderer,325,25,55);
	skier k6(renderer,400,25,55);
	skier k7(renderer,425,25,70);
	k5+k6;
	k6+k7;

	//Now I will draw the Sun
	
	SDL_Point center={575,0};
	SDL_Color color{255,255,0,0};
	drawCircle(renderer,center,100,color);

	//Drawing the waves
	drawWave(renderer,25,425);
	drawWave(renderer,100,425);
	drawWave(renderer,200,425);
	drawWave(renderer,300,425);
	drawWave(renderer,400,425);
	drawWave(renderer,25,525);
	drawWave(renderer,100,525);
	drawWave(renderer,200,525);
	drawWave(renderer,300,525);
	drawWave(renderer,400,525);

	//I will draw the bridgr now
	
	drawRect1(renderer,0,320,640,2);
	drawRect1(renderer,0,340,640,8);
	drawRect2(renderer,165,95,9,325);
	drawRect2(renderer,0,360,670,225);

	drawRect1(renderer,480,95,10,375);
	drawRect1(renderer,125,435,25,5);
	drawRect1(renderer,455,425,55,25);

	int a=0;
	int b=255;
	int c=25;
	while(b>100)
	{
		drawRect1(renderer,a,b,4,c);
		a=a+10;
		b=b-10;
		c=c+10;
	}
	b=b+10;
	c=c-10;

	while(b<300){
		drawRect1(renderer,a,b,4,c);
		a=a+10;
		b=b+10;
		c=c-10;
	}
	while(b>100){
		drawRect1(renderer,a,b,4,c);
		a=a+10;
		b=b-10;
		c=c+10;
	}
	b=b+10;
	c=c-10;
	while(b<300){
		drawRect1(renderer,a,b,4,c);
		a=a+10;
		b=b+10;
		c=c-10;
	}
	writeName(renderer);
	SDL_RenderPresent(renderer);





    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;
    while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
      }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

#include<SDL2/SDL.h>
#include<iostream>
#include"skier.h"

//Including an initialization list and an overload operator

skier::skier(SDL_Renderer* ren,int x,int y,int r):renderer(ren),xcoordinate(x),ycoordinate(y),radius(r){}

void skier::drawSkier(){
	SDL_SetRenderDrawColor(renderer,0,0,255,255);

	for(int w=0;w<radius*2;w++){
		for(int h=0;h<radius*2;h++){
			int dx=radius-w;
			int dy=radius-h;
			SDL_Point center={xcoordinate,ycoordinate};
			if ((dx*dy+dy*dy)<=(radius*radius)){
				SDL_RenderDrawPoint(renderer,center.x+dx,center.y+dy);

			}
		}
	}
}
void skier::operator+(skier&sk){
	sk.drawSkier();
	this->drawSkier();
}



#include<SDL2/SDL.h>
#include<iostream>

class skier{
public:
	skier(SDL_Renderer*,int x,int y,int r) ;
	void drawSkier();
	void operator+(skier&);

private:
	SDL_Renderer* renderer;
	int xcoordinate;
	int ycoordinate;
	int radius;
};


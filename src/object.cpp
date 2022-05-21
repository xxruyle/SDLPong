#include "object.h"

void Object::setDest(int x, int y, int w, int h)
{
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
}

void Object::setSource(int x, int y, int w, int h)
{
    source.x = x;
    source.y = y;
    source.w = w;
    source.h = h; 
}

void Object::loadImage(std::string filename, SDL_Renderer* renderer)
{

    SDL_Surface* surface = IMG_Load(filename.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}


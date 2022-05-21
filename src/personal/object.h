#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string> 


class Object
{
    private:
        SDL_Rect destination;
        SDL_Rect source; 
        SDL_Texture* texture = NULL; 
        
 

    public: 
        Object() {}
        SDL_Rect getDest() const {return destination;}
        SDL_Rect getSource() const {return source;}
        void setDest(int x, int y, int w, int h);
        void setSource(int x, int y, int w, int h);
        void loadImage(std::string filename, SDL_Renderer* renderer);
        SDL_Texture* getTex() const {return texture;}


        float POSITION_WIDTH; 
        float POSITION_HEIGHT; 

        float OBJECT_WIDTH;
        float OBJECT_HEIGHT; 

        bool movingLeft = false; 
        bool movingUp;
        bool diagonal = false; 
        int count = 0; 

};





#endif
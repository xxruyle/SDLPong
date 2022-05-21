#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "object.h"



class Game : private Object 
{
    public:
        Game();
        ~Game();
        void loadEntities();
        void loop();
        void update();
        void movement();
        void render();
        void input(SDL_Event& e);
        void draw(Object o);
        void loadMedia(Object o);

        void moveBall();


        bool checkRightCollision(Object o);
        bool checkLeftCollision(Object o);
        bool checkUpCollision(Object o);
        bool checkDownCollision(Object o);
        bool checkLeftOutOfBounds(Object o);
        bool checkRightOutOfBounds(Object o);


    private:
        bool running;
        bool player_moving;

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        const int WIDTH = 640;
        const int HEIGHT = 480;

        unsigned int last_time = 0, current_time, frame_count, delta_time; 

        Object player; 
        Object player2;
        Object ball; 

        char direction;
        float player_speed = 0; 
        float player_maxSpeed = .12; 
        double player_acceleration = 0.001;
        double player_deacceleration = 0.001; 
        float ball_speed = 0.05; 
        int times_hit = 0; 

};

#endif
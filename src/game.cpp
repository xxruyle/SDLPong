#include "game.h"
#include "object.h"
#include <iostream>


Game::Game()
{

    running = true; 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization has failed! SDL_Error: %s\n", SDL_GetError());
    }
    else 
    {
        window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            }
        }

    loadEntities();
    }
}

Game::~Game()
{
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
}

void Game::loadEntities()
{

    player.POSITION_WIDTH = 32;
    player.POSITION_HEIGHT = (HEIGHT/2) - 64; 
    player.OBJECT_WIDTH = 16;
    player.OBJECT_HEIGHT = 64;

    player.setDest(player.POSITION_WIDTH, player.POSITION_HEIGHT, player.OBJECT_WIDTH, player.OBJECT_HEIGHT);
    player.setSource(0, 0, 16, 64);
    player.loadImage("res/png/pong_paddle.png", renderer);

    player2.POSITION_WIDTH = WIDTH - 48;
    player2.POSITION_HEIGHT = (HEIGHT/2) - 64; 
    player2.OBJECT_WIDTH = 16;
    player2.OBJECT_HEIGHT = 64;
    player2.setDest(player2.POSITION_WIDTH, player2.POSITION_HEIGHT, player2.OBJECT_WIDTH, player2.OBJECT_HEIGHT);
    player2.setSource(0, 0, 16, 64);
    player2.loadImage("res/png/pong_paddle.png", renderer);


    ball.POSITION_WIDTH = WIDTH / 2;
    ball.POSITION_HEIGHT = 100;
    ball.OBJECT_WIDTH = 16;
    ball.OBJECT_HEIGHT = 16;

    ball.setDest(ball.POSITION_WIDTH, ball.POSITION_HEIGHT, ball.OBJECT_WIDTH, ball.OBJECT_HEIGHT = 16);
    ball.setSource(0, 0, 16, 16);
    ball.loadImage("res/png/pong_ball.png", renderer);

    

}

void Game::loop()
{
    SDL_Event e;

    last_time = 0; 
    
    while (running)
    {
        
        current_time = SDL_GetTicks();
        if (current_time > last_time + 1000)
        {
            delta_time = current_time - last_time;
            last_time = current_time;
            printf("BALL_SPEED: %g\n", ball_speed);
            printf("times_hit: %d\n", times_hit);
        }

        if (current_time > last_time + 5)
        {
            input(e);
        }

        render();
 
        update();  
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    draw(ball);
    draw(player);
    draw(player2);

    int timer_fps = SDL_GetTicks() - last_time;
    if (timer_fps < (1000/60))
    {
        SDL_Delay((1000/60) - timer_fps);
    }

    SDL_RenderPresent(renderer);
}

void Game::input(SDL_Event& e)
{

    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&e) != 0)
    {

        if (e.type == SDL_QUIT)
        {
            running = false; 
        }
        

        if (e.type == SDL_KEYDOWN)
        {
            player_moving = true;   
            if (keyboard_state_array[SDL_SCANCODE_DOWN] == SDL_PRESSED) 
                direction = 'D';
            if (keyboard_state_array[SDL_SCANCODE_UP] == SDL_PRESSED) 
                direction = 'U';
            if (keyboard_state_array[SDL_SCANCODE_RIGHT] == SDL_PRESSED)
                diagonal = true; 
            if (keyboard_state_array[SDL_SCANCODE_LEFT] == SDL_PRESSED)
                diagonal = false; 

            if (keyboard_state_array[SDL_SCANCODE_W] == SDL_PRESSED) 
                direction = 'W';
            if (keyboard_state_array[SDL_SCANCODE_S] == SDL_PRESSED)
                direction = 'S';
            
        }

        if (e.type == SDL_KEYUP)
        {
            player_moving = false; 
            if (keyboard_state_array[SDL_SCANCODE_DOWN] == SDL_RELEASED) 
                direction = 'D';
            if (keyboard_state_array[SDL_SCANCODE_UP] == SDL_RELEASED) 
                direction = 'U';

            if (keyboard_state_array[SDL_SCANCODE_W] == SDL_RELEASED) 
                direction = 'W';
            if (keyboard_state_array[SDL_SCANCODE_S] == SDL_RELEASED)
                direction = 'S';
        }
    }
}


void Game::movement()
{
    if (player_moving)
    {
        if (player_speed < player_maxSpeed)
            player_speed += player_acceleration;
        else if (player_speed > player_maxSpeed)
            player_speed = player_maxSpeed;
    }
    else
        player_speed = 0;

}

void Game::update()
{

    movement();

    if (direction == 'S' && !checkDownCollision(player))
    {
        player.POSITION_HEIGHT += player_speed; 
        player.setDest(player.POSITION_WIDTH , player.POSITION_HEIGHT, player.OBJECT_WIDTH, player.OBJECT_HEIGHT);
        
    }

    if (direction == 'W' && !checkUpCollision(player))
    {
        player.POSITION_HEIGHT -= player_speed;
        player.setDest(player.POSITION_WIDTH , player.POSITION_HEIGHT, player.OBJECT_WIDTH, player.OBJECT_HEIGHT);
    }

    if (direction == 'D' && !checkDownCollision(player2))
    {
        player2.POSITION_HEIGHT += player_speed; 
        player2.setDest(player2.POSITION_WIDTH , player2.POSITION_HEIGHT, player2.OBJECT_WIDTH, player2.OBJECT_HEIGHT);
    }

    if (direction == 'U' && !checkUpCollision(player2))
    {
        player2.POSITION_HEIGHT -= player_speed; 
        player2.setDest(player2.POSITION_WIDTH , player2.POSITION_HEIGHT, player2.OBJECT_WIDTH, player2.OBJECT_HEIGHT);
    }





    moveBall();
}

void Game::draw(Object o)
{
    SDL_Rect destination = o.getDest();
    SDL_Rect source = o.getSource();
    SDL_RenderCopyEx(renderer, o.getTex(), &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

void Game::moveBall()
{


    if (!movingLeft && !diagonal) // Right
    {
        ball.POSITION_WIDTH += ball_speed; 
    }
    else if (movingLeft && !diagonal) // Left
    {
        ball.POSITION_WIDTH -= ball_speed;
    }
    else if (!movingLeft && movingUp && diagonal) // Up Right
    {
        ball.POSITION_WIDTH += ball_speed;
        ball.POSITION_HEIGHT -= ball_speed;
    }
    else if (movingLeft && !movingUp && diagonal) // Down left
    {
        ball.POSITION_WIDTH -= ball_speed;
        ball.POSITION_HEIGHT += ball_speed;
    }
    else if (movingLeft && movingUp && diagonal) // Up Left
    {
        ball.POSITION_WIDTH -= ball_speed;
        ball.POSITION_HEIGHT -= ball_speed;
    }
    else if (!movingLeft && !movingUp && diagonal) // Down Right
    {
        ball.POSITION_WIDTH += ball_speed;
        ball.POSITION_HEIGHT += ball_speed;
    }


    if (checkRightCollision(ball))
        movingLeft = true; 

    if (checkLeftCollision(ball))
        movingLeft = false; 

    if (checkUpCollision(ball))
        movingUp = false; 

    if (checkDownCollision(ball))
        movingUp = true; 

    if (checkLeftOutOfBounds(ball))
    {
        running = false; 
    }
    else if (checkRightOutOfBounds(ball))
    {
        running = false;
    }

    ball.setDest(ball.POSITION_WIDTH, ball.POSITION_HEIGHT, player.OBJECT_WIDTH, player.OBJECT_WIDTH);
}

bool Game::checkRightCollision(Object o)
{
    if (o.POSITION_WIDTH >= (player2.POSITION_WIDTH - player2.OBJECT_WIDTH) && o.POSITION_HEIGHT + o.OBJECT_HEIGHT >= player2.POSITION_HEIGHT && o.POSITION_HEIGHT <= player2.POSITION_HEIGHT + player2.OBJECT_HEIGHT && !(o.POSITION_WIDTH > player2.POSITION_WIDTH))
    {
        if (times_hit < 5)
        {
            ball_speed += .01;
        }
        times_hit++;
        return true; 
        return true; 
    }
    else
    {
        return false; 
    }
}

bool Game::checkLeftCollision(Object o)
{
    if (o.POSITION_WIDTH  <= (player.POSITION_WIDTH + player.OBJECT_WIDTH) && o.POSITION_HEIGHT + o.OBJECT_HEIGHT >= player.POSITION_HEIGHT && o.POSITION_HEIGHT <= player.POSITION_HEIGHT + player.OBJECT_HEIGHT && !(o.POSITION_WIDTH < player.POSITION_WIDTH))
    {
        if (times_hit < 5)
        {
            ball_speed += .01;
        }
        times_hit++;
        return true; 
    }
    else
    {
        return false; 
    }
}

bool Game::checkUpCollision(Object o)
{
    return (o.POSITION_HEIGHT <= 0);
}

bool Game::checkDownCollision(Object o)
{
    return (o.POSITION_HEIGHT >= (HEIGHT - o.OBJECT_HEIGHT));
}

bool Game::checkLeftOutOfBounds(Object o)
{
    return (o.POSITION_WIDTH + o.OBJECT_WIDTH < 0);
}

bool Game::checkRightOutOfBounds(Object o)
{
    return (o.POSITION_WIDTH >= WIDTH);
}
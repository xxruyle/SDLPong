#include "game.h"
#include <iostream>

int main(int argc, char* args[])
{
    bool paused = false; 
    while (!paused)
    {
        Game g1;
        g1.loop();


        char ans; 
        printf("play again? (y/n)");
        std::cin >> ans; 
        if (ans == 'y')
            paused = false;
        else
            paused = true; 
    }

    return 0;
}
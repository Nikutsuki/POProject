// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

using namespace sf;

int main()
{
    //Configuring and creation of game:
    Game nowygame;

    
    //Game is open when the loop conditions are true, allows for the game to close
    while (nowygame.running())
    {
        //Checking for updates
        nowygame.update();

        //Rendering the game
        nowygame.render();
    }
    return 0;
}


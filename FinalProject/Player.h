#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Maze.h"

class Player {
private:
    
    float speed;
    

    bool canMove(float x, float y, Maze* maze1);

public:
    int health;
    void damagePlayer(int damage);
    void healPlayer();
    sf::RectangleShape body;
    const Maze& maze;
    sf::RectangleShape newShape;
    bool immunityCheck;
    sf::Clock immunityClock;
    Player(float size, float speed, const Maze& maze);
    void handleInput(sf::RenderWindow* window, Maze* maze);
    void render(sf::RenderWindow& window);
};

#endif // PLAYER_H
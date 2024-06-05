#include "Player.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include "Maze.h"

//std::vector<int> v[100000];
Player::Player(float size, float speed, const Maze& maze)
    : body(sf::Vector2f(size, size)), speed(speed), maze(maze), immunityCheck(false)
{
    body.setFillColor(sf::Color::Blue);
    body.setPosition(51.0f, 51.0f); // Starting position
}


bool Player::canMove(float x, float y, Maze* maze1)
{
    sf::Vector2f position = body.getPosition();
    int cellX = static_cast<int>((position.x + x)*20/1000);
    int cellY = static_cast<int>((position.y + y)*20/1000);
    int cellX2 = static_cast<int>((position.x + x + 25.0f)*20/1000);
    int cellY2 = static_cast<int>((position.y + y + 25.0f)*20/1000);
    float X = (position.x + x) * 20 / 1000;
    float Y = (position.y + y) * 20 / 1000;
    float X2 = (position.x + x + 25) * 20 / 1000;
    float Y2 = (position.y + y + 25) * 20 / 1000;

    if (maze.getCell(cellY, cellX) == Cell::Wall){
        newShape = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
        newShape.setFillColor(sf::Color::Red);
        newShape.setPosition(floor(X) * 1000 / 20, floor(Y) * 1000 / 20);
       // std::cout<<"cellX "<<cellX<<" cellY "<<cellY<<" "<<
    }
    else if (maze.getCell(cellY, cellX) == Cell::End) {
        body.setPosition(51.0f, 51.0f);
        delete maze1;
        maze1 = new Maze(21, 21);
        maze1->generateMaze();
        }
    else if (maze.getCell(cellY, cellX) == Cell::Key) {
        maze1->unlocked = true;
        maze1->grid[cellY][cellX] = Cell::Passage;
    }
    else if (maze.getCell(cellY, cellX) == Cell::Elixer)
    {
        healPlayer();
        maze1->grid[cellY][cellX] = Cell::Passage;
    }
    else if (maze.getCell(cellY, cellX) == Cell::SpikeFloor)
    {
        for (int i = 0; i < maze1->trapcount; i++)
        {
            if (maze1->spikelist[i].xposition == cellX && maze1->spikelist[i].yposition == cellY)
            {
                if (maze1->spikelist[i].discovered == false)
                {
                    maze1->spikelist[i].clock.restart();
                    maze1->spikelist[i].discovered = true;
                }
                else
                {
                    if (maze1->spikelist[i].clock.getElapsedTime() >= sf::seconds(1.0f))
                    {
                        damagePlayer(maze1->spikelist[i].damagePool);
                        maze1->spikelist[i].damagePool = 0;
                        maze1->spikelist[i].discovered = false;
                    }
                }
            }
        }
    }
    
    if (maze.getCell(cellY2, cellX) == Cell::Wall) {
        newShape = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
        newShape.setFillColor(sf::Color::Red);
        newShape.setPosition(floor(X) * 1000 / 20, floor(Y) * 1000 / 20);
    }
    else if (maze.getCell(cellY2, cellX) == Cell::End) {
        body.setPosition(51.0f, 51.0f);
        delete maze1;
        maze1 = new Maze(21, 21);
        maze1->generateMaze();
    }
    else if (maze.getCell(cellY2, cellX) == Cell::Key) {
        maze1->unlocked = true;
        maze1->grid[cellY2][cellX] = Cell::Passage;
    }
    else if (maze.getCell(cellY2, cellX) == Cell::Elixer)
    {
        healPlayer();
        maze1->grid[cellY2][cellX] = Cell::Passage;
    }
    else if (maze.getCell(cellY2, cellX) == Cell::SpikeFloor)
    {
        for (int i = 0; i < maze1->trapcount; i++)
        {
            if (maze1->spikelist[i].xposition == cellX && maze1->spikelist[i].yposition == cellY2)
            {
                if (maze1->spikelist[i].discovered == false)
                {
                    maze1->spikelist[i].clock.restart();
                    maze1->spikelist[i].discovered = true;
                }
                else
                {
                    if (maze1->spikelist[i].clock.getElapsedTime() >= sf::seconds(1.0f))
                    {
                        damagePlayer(maze1->spikelist[i].damagePool);
                        maze1->spikelist[i].damagePool = 0;
                        maze1->spikelist[i].discovered = false;
                    }
                }
            }
        }
    }

    if (maze.getCell(cellY2, cellX2) == Cell::Wall) {
        newShape = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
        newShape.setFillColor(sf::Color::Red);
        newShape.setPosition(floor(X2) * 1000 / 20, floor(Y2) * 1000 / 20);
    }
    else if (maze.getCell(cellY2, cellX2) == Cell::End) {
        body.setPosition(51.0f, 51.0f);
        delete maze1;
        maze1 = new Maze(21, 21);
        maze1->generateMaze();
    }
    else if (maze.getCell(cellY2, cellX2) == Cell::Key) {
        maze1->unlocked = true;
        maze1->grid[cellY2][cellX2] = Cell::Passage;
    }
    else if (maze.getCell(cellY2, cellX2) == Cell::Elixer)
    {
        healPlayer();
        maze1->grid[cellY2][cellX2] = Cell::Passage;
    }
    else if (maze.getCell(cellY2, cellX2) == Cell::SpikeFloor)
    {
        for (int i = 0; i < maze1->trapcount; i++)
        {
            if (maze1->spikelist[i].xposition == cellX2 && maze1->spikelist[i].yposition == cellY2)
            {
                if (maze1->spikelist[i].discovered == false)
                {
                    maze1->spikelist[i].clock.restart();
                    maze1->spikelist[i].discovered = true;
                }
                else
                {
                    if (maze1->spikelist[i].clock.getElapsedTime() >= sf::seconds(1.0f))
                    {
                        damagePlayer(maze1->spikelist[i].damagePool);
                        maze1->spikelist[i].damagePool = 0;
                        maze1->spikelist[i].discovered = false;
                    }
                }
            }
        }
    }

    if (maze.getCell(cellY, cellX2) == Cell::Wall) {
        newShape = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
        newShape.setFillColor(sf::Color::Red);
        newShape.setPosition(floor(X2) * 1000 / 20, floor(Y) * 1000 / 20);
    }
    else if (maze.getCell(cellY, cellX2) == Cell::End) {
        body.setPosition(51.0f, 51.0f);
        delete maze1;
        maze1 = new Maze(21, 21);
        maze1->generateMaze();
    }
    else if (maze.getCell(cellY, cellX2) == Cell::Key) {
        maze1->unlocked = true;
        maze1->grid[cellY][cellX2] = Cell::Passage;
    }
    else if (maze.getCell(cellY, cellX2) == Cell::Elixer)
    {
        healPlayer();
        maze1->grid[cellY][cellX2] = Cell::Passage;
    }
    else if (maze.getCell(cellY, cellX2) == Cell::SpikeFloor)
    {
        for (int i = 0; i < maze1->trapcount; i++)
        {
            if (maze1->spikelist[i].xposition == cellX2 && maze1->spikelist[i].yposition == cellY)
            {
                if (maze1->spikelist[i].discovered == false)
                {
                    maze1->spikelist[i].clock.restart();
                    maze1->spikelist[i].discovered = true;
                }
                else
                {
                    if (maze1->spikelist[i].clock.getElapsedTime() >= sf::seconds(1.0f))
                    {
                        damagePlayer(maze1->spikelist[i].damagePool);
                        maze1->spikelist[i].damagePool = 0;
                        maze1->spikelist[i].discovered = false;
                    }
                }
            }
        }
    }

    if (maze.getCell(cellY, cellX) != Cell::Wall && maze.getCell(cellY2, cellX2) != Cell::Wall && maze.getCell(cellY, cellX2) != Cell::Wall && maze.getCell(cellY2, cellX) != Cell::Wall)
    {
        if (maze.getCell(cellY, cellX) == Cell::Door || maze.getCell(cellY2, cellX2) == Cell::Door || maze.getCell(cellY, cellX2) == Cell::Door || maze.getCell(cellY2, cellX) == Cell::Door)
        {
            if (maze1->unlocked)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }



    
    
}

void Player::damagePlayer(int damage)
{
    if (!immunityCheck || immunityClock.getElapsedTime() >= sf::seconds(1.0f))
    {
        health = health - damage;
        immunityCheck = true;
        immunityClock.restart();

        if (health <= 0)
        {

            // Eventual death feature, will implement as a method or something
            body.setPosition(sf::Vector2f(51.0f, 51.0f));
            health = 100;
            return;
        }
    }

}

void Player::healPlayer()
{
    if (health = 100)
    {
        return;
    }
    else
    {
        health = health + 10;
        if (health > 100)
        {
            health = 100;
        }
    }
}

void Player::handleInput(sf::RenderWindow* window, Maze* maze)
{
    sf::Vector2f position = body.getPosition();
    float speed = 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canMove(0, -speed, maze)) {
        body.move(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && canMove(0, speed, maze)) {
        body.move(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && canMove(-speed, 0, maze)) {
        body.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && canMove(speed, 0, maze)) {
        body.move(speed, 0);
    }


}

void Player::render(sf::RenderWindow& window)
{
    // 
    


    window.draw(body);
    window.draw(newShape);
    
}
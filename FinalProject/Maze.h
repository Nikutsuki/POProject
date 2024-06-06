#pragma once

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include <queue>

enum class Cell
{
    Wall,
    Passage,
    End,
    Door,
    Key,
    Elixer,
    SpikeFloor
};

struct Room
{
    int x, y, width, height;
};

struct Spike
{
    bool discovered;
    int xposition;
    int yposition;
    int damagePool;
    sf::Clock clock;
};

class Maze
{
private:
    int width, height;
    
    std::vector<Room> rooms;
    

    std::random_device rd;
    std::mt19937 gen;

    sf::Texture wall_texture, key_texture, potion_texture;

    // Directions for carving passages
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    void generatePassages(int x, int y);

public:
    Spike* spikelist;
    int trapcount;
    int keypositionx;
    int keypositiony;
    bool unlocked;
  //  bool vis[100000];
//    std::vector<int> v[100000];
    /*void showpath(int x, int y);*/
    std::vector<std::vector<Cell>> grid;
    //static std::queue<int> QQ;
    Maze(int width, int height);
    Cell getCell(int x, int y) const;
    void generateMaze();
    void handleInput(sf::RectangleShape& body);
    void draw(sf::RenderWindow& window, float blockSize) const;
    const std::vector<Room>& getRooms() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif // MAZE_H
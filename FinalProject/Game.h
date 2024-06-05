#pragma once

/*
	Holds all the information of the game
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Enemy.h"
#include "Maze.h"
#include "Player.h"

using namespace sf;

struct GUI
{
	sf::RectangleShape OuterOuter;
	sf::RectangleShape Outer;
	sf::RectangleShape Inner;
	sf::Text Score;
};

class Game
{
private: 
	//Variables of the game

	
	Event event;
	VideoMode videomode;
	
	

	//Private functions

	void initializeVariables();
	void initializeWindow();
	void initializeEnemies();
	void initializeMaze();
	void initializeGUI();

public:
	//public variables
	GUI gamegui;
	RenderWindow* window;
	Maze* maze;
	Enemy* enemyList;
	Player* player;
	//Constructors and destructors

	Game();
	~Game();
	

	//Methods

	void renderObjects();
	void renderGUI(Player* player);
	void update();
	void render();
	void pollEvents();
	void spawnEnemies();

	//Accessors

	const bool running() const;

};


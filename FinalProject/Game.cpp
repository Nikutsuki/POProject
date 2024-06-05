#include "Game.h"
#include <random>
#include "Maze.h"
#include <vector>
#include <string>



//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->maze = new Maze(21, 21);
	this->maze->generateMaze();
	this->player = new Player(25.0f, 1.0f, *this->maze);
	this->initializeGUI();
}

void Game::initializeWindow()
{
	this->videomode.height = 1000;
	this->videomode.width = 1000;
	this->window = new RenderWindow(VideoMode(this->videomode.width, this->videomode.height), "LabirythGra", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initializeEnemies()
{
	/*random_device device;
	uniform_int_distribution<> randomizer(1, 6);
	int enemyCount = randomizer(device);
	*/
	enemyList = new Enemy[1];
	for (int i = 0; i < 1; i++)
	{
		enemyList[i] = Enemy();
	}
}

void Game::initializeMaze()
{

}

void Game::initializeGUI()
{
	this->gamegui.OuterOuter.setSize(sf::Vector2f(104.0f, 102.0f));
	this->gamegui.OuterOuter.setPosition(sf::Vector2f(0.0f, 898.0f));
	this->gamegui.OuterOuter.setFillColor(sf::Color(100, 100, 100));
	this->gamegui.Outer.setSize(sf::Vector2f(102.0f, 52.0f));
	this->gamegui.Outer.setPosition(sf::Vector2f(0.0f, 948.0f));
	this->gamegui.Outer.setFillColor(sf::Color(128, 128, 128));
	this->gamegui.Inner.setPosition(sf::Vector2f(0.0f, 950.0f));
	this->gamegui.Inner.setFillColor(sf::Color::Green);
	this->gamegui.Inner.setSize(sf::Vector2f(100.0f, 75.0f));
}

//Constructors and destructors
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->maze;
	delete this->player;
}




//Functions




void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->event.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}


	}
}

void Game::renderGUI(Player* player)
{
	this->window->draw(gamegui.OuterOuter);
	this->window->draw(gamegui.Outer);
	this->window->draw(gamegui.Inner);
	//gamegui.Score.setString();
	this->window->draw(gamegui.Score);
}

void renderObjects()
{

}



void Game::update()
{
	this->pollEvents();
	this->player->handleInput(window, maze);
	this->maze->handleInput(player->body);

}

void Game::render()
{
	//Drawing background
	this->window->clear();
	//Drawing game objects
	this->maze->draw(*this->window, 50.0f);
	//this->window->draw(this->enemyList[0].body);
	this->player->render(*this->window);
	this->renderGUI(player);
	this->window->display();

}

//Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}


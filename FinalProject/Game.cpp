#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;
	this->maze = new Maze(21, 21);
	this->maze->generateMaze();
	this->player = new Player(25.0f, 1.0f, *this->maze);
	this->font.loadFromFile("ARIAL.ttf");
	this->initializeGUI();
}

void Game::initializeWindow()
{
	this->videomode.height = 1000;
	this->videomode.width = 1000;
	this->window = new RenderWindow(VideoMode(this->videomode.width, this->videomode.height), "Labirynth", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(240);
}

void Game::initializeEnemies()
{
	this->enemy_list.clear();
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> dist(1, 20);
	
	bool spawned = false;
	float min_distance_to_player = 200.f;
	while (!spawned)
	{
		int x = dist(generator);
		int y = dist(generator);
		float distance = sqrt(pow(x * 50 - player->body.getPosition().x, 2) + pow(y * 50 - player->body.getPosition().y, 2));
		if (distance < min_distance_to_player)
			continue;
		if (maze->getCell(y, x) == Cell::Passage)
		{
			Enemy* enemy = new Enemy();
			enemy->body.setPosition(Vector2f((x) * 50.0f, (y) * 50.0f));
			this->enemy_list.push_back(enemy);
			spawned = true;
		}
	}
}

void Game::initializeMaze() {}

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
	this->gamegui.Score.setFont(font);
	this->gamegui.Score.setFillColor(Color::Black);
	this->gamegui.Score.setPosition(0, 910);
	this->gamegui.Score.setCharacterSize(10);
	this->gamegui.Level.setFont(font);
	this->gamegui.Level.setFillColor(Color::Black);
	this->gamegui.Level.setPosition(0, 930);
	this->gamegui.Level.setCharacterSize(10);
	this->gamegui.Health.setFont(font);
	this->gamegui.Health.setFillColor(Color::Black);
	this->gamegui.Health.setPosition(0, 950);
	this->gamegui.Health.setCharacterSize(10);
}

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
	gamegui.Inner.setSize(sf::Vector2f(player->health, 75.0f));
	this->window->draw(gamegui.Inner);
	gamegui.Score.setString("Score: " + std::to_string(player->score));
	this->window->draw(gamegui.Score);
	gamegui.Level.setString("Level: " + std::to_string(player->level));
	this->window->draw(gamegui.Level);
	gamegui.Health.setString("Health: " + std::to_string(player->health));
	this->window->draw(gamegui.Health);
}

void Game::update()
{
	this->pollEvents();
	this->player->handleInput(window, maze, sf::Mouse::getPosition(*window));
	this->maze->handleInput(player->body);

	if (this->player->showdamagefilter && this->player->damageClock.getElapsedTime() >= sf::seconds(0.15))
	{
		this->player->showdamagefilter = false;
	}

	for (Enemy* enemy : enemy_list)
	{
		enemy->is_in_fov(player->body.getPosition());
		if (enemy->follow_player)
		{
			std::cout << "Player is in FOV" << std::endl;
			player->damagePlayer(10, this->maze);
		}
		enemy->Update(maze);
	}
}

void Game::render()
{
	this->window->clear(sf::Color::Transparent);
	this->maze->draw(*this->window, 50.0f);
	this->player->render(*this->window);
	for (Enemy* enemy : enemy_list)
	{
		enemy->Render(*this->window);
	}
	this->renderGUI(player);
	this->window->display();
}

const bool Game::running() const
{
	return this->window->isOpen();
}


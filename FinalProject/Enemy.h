#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

class Enemy
{
private:
	//Variables of enemy
	
	
	//Private functions of enemy
public:
	sf::RectangleShape body;
	float health;
	//Constructors/Destructors
	Enemy();
	~Enemy();

	void Render(sf::RenderWindow& window);
	//Public methods

};



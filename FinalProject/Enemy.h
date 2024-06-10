#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "Maze.h"
#include "vector_utils.h"

using namespace sf;

#define deg_to_rad(angle) ((angle) * 3.14159265 / 180)

class Enemy
{
private:
	const float DETECTION_RADIUS = 400.f;
	sf::Texture texture;
	bool player_spotted = false;
	Vector2f player_pos;

	float closest_wall_distance(Maze* maze, sf::Vector2f pos, float size);
	sf::Vector2f raycast(sf::Vector2f start_pos, float angle, float distance);
public:
	sf::RectangleShape body;
	sf::CircleShape fov;
	sf::CircleShape ray;
	float rotation = 0.f;
	float health;
	bool follow_player = false;

	Enemy();
	~Enemy();

	void Render(sf::RenderWindow& window);
	void Update(Maze* maze);

	bool is_in_fov(Vector2f target_pos);
};



#include "Enemy.h"
//Change size of enemies here
Enemy::Enemy(): body(Vector2f(25.f, 25.f)), health(100)
{
	//this->body.setPosition();
	this->body.setFillColor(Color::Red);
}

Enemy::~Enemy()
{

}

void Enemy::Render(sf::RenderWindow& window)
{	
	window.draw(body);
}

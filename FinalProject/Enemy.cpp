#include "Enemy.h"
//Change size of enemies here
Enemy::Enemy(): body(), health(100)
{
	//this->body.setPosition();
	this->body.setSize(Vector2f(50.0f, 50.0f));
	this->body.setFillColor(Color::Red);
	this->body.setOutlineColor(Color::White);
	this->body.setOutlineThickness(1.0f);
}

Enemy::~Enemy()
{

}

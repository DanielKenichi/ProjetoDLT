#include "Object.h"

Object::Object()
{
	InitializeObject();
}

Object::~Object()
{
}

void Object::InitializeObject()
{
	//this->body.setPosition();
	this->body.setSize(sf::Vector2f(50.f, 50.f));
	this->body.setFillColor(sf::Color::Cyan);
	this->body.setOutlineColor(sf::Color::Black);
	this->body.setOutlineThickness(1.f);

	//this->Speed = std::rand() % 1000 + 1; //teoricamente gera um número entre 1 e 10

	//this->Speed = 5;

}

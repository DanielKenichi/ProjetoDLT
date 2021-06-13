#include "Object.h"


/*Construtor e Destrutor*/
Object::Object()
{
	initializeObject();
}

Object::~Object()
{
}

/*getters*/
sf::RectangleShape Object::getBody()
{
	return this->body;
}

/*
*initializeObject(): Inicializa os atributos de um objeto
*/
void Object::initializeObject() //h 600 w 800
{
	int keypos;

	std::srand(time(0));

	keypos = std::rand() % 4 + 1;
	
	/*OBS: AJUSTAR O TAMANHO PARA SPAWNAR FORA DA TELA*/
	switch (keypos) 
	{
	case 1:
		this->body.setPosition(375.f, 0.f); //O objeto ir� spawnar em cima do jogador
		break;

	case 2:
		this->body.setPosition(0.f, 275.f); //O objeto ir� spawnar � esquerda do jogador
		break;

	case 3:
		this->body.setPosition(750.f, 275.f); //O objeto ir� spawnar � direita do jogador
		break;
	case 4:
		this->body.setPosition(375.f, 550.f); //O objeto ir� spawnar embaixo do jogador
		break;
	}

	this->body.setSize(sf::Vector2f(50.f, 50.f));
	this->body.setFillColor(sf::Color::Cyan);
	this->body.setOutlineColor(sf::Color::Black);
	this->body.setOutlineThickness(1.f);

	//this->Speed = std::rand() % 1000 + 1; //teoricamente gera um n�mero entre 1 e 10

	//this->Speed = 5;

}

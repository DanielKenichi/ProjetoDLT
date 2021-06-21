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
sf::Sprite Object::getBody()
{
	return this->body;
}

/*
*initializeObject(): Inicializa os atributos de um objeto
*/
void Object::initializeObject() 
{
	const sf::Vector2f spriteScale(0.5f, 0.5f);

	this->poskey = std::rand() % 4 + 1;

	//Carregamento de Texturas
	if (!this->bodyImage.loadFromFile("resources/object.png")) //imagem 128x128
	{  
		std::cout << "Object.cpp : Falha na leitura de Object.png" << std::endl;
	}

	bodyImage.setSmooth(true);

	this->body.setTexture(bodyImage);

	sf::Vector2f middle(this->body.getLocalBounds().width / 2, this->body.getLocalBounds().height / 2);
	this->body.setOrigin(middle);

	
	/*OBS: AJUSTAR O TAMANHO PARA SPAWNAR FORA DA TELA*/
	switch (this->poskey) 
	{
	case 1:
		this->body.setPosition(400.f, 0.f); //O objeto ir� spawnar em cima do jogador
		this->body.setRotation(90.f);
		break;

	case 2:
		this->body.setPosition(0.f, 300.f); //O objeto ir� spawnar � esquerda do jogador
		this->body.setRotation(0.f);
		break;

	case 3:
		this->body.setPosition(800.f, 300.f); //O objeto ir� spawnar � direita do jogador
		this->body.setRotation(180.f);
		break;

	case 4:
		this->body.setPosition(400.f, 600.f); //O objeto ir� spawnar embaixo do jogador
		this->body.setRotation(270.f);
		break;
	}

	this->body.setScale(spriteScale);
	this->Speed = 0.2f;
	//this->Speed = 0.2f;
	//this->Speed = std::rand() % 5 + 1; //gera um n�mero entre 1 e 5

}

void Object::moveObject(float dt)
{

	sf::Vector2f pos;

	switch (this->poskey)
	{
	case 1:
		this->body.move(0.f, 1.f * this->Speed * dt); //Movimenta��o do objeto caso seja spawnado em cima
		break;

	case 2:
		this->body.move(1.f * this->Speed * dt, 0.f); //...caso seja spawnado � esquerda
		break;

	case 3:
		this->body.move(-1.f * this->Speed * dt, 0.f); //...caso seja spawnado � direita
		break;

	case 4:
		this->body.move(0.f, -1.f * this->Speed * dt); //...caso seja spawnado embaixo
		break;
	}
}

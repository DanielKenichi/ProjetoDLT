#include "Object.h"
#include "Game.h"
#
#include <math.h>

/*Construtor e Destrutor*/
Object::Object(){
	this->poskey = 0;
	this->Speed = 0;
}

Object::~Object(){
	//std::cout << "Objeto Destruido" << std::endl;
}

/*getters*/
sf::Sprite Object::getBody(){
	return this->body;
}

sf::Time Object::getHitTime()
{
	return this->hitTime;
}

int Object::getSpeed()
{
	return this->Speed;
}

/*
*initializeObject(): Inicializa os atributos de um objeto
*/
void Object::initializeObject(int level, int h, int w, float dt, int ph, int pw, int key) {
	const sf::Vector2f spriteScale(0.5f, 0.5f);

	this->poskey = std::rand() % 4 + 1;

	//Carregamento de Texturas
	if (!this->bodyImage.loadFromFile("resources/Stickersprite.png")){ //imagem 128x128  
		std::cout << "Object.cpp : Falha na leitura de Stickersprite.png" << std::endl;
	}

	bodyImage.setSmooth(true);

	this->body.setTexture(bodyImage);

	sf::Vector2f middle(this->body.getLocalBounds().width / 2, this->body.getLocalBounds().height / 2);
	this->body.setOrigin(middle);

	this->body.setScale(spriteScale);
	this->speedAdjust(level, key);
	
	/*OBS: AJUSTAR O TAMANHO PARA SPAWNAR FORA DA TELA*/
	switch (this->poskey) {
	case 1:
		this->body.setPosition(w/2.f, 0.f); //O objeto ir� spawnar em cima do jogador
		this->body.setRotation(90.f);
		this->hitTime = sf::seconds(((h / 2 - 0) - ph/2) / this->Speed * dt);
		break;

	case 2:
		this->body.setPosition(0.f, h/2.f); //O objeto ir� spawnar � esquerda do jogador
		this->body.setRotation(0.f);
		this->hitTime = sf::seconds(((w / 2 - 0) - pw/2) / this->Speed * dt);
		break;

	case 3:
		this->body.setPosition(w, h/2.f); //O objeto ir� spawnar � direita do jogador
		this->body.setRotation(180.f);
		this->hitTime = sf::seconds(((w - w / 2) + pw/2) / this->Speed * dt);
		break;

	case 4:
		this->body.setPosition(w/2.f, h); //O objeto ir� spawnar embaixo do jogador
		this->body.setRotation(270.f);
		this->hitTime = sf::seconds(((h - h / 2) + ph/2) / this->Speed * dt);
		break;
	}

	
	//this->Speed = 0.2f;
	//this->Speed = std::rand() % 5 + 1; //gera um n�mero entre 1 e 5

}

void Object::moveObject(float dt){

	switch (this->poskey){
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
	default:
		std::cout << "default" << std::endl;
		break;
	}
}

void Object::speedAdjust(int level, int key)
{
	
	
	/*key = 1: fase de Velocidade constante
	* key = 2: fase de velocidade variavel
	*/
	switch (key) {
	case 1:		
		if (level == 1)
			this->Speed = 300.f;
		else if (level > 1 && level <= 3)
			this->Speed = 400.f;
		else if (level > 3 && level < 10)
			this->Speed = 600.f;

		else if (level >= 10 && level % 5 == 0)
			this->Speed = 100.f;

		else if (level >= 10 && level % 5 != 0)
			this->Speed = 800.f;

		break;

	case 2:
		if(level < 10)
			this->Speed = (std::rand() % 6 + 2) * 100.f;
		else
			this->Speed = (std::rand() % 7 + 1) * 100.f;
		
		break;
	}
}

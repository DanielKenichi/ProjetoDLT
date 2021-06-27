#include "Object.h"
#include "Game.h"

/*Construtor e Destrutor*/
Object::Object(){
}

Object::~Object(){
	std::cout << "Objeto Destruido" << std::endl;
}

/*getters*/
sf::Sprite Object::getBody(){
	return this->body;
}

/*
*initializeObject(): Inicializa os atributos de um objeto
*/
void Object::initializeObject(int level, int h, int w) {
	const sf::Vector2f spriteScale(0.5f, 0.5f);

	this->poskey = std::rand() % 4 + 1;

	//Carregamento de Texturas
	if (!this->bodyImage.loadFromFile("resources/object.png")){ //imagem 128x128  
		std::cout << "Object.cpp : Falha na leitura de Object.png" << std::endl;
	}

	bodyImage.setSmooth(true);

	this->body.setTexture(bodyImage);

	sf::Vector2f middle(this->body.getLocalBounds().width / 2, this->body.getLocalBounds().height / 2);
	this->body.setOrigin(middle);

	
	/*OBS: AJUSTAR O TAMANHO PARA SPAWNAR FORA DA TELA*/
	switch (this->poskey) {
	case 1:
		this->body.setPosition(w/2.f, 0.f); //O objeto ir� spawnar em cima do jogador
		this->body.setRotation(90.f);
		break;

	case 2:
		this->body.setPosition(0.f, h/2.f); //O objeto ir� spawnar � esquerda do jogador
		this->body.setRotation(0.f);
		break;

	case 3:
		this->body.setPosition(w, h/2.f); //O objeto ir� spawnar � direita do jogador
		this->body.setRotation(180.f);
		break;

	case 4:
		this->body.setPosition(w/2.f, h); //O objeto ir� spawnar embaixo do jogador
		this->body.setRotation(270.f);
		break;
	}

	this->body.setScale(spriteScale);
	this->speedAdjust(level);
	//this->Speed = 0.2f;
	//this->Speed = std::rand() % 5 + 1; //gera um n�mero entre 1 e 5

}

void Object::moveObject(float dt){

	sf::Vector2f pos;

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
	}
}

void Object::speedAdjust(int level)
{
	//int key = std::rand() % 2 + 1;
	int key = 1;
	/*key = 1: fase de Velocidade constante
	* key = 2: fase de velocidade variavel
	*/
	switch (key) {
	case 1:		
		if (level == 1) {
			this->Speed = 200.f;
		}if (level > 1 && level <= 5) {
			this->Speed = 300.f;
		}if (level > 5) {
			this->Speed = 600.f;
		}
		break;
	case 2: 
		break;
	}
}

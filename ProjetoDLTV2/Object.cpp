#include "Object.h"
#include "Game.h"
#
#include <math.h>

/*Construtor e Destrutor*/
Object::Object(){
	poskey = 0;
	Speed = 0;
}

Object::~Object(){
	//std::cout << "Objeto Destruido" << std::endl;
}

/*getters*/
sf::Sprite Object::getBody(){
	return body;
}

sf::Time Object::getHitTime()
{
	return hitTime;
}

int Object::getSpeed()
{
	return Speed;
}

/*
*initializeObject(): Inicializa os atributos de um objeto
*/
void Object::initializeObject(int level, int h, int w, float dt, int ph, int pw, int key) {
	const sf::Vector2f spriteScale(0.5f, 0.5f);

	poskey = std::rand() % 4 + 1;

	//Carregamento de Texturas
	if (!bodyImage.loadFromFile("resources/Stickersprite.png")){ //imagem 128x128  
		std::cout << "Object.cpp : Falha na leitura de Stickersprite.png" << std::endl;
	}

	bodyImage.setSmooth(true);

	body.setTexture(bodyImage);

	sf::Vector2f middle(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
	body.setOrigin(middle);

	body.setScale(spriteScale);
	speedAdjust(level, key);
	
	/*OBS: AJUSTAR O TAMANHO PARA SPAWNAR FORA DA TELA*/
	switch (poskey) {
	case 1:
		body.setPosition(w/2.f, 0.f); //O objeto ir� spawnar em cima do jogador
		body.setRotation(90.f);
		hitTime = sf::seconds(((h / 2 - 0) - ph/2) / Speed * dt);
		break;

	case 2:
		body.setPosition(0.f, h/2.f); //O objeto ira spawnar a esquerda do jogador
		body.setRotation(0.f);
		hitTime = sf::seconds(((w / 2 - 0) - pw/2) / Speed * dt);
		break;

	case 3:
		body.setPosition(w, h/2.f); //O objeto ira spawnar a direita do jogador
		body.setRotation(180.f);
		hitTime = sf::seconds(((w - w / 2) + pw/2) / Speed * dt);
		break;

	case 4:
		body.setPosition(w/2.f, h); //O objeto ira spawnar embaixo do jogador
		body.setRotation(270.f);
		hitTime = sf::seconds(((h - h / 2) + ph/2) / Speed * dt);
		break;
	}

	
	//Speed = 0.2f;
	//Speed = std::rand() % 5 + 1; //gera um n�mero entre 1 e 5

}
/*
* moveObject(float dt): Movimenta os objetos
*/
void Object::moveObject(float dt){

	switch (poskey){
	case 1:
		body.move(0.f, 1.f * Speed * dt); //Movimentacao do objeto caso seja spawnado em cima
		break;

	case 2:
		body.move(1.f * Speed * dt, 0.f); //...caso seja spawnado a esquerda
		break;

	case 3:
		body.move(-1.f * Speed * dt, 0.f); //...caso seja spawnado a direita
		break;

	case 4:
		body.move(0.f, -1.f * Speed * dt); //...caso seja spawnado embaixo
		break;
	default:
		std::cout << "default" << std::endl;
		break;
	}
}
/*
* speedAdjust(int level, int key): Ajusta a velocidade do objeto com base no nivel da fase
*/
void Object::speedAdjust(int level, int key)
{	
	/*key = 1: fase de Velocidade constante
	* key = 2: fase de velocidade variavel
	*/
	switch (key) {
	case 1:		
		if (level == 1)
			Speed = 300.f;
		else if (level > 1 && level <= 3)
			Speed = 400.f;
		else if (level > 3 && level < 10)
			Speed = 600.f;

		else if (level >= 10 && level % 5 == 0)
			Speed = 100.f;

		else if (level >= 10 && level % 5 != 0)
			Speed = 800.f;

		break;

	case 2:
		if(level < 10)
			Speed = (std::rand() % 6 + 2) * 100.f;
		else
			Speed = (std::rand() % 7 + 1) * 100.f;
		
		break;
	}
}

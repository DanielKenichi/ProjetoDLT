
#ifndef GAME_H
#define GAME_H

/*
* A classe do jogo 
*/

//Bibliotecas e includes
#include <iostream>
#include "ObjectsQueue.h"
#include "ObjectsList.h"

class Game
{
public:

	//**Construtores e destrutores**
	Game();
	virtual ~Game();

	//**Getters**
	const bool getIsWindowOpen();

	//**Métodos**
	void update(); 
	void render(); 



private:
	//**Atributos**
	sf::RenderWindow* window;//Janela de Renderização
	sf::Event ev;//Variável de evento
	sf::VideoMode videoMode; //Dimensoes da janela
	ObjectsQueue objects;
	ObjectsList spawnedObjects;


	//**Métodos privados**
	void initializeVariables();
	void initializeWindow();
	void initializeObjects();
	void renderEnemies();

	
};

#endif // !GAME_H
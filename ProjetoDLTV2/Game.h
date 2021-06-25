
#ifndef GAME_H
#define GAME_H

/*
* A classe do jogo 
*/

//Bibliotecas e includes
#include <iostream>
#include "ObjectsQueue.h"
#include "ObjectsList.h"
#include "Player.h"

class Game
{
public:

	//**Construtores e destrutores**
	Game();
	virtual ~Game();

	//**Getters**
	const bool getIsWindowOpen();

	//**Métodos**
	void update(float dt); 
	void render(); 

private:
	//**Atributos**
	sf::RenderWindow* window;//Janela de Renderização
	sf::Event ev;//Variável de evento
	sf::VideoMode videoMode; //Dimensoes da janela
	
	//Atributos de Score
	sf::Font font; //Fonte
	int score = 0;
	int hp = 1;
	sf::Text tHP;
	sf::Text tScore;

	//Texto de game over

	ObjectsQueue objects; // Fila de Objetos
	ObjectsList spawnedObjects; // Lista de Objetos Ativos
	Player player; // Jogador

	//Indicador de estado
	int state;
	
	//start
	bool start;

	//Indicadores de fase
	int level;
	bool pass;
	bool inGame;

	//**Métodos privados**
	void initializeVariables();
	void initializeWindow();
	void initializeObjects();
	void initializePlayer();

	void renderObjects();
	void renderScore();
	void testCollisions();

	void updateObjects(float dt);
	void pollEvents(float dt);
	void generateQueue(int size);
	void spawnObject();

};

#endif // !GAME_H

#ifndef GAME_H
#define GAME_H
#define WIDTH 1000
#define HEIGHT 800

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
	sf::Text tGameover;
	sf::Text tFinalScore;

	ObjectsQueue objects; // Fila de Objetos
	ObjectsList spawnedObjects; // Lista de Objetos Ativos
	Player player; // Jogador

	//timers
	sf::Time spawnTimer;
	sf::Time checkerTimer;
	sf::Time LastObjTimer;

	//Indicador de estado
	int state;
	
	//Start game
	bool start;

	//Pause
	bool pause;

	//Indicadores de fase
	int level;
	bool pass;
	bool inGame;

	//**Métodos privados**
	void initializeVariables();
	void initializeWindow();
	void initializeObjects(float dt);
	void initializePlayer();
	void initializeTexts();

	void renderObjects();
	void renderScore();
	void renderGameOver();
	void testCollisions();

	sf::Time setSpawnTimer();
	void increaseTimer(float dt, sf::Time *timer);
	void decreaseTimer(float dt, sf::Time* timer);
	void updateObjects(float dt);
	void pollEvents(float dt);
	void generateQueue(int size, float dt);
	void spawnObject();

};

#endif // !GAME_H
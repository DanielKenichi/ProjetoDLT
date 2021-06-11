
#ifndef GAME_H
#define GAME_H

/*
* A classe do jogo 
*/

//Bibliotecas e includes
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


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


	//**Métodos privados**
	void initializeVariables();
	void initializeWindow();

	sf::RenderWindow* window;//window
	sf::Event ev;//variavel de evento
	sf::VideoMode videoMode; //Dimensoes da janela
	
};

#endif // !GAME_H
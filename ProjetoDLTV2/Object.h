#ifndef OBJECT_H
#define OBJECT_H

/*
* Classe do objeto/obst�culo atirado em dire��o ao jogador
*/

//Bibliotecas e includes
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Object{
public:

	//**Construtores e Destrutores**
	Object();
	~Object();

	//**getters**
	sf::Sprite getBody();
	sf::Time getHitTime();
	int getSpeed();
	//**setters**

	//**M�todos**
	void initializeObject(int level, int h, int w, float dt, int ph, int pw, int key);
	void moveObject(float dt);

private:

	sf::Sprite body; //Corpo improvisado pro nosso objeto
	int poskey; //determina a posi��o de spawn do objeto
	int Speed; //multiplicador de velocidade
	sf::Time hitTime; //tempo até colisao com o player
	sf::Texture bodyImage; //textura do corpo do objeto

	void speedAdjust(int level, int key);
};

#endif //OBJECT_H


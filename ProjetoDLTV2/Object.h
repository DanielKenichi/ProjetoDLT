#ifndef OBJECT_H
#define OBJECT_H

/*
* Classe do objeto/obstáculo atirado em direção ao jogador
*/

//Bibliotecas e includes
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Object
{
public:

	//**Construtores e Destrutores**
	Object();
	~Object();

	//**getters**
	sf::Sprite getBody();
	//**setters**

	//**Métodos**
	void initializeObject();
	void moveObject();

private:

	sf::Sprite body; //Corpo improvisado pro nosso objeto
	int poskey; //determina a posição de spawn do objeto
	int Speed; //multiplicador de velocidade

	sf::Texture bodyImage; //textura do corpo do objeto


};

#endif //OBJECT_H


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


class Object
{
public:

	//**Construtores e Destrutores**
	Object();
	~Object();

	//**getters**
	sf::RectangleShape getBody();
	//**setters**

	//**M�todos**
	void initializeObject();

private:

//atributos
	sf::RectangleShape body; //Corpo improvisado pro nosso objeto
	int Speed;


};

#endif //OBJECT_H


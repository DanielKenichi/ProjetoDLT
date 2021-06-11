#ifndef PLAYER_H
#define PLAYER_H

/*
* A classe do jogador 
*/

//Bibliotecas e includes
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
public:
    Player();
    ~Player();
private:
    // Vida
    int HP;

    // Sprite e funções relacionadas
    sf::Sprite spr;
    void rotate(double ang);
};

#endif // !PLAYER_H
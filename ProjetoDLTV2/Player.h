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

    // Escudos (4, alguns desabilitados)
    sf::Sprite sTop;
    sf::Sprite sBottom;
    sf::Sprite sLeft;
    sf::Sprite sRight;
    void InitializeShields(bool top, bool bottom, bool left, bool right);

    // Sprite e funções relacionadas
    sf::Sprite spr; // Player
    void rotate(double ang); // Rotacionar
    double getPRotation(); // Get Player Rotation
};

#endif // !PLAYER_H
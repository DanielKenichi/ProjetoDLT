#include "Player.h"
#include <stdio.h>

Player::Player()
{
    std::cout << "Player Criado" << std::endl;
}

Player::~Player()
{
    std::cout << "Player Destruído" << std::endl;
}

void Player::rotate(double ang)
{
    std::cout << "Rotacionando para " << ang << "º graus" << std::endl;
}
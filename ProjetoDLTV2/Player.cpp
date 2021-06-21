#include "Player.h"
#include <stdio.h>
#include <cmath>

Player::Player()
{
    this->initializeSprites();
}

void Player::initializeSprites(){
    // Carregamento de Texturas
    if(!tPlayer.loadFromFile("resources/Player.png")){ //Imagem quadrada 128x128
		std::cout<<"Player.cpp : Falha na leitura de Player.png" << std::endl;
	}
    tPlayer.setSmooth(true);
    if(!tShield.loadFromFile("resources/Escudo.png")){ //Imagem retangular 128x32
		std::cout<<"Player.cpp : Falha na leitura de Escudo.png" << std::endl;
	}
    tShield.setSmooth(true);

    // Atribuição de Texturas aos Sprites
    spr.setTexture(tPlayer);
    sTop.setTexture(tShield);
    sRight.setTexture(tShield);
    sDown.setTexture(tShield);
    sLeft.setTexture(tShield);

    // Ajuste de Tamanho
    const sf::Vector2f spriteScale(0.5f, 0.5f);
    spr.setScale(spriteScale);
    sTop.setScale(spriteScale);
    sRight.setScale(spriteScale);
    sDown.setScale(spriteScale);
    sLeft.setScale(spriteScale);

    // Ajuste de Origem
    sf::Vector2f middle(spr.getLocalBounds().width/2, spr.getLocalBounds().height/2);
    spr.setOrigin(middle);
    sTop.setOrigin(middle + sf::Vector2f(0.0f, middle.y/2));
}

Player::~Player(){
    std::cout << "Player Destruido" << std::endl;
}

int Player::getHP(){
    return this->HP;
}

void Player::setHP(int hp){
    this->HP = hp;
}

void Player::rotateDirection(char dir, float dt){
    switch(dir){
        case 'u': //up
            //this->rotatePlayer(0.f, dt);
            angAlvo = 360.f;
        break;
        case 'r': //right
            this->rotatePlayer(90.f, dt);
            angAlvo = 90.f;
        break;
        case 'd': //down
            //this->rotatePlayer(180.f, dt);
            angAlvo = 180.f;
        break;
        case 'l': //left
            //this->rotatePlayer(270.f, dt);
            angAlvo = 270.f;
        break;
    }
}

float modulo(float a, float b){
    return a - floor(a/b) * b;
}

void Player::rotatePlayer(double ang, float dt){
    float deltaAng = ang - this->getRotation();
    deltaAng = modulo((deltaAng + 180.f), 360.f) - 180.f;
    float distancia = fabs(deltaAng);  
    double distDecel = pow(this->velocidade, 2)/(2*DESACELERACAO);
    
    if(distancia < (velocidade)) //Muito próximo do ângulo final
    { 
        this->setRotation(ang);
        this->velocidade = 0;
    }
    else if(distancia > distDecel) //Longe, continuar acelerando
    { 
        velocidade = fmin(velocidade + ACELERACAO, VELOCIDADEMAX);
    }
    else //Começar a desacelerar
    { 
        velocidade = fmax(velocidade - DESACELERACAO, 0);
    }
    this->rotate(velocidade * (deltaAng < 0 ? -1 : 1) * dt * 100.f);
    //this->rotate(velocidade * (deltaAng < 0 ? -1 : 1) * dt); 
}

double Player::getPRotation(){
    return this->spr.getRotation();
}

void InitializeShields(bool top, bool right, bool bottom, bool left){
    // Inicializar os sprites (procurar nos resources)
    // TODO:
    if(top){

    }
    if(right){

    }
    if(bottom){

    }
    if(left){

    }
    //Configurar offset de rotação -> entity.setOrigin(10.f, 20.f); (Padrão é 0, 0)
    //Setar a rotação offset de cada escudo -> entity.setRotation(x); com x = 0, 90, 180, 270
}

void Player::renderAll(sf::RenderWindow *win){
    win->draw(spr);
    win->draw(sTop);
}

void Player::updateAll(float dt){
    //Temporário FIXME: solução permanente para todas as atualizações
    this->rotatePlayer(angAlvo, dt);
    spr.setPosition(this->getPosition());
    sTop.setPosition(this->getPosition());
    spr.setRotation(this->getRotation());
    sTop.setRotation(this->getRotation()); 

    //Animação Escudo
    if(cTop.getElapsedTime().asSeconds() > 0.06){
        sTop.setColor(sf::Color::White);
    }else{
        sTop.setColor(sf::Color::Red);
    }
    //Animação Player
    if(cSpr.getElapsedTime().asSeconds() > 0.06){
        spr.setColor(sf::Color::White);
    }else{
        spr.setColor(sf::Color::Red);
    }
}

bool Player::collidePlayer(sf::Sprite obj){
    if(Collision::CircleTest(this->spr, obj)){
        HP--;
        cSpr.restart();
        return true;
    }else{
        return false;
    }
}

bool Player::collideShields(sf::Sprite obj){ 
    if(Collision::BoundingBoxTest(this->sTop, obj)){
        cTop.restart();
        return true;
    }else{
        return false;
    }
}
#include "Game.h"
#include <stdio.h>

//**Construtores e destrutores**
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
}

Game::~Game()
{
	delete this->window; 
}

//**Getters**

//getIsWindowOpen(): Retorna true caso a janela do jogo esteja aberta, e false caso contrário
const bool Game::getIsWindowOpen()
{
	return this->window->isOpen();
}


//**Métodos Públicos**

//update():Atualiza os frames do jogo
void Game::update()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed) //Fecha a janela do jogo ao clicar no "X" da janela
			this->window->close();
	}
}

//render(): Renderiza os objetos do jogo
void Game::render()
{
	this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo

	this->window->display(); //Exibe na tela o desenho realizado no frame

}


//**Métodos Privados**

//InitializeVariables() : Inicializa as variáveis iniciais
void Game::initializeVariables()
{
	this->window = nullptr;
}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Projeto DLT", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	
	//Carrega e seta a imagem do jogo
	sf::Image icon;
	if(!icon.loadFromFile("resources/icon.png")){ //Imagem quadrada 128x128
		std::cout<<"Falha na leitura do ícone" << std::endl;
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}


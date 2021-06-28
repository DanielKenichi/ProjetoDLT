#include "Game.h"
#include <stdio.h>
#include <String>

// --> Construtor e Inicializadores <--
Game::Game(){
	this->initializeVariables();
	this->initializeWindow();
	this->initializeTexts();
}
// --> Destrutor <--
Game::~Game(){
	delete this->window;
}

/*
* update():Atualiza os frames do jogo de acordo com cada estado:
*	State 0: Main Screen 
*	State 1: Gerando nova fase
*   State 2: Em jogo
*   State 3: Game over
*	State 4: Pause
*/
void Game::update(float dt){

	this->pollEvents(dt);

	//state 0
	if (this->state == 0){
		std::cout << "Estou na tela principal" << std::endl;
		//gera main screen

		//condição de saida : start game
		if (this->start == true){
			this->initializePlayer();
			this->player.setHP(3);
			this->score = 0;
			this->state = 1;
		}
		
	}
	//state 1
	if (this->state == 1){
		std::cout << "gerando objetos da fase: " << this->level <<  std::endl;
		this->pass = false;
		this->initializeObjects(dt);
		this->LastObjTimer = objects.getFirst().getHitTime();
		this->checkerTimer = sf::seconds(-999.f);
		if (this->level % 5 == 0) this->player.setHP(this->player.getHP() + 1);

		//condição de saída: ter gerado os objetos
		this->state = 2;
	}

	//State 2
	if (this->state == 2){

		this->hp = this->player.getHP();
		this->updateObjects(dt);
		this->testCollisions();
		this->player.updateAll(dt);

		//condições de saída: Zerar hp 
		if (this->player.getHP() == 0){
			this->state = 3;
		}

		//Passar a fase
		else if (pass == true){
			std::cout << "YAY passou" << std::endl;
			this->level++;
			this->inGame = false;
			this->state = 1;
		}
		//Pausar o jogo
		else if (pause == true) {
			this->state = 4;
		}
	}

	//State 3
	if (this->state == 3) {
		//std::cout << "Game Over" << std::endl;

		//esvaziando lista e fila
		while (this->objects.isEmpty() == false) {
			this->objects.removeObject();
		}
		while (this->spawnedObjects.getNroElementos() != 0) {
			this->spawnedObjects.removeObject();
		}

		this->hp = this->player.getHP();
		this->player.updateAll(dt);

		//voltando variaveis ao estado inicial
		this->inGame = false;
		this->level = 1;
		this->spawnTimer = sf::seconds(0.f);
		
		

		//condição de saida: Após confirmação do player, voltar para tela inicial
		if (this->start == false) {
			this->state = 0;
		}		
	}

	//state 4
	if (this->state == 4) {
		std::cout << "Jogo pausado" << std::endl;

		//Condição de Saída: Despausar o jogo
		if (this->pause == false) {
			this->state = 2;
		}
	}
	
}

/*
* render(): Renderiza os objetos do jogo
* 	State 0: Main Screen 
*	State 1: Gerando nova fase
*   State 2: Em jogo
*   State 3: Game over
*	State 4: Pause
*/
void Game::render(){

	/*sf::View view;
	sf::FloatRect;*/

	//state 0 
	if (this->state == 0){
		this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		this->renderInicial();
		//renderiza mainScreen
	}
	
	//state 1
	if (this->state == 1) {
		this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		this->window->clear(sf::Color::Red); //limpa o frame antigo
		//renderiza uma tela de loading
	}

	//state 2
	if (this->state == 2) {
		this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		
		this->player.renderAll(this->window); //Desenha o Player

		this->renderObjects();

		this->renderScore();
	}

	//state 3
	if (this->state == 3) {
		//renderiza tela de Game over
		this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo
		
		this->player.renderAll(this->window); //Desenha o Player

		this->renderObjects();

		sf::RectangleShape opaco(sf::Vector2f(videoMode.width, videoMode.height));
		opaco.setFillColor(sf::Color(0,0,0,150));
		this->window->draw(opaco);

		this->renderGameOver();
	}

	//state 4
	if (this->state == 4) {
		//renderiza tela de pause
		sf::RectangleShape opaco(sf::Vector2f(videoMode.width, videoMode.height));
		opaco.setFillColor(sf::Color(0,0,0,150));

		this->player.renderAll(this->window); //Desenha o Player

		this->renderScore();

		this->renderObjects();

		this->window->draw(opaco);
		renderPause();
	}

	this->window->display(); //Exibe na tela o desenho realizado no frame
}


//**Getters**
//getIsWindowOpen(): Retorna true caso a janela do jogo esteja aberta, e false caso contrário
const bool Game::getIsWindowOpen(){
	return this->window->isOpen();
}

//**Outros metodos**

//InitializeVariables() : Inicializa as variáveis iniciais
void Game::initializeVariables(){
	this->window = nullptr;

	this->start = false;
	this->pause = false;

	this->spawnTimer = sf::seconds(0.f);
	this->checkerTimer = sf::seconds(-999.f);
	this->state = 0; 
	this->level = 1;
	this->pass = false;
	this->inGame = false;

	this->objects.initializeQueue();
	this->spawnedObjects.initializeList();

	if(!this->font.loadFromFile("resources/Fonts/Rubik.ttf")){
		std::cout << "Falha no carregamento da fonte" << std::endl;
	}

}

sf::Vector2f round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

void Game::initializeTexts(){

	// Texto HP
	tHP = sf::Text{"HP: ", font, 32};
	tHP.setPosition(10,0);

	// Texto Score
	tScore = sf::Text{"Score: ", font, 32};
	tScore.setPosition(10, tHP.getCharacterSize() + 10);

	// Texto Level
	nivel = sf::Text{ "Level ", font, 32 };
	nivel.setPosition(10, nivel.getCharacterSize() + 52);

	// Texto Gameover
	tGameover = sf::Text{"Gameover", font, 128};
	tGameover.setOrigin(tGameover.getLocalBounds().width/2.f, tGameover.getLocalBounds().height/2.f);
	tGameover.setPosition(videoMode.width/2.f, videoMode.height/2.f - 128);

	// Texto Final Score
	tFinalScore = sf::Text{"Score: ", font, 32};
	tFinalScore.setOrigin(tFinalScore.getLocalBounds().width/2.f, tFinalScore.getLocalBounds().height/2.f);
	tFinalScore.setPosition(videoMode.width/2.f, videoMode.height/2.f);	

	// Texto Pause
	tPause = sf::Text{"PAUSADO", font, 64};
	tPause.setOrigin(tPause.getLocalBounds().width + 10, tPause.getLocalBounds().height + 10);
	tPause.setPosition(videoMode.width - 20, videoMode.height - 20);	

	// Texto Instrução
	tInstrucao = sf::Text{"Aperte Enter para iniciar", font, 64};
	tInstrucao.setOrigin(tInstrucao.getLocalBounds().width/2, tInstrucao.getLocalBounds().height/2);
	tInstrucao.setPosition(videoMode.width/2.f, videoMode.height/2.f);	

	// Texto Extra (Menu Inicial)
	tExtra = sf::Text{L"2021 - Criado por Bruno L., Daniel K., João D.", font, 16};
	tExtra.setOrigin(tExtra.getLocalBounds().width/2, tExtra.getLocalBounds().height/2);
	tExtra.setPosition(videoMode.width/2.f, videoMode.height - 20);

}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow(){
	this->videoMode.height = HEIGHT;
	this->videoMode.width = WIDTH;
	this->window = new sf::RenderWindow(this->videoMode, "Dona Chica Simulator", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	//Carrega e seta a imagem do jogo
	sf::Image icon;
	if(!icon.loadFromFile("resources/icon.png")){ //Imagem quadrada 128x128
		std::cout<<"Falha na leitura do ícone" << std::endl;
	}
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

/*
* *initializeObjects(): Inicializa a fila de objetos a serem gerados e a lista de objetos spawnados
*/
void Game::initializeObjects(float dt){

	int numObjs = this->level * 3;
	if (numObjs > 200) numObjs = 200;

	std::srand(time(0));  //inicializando seed aleatoria

	this->generateQueue(numObjs, dt); //definir regra de geração pra queue (etapa de fase)
}

void Game::initializePlayer(){

	this->player.setPosition(videoMode.width/2, videoMode.height/2);
}

/*
* generateQueue(int size): Gera a fila de objetos de acordo com um parâmetro decidido no inicio de cada fase
*/
void Game::generateQueue(int size, float dt){

	int key = level > 5 ? std::rand() % 2 + 1 : 1;
	for (int i = 0; i < size; i++){
		this->objects.newObject(this->level, this->window->getSize().x, this->window->getSize().y, dt, 
								this->player.getSpriteSize().height, this->player.getSpriteSize().width, key);
	}
}

//pollEvents(): Verifica eventos (Teclado, Janela aberta)
void Game::pollEvents(float dt){
	//Event polling
	while (this->window->pollEvent(this->ev)){
		if (this->ev.type == sf::Event::Closed) //Fecha a janela do jogo ao clicar no "X" da janela
			this->window->close();

		if (this->ev.type == sf::Event::KeyPressed){
			//movimento do player
			if (this->state == 2) {

				if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W) {
					player.rotateDirection('u', dt);
				}
				else if (ev.key.code == sf::Keyboard::Right || ev.key.code == sf::Keyboard::D) {
					player.rotateDirection('r', dt);
				}
				else if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S) {
					player.rotateDirection('d', dt);
				}
				else if (ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::A) {
					player.rotateDirection('l', dt);
				}
			}

			//start game
			if (ev.key.code == sf::Keyboard::Enter && (this->state == 0 || this->state == 3)) {
				this->start = !start;
			}

			//pause and unpause
			if (ev.key.code == sf::Keyboard::Escape && (this->state == 2 || this->state == 4)) {
				this->pause = !pause;
			}
		}

	}
}
/*
* setSpawnTimer(): setta o timer de spawn do objeto com base no level
*/

sf::Time Game::setSpawnTimer() {
	if (this->level == 1) 
		return sf::seconds(1.5f);
	else if(this->level > 1 && this->level <=5){
		return sf::seconds(1.f);
	}
	else if (this->level > 5 && this->level <= 15) {
		return sf::seconds(0.6f);
	}
	else if (this->level > 15 && this->level % 5 == 0) {
		return sf::seconds(0.4f);
	}
	else if (this->level > 15 && this->level % 5 != 0) {
		return sf::seconds(0.55f);
	}
}

// updateObjects(): Atualiza as informações dos objetos
void Game::updateObjects(float dt) {
	sf::Time delay = setSpawnTimer(); //delay entre spawns de objetos

	this->increaseTimer(dt, &this->spawnTimer);

	if (this->objects.isEmpty() == false) {

		if (this->inGame == true) this->checkerTimer = (this->LastObjTimer - this->spawnTimer) + delay;

		if (this->spawnTimer.asSeconds() >= delay.asSeconds()) {
			sf::Time test = this->objects.getFirst().getHitTime();
			//std::cout << "Test time: " << test.asSeconds() << "CheckerTime: " << this->checkerTimer.asSeconds() << std::endl;
			if (test.asSeconds() > this->checkerTimer.asSeconds()) {

				this->LastObjTimer = this->objects.getFirst().getHitTime();

				spawnObject();

				this->spawnTimer = sf::seconds(0.f); //restarta timer de spawn de objetos
			}

		}
	}

	if(this->inGame == true){
		//std::cout << "Num elem na lista: " << this->spawnedObjects.getNroElementos() << std::endl;

		if (this->spawnedObjects.getNroElementos() != 0) { //se tiver elementos na lista de spawn, os movimenta
			for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++) {
				//if (this->spawnedObjects.getObjects() != nullptr) 
					this->spawnedObjects.getObjects()->moveObject(dt);
				//else std::cout << "OwO" << std::endl;
			}
		}
		else if(this->objects.isEmpty() == true){
			this->pass = true;
		}
	}
	
}

/*
* updateTimer(float dt, sf::Time *timer): Atualiza o timer desejado
*/
void Game::increaseTimer(float dt, sf::Time *timer) {
	sf::Time increase = sf::seconds(1.f);

	*timer += increase * dt; 
}

void Game::decreaseTimer(float dt, sf::Time* timer) {
	sf::Time decrease = sf::seconds(1.f);

	*timer -= decrease * dt;
}

/*
* testCollision(): Testa colisões entre obstáculos e o jogador
*/
void Game::testCollisions(){

	Object* testObject;
	for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++){

		testObject = this->spawnedObjects.getObjects();

		if(this->player.collidePlayer(testObject->getBody())){ // Colisão com player
			this->player.playHurt();
			this->spawnedObjects.removeObject();
		} 
		else if(this->player.collideShields(testObject->getBody())){ // Colisão com escudos
			this->player.playHitShield();
			this->spawnedObjects.removeObject();
			std::cout << testObject->getSpeed() << std::endl;
			this->score += 100 + (testObject->getSpeed()) / 10;	
		}
	}
}

/*
* spawnObject(): Checa se existem objetos a serem spawnados, e se houver, o coloca na lista de spawn
*/
void Game::spawnObject(){
	Object* object = nullptr;
	if (this->objects.isEmpty() == false){
		object = this->objects.removeObject();
		this->spawnedObjects.newObject(object);
		this->inGame = true;
	}
}

//renderObjects(): Desenha os inimigos na tela
void Game::renderObjects(){
	for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++){
		(this->window)->draw(this->spawnedObjects.getObjects()->getBody());
	}
	
}

//renderScore(): Desenha Pontuação e Vida
void Game::renderScore(){
	tHP.setString("HP: " + std::to_string(this->hp));
	tScore.setString("Score: " + std::to_string(this->score));
	nivel.setString("Level: " + std::to_string(this->level));
	this->window->draw(nivel);
	this->window->draw(tHP);
	this->window->draw(tScore);
	
}

void Game::renderGameOver(){
	this->tFinalScore.setString("Score: " + std::to_string(this->score));
	this->window->draw(tFinalScore);
	this->window->draw(tGameover);
}

void Game::renderPause(){
	timerPause++;
	if(timerPause > 1500){
		piscaPisca = !piscaPisca;
		timerPause = 0;
	}

	if(piscaPisca){
		this->window->draw(tPause);
	}
	
}

void Game::renderInicial(){
	this->window->draw(tInstrucao);
	this->window->draw(tExtra);
}
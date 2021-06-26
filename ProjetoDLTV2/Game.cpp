#include "Game.h"
#include <stdio.h>
#include <String>

//Variáveis globais


// --> Construtor e Inicializadores <--
Game::Game(){
	this->initializeVariables();
	this->initializeWindow();
	
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
		this->initializeObjects();
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
		std::cout << "Game Over" << std::endl;

		this->hp = this->player.getHP();
		//voltando variaveis ao estado inicial
		this->inGame = false;
		this->level = 1;
		this->spawnTimer = sf::seconds(0.f);
		
		//esvaziando lista e fila
		while (this->objects.isEmpty() == false) {
			this->objects.removeObject();
		}
		while (this->spawnedObjects.getNroElementos() != 0) {
			this->spawnedObjects.removeObject();
		}

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
	this->window->clear(sf::Color(19, 22, 28)); //limpa o frame antigo

	//state 0 
	if (this->state == 0){
		//renderiza mainScreen
	}
	
	//state 1
	if (this->state == 1) {
		//renderiza uma tela de loading?
	}

	//state 2
	if (this->state == 2) {

		this->player.renderAll(this->window); //Desenha o Player

		this->renderObjects();

		this->renderScore();

		this->window->display(); //Exibe na tela o desenho realizado no frame
	}

	//state 3
	if (this->state == 3) {
		//renderiza tela de Game over
		this->renderScore();
		this->window->display();
	}

	//state 4
	if (this->state == 4) {
		//renderiza tela de pause
	}

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

	this -> spawnTimer = sf::seconds(0.f);
	this->state = 0; 
	this->level = 1;
	this->pass = false;
	this->inGame = false;

	this->objects.initializeQueue();
	this->spawnedObjects.initializeList();

	if(!this->font.loadFromFile("resources/Fonts/Rubik.ttf")){
		std::cout << "Falha no carregamento da fonte" << std::endl;
	}

	//Colocar numa função depois TODO:
	this->tScore.setFont(this->font);
	this->tHP.setFont(this->font);
	this->tHP.setPosition(this->videoMode.width/10*5,0);
	this->tScore.setPosition(this->videoMode.width/10*5, this->tHP.getCharacterSize()+10);
}

//InitializeWindow(): Inicializa a janela com as especificações necessárias
void Game::initializeWindow(){
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

/*
* *initializeObjects(): Inicializa a fila de objetos a serem gerados e a lista de objetos spawnados
*/
void Game::initializeObjects(){

	int numObjs = this->level * 4;
	if (numObjs > 200) numObjs = 200;

	std::srand(time(0));  //inicializando seed aleatoria

	this->generateQueue(numObjs); //definir regra de geração pra queue (etapa de fase)
}

void Game::initializePlayer(){

	this->player.setPosition(videoMode.width/2, videoMode.height/2);
}

/*
* generateQueue(int size): Gera a fila de objetos de acordo com um parâmetro decidido no inicio de cada fase
*/
void Game::generateQueue(int size){

	for (int i = 0; i < size; i++){
		this->objects.newObject(this->level);
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
			if(ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W){
				player.rotateDirection('u', dt);
			}else if(ev.key.code == sf::Keyboard::Right || ev.key.code == sf::Keyboard::D){
				player.rotateDirection('r', dt);
			}else if(ev.key.code == sf::Keyboard::Down  || ev.key.code == sf::Keyboard::S){
				player.rotateDirection('d', dt);
			}else if(ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::A){
				player.rotateDirection('l', dt);
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
		return sf::seconds(2.f);
	else if(this->level > 1 && this->level <=5){
		return sf::seconds(1.f);
	}
	else if (this->level > 5 && this->level <= 15) {
		return sf::seconds(0.5f);
	}
	else if (this->level > 15) {
		return sf::seconds(0.4f);
	}
}

// updateObjects(): Atualiza as informações dos objetos
void Game::updateObjects(float dt) {
	sf::Time delay = setSpawnTimer(); //delay entre spawns de objetos

	this->updateTimer(dt, &this->spawnTimer);

	if (this->spawnTimer.asSeconds() >= delay.asSeconds()) {
		spawnObject();
		this->spawnTimer = sf::seconds(0.f); //restarta timer de spawn de objetos
	 }

	if(this->inGame == true){
		if (this->spawnedObjects.getNroElementos() != 0) { //se tiver elementos na lista de spawn, os movimenta
			for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++) {
				this->spawnedObjects.getObjects()->moveObject(dt);
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
void Game::updateTimer(float dt, sf::Time *timer) {
	sf::Time increase = sf::seconds(1.f);

	*timer += increase * dt; 
}

/*
* testCollision(): Testa colisões entre obstáculos e o jogador
*/
void Game::testCollisions(){

	sf::Sprite testObject;
	for (int i = 0; i < this->spawnedObjects.getNroElementos(); i++){

		testObject = this->spawnedObjects.getObjects()->getBody();

		if(this->player.collidePlayer(testObject)){ // Colisão com player
			this->spawnedObjects.removeObject();
		} 
		else if(this->player.collideShields(testObject)){ // Colisão com escudos
			this->spawnedObjects.removeObject();
			this->score += 100;
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
	this->window->draw(tHP);
	this->window->draw(tScore);
}


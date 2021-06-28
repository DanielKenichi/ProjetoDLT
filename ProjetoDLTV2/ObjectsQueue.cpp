#include "ObjectsQueue.h"


//**Construtores e Destrutores**
ObjectsQueue::ObjectsQueue(){
	initializeQueue();
}

ObjectsQueue::~ObjectsQueue(){
	std::cout << "Fila destruida" << std::endl;
}

Object ObjectsQueue::getFirst()
{
	return (this->Primeiro)->info;
}


bool ObjectsQueue::isEmpty()
{
	if (NroElementos == 0){
		return true;
	}

	else{
		return false;
	}
	
}


//InitializeQueue(): Inicializa os atributos da Fila de objetos
void ObjectsQueue::initializeQueue(){
	this->Primeiro = nullptr;
	this->Ultimo = nullptr;
	this->NroElementos = 0;
}

/*
* newObject(): Inicializa e insere um novo objeto na fila de objetos (sem prioridade ainda)
*/

void ObjectsQueue::newObject(int level, int w, int h, float dt, int ph, int pw, int key){
	Nodeptr Aux; 

	Aux = new Node;

	Aux->info.initializeObject(level, h, w, dt, ph, pw, key); 

	//Caso 1: Caso a fila esteja vazia
	if (this->NroElementos == 0){
		this->Primeiro = Aux;
		this->Ultimo = Aux;

		Aux->Next = Aux;

		this->NroElementos++;
	}

	//Caso 2: Caso a fila tenha apenas um elemento
	else if (this->NroElementos == 1){
		this->Ultimo = Aux;
		(this->Primeiro)->Next = Aux;

		Aux->Next = this->Primeiro;
		this->NroElementos++;
	}

	//Caso 3: Caso tenha mais de um elemento

	else if (this->NroElementos > 1){
		(this->Ultimo)->Next = Aux;
		this->Ultimo = Aux;

		Aux->Next = this->Primeiro;

		this->NroElementos++;
	}
}
/*
* removeObject(): Remove da fila o objeto para ser transferido para a lista de spawnados
*/
Object* ObjectsQueue::removeObject(){
	Nodeptr Aux; 

	Aux = this->Primeiro;

	//Caso 1: A fila está vazia
	if (this->NroElementos == 0){
		std::cout << "Falha no spawn do objeto (fila vazia)" << std::endl;
	}

	//Caso 2: A fila tem apenas um elemento
	else if (this->NroElementos == 1){
		Aux->Next = nullptr;


		this->Primeiro = nullptr;
		this->Ultimo = nullptr;

		this->NroElementos--;

		return &Aux->info;
	}

	//Caso 3: A fila tem mais de um elemento
	else if (this->NroElementos > 1){
		this->Primeiro = (this->Primeiro)->Next;

		(this->Ultimo)->Next = this->Primeiro;

		Aux->Next = nullptr;

		this->NroElementos--;

		return &Aux->info;
	}
}

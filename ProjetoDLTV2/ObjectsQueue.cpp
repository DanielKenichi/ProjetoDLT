#include "ObjectsQueue.h"


//**Construtores e Destrutores**
ObjectsQueue::ObjectsQueue(int Tamanho)
{
	this->Tamanho = Tamanho;
	InitializeQueue();
}

ObjectsQueue::~ObjectsQueue()
{
}

int ObjectsQueue::getTamanho()
{
	return this->Tamanho;
}

//InitializeQueue(): Inicializa os atributos da Fila de objetos

void ObjectsQueue::InitializeQueue()
{
	this->Primeiro = nullptr;
	this->Ultimo = nullptr;
	this->NroElementos = 0;
}

/*
* newObject(): Inicializa e insere um novo objeto na fila de objetos (sem prioridade ainda)
*/

void ObjectsQueue::newObject()
{
	Nodeptr Aux; 

	Aux = new Node;

	Aux->info.InitializeObject(); 

	//Caso 1: Caso a fila esteja vazia
	if (this->Tamanho == 0)
	{
		this->Primeiro = Aux;
		this->Ultimo = Aux;

		Aux->Dir = Aux;
		Aux->Esq = Aux;

		this->Tamanho++;
	}

	//Caso 2: Caso a fila tenha apenas um elemento
	else if (this->Tamanho == 1)
	{
		this->Ultimo = Aux;
		(this->Primeiro)->Dir = Aux;
		(this->Primeiro)->Esq = Aux;

		Aux->Dir = this->Primeiro;
		Aux->Esq = this->Primeiro;
	}

	//Caso 3: Caso tenha mais de um elemento

	else if (this->Tamanho > 1)
	{
		(this->Ultimo)->Dir = Aux;
		Aux->Esq = this->Ultimo;

		(this->Primeiro)->Esq = Aux;
		Aux->Dir = this->Primeiro;

		this->Ultimo = Aux;
	}
}

Object ObjectsQueue::removeObject()
{
	Nodeptr Aux; 

	Aux = this->Primeiro;

	//Caso 1: A fila está vazia
	if (this->Tamanho == 0)
	{
		std::cout << "Falha no spawn do objeto (fila vazia)" << std::endl;
	}

	//Caso 2: A fila tem apenas um elemento
	else if (this->Tamanho == 1)
	{
		Aux->Dir = nullptr;
		Aux->Esq = nullptr;

		this->Primeiro = nullptr;
		this->Ultimo = nullptr;

		this->Tamanho--;

		return Aux->info;
	}

	//Caso 3: A fila tem mais de um elemento
	else if (this->Tamanho > 1)
	{
		this->Primeiro = (this->Primeiro)->Dir;

		(this->Primeiro)->Esq = this->Ultimo;
		(this->Ultimo)->Dir = this->Primeiro;

		Aux->Dir = nullptr;
		Aux->Esq = nullptr;

		this->Tamanho--;

		return Aux->info;
	}
}

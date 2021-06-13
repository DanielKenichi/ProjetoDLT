#include "ObjectsList.h"

/*Construtor e Destrutor*/
ObjectsList::ObjectsList()
{
	initializeList();
}

ObjectsList::~ObjectsList()
{
}
/**setters**/
void ObjectsList::setAtt()
{
	this->att = this->PL;
}

/**getters**/
int ObjectsList::getNroElementos()
{
	return this->NroElementos;
}

/*
* getObjects(): 
*/
Object* ObjectsList::getObjects() /**feito para lista de um unico elemento, aprimorar para lista com mais de um elemento depois **/
{
	LNodeptr Aux;
	Aux = this->att;

	if (this->PL == NULL)
	{
		std::cout << "Acabou a os objetos da lista" << std::endl;
	}
	else
	{	
		this->att = (this->att)->Next;
		return &Aux->info;
	}	
}

/*
* initializeList(): Inicializa a lista de objetos, indicando quais objetos estão spawnados
*/
void ObjectsList::initializeList()
{
	this->PL = nullptr;
	this->UL = nullptr;
	this->att = nullptr;
	this->NroElementos = 0;
}
/*
* newObject(): Insere um novo objeto na lista para ser spawnado
*/

void ObjectsList::newObject(Object *obj)
{
	{
		LNodeptr Aux;

		Aux = new LNode;

		Aux->info = *obj;

		//Caso 1: Caso a lista esteja vazia
		if (this->NroElementos == 0)
		{
			this->att = Aux;
			this->PL = Aux;
			this->UL = Aux;

			Aux->Next = Aux;

			this->NroElementos++;
		}

		//Caso 2: Caso a lista tenha apenas um elemento
		else if (this->NroElementos == 1)
		{
			this->UL = Aux;
			(this->PL)->Next = Aux;

			Aux->Next = this->PL;
			this->NroElementos++;
		}

		//Caso 3: Caso tenha mais de um elemento

		else if (this->NroElementos > 1)
		{
			(this->UL)->Next = Aux;
			this->UL = Aux;

			Aux->Next = this->PL;

			this->NroElementos++;
		}
	}


}



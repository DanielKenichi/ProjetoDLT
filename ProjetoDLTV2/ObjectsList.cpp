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
Object* ObjectsList::getObjects() 
{
	LNodeptr Aux;
	Aux = this->att; //Identifica o objeto a ser atualizado em um loop

	if (this->PL == NULL)
	{
		std::cout << "Acabou a os objetos da lista" << std::endl;
	}
	else
	{	
		this->att = (this->att)->Next;
		return &(Aux->Next)->info;
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
			this->att = UL;

			this->NroElementos++;
		}

		//Caso 3: Caso tenha mais de um elemento

		else if (this->NroElementos > 1)
		{
			(this->UL)->Next = Aux;
			this->UL = Aux;

			Aux->Next = this->PL;

			this->att = UL;

			this->NroElementos++;
		}
	}


}

void ObjectsList::removeObject()
{
	//caso 0: lista vazia
	if (this->NroElementos == 0)
	{
		std::cout << "Não há objetos a serem removidos" << std::endl;
	}

	//caso 1: a lista tem apenas um elemento
	else if (this->NroElementos == 1)
	{
		(this->PL)->Next = nullptr;

		delete this->PL;

		this->PL = nullptr;
		this->UL = nullptr;
		this->att = nullptr;

		this->NroElementos--;
	}

	//caso 2: a lista tem mais de um elemento...
	else if (this->NroElementos > 1)
	{
		LNodeptr anterior = this->PL;
		//caso 2.1 ...e o elemento a ser removido esteja no começo da lista
		if (this->att == this->PL)
		{
			this->PL = (this->PL)->Next;
			(this->UL)->Next = this->PL;
			(this->att)->Next = nullptr;

			delete this->att;

			this->att = this->PL;
			this->NroElementos--;
		}

		//caso 2.2 ... e o elemento a ser removido esteja no meio da lista
		else
		{
			while (anterior->Next != this->att)
			{
				anterior = anterior->Next;
			}

			anterior->Next = (this->att)->Next;
			(this->att)->Next = nullptr;

			delete this->att;

			this->att = anterior->Next;
			this->NroElementos--;
		}

	}

}



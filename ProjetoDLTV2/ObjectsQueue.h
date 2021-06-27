#ifndef OBJECTSQUEUE_H
#define OBJECTSQUEUE_H

/*
* Fila de objetos atirados na direção do jogador
*/

//**bibliotecas e includes**
#include "Object.h"



//**structs**
struct Node{
    Object info;
    struct Node* Next;
};

typedef struct Node* Nodeptr;

//**Classe FilaObjetos**
class ObjectsQueue {

public:
    //**Construtor e destrutor**
    ObjectsQueue();
    ~ObjectsQueue();

    //**getters** 


    //**Métodos primitivos**
     bool isEmpty();
     void initializeQueue();
     void newObject(int level, int h, int w);
     Object* removeObject();



private:
    //**Atributos da Fila**

    Nodeptr Primeiro;
    Nodeptr Ultimo;

    int NroElementos;


};

#endif //OBJECTSQUEUE_H


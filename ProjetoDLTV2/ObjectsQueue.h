#ifndef OBJECTSQUEUE_H
#define OBJECTSQUEUE_H

/*
* Fila de objetos atirados na dire��o do jogador
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
    Object getFirst();

    //**M�todos primitivos**
     bool isEmpty();
     void initializeQueue();
     void newObject(int level, int h, int w, float dt, int ph, int pw, int key);
     Object* removeObject();



private:
    //**Atributos da Fila**

    Nodeptr Primeiro;
    Nodeptr Ultimo;

    int NroElementos;


};

#endif //OBJECTSQUEUE_H


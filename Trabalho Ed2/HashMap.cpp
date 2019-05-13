#include <iostream>
#include "HashMap.h"

HashMap::HashMap(int capacidade)
{
    this->capacidade = capacidade;
    tamanho = 0;
    vetor = new HashNode*[capacidade];
    for(int i = 0; i < capacidade; i++){
        vetor[i] = NULL;
    }
    dummy = new HashNode(-1, -1);
}

HashMap::~HashMap()
{
    //dtor
}


int HashMap::FuncaoHash(int key){
    return key % capacidade;
}

void HashMap::Insert(int userId, int movieId){
    HashNode *novo = new HashNode(userId, movieId);
    int index = FuncaoHash(userId);
    while(vetor[index] != NULL && (vetor[index]->getUserid() != userId && vetor[index]->getMovieId() != movieId)){
        index++;
        index = index % capacidade;
    }
    if(vetor[index] == NULL){
        tamanho++;
    }
    vetor[index] = novo;
}


void HashMap::Remove(int userId, int movieId){
    int index = FuncaoHash(userId);
    while(vetor[index] != NULL){
        if(vetor[index]->getUserid() == userId && vetor[index]->getMovieId() == movieId){
            vetor[index] = dummy;
            tamanho--;
            return;
            //Achou
        }
    }
    //Não achou
    return;
}






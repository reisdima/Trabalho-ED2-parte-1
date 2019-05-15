#include <iostream>
#include "HashNode.h"

HashNode::HashNode(int userId, int movieId)
{
    this->userId= userId;
    this->movieId= movieId;
    prox = NULL;
    anterior = NULL;
    proximaChave = -1;
}

HashNode::~HashNode()
{
    //dtor
}




int HashNode::getUserid(){
    return userId;
}

int HashNode::getMovieId(){
    return movieId;
}

void HashNode::setUserId(int userId) {
    this->userId = userId;
}

void HashNode::setMovieId(int movieId) {
    this->movieId = movieId;
}


void HashNode::setProx(HashNode *prox){
    this->prox = prox;
}

HashNode* HashNode::getProx(){
    return this->prox;
}

void HashNode::setAnt(HashNode *anterior){
    this->anterior = anterior;
}

HashNode* HashNode::getAnt(){
    return this->anterior;
}

void HashNode::setProximaChave(int key){
    this->proximaChave = key;
}

int HashNode::getProximaChave(){
    return this->proximaChave;
}

#include <iostream>
#include "HashNode.h"

HashNode::HashNode(int userId, int movieId)
{
    this->userId= userId;
    this->movieId= movieId;
    prox = NULL;
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

void HashNode::setUserId(int valor) {
    this->userId = userId;
}

void HashNode::setMovieId(int valor) {
    this->movieId = movieId;
}

#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashNode.h"


class HashMap
{
public:
    HashMap(int tamanho);
    ~HashMap();

    void Insert(int userId, int movieId);
    void Remove(int userId, int movieId);

private:
    HashNode **vetor;
    HashNode *dummy;
    int tamanho;
    int capacidade;

    int FuncaoHash(int key);

};

#endif // HASHMAP_H

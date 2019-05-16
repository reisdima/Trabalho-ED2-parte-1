#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashNode.h"


class HashMap
{
public:


    HashMap(int capacidade);
    ~HashMap();

    void InsertSondagemLinear(int userId, int movieId);
    void RemoveSondagemLinear(int userId, int movieId);
    void SearchSondagemLinear(int userId, int movieId);

    void InsertSondagemQuadratica(int userId, int movieId);
    void RemoveSondagemQuadratica(int userId, int movieId);
    void SearchSondagemQuadratica(int userId, int movieId);

    void InsertDuploHash(int userId, int movieId);
    void RemoveDuploHash(int userId, int movieId);
    void SearchDuploHash(int userId, int movieId);

    void InsertEncadeamentoSeparado(int userId, int movieId);
    void RemoveEncadeamentoSeparado(int userId, int movieId);
    void SearchEncadeamentoSeparado(int userId, int movieId);

    void InsertEncadeamentoCoalescido(int userId, int movieId);
    void RemoveEncadeamentoCoalescido(int userId, int movieId);
    void SearchEncadeamentoCoalescido(int userId, int movieId);

    void Print();
    void PrintEncadeamentoSeparado();
    void PrintEncadeamentoCoalescido();

private:
    int contadorComparacao;
    int contadorTrocaDeDados;
    HashNode **vetor;
    HashNode *dummy;
    int tamanho;
    int capacidade;

    int FuncaoHashSondagemLinear(int key, int k);
    int FuncaoHashSondagemQuadratica(int key, int k);
    int FuncaoHashDuploHash(int key, int k);
    int FuncaoHashDuploHash2(int key);
    int FuncaoHashEncadeamentoSeparado(int key);
    int FuncaoHashEncadeamentoCoalescido(int key);

    int EncontrarProximaPosicao();

};

#endif // HASHMAP_H

#include <iostream>
#include <stdlib.h>
#include "HashMap.h"
using namespace std;

HashMap::HashMap(int capacidade)
{
    if(capacidade == 100){
        this->capacidade = 107;
    }
    if(capacidade == 1000){
        this->capacidade = 1009;
    }
    if(capacidade == 5000){
        this->capacidade = 5003;
    }
    if(capacidade == 10000){
        this->capacidade = 10007;
    }
    if(capacidade == 50000){
        this->capacidade = 50021;
    }
    if(capacidade == 100000){
        this->capacidade = 100003;
    }
    if(capacidade == 500000){
        this->capacidade = 500009;
    }
    if(capacidade == 1000000){
        this->capacidade = 1000003;
    }
    tamanho = 0;
    vetor = new HashNode*[this->capacidade];
    for(int i = 0; i < this->capacidade; i++){
        vetor[i] = NULL;
    }
    dummy = new HashNode(-1, -1);
    contadorComparacao = 0;
    contadorTrocaDeDados = 0;
}

HashMap::~HashMap()
{
    //dtor
}


int HashMap::FuncaoHashSondagemLinear(int key, int k){
    return (key+k) % capacidade;
}

void HashMap::InsertSondagemLinear(int userId, int movieId){
    int k = 0;
    int index = FuncaoHashSondagemLinear(userId, k);
    HashNode *novo = new HashNode(userId, movieId);
    //cout << "Teste" << endl;
    while(vetor[index] != NULL && (vetor[index]->getUserid() != userId || vetor[index]->getMovieId() != movieId)){
        k++;
        //cout << "Index: " << index << " -> ";
        index = FuncaoHashSondagemLinear(userId, k);
        //cout << index << endl;
    }
    if(vetor[index] == NULL){
        tamanho++;
    }

    vetor[index] = novo;
}

void HashMap::RemoveSondagemLinear(int userId, int movieId){
    int k = 0;
    int index = FuncaoHashSondagemLinear(userId, k);
    while(vetor[index] != NULL){
        if(vetor[index]->getUserid() == userId && vetor[index]->getMovieId() == movieId){
            vetor[index] = NULL;
            tamanho--;
            return;
            //Achou
        }
        k++;
        index = FuncaoHashSondagemLinear(userId, k);
    }
    //Não achou
    return;
}

void HashMap::SearchSondagemLinear(int userId, int movieId){
    int k = 0;
    int hashIndex = FuncaoHashSondagemLinear(userId, k);
    int contador = 0;
    while(vetor[hashIndex] != NULL){
        contador++;
        if(contador > capacidade){
            cout << "Nao encontrou" << endl;
            return;
        }
        if(vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            cout << "UserId: " << vetor[hashIndex]->getUserid() << "  MovieId: " << vetor[hashIndex]->getMovieId() << endl;
            return;
        }
        k++;
        hashIndex = FuncaoHashSondagemLinear(userId, k);
    }
    cout << "Nao encontrou 2" << endl;
}

void HashMap::Print(){
    for(int i = 0; i < capacidade; i++){
        if(vetor[i] != NULL){
            cout << i << ": " << vetor[i]->getUserid() << "  " << vetor[i]->getMovieId() << endl;
        }
        else{
            cout << i << " eh nulo" << endl;
        }
    }
}


int HashMap::FuncaoHashSondagemQuadratica(int key, int k){
    return (key + (k*k)) % capacidade;
}

void HashMap::InsertSondagemQuadratica(int userId, int movieId){
    int k = 0;
    HashNode *novo = new HashNode(userId, movieId);
    int index = FuncaoHashSondagemQuadratica(userId, k);
    while(vetor[index] != NULL && (vetor[index]->getUserid() != userId || vetor[index]->getMovieId() != movieId)){
        //cout << index << " -> ";
        k++;
        index = FuncaoHashSondagemQuadratica(userId, k);
        //cout << index << endl;
    }
    if(vetor[index] == NULL){
        tamanho++;
    }
    vetor[index] = novo;
}



void HashMap::RemoveSondagemQuadratica(int userId, int movieId){
    int k = 0;
    int hashIndex = FuncaoHashSondagemQuadratica(userId, k);
    while(vetor[hashIndex] != NULL){
        if(vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            vetor[hashIndex] = dummy;
            tamanho--;
            return;
            //Achou
        }
        k++;
        hashIndex = FuncaoHashSondagemQuadratica(userId, k);
    }
    //Não achou
    return;
}

void HashMap::SearchSondagemQuadratica(int userId, int movieId){
    int k = 0;
    int hashIndex = FuncaoHashSondagemQuadratica(userId, k);
    int contador = 0;
    while(vetor[hashIndex] != NULL){
        contador++;
        if(contador > capacidade){
            cout << "Nao encontrou" << endl;
            return;
        }
        if(vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            cout << "UserId: " << vetor[hashIndex]->getUserid() << "  MovieId: " << vetor[hashIndex]->getMovieId() << endl;
            return;
        }
        k++;
        hashIndex = FuncaoHashSondagemQuadratica(userId, k);
    }
    cout << "Nao encontrou 2" << endl;
}

int HashMap::FuncaoHashDuploHash2(int key){
    return 3 - (key % 3);
}

int HashMap::FuncaoHashDuploHash(int key, int k){
    return (key + k*FuncaoHashDuploHash2(key)) % capacidade;
}




void HashMap::InsertDuploHash(int userId, int movieId){
    int k = 0;
    HashNode *novo = new HashNode(userId, movieId);
    int index = FuncaoHashDuploHash(userId, k);
    while(vetor[index] != NULL && (vetor[index]->getUserid() != userId || vetor[index]->getMovieId() != movieId)){
        k++;
        index = FuncaoHashDuploHash(userId, k);
    }
    if(vetor[index] == NULL){
        tamanho++;
    }
    vetor[index] = novo;
}


void HashMap::RemoveDuploHash(int userId, int movieId){
    int k = 0;
    int hashIndex = FuncaoHashDuploHash(userId, k);
    while(vetor[hashIndex] != NULL){
        if(vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            vetor[hashIndex] = dummy;
            tamanho--;
            return;
            //Achou
        }
        k++;
        hashIndex = FuncaoHashDuploHash(userId, k);
    }
    //Não achou
    return;
}

void HashMap::SearchDuploHash(int userId, int movieId){
    int k = 0;
    int hashIndex = FuncaoHashDuploHash(userId, k);
    int contador = 0;
    while(vetor[hashIndex] != NULL){
        contador++;
        if(contador > capacidade){
            cout << "Nao encontrou" << endl;
            return;
        }
        if(vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            cout << "index: " << hashIndex << " UserId: " << vetor[hashIndex]->getUserid() << "  MovieId: " << vetor[hashIndex]->getMovieId() << endl;
            return;
        }
        k++;
        hashIndex = FuncaoHashDuploHash(userId, k);
    }
    cout << "Nao encontrou 2" << endl;
}



int HashMap::FuncaoHashEncadeamentoSeparado(int key){
    return key % capacidade;
}

void HashMap::InsertEncadeamentoSeparado(int userId, int movieId){
    HashNode *novo = new HashNode(userId, movieId);
    int hashIndex = FuncaoHashEncadeamentoSeparado(userId);
    HashNode *aux = vetor[hashIndex];
    if(aux != NULL){
        while(aux->getProx() != NULL && (aux->getUserid() != userId || aux->getMovieId() != movieId)){
            aux = aux->getProx();
        }
        if(aux->getProx() == NULL){
            aux->setProx(novo);
            novo->setAnt(aux);
            tamanho++;
        }
        else{
            novo->setProx(aux->getProx());
            HashNode *deletar = aux;
            aux = aux->getAnt();
            aux->setProx(novo);
            delete deletar;
        }
    }
    else{
        vetor[hashIndex] = novo;
        tamanho++;
    }
}

void HashMap::RemoveEncadeamentoSeparado(int userId, int movieId){
    int hashIndex = FuncaoHashEncadeamentoSeparado(userId);
    HashNode *aux = vetor[hashIndex];
    if(aux != NULL){
        while(aux != NULL){
            if(aux->getUserid() == userId && aux->getMovieId() == movieId){
                HashNode *anterior = aux->getAnt();
                HashNode *proximo = aux->getProx();
                if(anterior != NULL){
                    anterior->setProx(proximo);
                }
                else{
                    vetor[hashIndex] = proximo;
                }
                if(proximo != NULL){
                    proximo->setAnt(anterior);
                }
                delete aux;
                tamanho--;
                return;
                //Achou
            }
            aux = aux->getProx();
        }
        if(aux == NULL){
            //Nao achou
            return;
        }
    }
    //Não achou
    return;
}

void HashMap::SearchEncadeamentoSeparado(int userId, int movieId){
    int hashIndex = FuncaoHashEncadeamentoSeparado(userId);
    HashNode *aux = vetor[hashIndex];
    while(aux != NULL){
        if(aux->getUserid() == userId && aux->getMovieId() == movieId){
            cout << "index: " << hashIndex << " UserId: " << aux->getUserid() << "  MovieId: " << aux->getMovieId() << endl;
            return;
        }
        aux = aux->getProx();
    }
    if(aux == NULL){
        cout << "Nao encontrou 2" << endl;
        return;
    }

}

void HashMap::PrintEncadeamentoSeparado(){
    for(int i = 0; i < capacidade; i++){
        HashNode *aux = vetor[i];
        cout << i << " : ";
        while(aux != NULL){
            cout << aux->getUserid() << ", " << aux->getMovieId() << " -> ";
            aux = aux->getProx();
        }
        cout << "||" << endl;
    }
}



int HashMap::FuncaoHashEncadeamentoCoalescido(int key){
    return key % capacidade;
}

int HashMap::EncontrarProximaPosicao(){
    for(int i = capacidade-1; i >= 0; i--){
        if(vetor[i] == NULL || vetor[i]->getUserid() == -1){
            return i;
        }
    }
    cout << "Retornou -1" << endl;
    return -1;
}

void HashMap::InsertEncadeamentoCoalescido(int userId, int movieId){
    //cout << "Inserindo " << userId << "  " << movieId << endl;
    HashNode *novo = new HashNode(userId, movieId);
    int hashIndex = FuncaoHashEncadeamentoCoalescido(userId);
    while(vetor[hashIndex] != NULL && vetor[hashIndex]->getUserid() != -1 &&( (vetor[hashIndex]->getUserid() != userId && vetor[hashIndex]->getMovieId() == movieId) ||
                                                                                (vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() != movieId) ||
                                                                                (vetor[hashIndex]->getUserid() != userId && vetor[hashIndex]->getMovieId() != movieId))){


    //int vetor1[10] = {16, 11, 11, 9, 11, 12, 16, 2, 15, 11};
    //int vetor2[10] = {1129, 1265, 165, 5349,1265, 800, 1080, 377, 55765, 63853};
        //cout << vetor[hashIndex]->getUserid() << " " << vetor[hashIndex]->getMovieId() << "  ";
        //cout << vetor[hashIndex]->getProximaChave() << " , Foi para: ";
        if(vetor[hashIndex]->getProximaChave() == -1){

            vetor[hashIndex]->setProximaChave(EncontrarProximaPosicao());
            //cout << vetor[hashIndex]->getProximaChave() << " " ;
        }
        hashIndex = vetor[hashIndex]->getProximaChave();
        //cout << hashIndex << endl;
    }
    if(vetor[hashIndex] == NULL || vetor[hashIndex]->getUserid() == -1){
        tamanho++;
    }
    else{
        novo->setProximaChave(vetor[hashIndex]->getProximaChave());
    }
    vetor[hashIndex] = novo;
}




void HashMap::RemoveEncadeamentoCoalescido(int userId, int movieId){
    int hashIndex = FuncaoHashEncadeamentoCoalescido(userId);
    while(vetor[hashIndex] != NULL){
        if(vetor[hashIndex]->getUserid() != -1 && vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            //cout << "A " << hashIndex << endl;
            //int prox = vetor[hashIndex]->getProximaChave();
            vetor[hashIndex]->setUserId(-1);
            vetor[hashIndex]->setMovieId(-1);
            cout << vetor[hashIndex]->getUserid() << "  " << vetor[hashIndex]->getMovieId() << endl;
            tamanho--;
            return;
            //Achou
        }
        hashIndex = vetor[hashIndex]->getProximaChave();
    }
    //Não achou
    return;
}

void HashMap::SearchEncadeamentoCoalescido(int userId, int movieId){
    int hashIndex = FuncaoHashEncadeamentoCoalescido(userId);
    while(vetor[hashIndex] != NULL){

        if(vetor[hashIndex]->getUserid() != -1 && vetor[hashIndex]->getUserid() == userId && vetor[hashIndex]->getMovieId() == movieId){
            //Achou
            cout << "Index: " << hashIndex << " UserId: " << vetor[hashIndex]->getUserid() << " MovieId: " << vetor[hashIndex]->getMovieId() << endl;
            return;
        }
        hashIndex = vetor[hashIndex]->getProximaChave();
        //cout << hashIndex << " ";
    }
    cout << "Nao achou" << endl;
    return;
}



void HashMap::PrintEncadeamentoCoalescido(){
    for(int i = 0; i < capacidade; i++){
        if(vetor[i] != NULL){
            cout << i << ": " << vetor[i]->getUserid() << "  " << vetor[i]->getMovieId() <<  "  " << vetor[i]->getProximaChave() <<endl;
        }
        else{
            cout << i << " eh nulo" << endl;
        }
    }
}

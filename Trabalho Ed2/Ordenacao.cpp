#include <iostream>
#include "Ordenacao.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

int Ordenacao::contadorComparacao = 0;
int Ordenacao::contadorTrocaDeDados = 0;

Ordenacao::Ordenacao()
{

}

Ordenacao::~Ordenacao()
{
    //dtor
}

void Ordenacao::zerarContadores(){
    contadorComparacao = 0;
    contadorTrocaDeDados = 0;
}

long long Ordenacao::getContadorComparacao(){
    return contadorComparacao;
}

long long Ordenacao::getContadorTrocaDados(){
    return contadorTrocaDeDados;
}

void Ordenacao::Troca(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
	contadorTrocaDeDados++;
}

int Ordenacao::Particiona(int *vet, int left, int right, float pivot) {
	int leftPtr = left - 1;
	int rightPtr = right;

	for(int j = left; j < right; j++){
        contadorComparacao++;

        if(vet[j] <= pivot){
            leftPtr++;
            Troca(vet, leftPtr, j);
        }
        contadorComparacao++;
	}
	Troca(vet, leftPtr+1, right);
	return (leftPtr + 1);
}



void Ordenacao::QuickSort(int *vet, int left, int right){
    contadorComparacao++;
    if(left >= right)
        return;
    else{
        int pivo = vet[right];
        int particao = Particiona(vet, left, right,pivo);

        QuickSort(vet, left, particao-1);
        QuickSort(vet, particao, right);
    }
}


void Ordenacao::ManualSort(int *vet, int left, int right){
    int tamanho = right - left + 1;
    contadorComparacao++;
    if(tamanho <= 1)
        return;
    contadorComparacao++;
    if(tamanho == 2){
        contadorComparacao++;
        if(vet[right] < vet[left])
            Troca(vet, left, right);
        return;
    }
    else{
        contadorComparacao++;
        if(vet[2] < vet[0]){
        Troca(vet, 2, 0);
        }
        contadorComparacao++;
        if(vet[2] < vet[1]){
            Troca(vet, 2, 1);
        }
        contadorComparacao++;
        if(vet[1] < vet[0]){
            Troca(vet, 1, 0);
        }
    }
}



void Ordenacao::Merge(int *vetor, int esq, int meio, int dir){
    int i, j, k;
    int n1 = meio-esq+1;
    int n2 = dir-meio;

    int esquerda[n1], direita[n2];

    contadorComparacao++;
    for(int i = 0; i < n1; i++){
        esquerda[i] = vetor[esq+i];
        contadorTrocaDeDados++;
        contadorComparacao++;
    }

    contadorComparacao++;
    for(j=0; j < n2; j++){
        direita[j] = vetor[meio+1+j];
        contadorTrocaDeDados++;
        contadorComparacao++;
    }

    i = 0;
    j = 0;
    k = esq;
    contadorComparacao++;
    contadorComparacao++;
    while(i < n1 && j < n2){
        contadorComparacao++;
        if(esquerda[i] <= direita[j]){
            vetor[k] = esquerda[i];
            contadorTrocaDeDados++;
            i++;
        }
        else{
            vetor[k] = direita[j];
            contadorTrocaDeDados++;
            j++;
        }
        k++;
        contadorComparacao++;
        contadorComparacao++;
    }
    contadorComparacao++;
    while(i < n1){
        vetor[k] = esquerda[i];
        contadorTrocaDeDados++;
        i++;
        k++;
        contadorComparacao++;
    }
    contadorComparacao++;
    while(j<n2){
        vetor[k] = direita[j];
        contadorTrocaDeDados++;
        j++;
        k++;
        contadorComparacao++;
    }
}



void Ordenacao::MergeSort(int *vet, int esq, int dir){
    contadorComparacao++;
    if(esq < dir){
        int meio = esq + (dir - esq) / 2;
        MergeSort(vet, esq, meio);
        MergeSort(vet, meio + 1, dir);
        Merge(vet, esq, meio, dir);
    }

}




//Função GetDist utilizada na CombSort
int Ordenacao::GetDist(int dist){
    dist = (dist*10)/13;
    contadorComparacao++;
    if(dist<1){
        return 1;
    }
    return dist;
}

//Função CombSort
void Ordenacao::CombSort(int *vetor, int n){
    int dist = n;
    bool troca = true;
    contadorComparacao++;
    contadorComparacao++;
    while(dist != 1 || troca == true){
        dist = GetDist(dist);
        troca = false;
        contadorComparacao++;
        for(int i=0 ; i < n-dist; i++){
            if(vetor[i]>vetor[i+dist]){
                Troca(vetor, i, i+dist);
                troca = true;
            }
            contadorComparacao++;
        }
        contadorComparacao++;
        contadorComparacao++;
    }
}


//Heapify utilizada na HeapSort
void Ordenacao::Heapify(int *vetor, int n, int i){
    int maior = i;
    int esq = 2*i+1;
    int dir = 2*i+2;
    contadorComparacao++;
    contadorComparacao++;
    if(esq < n && vetor[esq] > vetor[maior]){
        maior = esq;
    }

    contadorComparacao++;
    contadorComparacao++;
    if(dir < n && vetor[dir] > vetor[maior]){
        maior = dir;
    }
    contadorComparacao++;
    if(maior != i){
        Troca(vetor, i, maior);
        Heapify(vetor, n, maior);
    }
}


void Ordenacao::HeapSort(int *vetor, int n){
    contadorComparacao++;
    for(int i = n / 2-1; i >= 0; i--){
        Heapify(vetor, n, i);
        contadorComparacao++;
    }
    contadorComparacao++;
    for(int i=n-1;i>=0;i--){
        Troca(vetor, 0, i);
        Heapify(vetor, i, 0);
        contadorComparacao++;
    }
}


void Ordenacao::QuickSort(Registro **vet, int left, int right){
    contadorComparacao++;
    if(left >= right)
        return;
    else{
        //cout << vet[right]->getUserId() << endl;
        int pivo = vet[right]->getUserId();
        int particao = Particiona(vet, left, right, pivo);

        QuickSort(vet, left, particao-1);
        QuickSort(vet, particao, right);
    }
}

int Ordenacao::Particiona(Registro **vet, int left, int right, int pivot){
    int leftPtr = left - 1;
	int rightPtr = right;
	for(int j = left; j < right; j++){
        contadorComparacao++;
        if(vet[j]->getUserId() <= pivot){
            leftPtr++;
            Troca(vet, leftPtr, j);
        }
        contadorComparacao++;
	}
	Troca(vet, leftPtr+1, right);
	return (leftPtr + 1);
}

void Ordenacao::Troca(Registro **vet, int i, int j){
    //cout << vet[i]->getUserId() << "  " << i << "  " << j << " " << vet[j]->getUserId() << endl;
    Registro *aux = vet[j];
    vet[j] = vet[i];
    vet[i] = aux;
    contadorTrocaDeDados++;
    //cout << vet[i]->getUserId() << "  " << i << "  " << j << " " << vet[j]->getUserId() << endl;
}

void Ordenacao::PrintVetor(int vetor[], int n){
    for (int i=0; i<n; ++i){
        cout << vetor[i] << " ";
        contadorComparacao++;
    }
    cout << "\n";
}



void Ordenacao::InsertionSort(int *vet, int n){
    for(int i = 1; i < n; i++){
        int pivo = vet[i];
        contadorTrocaDeDados ++;
        int j = i - 1;
        while(j >= 0 && vet[j] > pivo){
            vet[j+1] = vet[j];
            j--;
            contadorTrocaDeDados ++;
            contadorComparacao = contadorComparacao + 2;
        }
        vet[j+1] = pivo;
        contadorTrocaDeDados ++;
        contadorComparacao++;
    }
}

void Ordenacao::QuickSortInsertion(int *vet, int left, int right){
    int tamanho = right - left + 1;
    contadorComparacao++;
    if(tamanho <= 10){
        InsertionSort(vet, tamanho);
        return;
    }
    int pivo = vet[right];
    int particao = Particao(vet, left, right, pivo);
    QuickSortInsertion(vet, left, particao-1);
    QuickSortInsertion(vet, particao, right);

}

//Função para particionar o vetor e encontrar o pivo
int Ordenacao::Particao(int *vet, int left, int right, float pivot) {
	int leftPtr = left - 1;
	int rightPtr = right;
	for(int j = left; j < right; j++){
        contadorComparacao++;
        if(vet[j] <= pivot){
            leftPtr++;
            Troca(vet, leftPtr, j);
        }
        contadorComparacao++;
	}
	Troca(vet, leftPtr+1, right);
	return (leftPtr + 1);
}

int Ordenacao::Mediana(int *vet, int left, int right, int k, int N){
    /*
    int mid = (right+left)/2;
    if(vet[mid] < vet[left]){
        Troca(vet, mid, left);
    }
    if(vet[right] < vet[left]){
        Troca(vet, right, left);
    }
    if(vet[right] < vet[mid]){
        Troca(vet, right, mid);
    }
    Troca(vet, mid, right-1);*/

    int *random = new int(k);

    for(int i = 0; i < k; i++){
        random[i] = rand()%N;
        contadorComparacao++;
    }
    cout << "Valores random: " << endl;
    for(int i = 0; i < k; i++){
        cout << random[i] << "  ";
        contadorComparacao++;
    }
    cout << endl << endl;
    cout << "Valor do vetor: " << endl;
    for(int i = 0; i < k; i++){
        cout << vet[random[i]] << "  ";
        contadorComparacao++;
    }
    cout << endl << endl;
    QuickSort(random, 0, k-1);

    for(int i = 0; i < k-1; i++){
        for(int j = i+1; j < k; j++){
            contadorComparacao++;
            if(vet[random[i]] > vet[random[j]]){
                cout << "Trocou" << endl;
                Troca(vet, random[i], random[j]);
            }
            contadorComparacao++;
        }
        contadorComparacao++;
    }
    cout << "Valor do vetor: " << endl;
    for(int i = 0; i < k; i++){
        cout << vet[random[i]] << "  ";
        contadorComparacao++;
    }
    cout << endl << endl;
    cout << "Valor do random: " << endl;
    for(int i = 0; i < k; i++){
        cout << random[i] << "  ";
        contadorComparacao++;
    }
    cout << endl << endl;
    Troca(vet, random[k-2], N-1);
    for(int i =0; i < N; i++){
        cout << vet[i] << "  ";
        contadorComparacao++;
    }
    cout << endl;
    return vet[N-1];

    /*int *random =  new int[k];
    for(int i = 0; i < k; i++){
        random[i] = rand()%tamanho;
    }
    ManualSort(random);
    if(vet[random[2]] < vet[random[0]]){
        Troca(vet, random[2], random[0]);
    }
    if(vet[random[2]] < vet[random[1]]){
        Troca(vet, random[2], random[1]);
    }
    if(vet[random[1]] < vet[random[0]]){
        Troca(vet, random[1], random[0]);
    }
    return random[2];*int *vetorTeste = new int(N);
    for(int i = 0; i< N; i++){

    }*/
}

void Ordenacao::QuickSortMediana(int *vet, int left, int right, int k, int n){
    int tamanho = right - left + 1;
    contadorComparacao++;
    if(tamanho <= 3)
        ManualSort(vet, left, right);
    else{

         int mediana = Mediana(vet, left, right, k, n);
        int particao = Particao(vet, left, right, mediana);

        QuickSortMediana(vet, left, particao-1, k,n);
        QuickSortMediana(vet, particao, right, k,n);
    }
}

void Ordenacao::imprimeContadores(){
    cout<<endl<<"ContadorComparacao: " << contadorComparacao << endl << "ContadorTrocaDeDados: " << contadorTrocaDeDados << endl;
}


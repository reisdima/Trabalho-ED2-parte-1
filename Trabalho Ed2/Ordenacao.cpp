#include <iostream>
#include "Ordenacao.h"

using namespace std;

Ordenacao::Ordenacao()
{
    //ctor
}

Ordenacao::~Ordenacao()
{
    //dtor
}


void Ordenacao::Troca(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

int Ordenacao::Particiona(int *vet, int left, int right, float pivot) {
	int leftPtr = left - 1;
	int rightPtr = right;
	for(int j = left; j < right; j++){
        if(vet[j] <= pivot){
            leftPtr++;
            Troca(vet, leftPtr, j);
        }
	}
	Troca(vet, leftPtr+1, right);
	return (leftPtr + 1);
}



void Ordenacao::QuickSort(int *vet, int left, int right){
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
    if(tamanho <= 1)
        return;

    if(tamanho == 2){
        if(vet[right] < vet[left])
            Troca(vet, left, right);
        return;
    }
    else{
        if(vet[2] < vet[0]){
        Troca(vet, 2, 0);
        }
        if(vet[2] < vet[1]){
            Troca(vet, 2, 1);
        }
        if(vet[1] < vet[0]){
            Troca(vet, 1, 0);
        }
    }
}



void Ordenacao::Merge(int *vetor, int esq, int meio, int dir){
    int i,j,k;
    int n1=meio-esq+1;
    int n2=dir-meio;

    int esquerda[n1], direita[n2];

    for(int i=0;i<n1;i++){
        esquerda[i]=vetor[esq+i];
    }
    for(j=0;j<n2;j++){
        direita[j]=vetor[meio+1+j];
    }
    i=0;j=0;k=esq;
    while(i<n1&&j<n2){
        if(esquerda[i]<=direita[j]){
            vetor[k]=esquerda[i];
            i++;
        }
        else{
            vetor[k]=direita[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        vetor[k]=esquerda[i];
        i++;
        k++;
    }
    while(j<n2){
        vetor[k]=direita[j];
        j++;
        k++;
    }
}



void Ordenacao::MergeSort(int *vet, int esq, int dir){
    if(esq<dir){
        int meio=esq+(dir-esq)/2;
        MergeSort(vet,esq,meio);
        MergeSort(vet,meio+1,dir);
        Merge(vet,esq,meio,dir);
    }

}




//Função GetDist utilizada na CombSort
int Ordenacao::GetDist(int dist){
    dist=(dist*10)/13;
    if(dist<1){
        return 1;
    }
    return dist;
}

//Função CombSort
void Ordenacao::CombSort(int *vetor, int n){
    int dist=n;
    bool troca=true;
    while(dist!=1||troca==true){
        dist = GetDist(dist);
        troca = false;
        for(int i=0;i<n-dist;i++){
            if(vetor[i]>vetor[i+dist]){
                Troca(vetor, i, i+dist);
                troca=true;
            }
        }
    }
}


//Heapify utilizada na HeapSort
void Ordenacao::Heapify(int *vetor, int n, int i){
    int maior=i;
    int esq=2*i+1;
    int dir=2*i+2;

    if(esq<n && vetor[esq]>vetor[maior]){
        maior=esq;
    }
    if(dir<n&&vetor[dir]>vetor[maior]){
        maior=dir;
    }
    if(maior!=i){
        Troca(vetor, i, maior);
        Heapify(vetor,n,maior);
    }
}


void Ordenacao::HeapSort(int *vetor, int n){
    for(int i=n/2-1; i>=0;i--){
        Heapify(vetor,n,i);
    }
    for(int i=n-1;i>=0;i--){
        Troca(vetor, 0, i);
        Heapify(vetor,i,0);
    }
}


void Ordenacao::QuickSort(Registro **vet, int left, int right){
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
        if(vet[j]->getUserId() <= pivot){
            leftPtr++;
            Troca(vet, leftPtr, j);
        }
	}
	Troca(vet, leftPtr+1, right);
	return (leftPtr + 1);
}

void Ordenacao::Troca(Registro **vet, int i, int j){
    //cout << vet[i]->getUserId() << "  " << i << "  " << j << " " << vet[j]->getUserId() << endl;
    Registro *aux = vet[j];
    vet[j] = vet[i];
    vet[i] = aux;
    //cout << vet[i]->getUserId() << "  " << i << "  " << j << " " << vet[j]->getUserId() << endl;
}

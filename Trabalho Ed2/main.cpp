#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define N 10

using namespace std;

//Função swap
void Troca(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}



//Função para particionar o vetor e encontrar o pivo
int Particao(int *vet, int left, int right, float pivot) {
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

//Função recursiva QuickSort, pivo é o mais a direita
void QuickSort(int *vet, int left, int right){
    if(left >= right)
        return;
    else{

        int pivo = vet[right];
        int particao = Particao(vet, left, right,pivo);

        QuickSort(vet, left, particao-1);
        QuickSort(vet, particao, right);
    }
}

void ManualSort(int *vet, int left, int right){
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

int Mediana(int *vet, int left, int right, int k){
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
    }
    cout << "Valores random: " << endl;
    for(int i = 0; i < k; i++){
        cout << random[i] << "  ";
    }
    cout << endl << endl;
    cout << "Valor do vetor: " << endl;
    for(int i = 0; i < k; i++){
        cout << vet[random[i]] << "  ";
    }
    cout << endl << endl;
    QuickSort(random, 0, k-1);

    for(int i = 0; i < k-1; i++){
        for(int j = i+1; j < k; j++){
            if(vet[random[i]] > vet[random[j]]){
                cout << "Trocou" << endl;
                Troca(vet, random[i], random[j]);
            }
        }
    }
    cout << "Valor do vetor: " << endl;
    for(int i = 0; i < k; i++){
        cout << vet[random[i]] << "  ";
    }
    cout << endl << endl;
    cout << "Valor do random: " << endl;
    for(int i = 0; i < k; i++){
        cout << random[i] << "  ";
    }
    cout << endl << endl;
    Troca(vet, random[k-2], N-1);
    for(int i =0; i < N; i++){
        cout << vet[i] << "  ";
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

void QuickSortMediana(int *vet, int left, int right, int k){
    int tamanho = right - left + 1;
    if(tamanho <= 3)
        ManualSort(vet, left, right);
    else{

        int mediana = Mediana(vet, left, right, k);
        int particao = Particao(vet, left, right, mediana);

        QuickSortMediana(vet, left, particao-1, k);
        QuickSortMediana(vet, particao, right, k);
    }
}


void InsertionSort(int *vet, int n){
    for(int i = 1; i < n; i++){
        int pivo = vet[i];
        int j = i - 1;
        while(j >= 0 && vet[j] > pivo){
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = pivo;
    }
}

void QuickSortInsertion(int *vet, int left, int right){
    int tamanho = right - left + 1;
    if(tamanho <= 10){
        InsertionSort(vet, tamanho);
        return;
    }
    int pivo = vet[right];
    int particao = Particao(vet, left, right, pivo);
    QuickSortInsertion(vet, left, particao-1);
    QuickSortInsertion(vet, particao, right);

}



int main()
{

/*
	//Cria vetor aleatório para teste
	srand(time(NULL));//Função recursiva QuickSort, pivo é o mais a direita
	int *vet = new int[N];
	for (int i = 0; i < N; i++)
	{
		vet[i] = rand() % 100;
	}



	for (int i = 0; i < N; i++)
	{
	cout << vet[i] << "  ";
	}
	cout << endl;

	QuickSort(vet, 0, N-1);
    cout << endl;
	for (int i = 0; i < N; i++)
	{
	cout << vet[i] << "  ";
	}
*/



	srand(time(NULL));
	int *vetor = new int[N];

	int *vetorPosicoes = new int[N];


	fstream myfile;

	myfile.open("ratings.csv");
	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << bytes << endl;
	string str;

	for(int i=0; i < N; i++){
        int posicaoRandom = rand()%bytes;
        vetorPosicoes[i] = posicaoRandom;
        //cout << posicaoRandom << endl;
        myfile.seekg(posicaoRandom, ios::beg);
        getline(myfile, str);
        getline(myfile, str, ',');
        istringstream iss (str);
        int aux;
        iss >> aux;
        vetor[i] = aux;
	}
    for(int i =0; i < N; i++){
        cout << vetor[i] << "  ";
    }
    cout << endl << endl;
	if (myfile.is_open()) {
        //QuickSort(vetor, 0, N-1);
        //InsertionSort(vetor, N);
        QuickSortMediana(vetor, 0, N-1, 3);
        for(int i = 0; i < N; i++){
            cout << vetor[i] << "  ";

        }
	}




	myfile.close();

    return 0;
}

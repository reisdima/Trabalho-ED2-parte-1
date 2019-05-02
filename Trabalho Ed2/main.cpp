#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define N 1000

using namespace std;

//Heapify utilizada na HeapSort
void heapify(int vetor[], int n, int i){
    int maior=i;
    int esq=2*i+1;
    int dir=2*i+2;

    if(esq<n&&vetor[esq]>vetor[maior]){
        maior=esq;
    }
    if(dir<n&&vetor[dir]>vetor[maior]){
        maior=dir;
    }
    if(maior!=i){
        swap(vetor[i],vetor[maior]);
        heapify(vetor,n,maior);
    }
}
//Função HeapSort
void heapSort(int vetor[], int n){
    for(int i=n/2-1; i>=0;i--){
        heapify(vetor,n,i);
    }
    for(int i=n-1;i>=0;i--){
        swap(vetor[0],vetor[i]);
        heapify(vetor,i,0);
    }
}

//Função para imprimir o vetor
void printVetor(int vetor[], int n)
{
    for (int i=0; i<n; ++i)
        cout << vetor[i] << " ";
    cout << "\n";
}


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
    Troca(vet, mid, right-1);

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
    return random[2];*/
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
	for(int i = 0; i < 100; i++){
        cout << rand()%bytes << endl;
	}
	cout << endl;

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

	if (myfile.is_open()) {
        //QuickSort(vetor, 0, N-1);
        //InsertionSort(vetor, N);
        QuickSortInsertion(vetorPosicoes, 0, N-1);
        for(int i = 0; i < N; i++){
            cout << vetorPosicoes[i] << "  ";

        }
	}

	cout << "\n\n";

    cout << "HeapSort:" << endl;
    heapSort(vetor,N);
    printVetor(vetor, N);

    cout << "\n";

    cout << "QuickSort:" << endl;

    QuickSort(vetor, 0, N-1);
	cout << endl;
	printVetor(vetor,N);




	myfile.close();

    return 0;
}


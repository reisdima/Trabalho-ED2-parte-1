#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define N 1000

using namespace std;

//Fun��o GetDist utilizada na CombSort
int GetDist(int dist){
    dist=(dist*10)/13;
    if(dist<1){
        return 1;
    }
    return dist;
}
//Fun��o CombSort
void CombSort(int vetor[], int n){
    int dist=n;
    bool troca=true;
    while(dist!=1||troca==true){
        dist=GetDist(dist);
        troca=false;
        for(int i=0;i<n-dist;i++){
            if(vetor[i]>vetor[i+dist]){
                swap(vetor[i],vetor[i+dist]);
                troca=true;
            }
        }
    }
}

//Fun��o merge utilizada na mergeSort
void Merge(int vetor[], int esq, int meio, int dir){
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

//Fun��o mergeSort
void MergeSort(int vetor[], int esq, int dir){
    if(esq<dir){
        int meio=esq+(dir-esq)/2;
        MergeSort(vetor,esq,meio);
        MergeSort(vetor,meio+1,dir);
        Merge(vetor,esq,meio,dir);
    }

}

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
//Fun��o HeapSort
void heapSort(int vetor[], int n){
    for(int i=n/2-1; i>=0;i--){
        heapify(vetor,n,i);
    }
    for(int i=n-1;i>=0;i--){
        swap(vetor[0],vetor[i]);
        heapify(vetor,i,0);
    }
}

//Fun��o para imprimir o vetor
void printVetor(int vetor[], int n)
{
    for (int i=0; i<n; ++i)
        cout << vetor[i] << " ";
    cout << "\n";
}


//Fun��o swap
void Troca(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}



//Fun��o para particionar o vetor e encontrar o pivo
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

//Fun��o recursiva QuickSort, pivo � o mais a direita
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
//Cria vetor aleat�rio para teste
/*
	srand(time(NULL));//Fun��o recursiva QuickSort, pivo � o mais a direita
	int *vet = new int[N];
	for (int i = 0; i < N; i++)
	{
		vet[i] = rand() % 100;
	}
*/

	srand(time(NULL));
	int *vetor = new int[N];
	int *vetorPosicoes = new int[N];

	fstream myfile;

	myfile.open("ratings.csv");
	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << "bytes: " << bytes << endl<<endl;
	string str;

	//imprimindo numeros random de 0 at� bytes
	for(int i = 0; i < 100; i++){
        cout << rand()%bytes << endl;
	}
	cout << endl;

	//leitura de arquivo
	for(int i=0; i < N; i++){
        int posicaoRandom = rand()%bytes;
        vetorPosicoes[i] = posicaoRandom;
        myfile.seekg(posicaoRandom, ios::beg);
        getline(myfile, str);
        getline(myfile, str, ',');
        istringstream iss (str);
        int aux;
        iss >> aux;
        vetor[i] = aux;
	}

//fun��es de ordena��o e fun��o de printVetor
/*
	cout << "\n\n";
    cout << "HeapSort:" << endl;
    heapSort(vetor,N);
    printVetor(vetor, N);
    cout << "\n";
    cout << "QuickSort:" << endl;
    QuickSort(vetor, 0, N-1);
	cout << endl;
	printVetor(vetor,N);
	cout << "\n";
    printVetor(vetor,N);
    cout << "MergeSort:" << endl;
    int tamVet=sizeof(vetor)/sizeof(vetor[0]);
    MergeSort(vetor,0,N-1);
	cout << endl;
	printVetor(vetor,N);
	cout << "CombSort:" << endl;
    CombSort(vetor,N);
    printVetor(vetor,N);
*/



	myfile.close();

    return 0;
}

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#define N 1000

using namespace std;

//Fun��o swap
void Troca(int *vet, int i, int j) {
	int aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

/*
int Particao(int *vet, int left, int right, int pivo){
    int leftPtr = left;
    int rightPtr = right;
    cout << endl << "Entrou:" << endl;
    cout << "L: " << leftPtr << "  R: " << rightPtr  << " Pivo: " << pivo<< endl << endl;
    while(true){
        while(vet[leftPtr] < pivo)
            leftPtr++;
        while(rightPtr > 0 && vet[rightPtr] > pivo)
            rightPtr--;

        if(leftPtr >= rightPtr){
            break;
        }
        else{
            Troca(vet, leftPtr, rightPtr);
        }
        cout << "L: " << leftPtr << "  R: " << rightPtr << endl;

    }
    for (int i = 0; i < N; i++)
    {
        cout << vet[i] << "  ";
    }
    cout << endl;
    cout << "Particao: " << leftPtr << endl;
    //Troca(vet, leftPtr, right);
    return leftPtr;
}
*/

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


/*
//Fun��o recursiva QuickSort, pivo � o mais a direita
void QuickSort(int *vet, int left, int right) {
	if (right <= left)
		return;
	else {
		float pivot = vet[right];
		cout << vet[right] << "teste" << endl;
		int particao = Particao(vet, left, right, pivot);
		QuickSort(vet, left, particao - 1);
		QuickSort(vet, particao, right);
	}
}
*/



int main()
{

/*
	//Cria vetor aleat�rio para teste
	srand(time(NULL));
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




	fstream myfile;

	myfile.open("ratings.csv");
	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << bytes << endl;
	string str;
	for(int i=0; i < N; i++){
        int posicaoRandom = rand()%bytes;
        cout << posicaoRandom << endl;
        myfile.seekg(posicaoRandom, ios::beg);
        getline(myfile, str);
        getline(myfile, str, ',');
        istringstream iss (str);
        int aux;
        iss >> aux;
        vetor[i] = aux;
	}

	if (myfile.is_open()) {
        cout << "teste" << endl;
	}
	for(int i = 0; i < N; i++){
        cout << vetor[i] << "  ";

	}

    QuickSort(vetor, 0, N-1);
	cout << endl;
	for(int i = 0; i < N; i++){
        cout << vetor[i] << "  ";

	}

	myfile.close();

}

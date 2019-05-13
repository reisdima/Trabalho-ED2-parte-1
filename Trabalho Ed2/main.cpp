#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "Registro.h"
#include "Ordenacao.h"
#define N 10000

using namespace std;

int main()
{
    int contadorComparacao;
    Registro **registros = new Registro*[N];
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

//funções de ordenação e função de printVetor
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


	srand(time(NULL));
	int *vetor = new int[N];

	int *vetorPosicoes = new int[N];


	fstream myfile;

	myfile.open("ratings.csv");

	/*
	if(myfile.is_open()){
        int userid;
        int movieId;
        string str;
        getline(myfile, str);
        getline(myfile, str);
        getline(myfile, str);
        cout << str << endl;
        getline(myfile, str , ',');
        cout << str << endl;
        getline(myfile, str , ',');
        cout << str << endl;

	}
*/


	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << "Bytes: " << bytes << endl;
	string str;


    string delimitador = ",";
	for(int i=0; i < N; i++){
        int contador = 0;
        int userId ;
        int movieId ;
        float rating;
        int timestamp;

        int posicaoRandom = rand()%bytes;
        vetorPosicoes[i] = posicaoRandom;
        myfile.seekg(posicaoRandom, ios::beg);
        getline(myfile, str);


        getline(myfile, str);
        //cout << "String: " << str << endl;
        int pos = 0;
        istringstream iss;
        string aux;
        while((pos = str.find(delimitador)) != string::npos){
            if(contador == 0){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> userId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 1){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> movieId;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            else if(contador == 2){
                aux = str.substr(0, str.find(delimitador));
                iss.str(aux);
                iss >> rating;
                iss.clear();
                str.erase(0, pos + delimitador.length());
            }
            //cout << "Aux: " << aux << endl;
            contador++;
        }
        //cout << "STR: " << str << endl;
        iss.str(str);
        iss >> timestamp;
        //cout << "UserId: " << userId << "  movieId: " << movieId << "  Rating: " << rating << "  Timestamp: " << timestamp << endl;
        registros[i] = new Registro(userId, movieId, rating, timestamp);


        //vetor[i] = userId;

	}
	for(int i = 0; i < N; i++){
        registros[i]->ExibirUserId();
	}
	cout << endl;

	Ordenacao::QuickSort(vetor,0,N-1);
	for(int i = 0; i < N; i++){
        registros[i]->ExibirUserId();
	}
    Ordenacao::imprimeContadores();
	cout << endl;
	/*
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
        Ordenacao::QuickSort(vetor, 0, N-1);
        //InsertionSort(vetor, N);
        //QuickSortMediana(vetor, 0, N-1, 3);
        for(int i = 0; i < N; i++){
            cout << vetor[i] << "  ";

        }
	}*/




	myfile.close();

    return 0;
}

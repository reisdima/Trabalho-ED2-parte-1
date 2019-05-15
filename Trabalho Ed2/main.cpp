#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Registro.h"
#include "Ordenacao.h"
#include "HashMap.h"

#define N 100

using namespace std;
using namespace chrono;

void testes(int *vetor){
//QuickSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileQuickSort ("saida.txt", ios::out | ios::app);
    steady_clock::time_point inicio = steady_clock::now();
    Ordenacao::QuickSort(vetor, 0, N-1);
    steady_clock::time_point fim = steady_clock::now();
    duration<double> tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileQuickSort.is_open()){
        myfileQuickSort << "*** tempo total QuickSort em segundos N = "<< N <<" --- ";
        myfileQuickSort << tempoTotal.count()<<" segundos";
        myfileQuickSort << "\n";
        myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao();
        myfileQuickSort <<"\n";
        myfileQuickSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileQuickSort <<"\n";
        myfileQuickSort.close();
    }

//HeapSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileHeapSort ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::HeapSort(vetor,N);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileHeapSort.is_open()){
        myfileHeapSort << "*** tempo total HeapSort em segundos N = "<< N <<" --- ";
        myfileHeapSort << tempoTotal.count()<<" segundos";
        myfileHeapSort << "\n";
        myfileHeapSort <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileHeapSort <<"\n";
        myfileHeapSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileHeapSort <<"\n";
        myfileHeapSort.close();
    }

//CombSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileCombSort ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::CombSort(vetor,N);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileCombSort.is_open()){
        myfileCombSort << "*** tempo total CombSort em segundos N = "<< N <<" --- ";
        myfileCombSort << tempoTotal.count()<<" segundos";
        myfileCombSort <<"\n";
        myfileCombSort <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileCombSort <<"\n";
        myfileCombSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileCombSort <<"\n";
        myfileCombSort.close();
    }
//InsertionSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileInsertionSort ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::InsertionSort(vetor,N);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileInsertionSort.is_open()){
        myfileInsertionSort << "*** tempo total InsertionSort em segundos N = "<< N <<" --- ";
        myfileInsertionSort << tempoTotal.count()<<" segundos";
        myfileInsertionSort <<"\n";
        myfileInsertionSort <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileInsertionSort <<"\n";
        myfileInsertionSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileInsertionSort <<"\n";
        myfileInsertionSort.close();
    }
//ManualSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileManualSort ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::ManualSort(vetor,0,N-1);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileManualSort.is_open()){
        myfileManualSort << "*** tempo total ManualSort em segundos N = "<< N <<" --- ";
        myfileManualSort << tempoTotal.count()<<" segundos";
        myfileManualSort <<"\n";
        myfileManualSort <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileManualSort <<"\n";
        myfileManualSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileManualSort <<"\n";
        myfileManualSort.close();
    }

//MergeSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileMergeSort ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::MergeSort(vetor,0,N-1);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileMergeSort.is_open()){
        myfileMergeSort << "*** tempo total MergeSort em segundos N = "<< N <<" --- ";
        myfileMergeSort << tempoTotal.count()<<" segundos";
        myfileMergeSort <<"\n";
        myfileMergeSort <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileMergeSort <<"\n";
        myfileMergeSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileMergeSort <<"\n";
        myfileMergeSort.close();
    }

//QuickSortInsertion Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
    ofstream myfileQuickSortInsertion ("saida.txt", ios::out | ios::app);
    inicio = steady_clock::now();
    Ordenacao::QuickSortInsertion(vetor,0,N-1);
    fim = steady_clock::now();
    tempoTotal=duration_cast<duration<double>>(fim-inicio);
    if (myfileQuickSortInsertion.is_open()){
        myfileQuickSortInsertion << "*** tempo total QuickSortInsertion em segundos N = "<< N <<" --- ";
        myfileQuickSortInsertion << tempoTotal.count()<<" segundos";
        myfileQuickSortInsertion <<"\n";
        myfileQuickSortInsertion <<"Quantidade de comparacoes "<<Ordenacao::getContadorComparacao();
        myfileQuickSortInsertion <<"\n";
        myfileQuickSortInsertion <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
        myfileQuickSortInsertion <<"\n";
        myfileQuickSortInsertion.close();
    }


   // inicio = steady_clock::now();
   // Ordenacao::QuickSortMediana(vetor,0,N-1,3,N);
   // fim = steady_clock::now();
   // tempoTotal=duration_cast<duration<double>>(fim-inicio);
   // cout<<"tempo total QuickSortMediana"<<tempoTotal.count() <<" segundos" <<endl;

}

int main()
{
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




	srand(time(NULL));
	int *vetor = new int[N];

	int *vetorPosicoes = new int[N];


	fstream myfile;

	myfile.open("ratings.csv");



	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << "Bytes: " << bytes << endl;
	string str;

/*
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
        cout << "UserId: " << userId << "  movieId: " << movieId << "  Rating: " << rating << "  Timestamp: " << timestamp << endl;
        registros[i] = new Registro(userId, movieId, rating, timestamp);


        //vetor[i] = userId;

	}

    //int vetor1[10] = {16, 11, 11, 9, 11, 12, 16, 2, 15, 11};
    //int vetor2[10] = {1129, 1265, 165, 5349,1265, 800, 1080, 377, 55765, 63853};

	for(int i = 0; i < N; i++){
        registros[i]->ExibirUserId();
        //cout << vetor1[i] << " ";
	}
	cout << endl << endl;
	HashMap *hashmap = new HashMap(N);
	for(int i = 0; i < N; i++){
        //hashmap->InsertEncadeamentoCoalescido(vetor1[i], vetor2[i]);
        hashmap->InsertEncadeamentoCoalescido(registros[i]->getUserId(), registros[i]->getMovieId());
	}
	 cout << endl;
    hashmap->Print();
	for(int i = 0; i< N; i++){
        //hashmap->SearchEncadeamentoCoalescido(vetor1[i], vetor2[i]);
        hashmap->SearchEncadeamentoCoalescido(registros[i]->getUserId(), registros[i]->getMovieId());
	}
    cout << endl;
    int i;
    int j;
    hashmap->Print();
    cin >> i >> j;
    hashmap->RemoveEncadeamentoCoalescido(i, j);
    cout << endl;
    hashmap->Print();
	Ordenacao::QuickSort(registros,0,N-1);
	for(int i = 0; i < N; i++){
        registros[i]->ExibirUserId();
	}
    Ordenacao::imprimeContadores();
	cout << endl;*/

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
        testes(vetor);
	}

	myfile.close();

    return 0;
}

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <random>
#include "Registro.h"
#include "Ordenacao.h"
#include "HashMap.h"

//#define N 10000

using namespace std;
using namespace chrono;

void CenarioUm(int *vetor, int N){
    //int vetN[4] = {1000, 5000, 10000, 40000};
    ofstream myfileQuickSort ("saida.txt", ios::out | ios::app);
    steady_clock::time_point inicio = steady_clock::now();
    steady_clock::time_point fim = steady_clock::now();
    duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);
    /*
    for(int i = 0; i < 1; i++){
        vetor = new int [vetN[i]];
        mt19937 generator;
        generator.seed(time(NULL));
        uniform_int_distribution<uint32_t> random(1, bytes);
        string str;
        //cout << Ordenacao::contadorComparacao << "  " << Ordenacao::contadorTrocaDeDados << endl;
        for(int j = 0; j < vetN[i]; j++){
            int posicaoRandom = random(generator);
            //cout << posicaoRandom << endl;
            myfile->seekg(posicaoRandom, ios::beg);
            getline(*myfile, str);
            getline(*myfile, str, ',');
            istringstream iss (str);
            int aux;
            iss >> aux;
            vetor[i] = aux;
        }*/
        //QuickSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        inicio = steady_clock::now();
        Ordenacao::QuickSort(vetor, 0, N - 1);
        fim = steady_clock::now();
        tempoTotal = duration_cast<duration<double>>(fim-inicio);

        if (myfileQuickSort.is_open()){
            myfileQuickSort << "*** Tempo total QuickSort em segundos N = "<< N <<" --- ";
            myfileQuickSort << tempoTotal.count()<<" segundos";
            myfileQuickSort << "\n";
            myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao();
            myfileQuickSort <<"\n";
            myfileQuickSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
            myfileQuickSort <<"\n\n";
        }
        else{
            cout << "teste" << endl;
        }
        //cout << Ordenacao::contadorComparacao << "  " << Ordenacao::contadorTrocaDeDados << endl;

        myfileQuickSort.close();
        Ordenacao::zerarContadores();
        //cout << Ordenacao::contadorComparacao << "  " << Ordenacao::contadorTrocaDeDados << endl;
}



void CenarioDois(int *vetor){

}

void CenarioTres(int *vetor){
    /*Ordenacao::CombSort(vetor, N);
    Ordenacao::HeapSort(vetor, N);
    Ordenacao::InsertionSort(vetor, N);
    Ordenacao::ManualSort(vetor, 0, N-1);
    Ordenacao::MergeSort(vetor, 0, N-1);
    Ordenacao::QuickSort(vetor, 0, N-1);*/

}

void CenarioQuatro(int *vetor){

}

void menu (int *vetor){

 cout << "Digite um numero correspondente a analise desejada: " << endl;

    int op = 0;
    cin >> op;

    switch(op){
        case 1:
            cout << "Analise de cenario 1:" << endl;
            //CenarioUm(vetor);
            break;
        case 2:
            cout << "Analise de cenario 2:" << endl;
            CenarioDois(vetor);
            break;
        case 3:
            cout << "Analise de cenario 3:" << endl;
            CenarioTres(vetor);
            break;
        case 4:
            cout << "Analise de cenario 4:" << endl;
            CenarioQuatro(vetor);
            break;


        default:
            cout << "O valor digitado nao corresponde a uma analise!" << endl;
    }
}

void realizarLeitura(fstream *myfile, int *vetor, int N, int bytes){
    //cout << "Teste" << endl;
    //vetor = new int [N];
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);

    uniform_int_distribution<uint32_t> random(1, bytes);
    string str;
    cout << N << endl;
    for(int i = 0; i < N; i++){
        int posicaoRandom = random(generator);
        //cout << posicaoRandom << endl;
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str, ',');
        istringstream iss (str);
        int aux;
        iss >> aux;
        vetor[i] = aux;
    }
}

int main()
{
    //Registro **registros = new Registro*[N];

    srand(time(NULL));

	fstream myfile;

	myfile.open("ratings.csv");
	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << "Bytes: " << bytes << endl;
    if (myfile.is_open()) {
        int escolha = 0;
        //cout << "Insira Um valor: ";
        //cin >> escolha;
        escolha = 1;
        if(escolha == 1){
            int vetN[1] = {100};
            for(int i = 0; i < 1; i++){

                for(int j = 0; j < 1; j++){
                    int *vetor = new int[vetN[i]];
                    realizarLeitura(&myfile, vetor, vetN[i], bytes);
                    //Ordenacao::PrintVetor(vetor, vetN[i]);
                    CenarioUm(vetor, vetN[i]);
                }

            }
        }

        //Ordenacao::QuickSort(vetor, 0, N-1);
        //Ordenacao::PrintVetor(vetor, N);
	}

	myfile.close();
    //int random = teste(generator);

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
	/*
    mt19937 generator;
    generator.seed(time(NULL));
    uniform_int_distribution<uint32_t> random(1, bytes);
    string str;
    string str;
    for(int j = 0; j < vetN[i]; j++){
        int posicaoRandom = random(generator);
        //cout << posicaoRandom << endl;
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str, ',');
        istringstream iss (str);
        int aux;
        iss >> aux;
        vetor[i] = aux;
    }*/




    return 0;
}

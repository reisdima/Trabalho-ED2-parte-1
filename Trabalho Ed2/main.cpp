#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <array>
#include <ctime>
#include <random>
#include "Registro.h"
#include "Ordenacao.h"
#include "HashMap.h"

//#define N 10000

using namespace std;
using namespace chrono;



void realizarLeitura(fstream *myfile, Registro **vetor, int N, int bytes){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);

    string str;
    string delimitador = ",";
    for(int i = 0; i < N; i++){
        int contador = 0;
        int userId;
        int movieId ;
        float rating;
        int timestamp;

        int posicaoRandom = random(generator);
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str);
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
        vetor[i] = new Registro(userId, movieId, rating, timestamp);
    }
}

void realizarLeitura(fstream *myfile, HashMap *hashMap, int N, int bytes){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);

    string str;
    string delimitador = ",";

    for(int i = 0; i < N; i++){
        int contador = 0;
        int userId ;
        int movieId ;
        float rating;
        int timestamp;

        int posicaoRandom = random(generator);
        myfile->seekg(posicaoRandom, ios::beg);
        getline(*myfile, str);
        getline(*myfile, str);
        int pos = 0;
        istringstream iss;
        string aux;
        while(contador < 2){
            pos = str.find(delimitador);
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
                //str.erase(str.begin(), str.end());
            }
            contador++;
        }
        //cout << "Teste" << endl;
        //cout << "UserId: " << userId << " MovieId: " << movieId << endl;
        //cout << "STR: " << str << endl;
        //cout << "UserId: " << userId << "  movieId: " << movieId << "  Rating: " << rating << "  Timestamp: " << timestamp << endl;
        hashMap->InsertSondagemQuadratica(userId, movieId);
    }
}

void realizarLeitura(fstream *myfile, int *vetor, int N, int bytes){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<uint32_t> random(1, bytes);

    string str;
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

void CenarioUm(fstream *myfile, int bytes){
    int vetN[2] = {1000, 5000};
    int *vetor;
    Registro **registros;
    int mediaT = 0;
    int mediaC = 0;
    int mediaD = 0;
    steady_clock::time_point inicio;
    steady_clock::time_point fim;
    duration<double> tempoTotal;
    ofstream myfileQuickSort ("saidaCenario1.txt", ios::out | ios::app);
    if (myfileQuickSort.is_open()){
        myfileQuickSort << "------------------------------------------------ Vetor de Inteiros ------------------------------------------------\n\n";
        for(int i = 0; i < 2; i++){
            myfileQuickSort << "****************************** N = "<< vetN[i] << " ******************************\n\n";
            for(int j = 0; j < 5; j++){
                vetor = new int[vetN[i]];
                realizarLeitura(myfile, vetor, vetN[i], bytes);

                inicio = steady_clock::now();
                Ordenacao::QuickSort(vetor, 0, vetN[i] - 1);
                fim = steady_clock::now();
                tempoTotal = duration_cast<duration<double>>(fim-inicio);

                mediaT = mediaT + tempoTotal.count();
                mediaC = mediaC + Ordenacao::getContadorComparacao();
                mediaD = mediaD + Ordenacao::getContadorTrocaDados();


                myfileQuickSort << "Tempo total em segundos (Iteracao " << j << ") = " << tempoTotal.count() << " segundos\n";
                myfileQuickSort << "Quantidade de comparacoes " << Ordenacao::getContadorComparacao() << "\n";
                myfileQuickSort << "Quantidade de Troca de Dados " << Ordenacao::getContadorTrocaDados();
                myfileQuickSort << "\n\n";
            }
            Ordenacao::zerarContadores();
            myfileQuickSort <<"Media do Tempo "<< mediaT/5 << "\nMedia de Comparacoes " << mediaC/5 << "\nMedia da Troca de Dados " << mediaD/5;
            myfileQuickSort <<"\n\n*********************************************************************\n\n";
            mediaT = 0;
            mediaC = 0;
            mediaD = 0;
        }
        myfileQuickSort << "------------------------------------------------ Vetor de Registros ------------------------------------------------\n\n";
        for(int i = 0; i < 2; i++){
            myfileQuickSort << "****************************** N = "<< vetN[i] << " ******************************\n\n";
            for(int j = 0; j < 5; j++){
                registros = new Registro*[vetN[i]];
                realizarLeitura(myfile, registros, vetN[i], bytes);

                inicio = steady_clock::now();
                Ordenacao::QuickSort(registros, 0, vetN[i] - 1);
                fim = steady_clock::now();
                tempoTotal = duration_cast<duration<double>>(fim-inicio);

                mediaT = mediaT + tempoTotal.count();
                mediaC = mediaC + Ordenacao::getContadorComparacao();
                mediaD = mediaD + Ordenacao::getContadorTrocaDados();


                myfileQuickSort << "Tempo total em segundos (Iteracao " << j << ") = " << tempoTotal.count() << " segundos\n";
                myfileQuickSort << "Quantidade de comparacoes " << Ordenacao::getContadorComparacao() << "\n";
                myfileQuickSort << "Quantidade de Troca de Dados " << Ordenacao::getContadorTrocaDados();
                myfileQuickSort << "\n\n";
            }
            Ordenacao::zerarContadores();
            myfileQuickSort <<"Media do Tempo "<< mediaT/5 << "\nMedia de Comparacoes " << mediaC/5 << "\nMedia da Troca de Dados " << mediaD/5;
            myfileQuickSort <<"\n\n*********************************************************************\n\n";
            mediaT = 0;
            mediaC = 0;
            mediaD = 0;
        }
        myfileQuickSort.close();
    }
}

void CenarioDois(fstream *myfile, int bytes){
    int vetN[7] = {1000,5000,10000,50000,100000,500000,1000000};
    for(int i = 0; i < 7; i++){
        //QuickSort recursiva(normal)
        for(int j = 0; j < 5; j++){
            int *vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            //Ordenacao::PrintVetor(vetor, vetN[i]);

            ofstream myfileQuickSort ("saida2.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSort(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);
            if (myfileQuickSort.is_open()){
                myfileQuickSort << "*** Tempo total QuickSort em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal.count()<<" segundos\n";
                myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
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
        //QuickSort Insercao
        for(int j = 0; j < 5; j++){
            int *vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            //Ordenacao::PrintVetor(vetor, vetN[i]);

            ofstream myfileQuickSort ("saida2.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSortInsertion(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);
            if (myfileQuickSort.is_open()){
                myfileQuickSort << "*** Tempo total QuickSortInsertion em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal.count()<<" segundos\n";
                myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
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

        /*
        //QuickSort Merdiana
        for(int j = 0; j < 5; j++){
            int *vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            //Ordenacao::PrintVetor(vetor, vetN[i]);

            ofstream myfileQuickSort ("saida2.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSortMediana(vetor,0,vetN[i]-1,3,vetN[i]);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);
            if (myfileQuickSort.is_open()){
                myfileQuickSort << "*** Tempo total QuickSortMediana em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal.count()<<" segundos\n";
                myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
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
            */
        }
    }


void CenarioTres(fstream *myfile, int bytes){

    int vetN[1] = {10000};
    int *vetor;
    long mediaT=0;
    long long mediaC=0;
    long long mediaD=0;
    for(int i = 0; i < 1; i++){
    //QuickSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            steady_clock::time_point inicio;
            steady_clock::time_point fim;
            duration<double> tempoTotal;
            duration<double> tempoTotal2;
            inicio = steady_clock::now();
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            fim = steady_clock::now();
            ofstream myfileQuickSort ("saida3.txt", ios::out | ios::app);


            tempoTotal2 = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSort(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileQuickSort.is_open()){
                myfileQuickSort << "*** Tempo total QuickSort em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal.count()<<" segundos\n";
                myfileQuickSort << "*** Tempo total QuickSort Leitura em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal2.count()<<" segundos\n";
                myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileQuickSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileQuickSort <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileQuickSort.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileQuickSort ("saida3.txt", ios::out | ios::app);
        if (myfileQuickSort.is_open()){
            myfileQuickSort <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileQuickSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;/*
//HeapSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            ofstream myfileHeapSort ("saida3.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::HeapSort(vetor, vetN[i] );
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileHeapSort.is_open()){
                myfileHeapSort << "*** Tempo total HeapSort em segundos N = "<< vetN[i] <<" --- ";
                myfileHeapSort << tempoTotal.count()<<" segundos\n";
                myfileHeapSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileHeapSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileHeapSort <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileHeapSort.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileHeapSort ("saida3.txt", ios::out | ios::app);
        if (myfileHeapSort.is_open()){
            myfileHeapSort <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileHeapSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;
//CombSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            ofstream myfileCombSort ("saida3.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::CombSort(vetor, vetN[i]);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileCombSort.is_open()){
                myfileCombSort << "*** Tempo total CombSort em segundos N = "<< vetN[i] <<" --- ";
                myfileCombSort << tempoTotal.count()<<" segundos\n";
                myfileCombSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileCombSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileCombSort <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileCombSort.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileCombSort ("saida3.txt", ios::out | ios::app);
        if (myfileCombSort.is_open()){
            myfileCombSort <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileCombSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;
//InsertionSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            ofstream myfileInsertionSort ("saida3.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::InsertionSort(vetor,vetN[i] );
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileInsertionSort.is_open()){
                myfileInsertionSort << "*** Tempo total InsertionSort em segundos N = "<< vetN[i] <<" --- ";
                myfileInsertionSort << tempoTotal.count()<<" segundos\n";
                myfileInsertionSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileInsertionSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileInsertionSort <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileInsertionSort.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileInsertionSort ("saida3.txt", ios::out | ios::app);
        if (myfileInsertionSort.is_open()){
            myfileInsertionSort <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileInsertionSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;
//MergeSort Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            ofstream myfileMergeSort ("saida3.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::MergeSort(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileMergeSort.is_open()){
                myfileMergeSort << "*** Tempo total MergeSort em segundos N = "<< vetN[i] <<" --- ";
                myfileMergeSort << tempoTotal.count()<<" segundos\n";
                myfileMergeSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileMergeSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileMergeSort <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileMergeSort.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileMergeSort ("saida3.txt", ios::out | ios::app);
        if (myfileMergeSort.is_open()){
            myfileMergeSort <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileMergeSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;
//QuickSortInsertion Teste contendo tempo de execução, contadorComparacao e contadorTrocaDeDados  com variaçoes de N
        for(int j = 0; j < 5; j++){
            vetor = new int[vetN[i]];
            realizarLeitura(myfile, vetor, vetN[i], bytes);
            ofstream myfileQSortI ("saida3.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSortInsertion(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);

            mediaT=mediaT+tempoTotal.count();
            mediaC=mediaC+Ordenacao::getContadorComparacao();
            mediaD=mediaD+Ordenacao::getContadorTrocaDados();

            if (myfileQSortI.is_open()){
                myfileQSortI << "*** Tempo total QuickSortInsertion em segundos N = "<< vetN[i] <<" --- ";
                myfileQSortI << tempoTotal.count()<<" segundos\n";
                myfileQSortI <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileQSortI <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileQSortI <<"\n\n";
            }
            else{
                cout << "Arquivo nao esta aberto" << endl;
            }
            myfileQSortI.close();
            Ordenacao::zerarContadores();
        }
        ofstream myfileQuickSortInsertion ("saida3.txt", ios::out | ios::app);
        if (myfileQuickSortInsertion.is_open()){
            myfileQuickSortInsertion <<"Media Tempo "<< mediaT/5<<" Media Comparacao "<<mediaC/5<<" Media Troca de Dados "<<mediaD/5;
        }
        myfileMergeSort.close();
        mediaC = 0;
        mediaT = 0;
        mediaD = 0;*/
    }
}


void CenarioQuatro(fstream *myfile, int bytes){
    int vetN[1] = {1000};
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 1; j++){
            HashMap *hashMap = new HashMap(vetN[i]);
            realizarLeitura(myfile, hashMap, vetN[i], bytes);
            hashMap->Print();
            int a;
            int b;
            cin >> a >> b;
            hashMap->SearchSondagemQuadratica(a, b);
            //Ordenacao::PrintVetor(vetor, vetN[i]);

            /*ofstream myfileQuickSort ("saida.txt", ios::out | ios::app);
            steady_clock::time_point inicio = steady_clock::now();
            steady_clock::time_point fim = steady_clock::now();
            duration<double> tempoTotal = duration_cast<duration<double>>(fim-inicio);

            inicio = steady_clock::now();
            Ordenacao::QuickSort(vetor, 0, vetN[i] - 1);
            fim = steady_clock::now();
            tempoTotal = duration_cast<duration<double>>(fim-inicio);
            if (myfileQuickSort.is_open()){
                myfileQuickSort << "*** Tempo total QuickSort em segundos N = "<< vetN[i] <<" --- ";
                myfileQuickSort << tempoTotal.count()<<" segundos\n";
                myfileQuickSort <<"Quantidade de comparacoes "<< Ordenacao::getContadorComparacao() << "\n";
                myfileQuickSort <<"Quantidade de Troca de Dados "<<Ordenacao::getContadorTrocaDados();
                myfileQuickSort <<"\n\n";
            }
            else{
                cout << "teste" << endl;
            }*/
            //cout << Ordenacao::contadorComparacao << "  " << Ordenacao::contadorTrocaDeDados << endl;
            //myfileQuickSort.close();
            //Ordenacao::zerarContadores();
            //cout << Ordenacao::contadorComparacao << "  " << Ordenacao::contadorTrocaDeDados << endl;
        }
    }
}

void Menu (fstream *myfile){
    cout << "Digite um numero correspondente a analise desejada: " << endl;
    myfile->seekg(0, ios::end);
	int bytes = myfile->tellg();
    int op = 1;
    //cin >> op;

    switch(op){
        case 1:
            cout << "Analise de cenario 1:" << endl;
            CenarioUm(myfile, bytes);
            break;
        case 2:
            cout << "Analise de cenario 2:" << endl;
            CenarioDois(myfile, bytes);
            break;
        case 3:
            cout << "Analise de cenario 3:" << endl;
            CenarioTres(myfile, bytes);
            break;
        case 4:
            cout << "Analise de cenario 4:" << endl;
            CenarioQuatro(myfile, bytes);
            break;


        default:
            cout << "O valor digitado nao corresponde a uma analise!" << endl;
    }
}

int main()
{
    //Registro **registros = new Registro*[N];

    srand(time(NULL));

	fstream myfile;

	myfile.open("ratings.csv");/*
	myfile.seekg(0, ios::end);
	int bytes = myfile.tellg();
	cout << "Bytes: " << bytes << endl;*/
    if (myfile.is_open()) {
        int escolha = 0;
        //cout << "Insira Um valor: ";
        //cin >> escolha;
        escolha = 1;
        Menu(&myfile);
        /*
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
        }*/

        //Ordenacao::QuickSort(vetor, 0, N-1);
        //Ordenacao::PrintVetor(vetor, N);vetN[7] = {1000,5000,10000,50000,100000,500000,1000000};
	}
    else{
        cout << "O arquivo nao abriu" << endl;
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

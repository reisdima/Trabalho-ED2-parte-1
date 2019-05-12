#include <iostream>
#include "Registro.h"

using namespace std;

Registro::Registro(int userId, int movieId, float rating, int timestamp)
{
    this->userId = userId;
    this->movieId = movieId;
    this->rating = rating;
    this->timestamp = timestamp;
}

Registro::~Registro()
{
    //dtor
}

void Registro::ExibirRegistro(){
    cout << "UserId: " << userId << endl;
    cout << "MovieId: " << movieId << endl;
    cout << "Rating: " << rating << endl;
    cout << "Timestamp: " << timestamp << endl << endl  ;
}

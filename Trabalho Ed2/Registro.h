#ifndef REGISTRO_H
#define REGISTRO_H


class Registro
{
public:
    Registro(int userId, int movieId, float rating, int timestamp);
    Registro();
    ~Registro();

    void setUserId(int id);
    void setMovied(int id);
    void setRating(float rating);
    void setTimestamp(int timestamp);

    void ExibirRegistro();

private:
    int userId;
    int movieId;
    float rating;
    int timestamp;
};

#endif // REGISTRO_H

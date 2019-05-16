#ifndef HASHNODE_H
#define HASHNODE_H


class HashNode
{
public:
    HashNode(int userId, int movieId);
    ~HashNode();

    int getUserid();
    int getMovieId();

    void setUserId(int userI);
    void setMovieId(int movieId);

    void setProx(HashNode *prox);
    void setAnt(HashNode *prox);
    HashNode *getProx();
    HashNode *getAnt();

    void setProximaChave(int key);
    int getProximaChave();

private:
    int userId;
    int movieId;

    HashNode *prox;
    HashNode *anterior;
    int proximaChave;
};

#endif // HASHNODE_H

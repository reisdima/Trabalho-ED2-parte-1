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
    HashNode *setProx();

private:
    int userId;
    int movieId;

    HashNode *prox;
};

#endif // HASHNODE_H

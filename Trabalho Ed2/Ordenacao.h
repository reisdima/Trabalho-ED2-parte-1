#ifndef ORDENACAO_H
#define ORDENACAO_H


class Ordenacao
{
public:
    Ordenacao();
    ~Ordenacao();
    static void QuickSort(int *vet, int left, int right);
    static void ManualSort(int *vet, int left, int right);
    static void MergeSort(int *vet, int left, int right);
    static void CombSort(int *vet, int n);
    static void HeapSort(int *vet, int n);

private:
    static void Heapify(int *vet, int n, int i);
    static int GetDist(int dist);
    static void Merge(int *vet, int left, int mid, int right);
    static int Particiona(int *vet, int left, int right, float pivot);
    static void Troca(int *vet, int i, int j);
};

#endif // ORDENACAO_H

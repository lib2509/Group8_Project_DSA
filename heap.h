#ifndef _heap_h_
#define _heap_h_

class IntHeap
{
public:
    IntHeap(int n);
    ~IntHeap();

    void init(int *a, int n);
    void fullBuild(int l, int r); //max-heap
    void build(int i, int r); //max-heap
    void fullBuildCntComp(int l, int r); //max-heap
    void buildCntComp(int i, int r); //max-heap
    bool isHeap(int l, int r); //max-heap
    void print(int l, int r);
    void sort(int l, int r, int t); //ascending order
    bool isSorted(int l, int r); //ascending order
    long long getCntComp();
    void resetCntComp();
    void clear();

private:
    int s = 0;
    long long cntComp = 0;
    int* h = nullptr;
};

#endif
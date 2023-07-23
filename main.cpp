#include "heap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

bool isSorted(int* a, int n); //Ascending order
void generateArray(int *&a, int n, int t);
void generateRandomArray(int *&a, int n);
void generateSortedArray(int *&a, int n, int t);

int main()
{
    int n = 1000000;
    int *a = new int[n];
    int t = 0; // 0 is random, 1 is sorted
    int cntComp = 0;
    generateArray(a, n, t);
    
    // IntHeap h(n);
    // h.init(a, n);
    // auto start = high_resolution_clock::now();
    // h.sort(0, n - 1, 1);
    // cout << h.isSorted(0, n - 1) << "\n";
    // cout << h.getCntComp() << "\n";
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count();
    // h.clear();

    // auto start = high_resolution_clock::now();
    // mergeSort(a, n);
    // mergeSortCntComp(a, n, cntComp);
    // cout << isSorted(a, n) << " " << cntComp << "\n";
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << duration.count();

    auto start = high_resolution_clock::now();
    quickSort(a, 0, n - 1);
    quickSortCntComp(a, 0, n - 1, cntComp);
    cout << isSorted(a, n) << " " << cntComp << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count();
    
    return 0;
}

void generateArray(int *&a, int n, int t)
{
    if (t == 0)
        generateRandomArray(a, n);
    else if (t == 1)
    {
        int s = 1;
        generateSortedArray(a, n, s);
    }
}

void generateRandomArray(int *&a, int n)
{
    srand((unsigned int)time(NULL));

    int r = 1000000;
    for (int i = 0; i < n; i++)
        a[i] = rand() % r;
}

void generateSortedArray(int *&a, int n, int t)
{
    if (t == 0)
    {
        for (int i = 0; i < n; i++)
            a[i] = i;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = n - i - 1;
        }
    }
}

bool isSorted(int* a, int n)
{
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            return false;

    return true;
}

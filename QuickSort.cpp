#include "QuickSort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void quickSort(int*& a, int l, int r)
{   
    if (l >= r) return;

    srand((unsigned int)time(NULL));
    int i = l;
    int j = r;
    int p = a[l + rand() % (r - l + 1)];
    while (i <= j)
    {
        while (a[i] < p)
            i++;
        while (a[j] > p)
            j--;
        if (i <= j)
            swap(a[i++], a[j--]);
    }

    quickSort(a, i, r);
    quickSort(a, l, j);
}

void quickSortCntComp(int*& a, int l, int r, int& cntComp)
{   
    if (l >= r) return;

    srand((unsigned int)time(NULL));
    int i = l;
    int j = r;
    int p = a[l + rand() % (r - l + 1)];
    while (i <= j)
    {
        cntComp++;
        while (a[i] < p)
        {
            i++;
            cntComp++;
        }
        while (a[j] > p)
        {
            j--;
            cntComp++;
        }
        if (i <= j)
        {
            swap(a[i++], a[j--]);
            cntComp++;
        }
    }

    quickSortCntComp(a, i, r, cntComp);
    quickSortCntComp(a, l, j, cntComp);
}
#include "MergeSort.h"
#include <iostream>

using namespace std;

void mergeSort(int *&a, int n)
{
    if (n <= 1)
        return;

    int ln = n / 2;
    int rn = (n + 1) / 2;
    int *la = new int[ln];
    int *ra = new int[rn];

    for (int i = 0; i < ln; i++)
        la[i] = a[i];

    for (int i = 0; i < rn; i++)
        ra[i] = a[i + ln];

    mergeSort(la, ln);
    mergeSort(ra, rn);

    int i, j, k;
    i = j = k = 0;
    while (true)
    {
        if (i >= ln)
        {
            for (; j < rn; j++)
                a[k++] = ra[j];
            break;
        }
        else if (j >= rn)
        {
            for (; i < ln; i++)
                a[k++] = la[i];
            break;
        }
        else if (la[i] < ra[j])
            a[k++] = la[i++];
        else
            a[k++] = ra[j++];
    }

    delete[] la;
    delete[] ra;
}

void mergeSortCntComp(int *&a, int n, int &cntComp)
{
    if (n <= 1)
        return;

    int ln = n / 2;
    int rn = (n + 1) / 2;
    int *la = new int[ln];
    int *ra = new int[rn];

    for (int i = 0; i < ln; i++)
        la[i] = a[i];
    for (int i = 0; i < rn; i++)
        ra[i] = a[i + ln];
    cntComp += n + 2;

    mergeSortCntComp(la, ln, cntComp);
    mergeSortCntComp(ra, rn, cntComp);

    int i, j, k;
    i = j = k = 0;
    while (true)
    {
        if (i >= ln)
        {
            cntComp += rn - j + 2;
            for (; j < rn; j++)
                a[k++] = ra[j];
            break;
        }
        else if (j >= rn)
        {
            cntComp += ln - i + 3;
            for (; i < ln; i++)
                a[k++] = la[i];
            break;
        }
        else
        {
            cntComp += 3;
            if (la[i] < ra[j])
                a[k++] = la[i++];
            else
                a[k++] = ra[j++];
        }
    }

    delete[] la;
    delete[] ra;
}
#include "heap.h"

using namespace std;

IntHeap::IntHeap(int n)
{
    s = n;
    h = new int[n];
}

IntHeap::~IntHeap()
{
}

void IntHeap::init(int *a, int n)
{
    if (n <= s)
    {
        for (int i = 0; i < n; i++)
            h[i] = a[i];
    }
}

void IntHeap::fullBuild(int l, int r)
{
    if (l >= r)
        return;

    for (int i = l + (r - l + 1) / 2 - 1; i >= l; i--)
        build(i, r);
}

void IntHeap::build(int i, int r)
{
    if (i >= r)
        return;

    int maxChild = i * 2 + 1;
    if (maxChild + 1 <= r)
        if (h[maxChild] < h[maxChild + 1])
            maxChild++;

    while (h[maxChild] > h[i])
    {
        swap(h[maxChild], h[i]);

        i = maxChild;
        if (i * 2 + 1 <= r)
            maxChild = i * 2 + 1;
        else
            break;
        if (maxChild + 1 <= r)
            if (h[maxChild] < h[maxChild + 1])
                maxChild++;
    }
}

void IntHeap::fullBuildCntComp(int l, int r)
{
    if (l >= r)
        return;

    int n = r - l + 1;
    cntComp += n / 2 + 1;
    for (int i = l + n / 2 - 1; i >= l; i--)
        buildCntComp(i, r);
}

void IntHeap::buildCntComp(int i, int r)
{
    if (i >= r)
        return;

    int maxChild = i * 2 + 1;
    if (maxChild + 1 <= r)
    {
        cntComp++;
        if (h[maxChild] < h[maxChild + 1])
            maxChild++;
    }
    cntComp++;

    while (h[maxChild] > h[i])
    {
        cntComp++;
        swap(h[maxChild], h[i]);

        i = maxChild;
        cntComp++;
        if (i * 2 + 1 <= r)
            maxChild = i * 2 + 1;
        else
            break;
        if (maxChild + 1 <= r)
        {
            cntComp++;
            if (h[maxChild] < h[maxChild + 1])
                maxChild++;
        }
        cntComp++;
    }
    cntComp++;
}

bool IntHeap::isHeap(int l, int r)
{
    if (l > r)
        return false;

    int n = r - l + 1;
    for (int i = l; i <= l + n / 2 - 1; i++)
    {
        if (h[i] < h[i * 2 + 1])
            return false;
        if (i * 2 + 2 <= r && h[i] < h[i * 2 + 2])
            return false;
    }

    return true;
}

void IntHeap::print(int l, int r)
{
    if (l >= r)
        return;

    for (; l <= r; l++)
    {
        cout << h[l] << " ";
    }
}

void IntHeap::sort(int l, int r, int t)
{
    if (l >= r)
        return;

    if (t == 0)
        fullBuild(l, r);
    else
        fullBuildCntComp(l, r);
    for (int i = r; i > l; i--)
    {
        swap(h[i], h[l]);
        if (t == 0)
            build(l, i - 1);
        else
            buildCntComp(l, i - 1);
    }
}

bool IntHeap::isSorted(int l, int r)
{
    if (l > r)
        return false;

    for (int i = l + 1; i <= r; i++)
        if (h[i] < h[i - 1])
            return false;
    return true;
}

long long IntHeap::getCntComp()
{
    return cntComp;
}

void IntHeap::resetCntComp()
{
    cntComp = 0;
}

void IntHeap::clear()
{
    delete[] h;
    s = 0;
    cntComp = 0;
}
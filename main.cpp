#include "heap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "sort.h"

int main(int argc, char *argv[])
{
    Sort sort;
    sort.run(argc, argv);
    return 0;
}
#include "components.h"
class Sort
{
private:
    int *arr;
    unsigned int size;
    unsigned long long int comparison;
    unsigned long long int runTime;
    //---------------------------------------------------------------------------------------------
    void selectionSort_runTime(int *arr, int size);
    void selectionSort_comparison(int *arr, int size);

    void insertionSort_runTime(int *arr, int size);
    void insertionSort_comparison(int *arr, int size);

    void bubbleSort_runTime(int *arr, int size);
    void bubbleSort_comparison(int *arr, int size);

    void shakerSort_runTime(int *arr, int size);
    void shakerSort_comparison(int *arr, int size);

    void shellSort_runTime(int *arr, int size);
    void shellSort_comparison(int *arr, int size);

    void heapSort_runTime(int *arr, int size);
    void heapSort_comparison(int *arr, int size);

    void mergeSort_runTime(int *arr, int size);
    void mergeSort_comparison(int *arr, int size);

    void quickSort_runTime(int *arr, int size);
    void quickSort_comparison(int *arr, int size);

    void countingSort_runTime(int *arr, int size);
    void countingSort_comparison(int *arr, int size);

    void radixSort_runTime(int *arr, int size);
    void radixSort_comparison(int *arr, int size);

    void flashSort_runTime(int *arr, int size);
    void flashSort_comparison(int *arr, int size);

public:
    Sort(int *arr = nullptr, unsigned int size = 0);
    int type(string sort_name);
    void reset();
    unsigned long long int getRunningTime();
    unsigned long long int getComparison();
    void setArr(int *arr, int size);
    int run(int argc, char *argv[]);
    // ---------------------------------------------------------------------------------------------
    void selectionSort();
    void insertionSort();
    void bubbleSort();
    void shakerSort();
    void shellSort();
    void heapSort();
    void mergeSort();
    void quickSort();
    void countingSort();
    void radixSort();
    void flashSort();
    void sort(int type);
    // ---------------------------------------------------------------------------------------------
    int command1(int sortType, string filename, int outputType);
    int command2(int sortType, unsigned int arrSize, int inputOrder, int outputType);
    int command3(int sortType, unsigned int arrSize, int outputType);
    int command4(int sortType1, int sortType2, string filename);
    int command5(int sortType1, int sortType2, unsigned int arrSize, int inputOrder);
    void experiment();
    void experiment_2();
    // ---------------------------------------------------------------------------------------------
    void printOutput(int outputType);
    void writeArrayToFile(string filename);
    ~Sort();
};

//-------------------------------------------------

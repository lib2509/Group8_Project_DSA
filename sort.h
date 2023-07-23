﻿#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <string>
#include <chrono>

using namespace std;

const unsigned int dataSize[6] = {10000, 30000, 50000, 100000, 300000, 500000};
const string dataOrder[4] = {"-rand", "-sorted", "-rev", "-nsorted"};
const string sortName[11] = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};
const string outputParameter[3] = {"-time", "-comp", "-both"};
const string data_order[4] = {"Randomize", "Sorted", "Reverse", "Nearly Sorted"};
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
    // ---------------------------------------------------------------------------------------------
    void printOutput(int outputType);
    void writeArrayToFile(string filename);
    ~Sort();
};

template <class T>
void HoanVi(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n);

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n);

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n);

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n);

void GenerateData(int a[], int n, int dataType);

unsigned int convert_string_to_num(string s);

int convert_string_to_outputType(string s);

bool isFileExist(string fileName);

int convert_string_to_inputOrderType(string s);

bool isAscending(int *arr, int size);

void printUserManual();

void printInvalidCommand();

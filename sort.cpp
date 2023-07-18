﻿#include "sort.h"

Sort::Sort(int* arr, unsigned int size)
{
    this->arr = arr;
    this->size = size;
    this->comparison = 0;
    this->runTime = 0;
}

void Sort::sort(int type)
{
    switch (type)
    {
    case 1:
        selectionSort();
        break;
    case 2:
        insertionSort();
        break;
    case 3:
        bubbleSort();
        break;
    case 4:
        shakerSort();
        break;
    case 5:
        shellSort();
        break;
    case 6:
        heapSort();
        break;
    case 7:
        mergeSort();
        break;
    case 8:
        quickSort();
        break;
    case 9:
        countingSort();
        break;
    case 10:
        radixSort();
        break;
    case 11:
        flashSort();
        break;
    default:
        cout << "Invalid type!" << endl;
        break;
    }
}

unsigned long long int Sort::getRunningTime() {
    return runTime;
}

unsigned long long int Sort::getComparison() {
    return comparison;
}

void Sort::setArr(int* arr, int size)
{
    if (this->arr != nullptr)
    {
        delete this->arr;
        this->arr = nullptr;
    }
    this->arr = arr;
    this->size = size;
}

void Sort::reset()
{
    if (this->arr != nullptr)
        delete this->arr;
    this->arr = nullptr;
    this->size = 0;
    this->comparison = 0;
    this->runTime = 0;
}

int Sort::type(string sort_name)
{
    for (int i = 0; i < 11; i++)
        if (sort_name == sortName[i])
            return i + 1;
    return 0;
}

int Sort::run(int argc, char* argv[])
{
    if (argc == 1)
    {
        experiment();
        return 0;
    }
    else if (argc == 5)
    {
        if (string(argv[1]) == "-a") {
            int sortType = this->type(string(argv[2]));
            if (sortType == 0)
            {
				cout << "Invalid sort name!" << endl;
				return 1;
			}
            // ------------------------------------------------------------
            int outputType = convert_string_to_outputType(string(argv[4]));
            if (outputType == -1) {
				cout << "Invalid output type!" << endl;
				return 1;
			}
            // ------------------------------------------------------------
            string filename = string(argv[3]);
            if (isFileExist(filename)) {
                return command1(sortType, filename, outputType);
                /* Prototype: [Execution file] - a[Algorithm][Given input][Output parameter(s)]
                Ex : a.exe - a radix - sort input.txt - both*/
            }
            unsigned int arrSize = convert_string_to_num(string(argv[3]));
            if (arrSize == 0) {
                cout << "Invalid size! Pls input a positive integer" << endl;
                return 1;
            }
            // ------------------------------------------------------------
            return command3(sortType, arrSize, outputType);
            /*Prototype: [Execution file] - a[Algorithm][Input size][Output parameter(s)]
            Ex : a.exe - a binary - insertion - sort 70000 - comp*/
        }
        
        else if (string(argv[1]) == "-c") {
            int sortType1 = this->type(string(argv[2]));
            int sortType2 = this->type(string(argv[3]));
            if (sortType1 == 0 || sortType2 == 0 || sortType1 == sortType2)
            {
                cout << "Invalid sort name!" << endl;
                return 4;
            }
            // ------------------------------------------------------------
            string filename = string(argv[4]);
            if (isFileExist(filename)) {
                return command4(sortType1, sortType2, filename);
            }
            else {
				cout << "Invalid file name!" << endl;
				return 4;
			}
        }
            
        /*Prototype: [Execution file] - c[Algorithm 1][Algorithm 2][Given input]
        Ex : a.exe - c heap - sort merge - sort input.txt*/
        
    }
    else if (argc == 6) {
        if (string(argv[1]) == "-a") {
			int sortType = this->type(string(argv[2]));
            if (sortType == 0)
            {
                return 2;
            }
            // ------------------------------------------------------------
            int outputType = convert_string_to_outputType(string(argv[5]));
            if (outputType == -1) {
                return 2;
			}
            // ------------------------------------------------------------
			unsigned int arrSize = convert_string_to_num(string(argv[3]));
            if (arrSize == 0) {
                return 2;
			}
			// ------------------------------------------------------------
            int inputOrder = convert_string_to_inputOrderType(string(argv[4]));
            if (inputOrder == -1) {
				return 2;
            }
			return command2(sortType, arrSize, inputOrder, outputType);
        }
        else if (string(argv[1]) == "-c") {
            int sortType1 = this->type(string(argv[2]));
            int sortType2 = this->type(string(argv[3]));
            if (sortType1 == 0 || sortType2 == 0 || sortType1 == sortType2)
            {
                cout << "Invalid sort name!" << endl;
                return 5;
            }
            // ------------------------------------------------------------
            unsigned int arrSize = convert_string_to_num(string(argv[4]));
            if (arrSize == 0) {
				cout << "Invalid size! Pls input a positive integer" << endl;
				return 5;
			}
            // ------------------------------------------------------------
			int inputOrder = convert_string_to_inputOrderType(string(argv[5]));
            if (inputOrder == -1) {
                cout << "Invalid data order!" << endl;
                return 5;
            }
            return command5(sortType1, sortType2, arrSize, inputOrder);
        }
        // command2();
        /*Prototype: [Execution file] - a[Algorithm][Input size][Input order]
        [Output parameter(s)]
        Ex : a.exe - a selection - sort 50 - rand - time*/

        //command5();
        /*Prototype: [Execution file] - c[Algorithm 1][Algorithm 2][Input size]
        [Input order]
        Ex : a.exe - c quick - sort merge - sort 100000 - nsorted*/
    }
    return -1;
}

void Sort::experiment()
{
    int* a = nullptr;
    ofstream ofs("result.csv");
    ofs << "DataOrder,DataSize,SortName,Comparison,RunTime" << endl;
    cout << "DataOrder,DataSize,SortName,Comparison,RunTime" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 1; k < 2; k++)
            {
                a = new int[dataSize[j]];
                GenerateData(a, dataSize[j], i);
                setArr(a, dataSize[j]);
                auto start = std::chrono::high_resolution_clock::now();
                sort(k + 1);
                auto end = std::chrono::high_resolution_clock::now();
                this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                unsigned long long int comparison = getComparison();
                unsigned long long int runTime = getRunningTime();
                ofs << dataOrder[i] << "," << dataSize[j] << "," << sortName[k] << "," << comparison << "," << runTime << endl;
                cout << dataOrder[i] << "," << dataSize[j] << "," << sortName[k] << "," << comparison << "," << runTime << endl;
                reset();
            }
        }
    }
    ofs.close();
}

Sort::~Sort()
{
    if (this->arr != nullptr)
        delete this->arr;
    this->arr = nullptr;
    this->size = 0;
    this->comparison = 0;
    this->runTime = 0;
}


void Sort::selectionSort_runTime(int* arr, int size) {
    int minIndex;
    for (int i = 0; i < size - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (i != minIndex)
            swap(arr[i], arr[minIndex]);
    }
}

void Sort::selectionSort_comparison(int* arr, int size) {
    int minIndex;
    for (int i = 0; ++this->comparison && i < size - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; ++this->comparison && j < size; j++)
        {
            if (++this->comparison && arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (++this->comparison && minIndex != i)
            swap(arr[i], arr[minIndex]);
    }
}

void Sort::insertionSort(int* arr, int size)
{
    int key, j;
    for (int i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            this->comparison++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void Sort::selectionSort()
{
    /*if (type == 0) {
        auto start = std::chrono::high_resolution_clock::now();
        selectionSort_runTime(this->arr, this->size);
        auto end = std::chrono::high_resolution_clock::now();
        this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    else if (type == 1) {
		selectionSort_comparison(this->arr, this->size);
	}*/
    return;
}

void Sort::insertionSort()
{
    return insertionSort(this->arr, this->size);
}

void Sort::bubbleSort() {
    return;
}

void Sort::shakerSort() {
	return;
}

void Sort::shellSort() {
	return;
}

void Sort::heapSort() {
	return;
}

void Sort::mergeSort() {
	return;
}

void Sort::quickSort() {
	return;
}

void Sort::countingSort() {
	return;
}

void Sort::radixSort() {
	return;
}

void Sort::flashSort() {
	return;
}

int Sort::command1(int sortType, string filename, int outputType) {
    return 1;
}

int Sort::command2(int sortType, unsigned int arrSize, int inputOrder, int outputType) {
    return 2;
}

int Sort::command3(int sortType, unsigned int arrSize, int outputType) {
    return 3;
}

int Sort::command4(int sortType1, int sortType2, string filename) {
    return 4;
}

int Sort::command5(int sortType1, int sortType2, unsigned int arrSize, int inputOrder) {
    return 5;
}

void GenerateRandomData(int a[], int n)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % n;
    }
}

void GenerateSortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

void GenerateReverseData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int r1 = rand() % n;
        int r2 = rand() % n;
        HoanVi(a[r1], a[r2]);
    }
}

void GenerateData(int a[], int n, int dataType)
{
    switch (dataType)
    {
    case 0: // ngẫu nhiên
        GenerateRandomData(a, n);
        break;
    case 1: // có thứ tự
        GenerateSortedData(a, n);
        break;
    case 2: // có thứ tự ngược
        GenerateReverseData(a, n);
        break;
    case 3: // gần như có thứ tự
        GenerateNearlySortedData(a, n);
        break;
    default:  
        printf("Error: unknown data type!\n");
    }
}

unsigned int convert_string_to_num(string s) {
    unsigned int num = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9')
		    num = num * 10 + (s[i] - '0');
        else {
            return 0;
        }
	}
	return num;
}

int convert_string_to_outputType(string s) {
    for (int i = 0; i < 3; i++)
        if (s == outputParameter[i])
            return i;
    return -1;
}

bool isFileExist(string fileName) {
	ifstream infile(fileName);
	return infile.good();
}

int convert_string_to_inputOrderType(string s) {
    for (int i = 0; i < 4; i++)
        if (dataOrder[i] == s)
            return i;
    return -1;
}


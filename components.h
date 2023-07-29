#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

const unsigned int dataSize[6] = {10000, 30000, 50000, 100000, 300000, 500000};
const string dataOrder[4] = {"-rand", "-sorted", "-rev", "-nsorted"};
const string sortName[11] = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};
const string outputParameter[3] = {"-time", "-comp", "-both"};
const string data_order[4] = {"Randomize", "Sorted", "Reverse", "NearlySorted"};
const string input_filename[24] = {"Randomize_10000", "Randomize_30000", "Randomize_50000", "Randomize_100000", "Randomize_300000", "Randomize_500000",
                                   "Sorted_10000", "Sorted_30000", "Sorted_50000", "Sorted_100000", "Sorted_300000", "Sorted_500000",
                                   "Reverse_10000", "Reverse_30000", "Reverse_50000", "Reverse_100000", "Reverse_300000", "Reverse_500000",
                                   "NearlySorted_10000", "NearlySorted_30000", "NearlySorted_50000", "NearlySorted_100000", "NearlySorted_300000", "NearlySorted_500000"};
class IntHeap;

class Sort;

//---------------------------------------------------------------------------------------------

unsigned int convert_string_to_num(string s);

int convert_string_to_outputType(string s);

bool isFileExist(string fileName);

int convert_string_to_inputOrderType(string s);

bool isAscending(int *arr, int size);

void printUserManual();

void printInvalidCommand();

void generateData();

int *getData(string fileName, int &n);
//---------------------------------------------------------------------------------------------
void mergeSortRunTime(int *&a, int n);               // Ascending order
void mergeSortCntComp(int *&a, int n, int &cntComp); // Ascending order

void quickSortRunTime(int *&a, int l, int r);               // Ascending order
void quickSortCntComp(int *&a, int l, int r, int &cntComp); // Ascending order

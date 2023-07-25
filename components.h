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
const string data_order[4] = {"Randomize", "Sorted", "Reverse", "Nearly Sorted"};

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

//---------------------------------------------------------------------------------------------
void mergeSortRunTime(int *&a, int n);               // Ascending order
void mergeSortCntComp(int *&a, int n, int &cntComp); // Ascending order

void quickSortRunTime(int *&a, int l, int r);               // Ascending order
void quickSortCntComp(int *&a, int l, int r, int &cntComp); // Ascending order
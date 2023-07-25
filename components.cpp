#include "components.h"

unsigned int convert_string_to_num(string s)
{
    unsigned int num = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num = num * 10 + (s[i] - '0');
        else
        {
            return 0;
        }
    }
    return num;
}

int convert_string_to_outputType(string s)
{
    for (int i = 0; i < 3; i++)
        if (s == outputParameter[i])
            return i;
    return -1;
}

bool isFileExist(string fileName)
{
    ifstream infile(fileName);
    bool check = infile.good();
    infile.close();
    return check;
}

int convert_string_to_inputOrderType(string s)
{
    for (int i = 0; i < 4; i++)
        if (dataOrder[i] == s)
            return i;
    return -1;
}

bool isAscending(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

void printUserManual()
{
    cout << "---------------------------------------------------------------\n\n";
    cout << "COMMAND LINE ARGUMENTS\n\n";
    cout << "Command 1: Run a sorting algorithm on the given input data\n"
         << "Prototype : [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]\n\n"
         << "Ex : a.exe -a radix-sort input.txt -both\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "Command 2: Run a sorting algorithm on the generated input data\n"
         << "Prototype : [Execution file] -a [Algorithm] [Data size] [Input order] [Output parameter(s)]\n\n"
         << "Ex : a.exe -a radix-sort 1000 -rand -both\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "Command 3: Run a sorting algorithm on the generated input data\n"
         << "Prototype : [Execution file] -a [Algorithm] [Data size] [Output parameter(s)]\n"
         << "Ex : a.exe -a radix-sort 1000 -both\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "Command 4: Compare two sorting algorithms on the given input data\n"
         << "Prototype : [Execution file] -a [Algorithm 1] [Algorithm 2] [Given input]\n"
         << "Ex : a.exe -a radix-sort insertion-sort input.txt\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "Command 5: Compare two sorting algorithms on the generated input data\n"
         << "Prototype : [Execution file] -a [Algorithm 1] [Algorithm 2] [Data size] [Input order]\n"
         << "Ex : a.exe -a radix-sort insertion-sort 1000 -rand\n\n";
    cout << "---------------------------------------------------------------\n";
    cout << "---------------------------------------------------------------\n";
    cout << "INPUT ARGUMENTS: The following arguments are applied for both modes.\n\n";
    cout << "1. Mode:\n"
         << "-a : Algorithm mode\n"
         << "-c : Comparison mode\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "2: Algorithm name: Lowercase, words are connected by \"-\":\n";
    for (int i = 0; i < 11; i++)
        cout << "+ " << sortName[i] << "\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "3. Input size: an integer number <= 1,000,000\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "4. Input order: Lowercase, words are connected by \"-\":\n";
    cout << "+ rand : randomized data\n"
         << "+ nsorted : nearly sorted data\n"
         << "+ sorted : sorted data\n"
         << "+ rev : reverse sorted data\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "5. Output parameter(s): Lowercase, words are connected by \"-\" :\n";
    cout << "+ time : algorithms's running time.\n"
         << "+ comp : number of comparisions.\n"
         << "+ both : both above options.\n\n";
    cout << "---------------------------------------------------------------\n\n";
    cout << "6. Given input(file): Path to the input file. The file format is as follows:\n"
         << "+ 1st line : an integer n, indicating the number of elements in the input data\n"
         << "+ 2nd line : n integers, separated by a single space.\n\n";
    cout << "---------------------------------------------------------------\n\n";
}

void printInvalidCommand()
{
    cout << "Please type \"sort.exe -help\" for help.\n";
}

void mergeSortRunTime(int *&a, int n)
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

    mergeSortRunTime(la, ln);
    mergeSortRunTime(ra, rn);

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

void quickSortRunTime(int *&a, int l, int r)
{
    if (l >= r)
        return;

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

    quickSortRunTime(a, i, r);
    quickSortRunTime(a, l, j);
}

void quickSortCntComp(int *&a, int l, int r, int &cntComp)
{
    if (l >= r)
        return;

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

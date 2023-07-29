#include "sort.h"
#include "heap.h"
#include "DataGenerator.h"

Sort::Sort(int *arr, unsigned int size)
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

unsigned long long int Sort::getRunningTime()
{
    return runTime;
}

unsigned long long int Sort::getComparison()
{
    return comparison;
}

void Sort::setArr(int *arr, int size)
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

int Sort::run(int argc, char *argv[])
{
    if (argc == 1)
    {
        experiment();
        return 0;
    }
    else if (argc == 2)
        if (string(argv[1]) == "-help")
        {
            printUserManual();
            return 2;
        }
        else
        {
            cout << "Invalid command!" << endl;
            printInvalidCommand();
            return 1;
        }
    else if (argc == 5)
    {
        if (string(argv[1]) == "-a")
        {
            int sortType = this->type(string(argv[2]));
            if (sortType == 0)
            {
                cout << "Invalid sort name!" << endl;
                printInvalidCommand();
                return 1;
            }
            // ------------------------------------------------------------
            int outputType = convert_string_to_outputType(string(argv[4]));
            if (outputType == -1)
            {
                cout << "Invalid output type!" << endl;
                printInvalidCommand();
                return 1;
            }
            // ------------------------------------------------------------
            string filename = string(argv[3]);
            if (isFileExist(filename))
            {
                return command1(sortType, filename, outputType);
                /* Prototype: [Execution file] - a[Algorithm][Given input][Output parameter(s)]
                Ex : a.exe - a radix - sort input.txt - both*/
            }
            unsigned int arrSize = convert_string_to_num(string(argv[3]));
            if (arrSize == 0)
            {
                cout << "Invalid size! Pls input a positive integer" << endl;
                printInvalidCommand();
                return 1;
            }
            // ------------------------------------------------------------
            return command3(sortType, arrSize, outputType);
            /*Prototype: [Execution file] - a[Algorithm][Input size][Output parameter(s)]
            Ex : a.exe - a binary - insertion - sort 70000 - comp*/
        }

        else if (string(argv[1]) == "-c")
        {
            int sortType1 = this->type(string(argv[2]));
            int sortType2 = this->type(string(argv[3]));
            if (sortType1 == 0 || sortType2 == 0 || sortType1 == sortType2)
            {
                cout << "Invalid sort name!" << endl;
                printInvalidCommand();
                return 4;
            }
            // ------------------------------------------------------------
            string filename = string(argv[4]);
            if (isFileExist(filename))
            {
                return command4(sortType1, sortType2, filename);
            }
            else
            {
                cout << "Invalid file name!" << endl;
                printInvalidCommand();
                return 4;
            }
        }

        /*Prototype: [Execution file] - c[Algorithm 1][Algorithm 2][Given input]
        Ex : a.exe - c heap - sort merge - sort input.txt*/
    }
    else if (argc == 6)
    {
        if (string(argv[1]) == "-a")
        {
            int sortType = this->type(string(argv[2]));
            if (sortType == 0)
            {
                cout << "Invalid sort name!" << endl;
                printInvalidCommand();
                return 2;
            }
            // ------------------------------------------------------------
            int outputType = convert_string_to_outputType(string(argv[5]));
            if (outputType == -1)
            {
                cout << "Invalid output type!" << endl;
                printInvalidCommand();
                return 2;
            }
            // ------------------------------------------------------------
            unsigned int arrSize = convert_string_to_num(string(argv[3]));
            if (arrSize == 0)
            {
                cout << "Invalid size! Pls input a positive integer" << endl;
                printInvalidCommand();
                return 2;
            }
            // ------------------------------------------------------------
            int inputOrder = convert_string_to_inputOrderType(string(argv[4]));
            if (inputOrder == -1)
            {
                cout << "Invalid input order!" << endl;
                printInvalidCommand();
                return 2;
            }
            return command2(sortType, arrSize, inputOrder, outputType);
        }
        else if (string(argv[1]) == "-c")
        {
            int sortType1 = this->type(string(argv[2]));
            int sortType2 = this->type(string(argv[3]));
            if (sortType1 == 0 || sortType2 == 0 || sortType1 == sortType2)
            {
                cout << "Invalid sort name!" << endl;
                printInvalidCommand();
                return 5;
            }
            // ------------------------------------------------------------
            unsigned int arrSize = convert_string_to_num(string(argv[4]));
            if (arrSize == 0)
            {
                cout << "Invalid size! Pls input a positive integer" << endl;
                printInvalidCommand();
                return 5;
            }
            // ------------------------------------------------------------
            int inputOrder = convert_string_to_inputOrderType(string(argv[5]));
            if (inputOrder == -1)
            {
                cout << "Invalid data order!" << endl;
                printInvalidCommand();
                return 5;
            }
            return command5(sortType1, sortType2, arrSize, inputOrder);
        }
        // command2();
        /*Prototype: [Execution file] - a[Algorithm][Input size][Input order]
        [Output parameter(s)]
        Ex : a.exe - a selection - sort 50 - rand - time*/

        // command5();
        /*Prototype: [Execution file] - c[Algorithm 1][Algorithm 2][Input size]
        [Input order]
        Ex : a.exe - c quick - sort merge - sort 100000 - nsorted*/
    }
    return -1;
}

void Sort::experiment()
{
    int *a = nullptr;
    ofstream ofs("data.csv");
    ofs << "DataOrder,DataSize,SortName,Comparison,RunTime" << endl;
    cout << "DataOrder,DataSize,SortName,Comparison,RunTime" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 11; k++)
            {
                a = new int[dataSize[j]];
                GenerateData(a, dataSize[j], i);
                setArr(a, dataSize[j]);
                sort(k + 1);
                unsigned long long comparison = getComparison();
                unsigned long long runTime = getRunningTime();
                ofs << data_order[i] << "," << dataSize[j] << "," << sortName[k] << "," << comparison << "," << runTime << endl;
                cout << data_order[i] << "," << dataSize[j] << "," << sortName[k] << "," << comparison << "," << runTime << endl;
                reset();
            }
        }
    }
    ofs.close();
}

void Sort::experiment_2()
{
    int *a = nullptr;
    ofstream ofs("data_2.csv");
    for (int i = 0; i < 4; i++)
    {
        cout << "Data order," << data_order[i] << endl;
        ofs << "Data order," << data_order[i] << endl;
        cout << "Sort name,Comp1,Run1,Comp2,Run2,Comp3,Run3,Comp4,Run4,Comp5,Run5,Comp6,Run6" << endl;
        ofs << "Sort name,Comp1,Run1,Comp2,Run2,Comp3,Run3,Comp4,Run4,Comp5,Run5,Comp6,Run6" << endl;
        for (int j = 0; j < 11; j++)
        {
            cout << sortName[j] << ",";
            ofs << sortName[j] << ",";
            for (int k = 0; k < 6; k++)
            {
                string filename = "Data/" + data_order[i] + "_" + to_string(dataSize[k]) + ".txt";
                int n;
                a = getData(filename, n);
                setArr(a, dataSize[k]);
                sort(j + 1);
                unsigned long long comparison = getComparison();
                unsigned long long runTime = getRunningTime();
                cout << comparison << "," << runTime << ",";
                ofs << comparison << "," << runTime << ",";
                reset();
            }
            cout << endl;
            ofs << endl;
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

void Sort::selectionSort_runTime(int *arr, int size)
{
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

void Sort::selectionSort_comparison(int *arr, int size)
{
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

void Sort::insertionSort_comparison(int *arr, int size)
{
    int key, j;
    for (int i = 1; ++this->comparison && i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (++this->comparison && j >= 0 && ++this->comparison && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void Sort::insertionSort_runTime(int *arr, int size)
{
    int key, j;
    for (int i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void Sort::bubbleSort_runTime(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        // Push the biggest value to the right of the array
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void Sort::bubbleSort_comparison(int *arr, int size)
{
    for (int i = 0; ++(this->comparison) && i < size - 1; i++)
    {
        // Push the biggest value to the right of the array
        for (int j = 0; ++(this->comparison) && j < size - 1 - i; j++)
        {
            if (++(this->comparison) && (arr[j] > arr[j + 1]))
                swap(arr[j], arr[j + 1]);
        }
    }
}

void Sort::shakerSort_runTime(int *arr, int size)
{
    int left, right, k, i;
    left = 0;
    right = size - 1;
    k = size - 1;

    while (left < right)
    {
        // Start from the right side of the array
        for (i = right; i > left; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                k = i;
            }
        }
        left = k;
        // Then from the left side of the array
        for (i = left; i < right; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                k = i;
            }
        }
        right = k;
    }
}

void Sort::shakerSort_comparison(int *arr, int size)
{
    int left, right, k, i;
    left = 0;
    right = size - 1;
    k = size - 1;

    while (++(this->comparison) && left < right)
    {
        for (i = right; ++(this->comparison) && i > left; i--)
        {
            if (++(this->comparison) && arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                k = i;
            }
        }
        left = k;
        for (i = left; ++(this->comparison) && i < right; i++)
        {
            if (++(this->comparison) && arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                k = i;
            }
        }
        right = k;
    }
}

void Sort::shellSort_runTime(int *arr, int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            int temp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return;
}

void Sort::shellSort_comparison(int *arr, int size)
{
    for (int gap = size / 2; ++this->comparison && gap > 0; gap /= 2)
    {
        for (int i = gap; ++this->comparison && i < size; i++)
        {
            int temp = arr[i];

            int j;
            for (j = i; ++this->comparison && j >= gap && ++this->comparison && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return;
}

void Sort::heapSort_runTime(int *arr, int n)
{
    IntHeap h(n);
    h.init(arr, n);
    h.sort(0, n - 1, 0);
    h.clear();
}

void Sort::heapSort_comparison(int *arr, int n)
{
    IntHeap h(n);
    h.init(arr, n);
    h.sort(0, n - 1, 1);
    this->comparison = h.getCntComp();
    h.clear();
}

void Sort::mergeSort_runTime(int *arr, int n)
{
    mergeSortRunTime(arr, n);
}

void Sort::mergeSort_comparison(int *arr, int n)
{
    int cntComp = 0;
    mergeSortCntComp(arr, n, cntComp);
    this->comparison = cntComp;
}

void Sort::quickSort_runTime(int *arr, int n)
{
    quickSortRunTime(arr, 0, n - 1);
}

void Sort::quickSort_comparison(int *arr, int n)
{
    int cntComp = 0;
    quickSortCntComp(arr, 0, n - 1, cntComp);
    this->comparison = cntComp;
}

void Sort::countingSort_runTime(int *arr, int size)
{
    int *output = new int[size];
    int max = arr[0];
    int min = arr[0];

    int i;
    for (i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        else if (arr[i] < min)
            min = arr[i];
    }

    int k = max - min + 1;
    int *count_array = new int[k];

    for (i = 0; i < k; i++)
    {
        count_array[i] = 0;
    }

    for (i = 0; i < size; i++)
    {
        count_array[arr[i] - min]++;
    }

    for (i = 1; i < k; i++)
    {
        count_array[i] += count_array[i - 1];
    }

    for (i = 0; i < size; i++)
    {
        output[count_array[arr[i] - min] - 1] = arr[i];
        count_array[arr[i] - min]--;
    }

    for (i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }

    delete[] output;
    delete[] count_array;
}

void Sort::countingSort_comparison(int *arr, int size)
{
    int *output = new int[size];
    int max = arr[0];
    int min = arr[0];

    int i;
    for (i = 1; ++this->comparison && i < size; i++)
    {
        if (++this->comparison && arr[i] > max)
            max = arr[i];
        else if (++this->comparison && arr[i] < min)
            min = arr[i];
    }

    int k = max - min + 1;
    int *count_array = new int[k];

    for (i = 0; ++this->comparison && i < k; i++)
    {
        count_array[i] = 0;
    }

    for (i = 0; ++this->comparison && i < size; i++)
    {
        count_array[arr[i] - min]++;
    }

    for (i = 1; ++this->comparison && i < k; i++)
    {
        count_array[i] += count_array[i - 1];
    }

    for (i = 0; ++this->comparison && i < size; i++)
    {
        output[count_array[arr[i] - min] - 1] = arr[i];
        count_array[arr[i] - min]--;
    }

    for (i = 0; ++this->comparison && i < size; i++)
    {
        arr[i] = output[i];
    }

    delete[] output;
    delete[] count_array;
}

void Sort::radixSort_runTime(int *arr, int size)
{
    // Find the maximum number to know the number of digits
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    // Create an array saving temporary data of array arr[]
    int *temp = new int[size];

    // exp is 10^i where i is current digit number
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        int i, count[10] = {0};

        // Store the number of occurrences in count[]
        for (i = 0; i < size; i++)
            count[(arr[i] / exp) % 10]++;

        // Change count[i] so that count[i] now contains the actual position of this digit in temp[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Build the temp array
        for (i = size - 1; i >= 0; i--)
        {
            temp[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the temp array to arr[], so that arr[] now contains sorted numbers according to current digit
        for (i = 0; i < size; i++)
            arr[i] = temp[i];
    }

    delete[] temp;
}

void Sort::radixSort_comparison(int *arr, int size)
{
    // Find the maximum number to know the number of digits
    int max = arr[0];
    for (int i = 1; ++(this->comparison) && (i < size); i++)
    {
        if (++(this->comparison) && arr[i] > max)
            max = arr[i];
    }

    // Create an array saving temporary data of array arr[]
    int *temp = new int[size];

    // exp is 10^i where i is current digit number
    for (int exp = 1; ++(this->comparison) && max / exp > 0; exp *= 10)
    {
        int i, count[10] = {0};

        // Store the number of occurrences in count[]
        for (i = 0; ++(this->comparison) && (i < size); i++)
            count[(arr[i] / exp) % 10]++;

        // Change count[i] so that count[i] now contains the actual position of this digit in temp[]
        for (i = 1; ++(this->comparison) && (i < 10); i++)
            count[i] += count[i - 1];

        // Build the temp array
        for (i = size - 1; ++(this->comparison) && (i >= 0); i--)
        {
            temp[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the temp array to arr[], so that arr[] now contains sorted numbers according to current digit
        for (i = 0; ++(this->comparison) && (i < size); i++)
            arr[i] = temp[i];
    }

    delete[] temp;
}

void Sort::flashSort_runTime(int *arr, int size)
{
    int minVal = arr[0];
    int max = 0;
    int m = int(0.45 * size);
    int *l = new int[m];
    for (int i = 0; i < m; i++)
    {
        l[i] = 0;
    }
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < minVal)
            minVal = arr[i];
        if (arr[i] > arr[max])
            max = i;
    }
    if (arr[max] == minVal)
    {
        return;
    }
    double c1 = (double)(m - 1) / (arr[max] - minVal);
    for (int i = 0; i < size; i++)
    {
        int k = int(c1 * (arr[i] - minVal));
        ++l[k];
    }
    for (int i = 1; i < m; i++)
    {
        l[i] += l[i - 1];
    }

    swap(arr[max], arr[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < size - 1)
    {
        while (j > l[k] - 1)
        {
            j++;
            k = int(c1 * (arr[j] - minVal));
        }

        flash = arr[j];
        if (k < 0)
            break;

        while (j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = arr[t = --l[k]];
            arr[t] = flash;
            flash = hold;
            ++nmove;
        }
    }

    delete[] l;
    insertionSort_runTime(arr, size);
}

void Sort::flashSort_comparison(int *arr, int size)
{
    int minVal = arr[0];
    int max = 0;
    int m = int(0.45 * size);
    int *l = new int[m];

    for (int i = 0; ++this->comparison && i < m; i++)
    {
        l[i] = 0;
    }
    for (int i = 1; ++this->comparison && i < size; i++)
    {
        if (++this->comparison && arr[i] < minVal)
            minVal = arr[i];
        if (++this->comparison && arr[i] > arr[max])
            max = i;
    }

    if (++this->comparison && arr[max] == minVal)
        return;

    double c1 = (double)(m - 1) / (arr[max] - minVal);

    for (int i = 0; ++this->comparison && i < size; i++)
    {
        int k = int(c1 * (arr[i] - minVal));
        ++l[k];
    }
    for (int i = 1; ++this->comparison && i < m; i++)
    {
        l[i] += l[i - 1];
    }

    swap(arr[max], arr[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;

    while (++this->comparison && nmove < size - 1)
    {

        while (++this->comparison && j > l[k] - 1)
        {
            j++;
            k = int(c1 * (arr[j] - minVal));
        }

        flash = arr[j];
        if (++this->comparison && k < 0)
            break;

        while (++this->comparison && j != l[k])
        {
            k = int(c1 * (flash - minVal));
            int hold = arr[t = --l[k]];
            arr[t] = flash;
            flash = hold;
            ++nmove;
        }
    }

    delete[] l;
    insertionSort_comparison(arr, size);
}

void Sort::selectionSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    selectionSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    selectionSort_comparison(this->arr, this->size);
    return;
}

void Sort::insertionSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    insertionSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    insertionSort_comparison(this->arr, this->size);
    return;
}

void Sort::bubbleSort()
{
    // Create a copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];

    // Calculate the amount of running time
    auto start = chrono::high_resolution_clock::now();
    bubbleSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate the number of comparisons
    bubbleSort_comparison(this->arr, this->size);
    return;
}

void Sort::shakerSort()
{
    // Create a copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];

    // Calculate the amount of running time
    auto start = chrono::high_resolution_clock::now();
    shakerSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate the number of comparisons
    shakerSort_comparison(this->arr, this->size);
    return;
}

void Sort::shellSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    shellSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    shellSort_comparison(this->arr, this->size);

    return;
}

void Sort::heapSort()
{
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    heapSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    heapSort_comparison(this->arr, this->size);
}

void Sort::mergeSort()
{
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    mergeSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    mergeSort_comparison(this->arr, this->size);
}

void Sort::quickSort()
{
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    quickSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    quickSort_comparison(this->arr, this->size);
}

void Sort::countingSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }

    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    countingSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    countingSort_comparison(this->arr, this->size);

    return;
}

void Sort::radixSort()
{
    // Create a copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];

    // Calculate the amount of running time
    auto start = chrono::high_resolution_clock::now();
    radixSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate the number of comparisons
    radixSort_comparison(this->arr, this->size);
    return;
}

void Sort::flashSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
    {
        copyArr[i] = this->arr[i];
    }
    // Calculate running time
    auto start = chrono::high_resolution_clock::now();
    flashSort_runTime(this->arr, this->size);
    auto end = chrono::high_resolution_clock::now();
    this->runTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Reset array
    setArr(copyArr, this->size);

    // Calculate comparison
    flashSort_comparison(this->arr, this->size);

    return;
}

int Sort::command1(int sortType, string filename, int outputType)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return 1;
    }
    ifs >> this->size;
    this->arr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        ifs >> this->arr[i];
    ifs.close();
    sort(sortType);
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << sortName[sortType - 1] << endl;
    cout << "Input file: " << filename << endl;
    cout << "Input size: " << this->size << endl;
    cout << "-----------------------------------\n";
    printOutput(outputType);
    cout << endl;
    writeArrayToFile("output.txt");
    reset();
    return 1;
}

int Sort::command2(int sortType, unsigned int arrSize, int inputOrder, int outputType)
{
    int *arr = new int[arrSize];
    GenerateData(arr, arrSize, inputOrder);
    writeArrayToFile("input.txt");
    setArr(arr, arrSize);
    sort(sortType);
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << sortName[sortType - 1] << endl;
    cout << "Input size: " << this->size << endl;
    cout << "Input order: " << data_order[inputOrder] << endl;
    cout << "-----------------------------------\n";
    printOutput(outputType);
    cout << endl;
    writeArrayToFile("output.txt");
    reset();
    return 1;
}

int Sort::command3(int sortType, unsigned int arrSize, int outputType)
{
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << sortName[sortType - 1] << endl;
    cout << "Input size: " << arrSize << endl;

    for (int i = 0; i < 4; i++)
    {
        string filename = "input_" + to_string(i + 1) + ".txt";
        int *arr = new int[arrSize];
        GenerateData(arr, arrSize, i);
        setArr(arr, arrSize);
        writeArrayToFile(filename);
        sort(sortType);
        cout << endl;
        cout << "Input order: " << data_order[i] << endl;
        cout << "-----------------------------------\n";
        printOutput(outputType);
        reset();
    }
    return 3;
}

int Sort::command4(int sortType1, int sortType2, string filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return 1;
    }
    ifs >> this->size;
    this->arr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        ifs >> this->arr[i];
    unsigned int size = this->size;
    int *copyArr = new int[size];
    for (int i = 0; i < size; i++)
        copyArr[i] = this->arr[i];
    ifs.close();
    sort(sortType1);
    unsigned long long int runTime1 = this->runTime;
    unsigned long long int comparison1 = this->comparison;
    reset();
    setArr(copyArr, size);
    sort(sortType2);
    unsigned long long int runTime2 = this->runTime;
    unsigned long long int comparison2 = this->comparison;
    reset();
    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << sortName[sortType1 - 1] << " | " << sortName[sortType2 - 1] << endl;
    cout << "Input file: " << filename << endl;
    cout << "Input size: " << size << endl;
    cout << "----------------------------\n";
    cout << "Running time: " << sortName[sortType1 - 1] << " Time " << runTime1 << " | "
         << sortName[sortType2 - 1] << " Time " << runTime2 << endl;
    cout << "Comparison: " << sortName[sortType1 - 1] << " Comp " << comparison1 << " | "
         << sortName[sortType2 - 1] << " Comp " << comparison2 << endl;
    cout << endl;
    return 4;
}

int Sort::command5(int sortType1, int sortType2, unsigned int arrSize, int inputOrder)
{
    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << sortName[sortType1 - 1] << " | " << sortName[sortType2 - 1] << endl;
    cout << "Input size: " << arrSize << endl;
    cout << "Input order: " << data_order[inputOrder] << endl;
    cout << "----------------------------------------\n";
    int *arr = new int[arrSize];
    GenerateData(arr, arrSize, inputOrder);
    setArr(arr, arrSize);
    writeArrayToFile("input.txt");
    int *copyArr = new int[arrSize];
    for (int i = 0; i < arrSize; i++)
        copyArr[i] = this->arr[i];
    sort(sortType1);
    unsigned long long int runTime1 = this->runTime;
    unsigned long long int comparison1 = this->comparison;
    reset();
    setArr(copyArr, arrSize);
    sort(sortType2);
    unsigned long long int runTime2 = this->runTime;
    unsigned long long int comparison2 = this->comparison;
    reset();
    cout << "Running time: " << sortName[sortType1 - 1] << " Time " << runTime1 << " | "
         << sortName[sortType2 - 1] << " Time " << runTime2 << endl;
    cout << "Comparison: " << sortName[sortType1 - 1] << " Comp " << comparison1 << " | "
         << sortName[sortType2 - 1] << " Comp " << comparison2 << endl;
    cout << endl;
    return 5;
}

void Sort::writeArrayToFile(string filename)
{
    ofstream ofs(filename);
    ofs << this->size << endl;
    for (int i = 0; i < this->size; i++)
        ofs << this->arr[i] << " ";
    ofs.close();
}

void Sort::printOutput(int outputType)
{
    if (outputType == 0)
    {
        cout << "Running time: " << this->runTime << " ms" << endl;
    }
    else if (outputType == 1)
    {
        cout << "Comparison: " << this->comparison << endl;
    }
    else if (outputType == 2)
    {
        cout << "Running time: " << this->runTime << " ms" << endl;
        cout << "Comparison: " << this->comparison << endl;
    }
}

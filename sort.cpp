#include "sort.h"

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
            for (int k = 0; k < 2; k++)
            {
                a = new int[dataSize[j]];
                GenerateData(a, dataSize[j], i);
                setArr(a, dataSize[j]);
                sort(k + 1);
                unsigned long long comparison = getComparison();
                unsigned long long runTime = getRunningTime();
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


void Sort::shellSort_runTime(int *arr, int size)
{
    for (int gap = size/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            int temp = arr[i];

            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return;
}

void Sort::shellSort_comparison(int *arr, int size)
{
    for (int gap = size/2; ++this->comparison && gap > 0; gap /= 2)
    {
        for (int i = gap; ++this->comparison && i < size; i++)
        {
            int temp = arr[i];

            int j;            
            for (j = i; ++this->comparison && j >= gap && ++this->comparison && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return;
}

void Sort::countingSort_runTime(int *arr, int size)
{
    int *output = new int[size];
    int max = arr[0];
    int min = arr[0];

	int i;
    for (i = 1; i < size; i++)
    {
        if(arr[i] > max)
            max = arr[i];
        else if(arr[i] < min)
            min = arr[i];
    }

    int k = max - min + 1; 
    int *count_array = new int[k];
    
    for (i = 0; i < k; i++) {
        count_array[i] = 0;
    }

    for (i = 0; i < size; i++) {
        count_array[arr[i] - min]++;
    }

    for (i = 1; i < k; i++) {
        count_array[i] += count_array[i-1];
    }

    for (i = 0; i < size; i++) {
        output[count_array[arr[i] - min] - 1] = arr[i];
        count_array[arr[i] - min]--;
    }

    for (i = 0; i < size; i++) {
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
        if(++this->comparison && arr[i] > max)
            max = arr[i];
        else if(++this->comparison && arr[i] < min)
            min = arr[i];
    }

    int k = max - min + 1;
    int *count_array = new int[k];
    
    for (i = 0; ++this->comparison && i < k; i++) {
        count_array[i] = 0;
    }

    for (i = 0; ++this->comparison && i < size; i++) {
        count_array[arr[i] - min]++;
    }

    for (i = 1; ++this->comparison && i < k; i++) {
        count_array[i] += count_array[i-1];
    }

    for (i = 0; ++this->comparison && i < size; i++) {
        output[count_array[arr[i] - min] - 1] = arr[i];
        count_array[arr[i] - min]--;
    }

    for (i = 0; ++this->comparison && i < size; i++) {
        arr[i] = output[i];
    }

    delete[] output;
    delete[] count_array;
}

void Sort::flashSort_runTime(int *arr, int size)
{
    int minVal = arr[0];
	int max = 0;
	int m = int(0.45 * size);
	int *l = new int[m];
	for (int i = 0; i < m; i++) {
		l[i] = 0;
    }
	for (int i = 1; i < size; i++) {
		if (arr[i] < minVal)
			minVal = arr[i];
		if (arr[i] > arr[max])
			max = i;
	}
	if (arr[max] == minVal) {
		return;
    }
	double c1 = (double)(m - 1) / (arr[max] - minVal);
	for (int i = 0; i < size; i++) {
		int k = int(c1 * (arr[i] - minVal));
		++l[k];
	}
	for (int i = 1; i < m; i++) {
		l[i] += l[i - 1];
    }

	swap(arr[max], arr[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < size - 1) {
		while (j > l[k] - 1) {
			j++;
			k = int(c1*(arr[j] - minVal));
		}
		
        flash = arr[j];
		if (k < 0) break;
		
        while (j != l[k]) {
			k = int(c1*(flash - minVal));
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

	for (int i = 0; ++this->comparison && i < m; i++) {
		l[i] = 0;
    }
	for (int i = 1; ++this->comparison && i < size; i++) {
		if (++this->comparison && arr[i] < minVal) minVal = arr[i];
		if (++this->comparison && arr[i] > arr[max]) max = i;
	}

	if (++this->comparison && arr[max] == minVal) return;

	double c1 = (double)(m - 1) / (arr[max] - minVal);

	for (int i = 0; ++this->comparison && i < size; i++) {
		int k = int(c1 * (arr[i] - minVal));
		++l[k];
	}
	for (int i = 1; ++this->comparison && i < m; i++) {
		l[i] += l[i - 1];
    }

	swap(arr[max], arr[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;

	while (++this->comparison && nmove < size - 1) {

		while (++this->comparison && j > l[k] - 1) {
			j++;
			k = int(c1*(arr[j] - minVal));
		}
		
        flash = arr[j];
		if (++this->comparison && k < 0) break;
		
        while (++this->comparison && j != l[k]) {
			k = int(c1*(flash - minVal));
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
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort_runTime(this->arr, this->size);
    auto end = std::chrono::high_resolution_clock::now();
    this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << isAscending(this->arr, this->size) << endl;
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    selectionSort_comparison(this->arr, this->size);
    // cout << isAscending(this->arr, this->size) << endl;
    return;
}

void Sort::insertionSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort_runTime(this->arr, this->size);
    auto end = std::chrono::high_resolution_clock::now();
    this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << isAscending(this->arr, this->size) << endl;
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    insertionSort_comparison(this->arr, this->size);
    // cout << isAscending(this->arr, this->size) << endl;
    return;
}

void Sort::bubbleSort()
{
    return;
}

void Sort::shakerSort()
{
    return;
}

void Sort::shellSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = std::chrono::high_resolution_clock::now();
    shellSort_runTime(this->arr, this->size);
    auto end = std::chrono::high_resolution_clock::now();
    this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << isAscending(this->arr, this->size) << endl;
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    shellSort_comparison(this->arr, this->size);
    // cout << isAscending(this->arr, this->size) << endl;
    return;
}

void Sort::heapSort()
{
    return;
}

void Sort::mergeSort()
{
    return;
}

void Sort::quickSort()
{
    return;
}

void Sort::countingSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = std::chrono::high_resolution_clock::now();
    countingSort_runTime(this->arr, this->size);
    auto end = std::chrono::high_resolution_clock::now();
    this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << isAscending(this->arr, this->size) << endl;
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    countingSort_comparison(this->arr, this->size);
    // cout << isAscending(this->arr, this->size) << endl;
    return;
}

void Sort::radixSort()
{
    return;
}

void Sort::flashSort()
{
    // Create copy array
    int *copyArr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        copyArr[i] = this->arr[i];
    // Calculate running time
    auto start = std::chrono::high_resolution_clock::now();
    flashSort_runTime(this->arr, this->size);
    auto end = std::chrono::high_resolution_clock::now();
    this->runTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << isAscending(this->arr, this->size) << endl;
    // Reset array
    setArr(copyArr, this->size);
    // Calculate comparison
    flashSort_comparison(this->arr, this->size);
    // cout << isAscending(this->arr, this->size) << endl;
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
    writeArrayToFile("input.txt");
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
    return infile.good();
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
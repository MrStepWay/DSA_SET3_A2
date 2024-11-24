#include "SortTester.h"

void insertionSort(std::vector<int>& A, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int tmp = A[i];
        int j = i - 1;
        while (j >= l && A[j] > tmp) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = tmp;
    }
}

void merge(std::vector<int>& A, int l, int m, int r) {
    std::vector<int> leftA(A.begin() + l, A.begin() + m + 1);
    std::vector<int> rightA(A.begin() + m + 1, A.begin() + r + 1);

    size_t leftSize = leftA.size();
    size_t rightSize = rightA.size();

    int i = 0;
    int j = 0;
    int k = l;

    while (i < leftSize && j < rightSize) {
        if (leftA[i] <= rightA[j] ) {
            A[k++] = leftA[i++];
        } else {
            A[k++] = rightA[j++];
        }
    }

    while (i < leftSize) {
        A[k] = leftA[i];
        ++i;
        ++k;
    }
    while (j < rightSize) {
        A[k] = rightA[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int> &A, int l, int r) {
    if (l >= r) {
        return;
    }

    int m = (l + r) / 2;
    mergeSort(A, l, m);
    mergeSort(A, m + 1, r);

    merge(A, l, m, r);
}

void hybridMergeSort(std::vector<int>& A, int l, int r, int thresh = 30) {
    if (r - l + 1 <= thresh) {
        insertionSort(A, l, r);
        return;
    }

    if (l < r) {
        int m = l + (r - l) / 2;

        hybridMergeSort(A, l, m, thresh);
        hybridMergeSort(A, m + 1, r, thresh);

        merge(A, l, m, r);
    }
}

// Тест реализации алгоритма Merge Sort с выделением дополнительной памяти.
// Сортировка случайного массива.
long long SortTester::testMergeSortRandArr(int numElements, int numAttempts, int minValue, int maxValue) {
    long long timeSum = 0;

    for (int i = 0; i < numAttempts; ++i) {
        std::vector<int> testVec = ArrayGenerator::generateRandomArray(numElements, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(testVec, 0, numElements - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}

// Тест реализации алгоритма Merge Sort с выделением дополнительной памяти.
// Сортировка массива, отсортированного по убыванию.
long long SortTester::testMergeSortDescArr(int numElements, int numAttempts, int minValue, int maxValue) {
    long long timeSum = 0;

    for (int i = 0; i < numAttempts; ++i) {
        std::vector<int> testVec = ArrayGenerator::generateDescendingArray(numElements, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(testVec, 0, numElements - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}

// Тест реализации алгоритма Merge Sort с выделением дополнительной памяти.
// Сортировка «почти» отсортированного массива. Количество перестановок - случайное число от 2 до 10.
long long SortTester::testMergeSortSemiSortArr(int numElements, int numAttempts, int minValue, int maxValue) {
    long long timeSum = 0;

    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<size_t> dis(2, 10);
    for (int i = 0; i < numAttempts; ++i) {
        int numSwaps = dis(gen);
        std::vector<int> testVec = ArrayGenerator::generateSemiSortedArray(numElements, numSwaps, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(testVec, 0, numElements - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}

// Тест гибридной реализации алгоритма Merge Sort + Selection Sort.
// Сортировка случайного массива.
long long SortTester::testHybridMergeSortRandArr(int numElements, int numAttempts, int minValue, int maxValue,
                                                 int thresh = 30) {
    long long timeSum = 0;

    for (int i = 0; i < numAttempts; ++i) {
        std::vector<int> testVec = ArrayGenerator::generateRandomArray(numElements, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(testVec, 0, numElements - 1, thresh);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}

// Тест гибридной реализации алгоритма Merge Sort + Selection Sort.
// Сортировка массива, отсортированного по убыванию.
long long SortTester::testHybridMergeSortDescArr(int numElements, int numAttempts, int minValue, int maxValue,
                                                 int thresh = 30) {
    long long timeSum = 0;

    for (int i = 0; i < numAttempts; ++i) {
        std::vector<int> testVec = ArrayGenerator::generateDescendingArray(numElements, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(testVec, 0, numElements - 1, thresh);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}

// Тест гибридной реализации алгоритма Merge Sort + Selection Sort.
// Сортировка «почти» отсортированного массива. Количество перестановок - случайное число от 2 до 10.
long long SortTester::testHybridMergeSortSemiSortArr(int numElements, int numAttempts, int minValue, int maxValue,
                                                     int thresh = 30) {
    long long timeSum = 0;

    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<size_t> dis(2, 10);
    for (int i = 0; i < numAttempts; ++i) {
        int numSwaps = dis(gen);
        std::vector<int> testVec = ArrayGenerator::generateSemiSortedArray(numElements, numSwaps, minValue, maxValue);
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(testVec, 0, numElements - 1, thresh);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        timeSum += msec;
    }

    return timeSum / numAttempts;
}
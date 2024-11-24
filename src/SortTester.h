#ifndef SRC_SORTTESTER_H
#define SRC_SORTTESTER_H

#include <chrono>
#include <vector>
#include <random>
#include "ArrayGenerator.h"

class SortTester {
 private:

 public:
    static long long testMergeSortRandArr(int numElements, int numAttempts, int minValue, int maxValue);
    static long long testMergeSortDescArr(int numElements, int numAttempts, int minValue, int maxValue);
    static long long testMergeSortSemiSortArr(int numElements, int numAttempts, int minValue, int maxValue);

    static long long testHybridMergeSortRandArr(int numElements, int numAttempts, int minValue, int maxValue, int thresh);
    static long long testHybridMergeSortDescArr(int numElements, int numAttempts, int minValue, int maxValue, int thresh);
    static long long testHybridMergeSortSemiSortArr(int numElements, int numAttempts, int minValue, int maxValue, int thresh);
};


#endif //SRC_SORTTESTER_H

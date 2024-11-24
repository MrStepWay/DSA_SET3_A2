#ifndef SRC_ARRAYGENERATOR_H
#define SRC_ARRAYGENERATOR_H

#include <vector>

class ArrayGenerator {
 public:
    static std::vector<int> generateRandomArray(size_t size, int minValue, int maxValue);

    static std::vector<int> generateDescendingArray(size_t size, int minValue, int maxValue);

    static std::vector<int> generateSemiSortedArray(size_t size, int swaps, int minValue, int maxValue);

 private:
    static void randomSwaps(std::vector<int>& array, int swaps);
};


#endif //SRC_ARRAYGENERATOR_H

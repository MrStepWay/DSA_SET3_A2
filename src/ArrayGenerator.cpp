#include "ArrayGenerator.h"
#include <algorithm>
#include <random>

std::vector<int> ArrayGenerator::generateRandomArray(size_t size, int minValue, int maxValue) {
    std::vector<int> array(size);
    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<int> dis(minValue, maxValue);

    for (auto& element : array) {
        element = dis(gen);
    }

    return array;
}

std::vector<int> ArrayGenerator::generateDescendingArray(size_t size, int minValue, int maxValue) {
    std::vector<int> array = generateRandomArray(size, minValue, maxValue);
    std::sort(array.begin(), array.end(), std::greater<int>());
    return array;
}

std::vector<int> ArrayGenerator::generateSemiSortedArray(size_t size, int swaps, int minValue, int maxValue) {
    std::vector<int> array = generateRandomArray(size, minValue, maxValue);
    std::sort(array.begin(), array.end());
    randomSwaps(array, swaps);
    return array;
}


void ArrayGenerator::randomSwaps(std::vector<int>& array, int swaps) {
    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<size_t> dis(0, array.size() - 1);

    for (int i = 0; i < swaps; ++i) {
        size_t idx1 = dis(gen);
        size_t idx2 = dis(gen);
        std::swap(array[idx1], array[idx2]);
    }
}

#include <iostream>
#include <vector>
#include <fstream>
#include <format>
#include <string>
#include "SortTester.h"

int main() {
    const int minRandValue = 0;
    const int maxRandValue = 6000;
    const int numAttempts = 10; // 10 попыток на 1 тест для усреднения результата.

    // Тест Merge Sort.
    std::ofstream randArrFile;
    std::ofstream descArrFile;
    std::ofstream semiSortArrFile;
    std::ofstream avgTimeFile;
    randArrFile.open("../../data/MergeSort/random_array_res.txt");
    descArrFile.open("../../data/MergeSort/descending_array_res.txt");
    semiSortArrFile.open("../../data/MergeSort/semisorted_array_res.txt");
    avgTimeFile.open("../../data/MergeSort/avg_time_res.txt");
    for (int numElements = 500; numElements < 10001; numElements += 100) {
        long long resRandArr = SortTester::testMergeSortRandArr(numElements, numAttempts, minRandValue, maxRandValue);
        long long resDescArr = SortTester::testMergeSortDescArr(numElements, numAttempts, minRandValue, maxRandValue);
        long long resSemiSortArr = SortTester::testMergeSortSemiSortArr(numElements, numAttempts, minRandValue, maxRandValue);
        long long avgTime = (resRandArr + resDescArr + resSemiSortArr) / 3;
        randArrFile << numElements << ' ' << resRandArr << '\n';
        descArrFile << numElements << ' ' << resDescArr << '\n';
        semiSortArrFile << numElements << ' ' << resSemiSortArr << '\n';
        avgTimeFile << numElements << ' ' << avgTime << '\n';
    }
    randArrFile.close();
    descArrFile.close();
    semiSortArrFile.close();
    avgTimeFile.close();

    // Тест гибридной реализации Merge Sort + Selection Sort c разным threshold.
    std::vector<int> thresholds{5, 10, 20, 30, 50, 500, 800};
    for (int threshold : thresholds) {
        randArrFile.open(std::format("../../data/HybridMergeSort/threshold_{}/random_array_res.txt", threshold));
        descArrFile.open(std::format("../../data/HybridMergeSort/threshold_{}/descending_array_res.txt", threshold));
        semiSortArrFile.open(std::format("../../data/HybridMergeSort/threshold_{}/semisorted_array_res.txt", threshold));
        avgTimeFile.open(std::format("../../data/HybridMergeSort/threshold_{}/avg_time_res.txt", threshold));
        for (int numElements = 500; numElements < 10001; numElements += 100) {
            long long resRandArr = SortTester::testHybridMergeSortRandArr(numElements, numAttempts, minRandValue, maxRandValue, threshold);
            long long resDescArr = SortTester::testHybridMergeSortDescArr(numElements, numAttempts, minRandValue, maxRandValue, threshold);
            long long resSemiSortArr = SortTester::testHybridMergeSortSemiSortArr(numElements, numAttempts, minRandValue, maxRandValue, threshold);
            long long avgTime = (resRandArr + resDescArr + resSemiSortArr) / 3;
            randArrFile << numElements << ' ' << resRandArr << '\n';
            descArrFile << numElements << ' ' << resDescArr << '\n';
            semiSortArrFile << numElements << ' ' << resSemiSortArr << '\n';
            avgTimeFile << numElements << ' ' << avgTime << '\n';
        }
        randArrFile.close();
        descArrFile.close();
        semiSortArrFile.close();
        avgTimeFile.close();
    }
}

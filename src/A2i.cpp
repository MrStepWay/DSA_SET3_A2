#include <iostream>
#include <vector>

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

void hybridMergeSort(std::vector<int>& A, int l, int r, int thresh = 15) {
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

void printVector(const std::vector<int> &A) {
    size_t n = A.size();
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << ' ';
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    hybridMergeSort(arr, 0, n - 1);
    printVector(arr);
    return 0;
}

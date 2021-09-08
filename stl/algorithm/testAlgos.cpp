#include "algorithm.hpp"
#include <iostream>
#include <algorithm>

bool func(int elem) {
    return elem >= 5;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 6, 7, 8};
    int arr2[6];

    auto k = std_copy::lower_bound(arr, &arr[20], 5);
    std::cout << *k << "\n";
}
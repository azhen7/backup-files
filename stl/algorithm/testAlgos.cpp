#include "algorithm.hpp"
#include <iostream>
#include <algorithm>

bool func(int elem, int elem2) {
    return elem > elem2;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 6, 7, 8};
    int arr2[6];
    int arr3[4] = {4, 5, 6, 7};

    auto k = std::find_first_of(arr, &arr[7], arr3, arr3 + 4);
    std::cout << *k << "\n";
}
#include "algorithm.hpp"
#include <iostream>
#include <algorithm>

bool func(int elem) {
    return elem == 5;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 6, 7, 8};
    int arr2[10];

    std_copy::copy_backward(arr, &arr[9], &arr2[9]);
    for (int i = 0; i < 10; i++) {
        std::cout << arr2[i] << "\n";
    }
}
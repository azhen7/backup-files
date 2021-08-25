#include <iostream>
#include "array.hpp"

int main() {
    std_copy::array<int, 5> t;
    for (int i = 1; i < 5; i++) {
        t.push_back(i * i);
    }
    std_copy::array<int, 5>::iterator it;
}
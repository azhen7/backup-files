#include <iostream>
#include "array.hpp"

int main() {
    std_copy::array<int, 5> t;
    for (int i = 0; i < 5; i++) {
        t.add(i * i);
    }
    std_copy::array<int, 5> it(t);
    for (int i = 0; i < 5; i++) {
        std::cout << it[i] << "\n";
    }
}
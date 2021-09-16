#include <iostream>
#include <vector>
#include "vector.hpp"
#include "algorithm.hpp"

int main() {
    std_copy::vector<int> r(1, 4, 9, 16, 25, 36, 49, 64, 64, 64, 81, 100);
    std_copy::vector<int> ss(r);
    for (int i = 0; i < ss.size(); i++) {
        std::cout << ss[i] << "\n";
    }
}
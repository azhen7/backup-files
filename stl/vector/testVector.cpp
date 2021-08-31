#include <iostream>
#include <vector>
#include "vector.hpp"

int main() {
    std_copy::vector<int> r(1, 4, 9, 16, 25, 36, 49, 64, 81, 100);
    r.erase(1, 3);
    std_copy::vector<int>::iterator it;
    for (it = r.begin(); it != r.end(); it++) {
        std::cout << *it << "\n";
    }
}
#include <iostream>
#include "vector.hpp"

int main() {
    std_copy::vector<int> r;
    for (int i = 1; i < 10; i++) {
        r.push_back(i * i);
    }
    std_copy::vector<int> t(r);
    std_copy::vector<int>::iterator it;
    it = r.begin();

    std_copy::vector<int>::iterator newIt = std_copy::next(it, 4);
    *newIt++;
    std::cout << *newIt << "\n";
}
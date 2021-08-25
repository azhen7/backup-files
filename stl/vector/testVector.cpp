#include <iostream>
#include "vector.hpp"

int main() {
    std_copy::vector<int> r;
    for (int i = 1; i < 10; i++) {
        r.push_back(i * i);
    }
    std_copy::vector<int> t(r);
    std_copy::vector<int>::iterator it;
    for (it = t.begin(); it != t.end(); it++) {
        std::cout << *it << "\n";
    }
}
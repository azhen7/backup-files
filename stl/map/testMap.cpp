#include <iostream>
#include "map.hpp"

int main() {
    std_copy::map<int, char> s;
    s[1] = '4';
    s[1] = '6';
    std::cout << s[1] << "\n";
}
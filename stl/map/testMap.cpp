#include <iostream>
#include "map.hpp"
#include "pair.hpp"
#include <map>

int main() {
    std_copy::map<int, char> rr;
    std_copy::pair<int, char> i(100, '8');
    std_copy::pair<int, char> r(123, '4');
    std_copy::pair<int, char> s(100, '9');
    rr.insert(r);
    rr.insert(i);
    rr.insert_or_assign(s);

    for (std_copy::map<int, char>::iterator it = rr.begin(); it != rr.end(); it++) {
        std::cout << "A " << it->first << " " << it->second << "\n";
    }
}
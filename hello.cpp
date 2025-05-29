#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> names{"John", "Paul", "George", "Ringo"};
    for (std::string const &name : names) {
        std::cout << name << std::endl;
    }
    return 0;
}
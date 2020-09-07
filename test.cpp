#include <iostream>
#include <ctime>

int main() {
    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);
    std::cout << now->tm_hour << "\n";
}

#include <iostream>
#include <cmath>

int
main()
{
    double value = 1.0;
    while ((value + 1.0) != value) value *= 2;
    std::cout << value << std::endl;
}


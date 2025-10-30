#include <iostream>
#include <cstdint>

int
main()
{
    float value = 1.0;
    while (true) {
        int64_t bits = *reinterpret_cast<int64_t*>(&value);
        bits++;
        float next = *reinterpret_cast<double*>(&bits);
        if (next - value >= 1.0) {
            std::cout << value << std::endl;
            break;
        }
        value = next;
    }
}


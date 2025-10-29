#include <iostream>

int
main()
{
    int array[] = {165, 2, 3654, 9, 18765, 2, 165, 9};
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        result ^= array[i];
    }
    const int mask = result & -result;
    int a = 0;
    int b = 0;
    for (int i = 0; i < 8; ++i) {
        if ((array[i] & mask) != 0) {
            a ^= array[i];
            continue;
        }
        b ^= array[i];
    }
    std::cout << "a = " << a << '\n' << "b = " << b << '\n'; 
    return 0;
}


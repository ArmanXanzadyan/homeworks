#include <iostream>

int
main()
{
    int array[] = {1, 2, 3, 4, 0, 4, 3, 2, 1};
    const size_t size = sizeof(array) / sizeof(array[0]);

    int result = 0;
    for (size_t i = 0; i < size; ++i) {
        result ^= array[i];
    }

    std::cout << "Unique number: " << result << std::endl;
    return 0;
}


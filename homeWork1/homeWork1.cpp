#include <iostream>

void print(const int* array, const int size);


int
main()
{
    int array[] = {2, 4, 8, 23, 987, 8, 2, 4, 987};
    return 0;
}

void
print(const int* array, const int size)
{
    for (size_t i = 0; i < size; ++i) {
        std::cout << *(array + i);
    }
}

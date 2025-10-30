#include <iostream>
#include <vector>
#include <algorithm>

void
rotation_left(std::vector<int>& arr, const size_t d)
{
    const size_t n = arr.size();
    if (n == 0 || d == 0 || d == n)
        return;

    std::reverse(arr.begin(), arr.begin() + d);
    std::reverse(arr.begin() + d, arr.end());
    std::reverse(arr.begin(), arr.end());
}

int
main()
{
    size_t n;
    size_t d;
    std::cin >> n >> d;
    d %= n;

    std::vector<int> arr(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    rotation_left(arr, d);

    for (size_t i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }

    std::cout << '\n';
    return 0;
}


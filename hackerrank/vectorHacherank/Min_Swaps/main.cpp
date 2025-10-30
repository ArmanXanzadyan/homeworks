#include <iostream>
#include <vector>
#include <utility>

void
minimumSwaps(std::vector<int> arr)
{
    size_t swaps = 0;
    const size_t n = arr.size();

    for (size_t i = 0; i < n; ++i) {
        while (arr[i] != static_cast<int>(i + 1)) {
            const size_t correctIndex = static_cast<size_t>(arr[i] - 1);
            std::swap(arr[i], arr[correctIndex]);
            ++swaps;
        }
    }

    std::cout << swaps << '\n';
}

int
main()
{
    int n;
    std::cin >> n;

    std::vector<int> queries(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> queries[i];
    }

    minimumSwaps(queries);
    return 0;
}


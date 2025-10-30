#include <iostream>
#include <climits>

int
main()
{
    const int N = 6;
    const int H = 3;
    int a[N][N];
    int mx = INT_MIN;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> a[i][j];
        }
    }
    const int difference = N - H;
    for (int i = 0; i <= difference; ++i)
        for (int j = 0; j <= difference; ++j) {
            const int s = a[i][j] + a[i][j+1] + a[i][j+2]
                        + a[i + 1][j + 1]
                        + a[i + 2][j] + a[i + 2][j + 1] + a[i + 2][j + 2];
            if (s > mx) mx = s;
        }

    std::cout << mx << '\n';
    return 0;
}


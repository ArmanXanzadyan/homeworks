#include <iostream>
#include <vector>

struct Query
{
    int a;
    int b;
    long long k;
};

long long
arrayManipulation(const int n, const std::vector<Query>& queries)
{
    std::vector<long long> diff(n + 2, 0);

    for (const Query& q : queries) {
        diff[q.a] += q.k;
        diff[q.b + 1] -= q.k;
    }

    long long max_val = 0;
    long long current = 0;

    for (int i = 1; i <= n; ++i) {
        current += diff[i];
        if (current > max_val)
            max_val = current;
    }

    return max_val;
}

int
main()
{
    int n;
    int q;
    std::cin >> n >> q;

    std::vector<Query> queries(q);

    for (int i = 0; i < q; ++i) {
        std::cin >> queries[i].a >> queries[i].b >> queries[i].k;
    }

    std::cout << arrayManipulation(n, queries) << '\n';
    return 0;
}


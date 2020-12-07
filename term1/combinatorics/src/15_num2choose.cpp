#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "num2choose"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k, m;
    cin >> n >> k >> m;

    vector<vector<size_t>> c(n, vector<size_t>(n, 1));

    for (size_t i = 2; i < n; ++i) {
        for (size_t j = 1; j < i; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    vector<size_t> v;

    for (size_t i = 0; 0 < k; ++i, --n) {
        if (m < c[n - 1][k - 1]) {
            v.push_back(1 + i);
            --k;
        } else {
            m -= c[n - 1][k - 1];
        }
    }

    for (const auto &e : v) {
        cout << e << ' ';
    }

    return 0;
}

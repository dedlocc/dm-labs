#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "num2brackets2"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    uint64_t k;
    cin >> n >> k;

    n <<= 1u;

    vector<vector<uint64_t>> d(n, vector<uint64_t>(1 + n));
    d[0][0] = 1;
    for (size_t i = 1; i < n; ++i) {
        d[i][0] = d[i - 1][1];
        d[i][n] = d[i - 1][n - 1];
        for (size_t j = 1; j < n; ++j) {
            d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
        }
    }

    stack<bool> b;

    for (size_t i = n - 1; i < n; --i) {
        const auto t1 = d[i][b.size() + 1] << (i - b.size() - 1) / 2;

        if (t1 > k) {
            cout << '(';
            b.push(true);
            continue;
        }

        const auto t2 = !b.empty() && b.top() ? d[i][b.size() - 1] << (i - b.size() + 1) / 2 : 0;

        k -= t1;
        if (t2 > k) {
            cout << ')';
            b.pop();
            continue;
        }

        k -= t2;
        if (t1 > k) {
            cout << '[';
            b.push(false);
        } else {
            k -= t1;
            cout << ']';
            b.pop();
        }
    }

    return 0;
}

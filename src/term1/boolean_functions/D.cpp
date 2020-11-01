#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    const size_t m = 1u << n;

    stringstream res;

    for (size_t i = 1; i <= n; ++i) {
        res << "1 " << i << '\n';
    }

    size_t cnt = 2 * n;
    size_t p = cnt + n - 1;

    for (size_t i = 0; i < m; ++i) {
        unsigned t;
        bool f;
        cin >> t >> f;
        if (f) {
            size_t prev = 0 == (i & 1u) ? 2 * n : n;
            for (size_t j = 1; j < n; ++j) {
                res << "2 " << prev << ' ' << (0 == (i & 1u << j) ? 2 * n - j : n - j) << '\n';
                prev = ++cnt;
            }
        }
        if (cnt > p) {
            res << "3 " << p << ' ' << cnt << '\n';
            p = ++cnt;
        }
    }

    if (cnt == 2 * n) {
        cout << n + 2 << "\n1 1\n2 1 " << n + 1 << '\n'<< endl;
    } else {
        cout << cnt << '\n' << res.str();
    }

    return 0;
}

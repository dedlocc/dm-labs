#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextmultiperm"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<size_t> v(n);

    for (auto &e : v) {
        cin >> e;
    }

    size_t i = n - 2;
    while (i < n && v[i] >= v[i + 1]) {
        --i;
    }

    if (i > n) {
        fill(v.begin(), v.end(), 0);
    } else {
        size_t j = i + 2;
        while (j < n && v[i] < v[j]) {
            ++j;
        }
        swap(v[i], v[j - 1]);
        reverse(v.begin() + i + 1, v.end());
    }

    for (const auto &e : v) {
        cout << e << ' ';
    }

    return 0;
}

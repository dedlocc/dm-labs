#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "permutations"
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

    iota(v.begin(), v.end(), 1);

    do {
        for (const auto &e : v) {
            cout << e << ' ';
        }
        cout << '\n';
    } while (next_permutation(v.begin(), v.end()));

    return 0;
}
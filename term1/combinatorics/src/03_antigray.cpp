#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "antigray"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<uint16_t> &v, const size_t &p)
{
    if (p == v.size()) {
        for (size_t i = 0; i < 3; ++i) {
            for (const auto &e : v) {
                cout << (e + i) % 3;
            }
            cout << '\n';
        }
        return;
    }

    v[p] = 0;
    foo(v, 1 + p);

    v[p] = 1;
    foo(v, 1 + p);

    v[p] = 2;
    foo(v, 1 + p);
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<uint16_t> v(n);
    foo(v, 1);

    return 0;
}

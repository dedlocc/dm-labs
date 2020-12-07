#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "brackets"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<bool> &v, const size_t &p = 0, const size_t &balance = 0, const size_t &open = 0)
{
    if (p == v.size()) {
        for (const auto &b : v) {
            cout << (b ? '(' : ')');
        }
        cout << '\n';
        return;
    }

    if (open << 1u < v.size()) {
        v[p] = true;
        foo(v, 1 + p, 1 + balance, 1 + open);
    }

    if (0 < balance) {
        v[p] = false;
        foo(v, 1 + p, balance - 1, open);
    }

}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<bool> v(n << 1u);
    foo(v);

    return 0;
}

#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "partition"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<size_t> &v, const size_t &p)
{
    if (0 == p) {
        cout << v.front();
        for (size_t i = 1; i < v.size(); ++i) {
            cout << '+' << v[i];
        }
        cout << '\n';
        return;
    }

    for (size_t i = 1; i <= p; ++i) {
        if (v.empty() || v.back() <= i) {
            v.push_back(i);
            foo(v, p - i);
            v.pop_back();
        }
    }
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<size_t> v;

    foo(v, n);

    return 0;
}

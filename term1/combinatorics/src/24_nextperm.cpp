#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextperm"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void output(const vector<size_t> &v)
{
    for (const auto &e : v) {
        cout << e << ' ';
    }
    cout << '\n';
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<size_t> v(n);

    for (auto &e : v) {
        cin >> e;
    }

    vector<size_t> u = v;
    const vector<size_t> zeros(n, 0);

    output(prev_permutation(v.begin(), v.end()) ? v : zeros);
    output(next_permutation(u.begin(), u.end()) ? u : zeros);

    return 0;
}
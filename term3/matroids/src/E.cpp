#include <iostream>
#include <unordered_set>
#include <vector>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "cycles"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, m;
    cin >> n >> m;

    vector<size_t> w(n);
    unordered_set<size_t> a;

    for (size_t i = 0; i < n; ++i) {
        cin >> w[i];
        a.insert(i);
    }

    for (size_t i = 0; i < m; ++i) {
        size_t k;
        cin >> k;
        size_t minElement;
        cin >> minElement;
        --minElement;
        for (size_t j = 1; j < k; ++j) {
            size_t t;
            cin >> t;
            if (w[--t] < w[minElement]) {
                minElement = t;
            }
        }
        a.erase(minElement);
    }

    size_t ans = 0;
    for (auto i : a) {
        ans += w[i];
    }
    cout << ans;

    return 0;
}
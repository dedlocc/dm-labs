#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

constexpr int64_t MOD = 1'000'000'007;

int main()
{
    size_t k, m;
    cin >> k >> m;

    map<size_t, int64_t> a;
    for (size_t i = 0; i < k; ++i) {
        size_t c;
        cin >> c;
        ++a[c];
    }

    unordered_map<size_t, int64_t> sums;
    vector<int64_t> res(m + 1);
    res[0] = 1;

    for (size_t i = 1; i <= m; ++i) {
        for (auto & [c, n] : a) {
            if (c > i) {
                break;
            }
            size_t d = i - c;
            if (sums.find(d) == sums.end()) {
                for (size_t j = 0; j <= d; ++j) {
                    sums[d] += res[j] % MOD * res[d - j] % MOD;
                    sums[d] %= MOD;
                }
            }
            res[i] += n * sums[d] % MOD;
            res[i] %= MOD;
        }
        cout << res[i] << ' ';
    }

    return 0;
}

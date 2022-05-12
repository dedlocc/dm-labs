#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

using Array = std::array<uint64_t, 7>;

char next()
{
    char c;
    cin >> c;
    return c;
}

template <class T>
T binom(T n, T k)
{
    if (n < k) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k == 1 || k == n - 1) {
        return n;
    }
    return binom(n - 1, k - 1) * n / k;
}

template <class T>
T binomCached(T n, T k)
{
    static auto hash = [](pair<T, T> const & p) {
        return (p.first * 211) ^ p.second;
    };
    static unordered_map<pair<T, T>, T, decltype(hash)> cache(10, hash);
    if (auto it = cache.find({n, k}); it != cache.end()) {
        return it->second;
    }
    return cache[{n, k}] = binom(n, k);
}

Array parse()
{
    switch (next()) {
        case 'B':
            return {0, 1, 0, 0, 0, 0, 0};
        case 'L': {
            next(); // '('
            Array arg = parse();
            next(); // ')'

            Array res {};
            res[0] = 1;

            for (size_t i = 1; i < res.size(); ++i) {
                for (size_t j = 1; j <= i; ++j) {
                    res[i] += arg[j] * res[i - j];
                }
            }

            return res;
        }
        case 'S': {
            next(); // '('
            Array arg = parse();
            next(); // ')'

            std::array<Array, 7> dp {};
            std::fill(dp[0].begin(), dp[0].end(), 1);

            for (size_t i = 1; i < dp.size(); ++i) {
                for (size_t j = 1; j < dp[i].size(); ++j) {
                    for (size_t k = 0; k <= i / j; ++k) {
                        dp[i][j] += binomCached(arg[j] + k - 1, k) * dp[i - j * k][j - 1];
                    }
                }
            }

            Array res {};
            for (size_t i = 0; i < res.size(); ++i) {
                res[i] = dp[i][i];
            }

            return res;
        }
        case 'P': {
            next(); // '('
            Array left = parse();
            next(); // ','
            Array right = parse();
            next(); // ')'

            Array res {};

            for (size_t i = 0; i < res.size(); ++i) {
                for (size_t j = 0; j <= i; ++j) {
                    res[i] += left[j] * right[i - j];
                }
            }

            return res;
        }
    }
}

int main()
{
    for (auto e: parse()) {
        cout << e << ' ';
    }

    return 0;
}

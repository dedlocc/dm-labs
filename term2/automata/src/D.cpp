#include <iostream>
#include <utility>
#include <vector>
#include <numeric>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "problem4"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);
    constexpr std::size_t MOD = 1e9 + 7;

    std::size_t n, m, k, l;
    std::cin >> n >> m >> k >> l;

    std::vector<std::size_t> terminal;
    terminal.reserve(k);

    for (std::size_t i = 0; i < k; ++i) {
        std::size_t t;
        std::cin >> t;
        terminal.push_back(t - 1);
    }

    std::vector<std::vector<std::size_t>> transitions(n);

    for (std::size_t i = 0; i < m; ++i) {
        std::size_t a, b;
        char c;
        std::cin >> a >> b >> c;
        transitions[a - 1].push_back(b - 1);
    }

    std::vector<std::size_t> dp(n);
    dp[0] = 1;

    for (std::size_t i = 0; i < l; ++i) {
        std::vector<std::size_t> ndp(n);

        for (std::size_t j = 0; j < n; ++j) {
            if (dp[j] != 0) {
                for (const auto to : transitions[j]) {
                    (ndp[to] += dp[j]) %= MOD;
                }
            }
        }

        dp = std::move(ndp);
    }

    std::cout << std::accumulate(
        terminal.begin(), terminal.end(),
        std::size_t(),
        [&dp](const std::size_t sum, const std::size_t i) { return (sum + dp[i]) % MOD; }
    );

    return 0;
}
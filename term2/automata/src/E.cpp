#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>
#include <functional>
#include <queue>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "problem5"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using State = std::unordered_set<std::size_t>;

namespace std
{
template<>
struct hash<State>
{
    std::size_t operator()(const State &s) const noexcept
    {
        return std::accumulate(s.begin(), s.end(), std::size_t(), std::bit_xor());
    }
};
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);
    constexpr std::size_t MOD = 1e9 + 7;

    std::size_t n, m, k, l;
    std::cin >> n >> m >> k >> l;

    std::unordered_set<std::size_t> terminal;

    for (std::size_t i = 0; i < k; ++i) {
        std::size_t t;
        std::cin >> t;
        terminal.insert(t - 1);
    }

    std::vector<std::unordered_map<char, std::unordered_set<std::size_t>>> transitions(n);
    std::unordered_set<char> chars;

    for (std::size_t i = 0; i < m; ++i) {
        std::size_t a, b;
        char c;
        std::cin >> a >> b >> c;
        transitions[a - 1][c].insert(b - 1);
        chars.insert(c);
    }

    // Thompson's algorithm

    std::unordered_map<State, std::size_t> states {{{0}, 0}};
    std::vector<std::unordered_map<char, std::size_t>> transitions2(1);
    std::queue<State> q;
    q.push({0});

    while (!q.empty()) {
        const auto cur = std::move(q.front());
        q.pop();

        for (const auto c : chars) {
            State state;
            for (const auto from : cur) {
                const auto &tr = transitions[from];
                if (const auto it = tr.find(c); it != tr.end()) {
                    state.insert(it->second.begin(), it->second.end());
                }
            }
            if (!state.empty()) {
                auto [it, inserted] = states.emplace(state, states.size());
                if (inserted) {
                    q.push(state);
                    transitions2.emplace_back();
                }
                transitions2[states[cur]][c] = it->second;
            }
        }
    }

    //

    n = states.size();
    std::vector<std::size_t> dp(n);
    dp[0] = 1;

    for (std::size_t i = 0; i < l; ++i) {
        std::vector<std::size_t> ndp(n);

        for (std::size_t j = 0; j < n; ++j) {
            if (dp[j] != 0) {
                for (const auto [c, to] : transitions2[j]) {
                    (ndp[to] += dp[j]) %= MOD;
                }
            }
        }

        dp = std::move(ndp);
    }

    std::size_t result = 0;

    for (const auto &[s, i] : states) {
        if (std::any_of(
            s.begin(), s.end(),
            [&terminal](const auto t) { return terminal.find(t) != terminal.end(); }
        )) {
            (result += dp[i]) %= MOD;
        }
    }

    std::cout << result;

    return 0;
}
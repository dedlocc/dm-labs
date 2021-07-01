#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nfc"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif


int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    constexpr std::size_t MOD = 1e9 + 7;

    std::size_t n;
    char s;
    std::cin >> n >> s;

    std::unordered_set<char> nonterminals {s};
    std::unordered_multimap<char, char> transitions1;
    std::unordered_map<char, std::vector<std::pair<char, char>>> transitions2;

    for (std::size_t i = 0; i < n; ++i) {
        char a;
        std::string bc;
        std::cin >> a >> bc >> bc;
        nonterminals.insert(a);
        if (bc.size() == 1) {
            transitions1.emplace(a, bc[0]);
        } else {
            transitions2[a].emplace_back(bc[0], bc[1]);
            nonterminals.insert(bc.begin(), bc.end());
        }
    }

    std::string w;
    std::cin >> w;

    std::unordered_map<char, std::vector<std::vector<uint64_t>>> d;

    for (const auto nt : nonterminals) {
        d.try_emplace(nt, w.size(), std::vector<std::uint64_t>(w.size()));
    }

    for (const auto [a, c] : transitions1) {
        for (std::size_t i = 0; i < w.size(); ++i) {
            if (w[i] == c) {
                d[a][i][i] = 1;
            }
        }
    }

    for (std::size_t diff = 1; diff < w.size(); ++diff) {
        for (std::size_t i = 0, j = diff; j < w.size(); ++i, ++j) {
            for (const auto &[a, tr] : transitions2) {
                for (const auto [b, c] : tr) {
                    for (std::size_t k = i; k < j; ++k) {
                        d[a][i][j] += d[b][i][k] * d[c][k + 1][j];
                        d[a][i][j] %= MOD;
                    }
                }
            }
        }
    }

    std::cout << d[s].front().back();

    return 0;
}
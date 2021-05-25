#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "isomorphism"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

struct DFA
{
    inline static std::unordered_set<char> chars;
    std::vector<std::unordered_map<char, std::size_t>> transitions;
    std::unordered_set<std::size_t> terminal;

    std::size_t size() const
    {
        return transitions.size();
    }

    bool isTerminal(const std::size_t s) const
    {
        return terminal.find(s) == terminal.end();
    }

    friend std::istream &operator>>(std::istream &in, DFA &dfa)
    {
        std::size_t n, m, k;
        in >> n >> m >> k;

        dfa.terminal.reserve(k);

        for (std::size_t i = 0; i < k; ++i) {
            std::size_t t;
            in >> t;
            dfa.terminal.insert(t);
        }

        dfa.transitions.resize(n + 1);

        for (std::size_t i = 0; i < m; ++i) {
            std::size_t a, b;
            char c;
            in >> a >> b >> c;
            dfa.transitions[a][c] = b;
            chars.insert(c);
        }

        return in;
    }

    bool static equal(
        const DFA &a, const DFA &b,
        std::vector<std::size_t> &map,
        const std::size_t fromA = 1, const std::size_t fromB = 1
    ) {
        if (a.isTerminal(fromA) != b.isTerminal(fromB)) {
            return false;
        }

        map[fromA] = fromB;

        const auto &trA = a.transitions[fromA], &trB = b.transitions[fromB];

        for (const auto c : chars) {
            const auto itA = trA.find(c), itB = trB.find(c);
            const auto zeroA = itA == trA.end(), zeroB = itB == trB.end();

            if (zeroA != zeroB) {
                return false;
            }

            if (zeroA) {
                continue;
            }

            const auto toA = itA->second, toB = itB->second;

            if (!(map[toA] == 0 ? equal(a, b, map, toA, toB) : map[toA] == toB)) {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    DFA a, b;
    std::cin >> a >> b;

    std::vector<std::size_t> map(a.size());
    std::cout << (DFA::equal(a, b, map) ? "YES" : "NO");

    return 0;
}
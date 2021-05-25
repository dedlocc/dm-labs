#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "equivalence"
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

    friend bool operator==(const DFA &a, const DFA &b)
    {
        std::vector<std::vector<bool>> done(a.size(), std::vector<bool>(b.size()));
        std::queue<std::pair<std::size_t, std::size_t>> q;
        q.emplace(1, 1);

        while (!q.empty()) {
            const auto[fromA, fromB] = q.front();
            q.pop();

            if (a.isTerminal(fromA) != b.isTerminal(fromB)) {
                return false;
            }

            done[fromA][fromB] = true;

            const auto &trA = a.transitions[fromA], &trB = b.transitions[fromB];

            for (const auto c : chars) {
                const auto itA = trA.find(c), itB = trB.find(c);
                const auto toA = itA == trA.end() ? 0 : itA->second;
                const auto toB = itB == trB.end() ? 0 : itB->second;
                if (!done[toA][toB]) {
                    q.emplace(toA, toB);
                }
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

    std::cout << (a == b ? "YES" : "NO");

    return 0;
}
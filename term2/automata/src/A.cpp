#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "problem1"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

class DFA
{
public:
    using State = std::size_t;
    using Word = std::string;
    using Char = Word::value_type;
    using States = std::unordered_set<State>;
    using TransitionMatrix = std::unordered_map<State, std::unordered_map<Char, State>>;

    DFA(const State start, States terminal, TransitionMatrix transitions) :
        start(start),
        terminal(std::move(terminal)),
        transitions(std::move(transitions))
    {}

    bool accept(const Word &word) const
    {
        auto state = start;
        for (const auto c : word) {
            if (const auto &tr1 = transitions.find(state); transitions.end() != tr1) {
                if (const auto &tr2 = tr1->second.find(c); tr1->second.end() != tr2) {
                    state = tr2->second;
                    continue;
                }
            }
            return false;
        }

        return terminal.end() != terminal.find(state);
    }

private:
    const State start;
    const States terminal;
    const TransitionMatrix transitions;
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::string word;
    std::size_t n, m, k;
    std::cin >> word >> n >> m >> k;

    DFA::States terminal;
    terminal.reserve(k);

    for (std::size_t i = 0; i < k; ++i) {
        DFA::State t;
        std::cin >> t;
        terminal.insert(t);
    }

    DFA::TransitionMatrix transitions;

    for (std::size_t i = 0; i < m; ++i) {
        DFA::State a, b;
        DFA::Char c;
        std::cin >> a >> b >> c;
        transitions[a][c] = b;
    }

    DFA dfa(1, terminal, transitions);

    std::cout << (dfa.accept(word) ? "Accepts" : "Rejects");

    return 0;
}
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "problem2"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

class NFA
{
public:
    using State = std::size_t;
    using Word = std::string;
    using Char = Word::value_type;
    using States = std::unordered_set<State>;
    using TransitionMatrix = std::unordered_map<Char, std::unordered_map<State, States>>;

    NFA(States start, States terminal, TransitionMatrix transitions) :
        start(std::move(start)),
        terminal(std::move(terminal)),
        transitions(std::move(transitions))
    {}

    bool accept(const Word &word) const
    {
        std::vector<States> matrix(word.size());
        matrix[0] = start;

        for (std::size_t i = 0; i < word.size(); ++i) {
            if (transitions.end() == transitions.find(word[i])) {
                return false;
            }
            const auto &tr1 = transitions.at(word[i]);
            for (const auto &[state, tr2] : tr1) {
                if (matrix[i].find(state) != matrix[i].end()) {
                    for (const auto &r : tr2) {
                        if (i + 1 < word.size()) {
                            matrix[i + 1].insert(r);
                        } else if (terminal.end() != terminal.find(r)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

private:
    const States start;
    const States terminal;
    const TransitionMatrix transitions;
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::string word;
    std::size_t n, m, k;
    std::cin >> word >> n >> m >> k;

    NFA::States terminal;
    terminal.reserve(k);

    for (std::size_t i = 0; i < k; ++i) {
        NFA::State t;
        std::cin >> t;
        terminal.insert(t);
    }

    NFA::TransitionMatrix transitions;

    for (std::size_t i = 0; i < m; ++i) {
        NFA::State a, b;
        NFA::Char c;
        std::cin >> a >> b >> c;
        transitions[c][a].insert(b);
    }

    NFA nfa({1}, terminal, transitions);

    std::cout << (nfa.accept(word) ? "Accepts" : "Rejects");

    return 0;
}
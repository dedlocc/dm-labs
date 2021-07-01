#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "automaton"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

class NFA
{
public:
    using State = char;
    using Word = std::string;
    using Char = Word::value_type;
    using States = std::unordered_set<State>;
    using TransitionMatrix = std::unordered_map<Char, std::unordered_map<State, States>>;

    NFA(State start, State terminal, TransitionMatrix transitions) :
        start(start),
        terminal(terminal),
        transitions(std::move(transitions)) {}

    bool accept(const Word &word) const
    {
        std::vector<States> matrix(word.size());
        matrix[0].insert(start);

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
                        } else if (r == terminal) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

private:
    const State start;
    const State terminal;
    const TransitionMatrix transitions;
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::size_t n;
    char s;
    std::cin >> n >> s;

    NFA::TransitionMatrix transitions;

    for (std::size_t i = 0; i < n; ++i) {
        char a;
        std::string bc;
        std::cin >> a >> bc >> bc;
        transitions[bc[0]][a].insert(bc.size() == 1 ? '$' : bc[1]);
    }

    NFA nfa(s, '$', transitions);

    std::size_t m;
    std::cin >> m;

    for (std::size_t i = 0; i < m; ++i) {
        std::string w;
        std::cin >> w;
        std::cout << (nfa.accept(w) ? "yes" : "no") << '\n';
    }

    return 0;
}
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "problem3"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

class WordCounter
{
public:
    using State = std::size_t;
    using States = std::unordered_set<State>;
    using TransitionMatrix = std::unordered_map<State, std::vector<State>>;

    WordCounter(const States &terminal, TransitionMatrix &&transitions, TransitionMatrix &&rTransitions) :
        transitions(std::move(transitions)),
        rTransitions(std::move(rTransitions))
    {
        for (const auto state : terminal) {
            markUseful(state);
            states.at(state).n = 1;
        }
    }

    std::size_t count(const State from)
    {
        auto it = states.find(from);

        if (it == states.end()) {
            return 0;
        }

        auto &info = it->second;

        switch (info.status) {
            case Info::NEW: {
                const auto &trs = transitions.find(from);
                if (transitions.end() != trs) {
                    info.status = Info::VISITING;
                    for (const auto to : trs->second) {
                        info.n += count(to);
                        info.n %= MOD;
                    }
                }
                info.status = Info::DONE;
                return info.n;
            }
            case Info::VISITING:
                throw LoopFound();
            case Info::DONE:
                return info.n;
        }
    }

    struct LoopFound : std::runtime_error
    {
        LoopFound() : std::runtime_error("") {}
    };

private:
    static constexpr std::size_t MOD = 1e9 + 7;

    const TransitionMatrix transitions;
    const TransitionMatrix rTransitions;

    struct Info
    {
        enum
        {
            NEW,
            VISITING,
            DONE,
        } status = NEW;

        std::size_t n = 0;
    };

    std::unordered_map<State, Info> states;

    void markUseful(const State &to)
    {
        if (states.end() == states.find(to)) {
            states.try_emplace(to);
            const auto &trs = rTransitions.find(to);
            if (transitions.end() != trs) {
                for (const auto from : trs->second) {
                    markUseful(from);
                }
            }
        }
    }
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::size_t n, m, k;
    std::cin >> n >> m >> k;

    WordCounter::States terminal;
    terminal.reserve(k);

    for (std::size_t i = 0; i < k; ++i) {
        WordCounter::State t;
        std::cin >> t;
        terminal.insert(t);
    }

    WordCounter::TransitionMatrix transitions;
    WordCounter::TransitionMatrix reverseTransitions;

    for (std::size_t i = 0; i < m; ++i) {
        WordCounter::State a, b;
        char c;
        std::cin >> a >> b >> c;
        transitions[a].push_back(b);
        reverseTransitions[b].push_back(a);
    }

    WordCounter wc(terminal, std::move(transitions), std::move(reverseTransitions));

    try {
        std::cout << wc.count(1);
    } catch (WordCounter::LoopFound &) {
        std::cout << -1;
    }

    return 0;
}
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "minimization"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

template<class T>
bool contains(const std::unordered_set<T> &set, const T &key)
{
    return set.find(key) != set.end();
}

struct Transition
{
    std::size_t from, to;
    char ch;

    bool operator==(const Transition &other) const
    {
        return from == other.from && to == other.to && ch == other.ch;
    }

    friend std::ostream &operator<<(std::ostream &out, const Transition &tr)
    {
        return out << tr.from + 1 << ' ' << tr.to + 1 << ' ' << tr.ch;
    }

    struct Hash
    {
        std::size_t operator()(const Transition &tr) const noexcept
        {
            return tr.from ^ (tr.from + 1) ^ tr.ch;
        }
    };
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::size_t n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::size_t> terminal;
    std::queue<std::size_t> rq;

    for (std::size_t i = 0; i < k; ++i) {
        std::size_t t;
        std::cin >> t;
        terminal.push_back(t - 1);
        rq.push(t - 1);
    }

    std::unordered_set<char> chars;
    std::vector<std::unordered_map<char, std::size_t>> transitions(n);
    std::vector<std::unordered_map<char, std::vector<std::size_t>>> rTransitions(n);

    for (std::size_t i = 0; i < m; ++i) {
        std::size_t a, b;
        char c;
        std::cin >> a >> b >> c;
        transitions[a - 1][c] = b - 1;
        rTransitions[b - 1][c].push_back(a - 1);
        chars.insert(c);
    }

    std::unordered_set<std::size_t> reachableFromTerminal(n);

    while (!rq.empty()) {
        const auto to = rq.front();
        rq.pop();
        if (reachableFromTerminal.insert(to).second) {
            for (const auto &tr : rTransitions[to]) {
                for (const auto from : tr.second) {
                    rq.push(from);
                }
            }
        }
    }

    std::unordered_set<std::size_t> useful(n);
    rq.push(0);

    while (!rq.empty()) {
        const auto from = rq.front();
        rq.pop();
        if (contains(reachableFromTerminal, from) && useful.insert(from).second) {
            for (const auto &[c, to] : transitions[from]) {
                rq.push(to);
            }
        }
    }

    if (useful.empty()) {
        std::cout << "1 0 0\n";
        return 0;
    }

    std::vector<std::size_t> colors(n, 1);
    std::vector<std::unordered_set<std::size_t>> classes;
    classes.emplace_back().reserve(k);
    std::vector<bool> terminalMin {true};

    for (const auto t : terminal) {
        if (contains(useful, t)) {
            colors[t] = 0;
            classes.front().insert(t);
        }
    }

    if (useful.size() > classes.front().size()) {
        classes.emplace_back().reserve(useful.size() - classes.front().size());
        terminalMin.emplace_back();
        for (const auto i : useful) {
            if (colors[i] == 1) {
                classes.back().insert(i);
            }
        }
    }

    std::queue<std::pair<std::size_t, char>> queue;

    for (const auto c : chars) {
        for (std::size_t i = 0; i < classes.size(); ++i) {
            queue.emplace(i, c);
        }
    }

    while (!queue.empty()) {
        const auto [cl, ch] = queue.front();
        queue.pop();

        std::unordered_map<std::size_t, std::unordered_set<std::size_t>> current;

        for (const auto i : classes[cl]) {
            if (const auto tr = rTransitions[i].find(ch); tr != rTransitions[i].end()) {
                for (const auto j : tr->second) {
                    if (contains(useful, j)) {
                        current[colors[j]].insert(j);
                    }
                }
            }
        }

        for (const auto &[i, v] : current) {
            if (v.size() == classes[i].size()) {
                continue;
            }

            for (const auto j : v) {
                classes[i].erase(j);
            }

            classes.emplace_back(v.begin(), v.end());
            terminalMin.push_back(terminalMin[i]);

            if (v.size() > classes[i].size()) {
                std::swap(classes.back(), classes[i]);
            }

            const auto s = classes.size() - 1;

            for (const auto j : classes.back()) {
                colors[j] = s;
            }

            for (const auto c : chars) {
                queue.emplace(s, c);
            }
        }
    }

    if (colors[0] != 0) {
        const auto j = colors[0];
        std::swap(classes[0], classes[j]);
        std::swap(terminalMin[0], terminalMin[j]);
        for (const auto i : classes[0]) {
            colors[i] = 0;
        }
        for (const auto i : classes[j]) {
            colors[i] = j;
        }
    }

    std::unordered_set<Transition, Transition::Hash> minTransitions;

    for (const auto i : useful) {
        for (const auto &[c, tr] : rTransitions[i]) {
            for (const auto j : tr) {
                if (contains(useful, j)) {
                    minTransitions.insert({colors[j], colors[i], c});
                }
            }
        }
    }

    std::cout << classes.size() << ' '
              << minTransitions.size() << ' '
              << std::count(terminalMin.begin(), terminalMin.end(), true) << '\n';

    for (std::size_t i = 0; i < classes.size(); ++i) {
        if (terminalMin[i]) {
            std::cout << i + 1 << ' ';
        }
    }

    for (const auto &tr : minTransitions) {
        std::cout << '\n' << tr;
    }

    return 0;
}
#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "epsilon"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::size_t n;
    char s;
    std::cin >> n >> s;

    std::set<char> answer;
    std::unordered_multimap<char, std::set<char>> transitions;

    for (std::size_t i = 0; i < n; ++i) {
        char a;
        std::string bc;
        std::cin >> a >> bc;
        std::getline(std::cin, bc);
        std::stringstream ss(bc);
        bc.clear();
        ss >> bc;
        if (bc.empty()) {
            answer.insert(a);
        } else if (std::all_of(bc.begin(), bc.end(), isupper)) {
            transitions.emplace(a, std::set<char> {bc.begin(), bc.end()});
        }
    }

    bool modified;

    do {
        modified = false;
        for (const auto &[nt, s] : transitions) {
            if (std::includes(answer.begin(), answer.end(), s.begin(), s.end()) && answer.insert(nt).second) {
                modified = true;
            }
        }
    } while (modified);

    std::copy(answer.begin(), answer.end(), std::ostream_iterator<char>(std::cout, " "));

    return 0;
}
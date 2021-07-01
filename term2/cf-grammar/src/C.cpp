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
#define FILE "useless"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    std::size_t n;
    char s;
    std::cin >> n >> s;

    std::set<char> all {s}, gen, rch {s};
    std::unordered_multimap<char, std::set<char>> transitions;

    for (std::size_t i = 0; i < n; ++i) {
        char a;
        std::string bc;
        std::cin >> a >> bc;
        std::getline(std::cin, bc);
        std::stringstream ss(bc);
        bc.clear();
        ss >> bc;
        all.insert(a);
        if (std::all_of(bc.begin(), bc.end(), islower)) {
            gen.insert(a);
        } else {
            auto &set = transitions.emplace(a, std::set<char> {})->second;
            for (const auto c : bc) {
                if (isupper(c)) {
                    set.insert(c);
                    all.insert(c);
                }
            }
        }
    }

    bool modified;

    do {
        modified = false;
        for (const auto &[nt, s] : transitions) {
            if (std::includes(gen.begin(), gen.end(), s.begin(), s.end()) && gen.insert(nt).second) {
                modified = true;
            }
        }
    } while (modified);

    if (gen.find(s) == gen.end()) {
        std::copy(all.begin(), all.end(), std::ostream_iterator<char>(std::cout, " "));
        return 0;
    }

    do {
        modified = false;
        for (const auto &[nt, set] : transitions) {
            if (rch.find(nt) != rch.end() && std::includes(gen.begin(), gen.end(), set.begin(), set.end())) {
                const auto prevSize = rch.size();
                rch.insert(set.begin(), set.end());
                if (prevSize != rch.size()) {
                    modified = true;
                }
            }
        }
    } while (modified);

    std::set_difference(all.begin(), all.end(), rch.begin(), rch.end(), std::ostream_iterator<char>(std::cout, " "));

    return 0;
}
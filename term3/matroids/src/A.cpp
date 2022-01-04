#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "schedule"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

struct Task
{
    size_t d;
    uint64_t w;

    Task(size_t d, uint64_t w) : d(d), w(w)
    {}
};

bool operator<(Task const &l, Task const &r)
{
    return l.w > r.w || l.w == r.w && l.d < r.d;
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<Task> tasks;
    set<size_t> schedule;

    for (size_t i = 1; i <= n; ++i) {
        size_t d;
        uint64_t w;
        cin >> d >> w;
        tasks.emplace_back(d, w);
        schedule.insert(i);
    }

    sort(tasks.begin(), tasks.end());

    uint64_t penalty = 0;

    for (auto [d, w] : tasks) {
        auto it = schedule.upper_bound(d);
        if (it == schedule.begin()) {
            it = schedule.end();
            penalty += w;
        }
        schedule.erase(--it);
    }

    cout << penalty;

    return 0;
}
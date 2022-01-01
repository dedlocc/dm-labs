#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> code(n - 2);
    vector<size_t> deg(n, 1);

    for (auto &p : code) {
        cin >> p;
        ++deg[--p];
    }

    code.push_back(n - 1);

    priority_queue<size_t, vector<size_t>, greater<>> q;
    for (size_t i = 0; i < n; ++i) {
        if (deg[i] == 1) {
            q.push(i);
        }
    }

    for (const auto v : code) {
        const size_t u = q.top();
        q.pop();
        cout << u + 1 << ' ' << v + 1 << '\n';
        if (--deg[v] == 1) {
            q.push(v);
        }
    }

    return 0;
}
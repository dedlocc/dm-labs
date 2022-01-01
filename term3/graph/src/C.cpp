#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<size_t> v(n);
    iota(v.begin(), v.end(), 1);

    stable_sort(v.begin(), v.end(), [](size_t x, size_t y) {
        cout << "1 " << x << ' ' << y << endl;
        string r;
        cin >> r;
        return r == "YES";
    });

    cout << 0;
    for (size_t e : v) {
        cout << ' ' << e;
    }
    cout << endl;

    return 0;
}
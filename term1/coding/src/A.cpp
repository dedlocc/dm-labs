#include <bits/stdc++.h>

using namespace std;

struct Node
{
    const uint64_t p;
    const Node *left, *right;

    explicit Node(const uint32_t &p) : p(p), left(nullptr), right(nullptr)
    {
    }

    Node(Node *left, Node *right) : p(left->p + right->p), left(left), right(right)
    {
    }

    [[nodiscard]] uint64_t sum(const size_t len = 0) const
    {
        const auto s = nullptr == left ? len * p : left->sum(1 + len) + right->sum(1 + len);
        delete this;
        return s;
    }
};

template<typename T, typename U, typename V>
T pop(priority_queue<T, U, V> &pq)
{
    const auto e = pq.top();
    pq.pop();
    return e;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    typedef Node *ptr;
    const auto comp = [](const ptr &a, const ptr &b) { return a->p > b->p; };
    priority_queue<ptr, vector<ptr>, decltype(comp)> p(comp);

    for (size_t i = 0; i < n; ++i) {
        uint32_t e;
        cin >> e;
        p.emplace(new Node(e));
    }

    for (size_t i = 1; i < n; ++i) {
        p.emplace(new Node(pop(p), pop(p)));
    }

    cout << pop(p)->sum();

    return 0;
}
